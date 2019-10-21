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
    // DEBUG
    dump_data( _kernel_name+"_o.dat", (char*)_output, _output_size, sizeof(float));
    logfs << "\n";

    return 0;
}

int Kernel_nn_scale::Run( RunContext &rcontext ) {
    _input  = (rcontext.main_buffer + _itinfo[0].mem_addr);
    _output = (rcontext.main_buffer + _otinfo[0].mem_addr);

    // DEBUG
    dump_data( _kernel_name+"_i.dat", _input, _input_size, sizeof(float));
    dump_data( _kernel_name+"_w.dat", (char*)_weight, _weight_size, sizeof(float));
    dump_data( _kernel_name+"_b.dat", (char*)_bias, _bias_size, sizeof(float));

    /* Generates kernel threads 
     */
    creates_threads();
    wait_threads();

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

    get_itile_info( opinfo->itile() );
    get_otile_info( opinfo->otile() );


    /* Print decoded content on log file
     */
    logfs << "-------- Kernel_opinfo fb data decode result --------\n";
    logfs << "name           = " << _kernel_name << "\n";
    logfs << "weight_size    = " << _weight_size << "\n";
    logfs << "bias_size      = " << _bias_size << "\n";
    display_tile_info( logfs );
   
    return 0;
}

void Kernel_nn_scale::wait_threads(void)
{
    for(auto& thread : thread_list)
        thread.join();

    thread_args_list.clear();
    thread_list.clear();

}

void Kernel_nn_scale::creates_threads(void)
{

    assert( _itinfo.size() == 1 );
    assert( _otinfo.size() == 1 );
    assert( _itinfo[0].dim.size() == 4 );
    assert( _otinfo[0].dim.size() == 4 );
    assert( _itinfo[0].dim[0] == 1 );
    assert( _otinfo[0].dim[0] == 1 );

    /* Check tile sizes
     */
    int oN = _otinfo[0].dim[0];
    int oC = _otinfo[0].dim[1];
    int oH = _otinfo[0].dim[2];
    int oW = _otinfo[0].dim[3];
    int oC_t = (oC + 3) / 4;

    int t_ot_mem_addr = oN * oC_t * oH * oW;
    int t_weight_addr = oC_t;
    int t_bias_addr   = oC_t;
    t_ot_mem_addr *= sizeof(float);
    //t_weight_addr *= sizeof(float);
    //t_bias_addr   *= sizeof(float);

    /* Creates CPU kernel threads
     */
    for(int i = 0; i < 4 ; i++) {
        KernelArgs_t arg;
        tileinfo_t iti, oti;
        // input/output tile info

        iti = _itinfo[0];
        oti = _otinfo[0];
        oC -= oC_t;
        oti.dim[1] = (oC >= 0) ? oC_t : (oC_t + oC);
        oti.mem_addr = oti.mem_addr + t_ot_mem_addr * i;
        arg.iti    = iti;
        arg.oti    = oti;

        arg.output = (float*) (_output + t_ot_mem_addr * i);
        arg.input  = (float*) _input;
        arg.weight = _weight + t_weight_addr * i;
        arg.bias   = _bias   + t_bias_addr * i;

        thread_args_list.push_back( arg );
    }

    for(int i = 0; i < 4 ; i++)
        thread_list.push_back( thread(cpu_kernel_wrapper, this, i) );

    /* Creates GPU kernel threads
     */
    //TODO: implements it

    return;
}

void Kernel_nn_scale::gpu_kernel_scale(
    int args_list_index
)
{
}

void Kernel_nn_scale::cpu_kernel_scale(
    int args_list_index
) {

    auto& args = thread_args_list[ args_list_index ];
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
