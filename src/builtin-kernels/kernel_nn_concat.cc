#include "kernel_nn_concat.hpp"
#include "log.h"

#include <iomanip>

namespace NNFramework {

#define CPU_THREAD_NUM 1

Kernel_nn_concat kernel_nn_concat;

Kernel_nn_concat::Kernel_nn_concat(void) : Kernel() {
    REGISTER_KERNEL();
}

Kernel_nn_concat::~Kernel_nn_concat(void) {
}

int Kernel_nn_concat::GetOpCode(void) {
    return OpCode_Concat;
}

int Kernel_nn_concat::preProc( const Instruction *inst ) {
    auto concatinfo = inst->operand_as_Concat();

    decode_fb_data( concatinfo );

    return 0;
}

int Kernel_nn_concat::postProc(void) {
    logfs << "\n";

    return 0;
}

int Kernel_nn_concat::Run( RunContext &rcontext ) {
    for(auto itinfo : _itinfo)
        _input_cc.push_back( rcontext.main_buffer + itinfo.mem_addr);
    _output = (rcontext.main_buffer + _otinfo[0].mem_addr);

    // DEBUG
    for(unsigned int i = 0; i < _input_cc.size(); i++) {
        tileinfo_t t;
        int input_size = t.total_size( _itinfo[i].dim );
        dump_data( _kernel_name+"_i"+std::to_string(i)+".dat", _input_cc[i], input_size, sizeof(float));
    }

    /* Generates kernel threads 
     */
#if 0   // multi-thread mode (CPU-only)
    create_kernel_args_list();
    create_threads();
#else   // singletone mode
    create_kernel_args_list();
    run_kernel();
#endif
    wait_threads();

    // DEBUG
    dump_data( _kernel_name+"_o.dat", (char*)_output, _output_size, sizeof(float));

    return 0;
}

int Kernel_nn_concat::decode_fb_data(const Concat *opinfo) {
    /* Decoder flatbuffer contents
     */
    _kernel_name = opinfo->kernel_name()->c_str();

    get_itile_info( opinfo->itile() );
    get_otile_info( opinfo->otile() );


    /* Print decoded content on log file
     */
    logfs << "-------- Kernel_opinfo fb data decode result --------\n";
    logfs << "name           = " << _kernel_name << "\n";
    display_tile_info( logfs );
   
    return 0;
}

void Kernel_nn_concat::wait_threads(void)
{
    for(auto& thread : thread_list)
        thread.join();

    kernel_args_list.clear();
    thread_list.clear();
    cpu_thread_arg_index.clear();
    gpu_thread_arg_index.clear();
    _input_cc.clear();
}

void Kernel_nn_concat::create_kernel_args_list(void)
{
    assert( _otinfo.size() == 1 );
    assert( _itinfo[0].dim.size() == 4 );
    assert( _otinfo[0].dim.size() == 4 );
    assert( _itinfo[0].dim[0] == 1 );
    assert( _otinfo[0].dim[0] == 1 );

    /* Check tile sizes
     */
    int oC = _otinfo[0].dim[1]; // OFM ch size

    logfs << "kernel_nn_concat::create_kernel_args_list() debug\n";
    logfs << "oC = " << oC << "\n";
    logfs << "iC = [ ";
    for(auto a : _itinfo) {
        logfs << a.dim[1] << " ";
    }   logfs << "]\n";
    
    /* Creates kernel argument list for CPU
     */
    vector<int> thr_out_addr_offset;
    thr_out_addr_offset.push_back( 0 );
    for(unsigned int i = 0; i < _itinfo.size()-1; i++) {
        tileinfo_t t;
        thr_out_addr_offset.push_back( t.total_size( _itinfo[i].dim ) * sizeof(float) );
    }

    for(unsigned int i = 0; i < _itinfo.size(); i++) {
        KernelArgs_t arg;
        tileinfo_t iti, oti;

        iti = _itinfo[i];
        oti = _otinfo[0];
        oti.mem_addr = oti.mem_addr + thr_out_addr_offset[i];
        oti.dim[1] = iti.dim[1];
        arg.iti = iti;
        arg.oti = oti;

        arg.output = (float*) (_output + thr_out_addr_offset[i]);
        arg.input  = (float*) _input_cc[i];

        kernel_args_list.push_back( arg );
        cpu_thread_arg_index.push_back( i );
    }


#if 1
    logfs << "---------------- Kernel_args list ---------------------\n";
    for(unsigned int j = 0; j < kernel_args_list.size(); j++) {
        auto a = kernel_args_list[ j ];
        logfs << "+++++ CPU thread info [" << j << "] +++++\n";
        logfs << "output = 0x" << std::setw(8) << std::setfill('0') << std::hex \
              << a.output << std::setfill(' ') << std::dec << "\n";
        logfs << "input  = 0x" << std::setw(8) << std::setfill('0') << std::hex \
              << a.input  << std::setfill(' ') << std::dec << "\n";
        logfs << "it.addr= 0x" << std::setw(8) << std::setfill('0') << std::hex \
              << a.iti.mem_addr << std::setfill(' ') << std::dec << "\n";
        logfs << "it.dim = [";
        for(unsigned int k = 0; k < a.iti.dim.size()-1; k++)
            logfs << a.iti.dim[k] << ",";
        logfs << a.iti.dim.back() << "]\n";
        logfs << "ot.addr= 0x" << std::setw(8) << std::setfill('0') << std::hex \
              << a.oti.mem_addr << std::setfill(' ') << std::dec << "\n";
        logfs << "ot.dim = [";
        for(unsigned int k = 0; k < a.oti.dim.size()-1; k++)
            logfs << a.oti.dim[k] << ",";
        logfs << a.oti.dim.back() << "]\n";
    }
#endif

    return;
}

void Kernel_nn_concat::create_threads(void)
{
    /* Creates CPU kernel threads
     */
    for(auto index : cpu_thread_arg_index)
        thread_list.push_back( thread(cpu_kernel_thread_wrapper, this, index) );

    /* Creates GPU kernel threads
     */
    for(auto index : gpu_thread_arg_index)
        thread_list.push_back( thread(gpu_kernel_thread_wrapper, this, index) );

    return;
}

void Kernel_nn_concat::run_kernel(void) 
{
    for(unsigned int i = 0; i < cpu_thread_arg_index.size(); i++)
        cpu_kernel_concat( i );
}

void Kernel_nn_concat::gpu_kernel_concat(
    int args_list_index
)
{
}

void Kernel_nn_concat::cpu_kernel_concat(
    int args_list_index
) {

    auto& args = kernel_args_list[ args_list_index ];
    int N = args.iti.dim[0];
    int C = args.iti.dim[1];
    int H = args.iti.dim[2];
    int W = args.iti.dim[3];

    float *output = args.output;
    float *input  = args.input;

    int size = N*C*H*W;

    for(int n = 0 ; n < size ; n++) {
        *output++ = *input++;
    }
}

}
