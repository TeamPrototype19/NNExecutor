#include "kernel_nn_scale.hpp"
#include "log.h"

#include <iomanip>

namespace NNFramework {

Kernel_nn_scale kernel_nn_scale;

Kernel_nn_scale::Kernel_nn_scale(void) : Kernel() {
    REGISTER_KERNEL();
}

Kernel_nn_scale::~Kernel_nn_scale(void) {
}

int Kernel_nn_scale::GetOpCode(void) {
    return OpCode_Scale;
}

int Kernel_nn_scale::preProc( const Instruction *inst ) {
    auto scaleinfo = inst->operand_as_Scale();

    decode_fb_data( scaleinfo );

    return 0;
}

int Kernel_nn_scale::postProc(void) {
#if LOG_LEVEL > 1
    logfs << "\n";
#endif

    return 0;
}

int Kernel_nn_scale::Run( RunContext &rcontext ) {
    _input  = (rcontext.main_buffer + _itinfo[0].mem_addr);
    _output = (rcontext.main_buffer + _otinfo[0].mem_addr);

#if defined(DUMP_LEVEL) && DUMP_LEVEL > 0
    dump_data( _kernel_name+"_i.dat", _input, _input_size, sizeof(float));
    dump_data( _kernel_name+"_w.dat", (char*)_weight, _weight_size, sizeof(float));
    dump_data( _kernel_name+"_b.dat", (char*)_bias, _bias_size, sizeof(float));
#endif

    /* Generates kernel threads 
     */
#if 1   // multi-thread mode (CPU-only)
    create_kernel_args_list( 4, 0, 1, 0 );
    create_threads();
#else   // singletone mode
    create_kernel_args_list( 1, 0, 1, 0 );
    run_kernel();
#endif
    wait_threads();

#if defined(DUMP_LEVEL) && DUMP_LEVEL > 0
    dump_data( _kernel_name+"_o.dat", (char*)_output, _output_size, sizeof(float));
#endif

    return 0;
}

int Kernel_nn_scale::decode_fb_data(const Scale *opinfo) {
    /* Decoder flatbuffer contents
     */
    _kernel_name = opinfo->kernel_name()->c_str();
    _weight = (float*)opinfo->weight()->data();
    _bias = (float*)opinfo->bias()->data();
    _weight_size = opinfo->weight()->size();
    _bias_size = opinfo->bias()->size();

    if( _weight_size == 0 ) _weight = nullptr;
    if( _bias_size   == 0 ) _bias = nullptr;

    get_itile_info( opinfo->itile() );
    get_otile_info( opinfo->otile() );


#if LOG_LEVEL > 1
    /* Print decoded content on log file
     */
    logfs << "-------- Kernel_opinfo fb data decode result --------\n";
    logfs << "name           = " << _kernel_name << "\n";
    logfs << "weight_size    = " << _weight_size << "\n";
    logfs << "bias_size      = " << _bias_size << "\n";
    display_tile_info( logfs );
#endif
   
    return 0;
}

void Kernel_nn_scale::wait_threads(void)
{
    for(auto& thread : thread_list)
        thread.join();

    kernel_args_list.clear();
    thread_list.clear();
    cpu_thread_arg_index.clear();
    gpu_thread_arg_index.clear();
}

void Kernel_nn_scale::create_kernel_args_list(
    int thread_num_cpu,     // total number of cpu thread
    int thread_num_gpu,
    int thread_ratio_cpu,   // processing ratio by cpu thread
    int thread_ratio_gpu
)
{
    assert( _itinfo.size() == 1 );
    assert( _otinfo.size() == 1 );
    assert( _itinfo[0].dim.size() == 4 );
    assert( _otinfo[0].dim.size() == 4 );
    assert( _itinfo[0].dim[0] == 1 );
    assert( _otinfo[0].dim[0] == 1 );

    /* Check tile sizes
     */
    int oN = _otinfo[0].dim[0]; // OFM num size
    int oC = _otinfo[0].dim[1]; // OFM ch size
    int oH = _otinfo[0].dim[2]; // OFM height size
    int oW = _otinfo[0].dim[3]; // OFM width size

    /* Calculates each processing ratio of cpu/gpu
     */
    int total_ratio = thread_ratio_cpu + thread_ratio_gpu;
    int och_by_cpu = (oC * thread_ratio_cpu) / total_ratio;
    int och_by_gpu = oC - och_by_cpu;

#if LOG_LEVEL > 1
    logfs << "kernel_nn_scale::create_kernel_args_list() debug\n";
    logfs << "oC = " << oC << "\toch_by_cpu = " << och_by_cpu\
          << "\toch_by_gpu = " << och_by_gpu << "\n";
#endif

    int och_base_addr_cpu = 0;
    int och_base_addr_gpu = (oW * oH) * och_by_cpu * sizeof(float);
    int wgt_base_addr_cpu = 0;
    int wgt_base_addr_gpu = och_by_cpu;
    int bias_base_addr_cpu = 0;
    int bias_base_addr_gpu = och_by_cpu;

    /* Creates kernel argument list for CPU
     */
    int och_per_Cthread = (och_by_cpu + (thread_num_cpu-1)) / thread_num_cpu;
    int och_offset_per_Cthread = oN * (oH * oW) * och_per_Cthread * sizeof(float);
    int wgt_offset_per_Cthread = och_per_Cthread;
    int bias_offset_per_Cthread = och_per_Cthread;

    int oC_org = och_by_cpu;
    int arg_idx = 0;
    for(int i = 0; arg_idx < thread_num_cpu; arg_idx++, i++) {
        KernelArgs_t arg;
        tileinfo_t iti, oti;

        iti = _itinfo[0];
        oti = _otinfo[0];
        // set output tile channel size
        oC_org -= och_per_Cthread;
        iti.dim[1] = (oC_org >= 0) ? och_per_Cthread : (och_per_Cthread + oC_org);
        oti.dim[1] = (oC_org >= 0) ? och_per_Cthread : (och_per_Cthread + oC_org);
        // set output tile memory address
        iti.mem_addr = iti.mem_addr + och_base_addr_cpu + (och_offset_per_Cthread * i);
        oti.mem_addr = oti.mem_addr + och_base_addr_cpu + (och_offset_per_Cthread * i);
        arg.iti    = iti;
        arg.oti    = oti;

        arg.output = (float*) (_output + och_base_addr_cpu + (och_offset_per_Cthread * i));
        arg.input  = (float*) (_input  + och_base_addr_cpu + (och_offset_per_Cthread * i));
        arg.weight = _weight + wgt_base_addr_cpu  + (wgt_offset_per_Cthread * i);
        arg.bias   = _bias   + bias_base_addr_cpu + (bias_offset_per_Cthread * i);

        kernel_args_list.push_back( arg );
        cpu_thread_arg_index.push_back( arg_idx );
    }


#if 0
#if LOG_LEVEL > 1
    logfs << "---------------- Kernel_args list ---------------------\n";
    logfs << "thread_num_cpu   = " << thread_num_cpu << "\n";
    logfs << "thread_num_gpu   = " << thread_num_gpu << "\n";
    logfs << "thread_ratio_cpu = " << thread_ratio_cpu << "\n";
    logfs << "thread_ratio_gpu = " << thread_ratio_gpu << "\n";
    int j = 0;
    for(j = 0; j < thread_num_cpu ; j++) {
        auto a = kernel_args_list[ j ];
        logfs << "+++++ CPU thread info [" << j << "] +++++\n";
        logfs << "output = 0x" << std::setw(8) << std::setfill('0') << std::hex \
              << a.output << std::setfill(' ') << std::dec << "\n";
        logfs << "input  = 0x" << std::setw(8) << std::setfill('0') << std::hex \
              << a.input  << std::setfill(' ') << std::dec << "\n";
        logfs << "weight = 0x" << std::setw(8) << std::setfill('0') << std::hex \
              << a.weight << std::setfill(' ') << std::dec << "\n";
        logfs << "bias   = 0x" << std::setw(8) << std::setfill('0') << std::hex \
              << a.bias   << std::setfill(' ') << std::dec << "\n";
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
#endif


    /* Creates kernel argument list for GPU
     */
    if( thread_ratio_gpu == 0 )
        return;
    int och_per_Gthread = (och_by_gpu + (thread_num_gpu-1)) / thread_num_gpu;
    int och_offset_per_Gthread = oN * (oH * oW) * och_per_Gthread * sizeof(float);
    int wgt_offset_per_Gthread = och_per_Gthread;
    int bias_offset_per_Gthread = och_per_Gthread;

    oC_org = och_by_gpu;
    int thread_num_total = thread_num_cpu + thread_num_gpu;
    for(int i = 0; arg_idx < thread_num_total; arg_idx++, i++) {
        KernelArgs_t arg;
        tileinfo_t iti, oti;

        iti = _itinfo[0];
        oti = _otinfo[0];
        // set output tile channel size
        oC_org -= och_per_Gthread;
        iti.dim[1] = (oC_org >= 0) ? och_per_Gthread : (och_per_Gthread + oC_org);
        oti.dim[1] = (oC_org >= 0) ? och_per_Gthread : (och_per_Gthread + oC_org);
        // set output tile memory address
        iti.mem_addr = iti.mem_addr + och_base_addr_gpu + (och_offset_per_Gthread * i);
        oti.mem_addr = oti.mem_addr + och_base_addr_gpu + (och_offset_per_Gthread * i);
        arg.iti    = iti;
        arg.oti    = oti;

        arg.output = (float*) (_output + oti.mem_addr);
        arg.input  = (float*) (_input  + iti.mem_addr);
        arg.weight = _weight + wgt_base_addr_gpu  + (wgt_offset_per_Gthread * i);
        arg.bias   = _bias   + bias_base_addr_gpu + (bias_offset_per_Gthread * i);

        kernel_args_list.push_back( arg );
        gpu_thread_arg_index.push_back( arg_idx );
    }

#if 0
    j = thread_num_cpu;
    for(j = 0; j < thread_num_total; j++) {
        auto a = kernel_args_list[ j ];
        logfs << "+++++ GPU thread info [" << j << "] +++++\n";
        logfs << "output = 0x" << std::setw(8) << std::setfill('0') << std::hex \
              << a.output << std::setfill(' ') << std::dec << "\n";
        logfs << "input  = 0x" << std::setw(8) << std::setfill('0') << std::hex \
              << a.input  << std::setfill(' ') << std::dec << "\n";
        logfs << "weight = 0x" << std::setw(8) << std::setfill('0') << std::hex \
              << a.weight << std::setfill(' ') << std::dec << "\n";
        logfs << "bias   = 0x" << std::setw(8) << std::setfill('0') << std::hex \
              << a.bias   << std::setfill(' ') << std::dec << "\n";
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

void Kernel_nn_scale::create_threads(void)
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

void Kernel_nn_scale::run_kernel(void) 
{
    cpu_kernel_scale( 0 );
}

void Kernel_nn_scale::gpu_kernel_scale(
    int args_list_index
)
{
}

void Kernel_nn_scale::cpu_kernel_scale(
    int args_list_index
) {

    auto& args = kernel_args_list[ args_list_index ];
    int N = args.iti.dim[0];
    int C = args.iti.dim[1];
    int H = args.iti.dim[2];
    int W = args.iti.dim[3];

    float *output = args.output;
    float *input  = args.input;
    float *weight = args.weight;
    float *bias   = args.bias;

    if( bias == nullptr ) {
        for(int n = 0 ; n < N ; n++) {
            for(int c = 0 ; c < C ; c++) {
                for(int i = 0 ; i < W*H ; i++) {
                    *output++ = (*input++ * *weight);
                }
                weight++;
            }
        }
    }
    else {
        for(int n = 0 ; n < N ; n++) {
            for(int c = 0 ; c < C ; c++) {
                for(int i = 0 ; i < W*H ; i++) {
                    *output++ = (*input++ * *weight) + *bias;
                }
                weight++;
                bias++;
            }
        }
    }
}

}
