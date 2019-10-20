#include "kernel_nn_conv.hpp"
#include "log.h"

#include <iomanip>

namespace NNFramework {

Kernel_nn_conv kernel_nn_conv;

Kernel_nn_conv::Kernel_nn_conv(void) : Kernel() {
    REGISTER_KERNEL();
}

Kernel_nn_conv::~Kernel_nn_conv(void) {
}

int Kernel_nn_conv::GetOpCode(void) {
    return OpCode_Convolution;
}

int Kernel_nn_conv::preProc( const Instruction *inst ) {
    auto convinfo = inst->operand_as_Conv();

    decode_fb_data( convinfo );

    return 0;
}

int Kernel_nn_conv::postProc(void) {
    // DEBUG
    dump_data( _kernel_name+"_o.dat", (char*)_output, _output_size, sizeof(float));
    logfs << "\n";

    return 0;
}

int Kernel_nn_conv::Run( RunContext &rcontext ) {
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

int Kernel_nn_conv::decode_fb_data(const Conv *opinfo) {
    /* Decoder flatbuffer contents
     */
    _kernel_name = opinfo->kernel_name()->c_str();
    _kernel_size_w = opinfo->kernel_size_w();
    _kernel_size_h = opinfo->kernel_size_h();
    _stride_size_w = opinfo->stride_size_w();
    _stride_size_h = opinfo->stride_size_h();
    _pad_size_w = opinfo->pad_size_w();
    _pad_size_h = opinfo->pad_size_h();
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
    logfs << "kernel_size_w  = " << _kernel_size_w << "\n";
    logfs << "kernel_size_h  = " << _kernel_size_h << "\n";
    logfs << "stride_size_w  = " << _stride_size_w << "\n";
    logfs << "stride_size_h  = " << _stride_size_h << "\n";
    logfs << "pad_size_w     = " << _pad_size_w    << "\n";
    logfs << "pad_size_h     = " << _pad_size_h    << "\n";
    logfs << "weight_size    = " << _weight_size << "\n";
    logfs << "bias_size      = " << _bias_size << "\n";
    display_tile_info( logfs );
   
    return 0;
}

void Kernel_nn_conv::wait_threads(void)
{
    for(auto& thread : thread_list)
        thread.join();

    thread_args_list.clear();
    thread_list.clear();

}

void Kernel_nn_conv::creates_threads(void)
{

    assert( _itinfo.size() == 1 );
    assert( _otinfo.size() == 1 );
    assert( _itinfo[0].dim.size() == 4 );
    assert( _otinfo[0].dim.size() == 4 );
    assert( _itinfo[0].dim[0] == 1 );
    assert( _otinfo[0].dim[0] == 1 );

    /* Check tile sizes
     */
    int iC = _itinfo[0].dim[1];
    int oN = _otinfo[0].dim[0];
    int oC = _otinfo[0].dim[1];
    int oH = _otinfo[0].dim[2];
    int oW = _otinfo[0].dim[3];
    int oC_t = (oC + 3) / 4;

    int t_ot_mem_addr = oN * oC_t * oH * oW;
    int t_weight_addr = _kernel_size_h * _kernel_size_w * iC * oC_t;
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

void Kernel_nn_conv::gpu_kernel_conv3d(
    int args_list_index
)
{
}

void Kernel_nn_conv::cpu_kernel_conv3d(
    int args_list_index
) {

    auto& args = thread_args_list[ args_list_index ];
    int N = args.iti.dim[0];
    int C = args.iti.dim[1];
    int H = args.iti.dim[2];
    int W = args.iti.dim[3];
    int O = args.oti.dim[1];
    int KW = _kernel_size_w;
    int KH = _kernel_size_h;
    int SW = _stride_size_w;
    int SH = _stride_size_h;
    int PW = _pad_size_w;
    int PH = _pad_size_h;

    float *output = args.output;
    float *input  = args.input;
    float *weight = args.weight;
    float *bias   = args.bias;

    for(int n = 0 ; n < N ; n++) {
        float *bp = bias;
    for(int o = 0 ; o < O ; o++) {

        /* IFM loop (3D)
         */
        for(int h = -PH ; h < (H+PH) ; h += SH) {
            for(int w = -PW ; w < (W+PW) ; w += SW) {

                /* Kernel loop
                 */
                if( (w+KW) <= (W+PW) && (h+KH) <= (H+PH) ) {
                    float sum = 0;
                    for(int c = 0 ; c < C ; c++) {
                        for(int kh = 0 ; kh < KH ; kh++) {
                            if( (h+kh) >= 0 && (h+kh) < H ) {
                                float *inp = input + (W*(h+kh)) + (W*H*c) + w + (C*H*W*n);
                                float *wgt = weight + (KW*kh) + (KW*KH*c) + (KW*KH*C*o);
                                for(int kw = 0 ; kw < KW ; kw++) {
                                    if( (w+kw) >= 0 && (w+kw) < W )
                                        sum += (*inp) * (*wgt++);
                                    inp++;
                                }
                            }
                        }
                    }
                    *output++ = sum + *bp;
                }
            }
        }
        bp++;
    }
    }
}

}
