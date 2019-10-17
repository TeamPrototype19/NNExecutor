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
    _input  = (float*)(rcontext.main_buffer + _itinfo[0].mem_addr);
    _output = (float*)(rcontext.main_buffer + _otinfo[0].mem_addr);

    // DEBUG
    dump_data( _kernel_name+"_i.dat", (char*)_input, _input_size, sizeof(float));
    dump_data( _kernel_name+"_w.dat", (char*)_weight, _weight_size, sizeof(float));
    dump_data( _kernel_name+"_b.dat", (char*)_bias, _bias_size, sizeof(float));

    test_kernel_conv3d( _output, _input, _weight, _bias );

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


void Kernel_nn_conv::test_kernel_conv3d(
    float *output,
    float *input,
    float *weight,
    float *bias
) {

    int N = _itinfo[0].dim[0];
    int C = _itinfo[0].dim[1];
    int H = _itinfo[0].dim[2];
    int W = _itinfo[0].dim[3];
    int O = _otinfo[0].dim[1];
    int KW = _kernel_size_w;
    int KH = _kernel_size_h;
    int SW = _stride_size_w;
    int SH = _stride_size_h;
    int PW = _pad_size_w;
    int PH = _pad_size_h;

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
