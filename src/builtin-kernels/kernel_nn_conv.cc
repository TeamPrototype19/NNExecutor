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

    // DEBUG
    decode_fb_data( convinfo );

    return 0;
}

int Kernel_nn_conv::postProc(void) {
    return 0;
}

int Kernel_nn_conv::Run( RunContext &rcontext ) {
    return 0;
}

int Kernel_nn_conv::decode_fb_data(const Conv *conv) {
    logfs << "-------- Kernel_opinfo fb data decode result --------\n";
    logfs << "name           = " << conv->kernel_name()->c_str() << "\n";
    logfs << "kernel_size_w  = " << conv->kernel_size_w() << "\n";
    logfs << "kernel_size_h  = " << conv->kernel_size_h() << "\n";
    logfs << "stride_size_w  = " << conv->stride_size_w() << "\n";
    logfs << "stride_size_h  = " << conv->stride_size_h() << "\n";
    logfs << "pad_size_w     = " << conv->pad_size_w()    << "\n";
    logfs << "pad_size_h     = " << conv->pad_size_h()    << "\n";
    logfs << "weight_size    = " << conv->weight()->size() << "\n";
    logfs << "bias_size      = " << conv->bias()->size() << "\n";
    logfs << "*** tile info ***\n";
    auto iti = conv->itile();
    for(unsigned int i = 0 ; i < iti->Length() ; i++) {
        auto ti = iti->Get(i);
        logfs << "Input tile info => " << i << "'th\n";
        logfs << "memory address = 0x" << setfill('0') << right << setw(8) << hex << ti->addr() << "\n";
        logfs << "tsize[n,c,h,w] = [";
        logfs << ti->tsize_n() << ",";
        logfs << ti->tsize_c() << ",";
        logfs << ti->tsize_h() << ",";
        logfs << ti->tsize_w() << "]\n";
    }
    auto oti = conv->otile();
    for(unsigned int i = 0 ; i < oti->Length() ; i++) {
        auto ti = oti->Get(i);
        logfs << "Output tile info => " << i << "'th\n";
        logfs << "memory address = 0x" << setfill('0') << right << setw(8) << hex << ti->addr() << "\n";
        logfs << "tsize[n,c,h,w] = [";
        logfs << ti->tsize_n() << ",";
        logfs << ti->tsize_c() << ",";
        logfs << ti->tsize_h() << ",";
        logfs << ti->tsize_w() << "]\n";
    }
    logfs << "\n";
    
    return 0;
}

}

#if 0
void test_kernel_conv3d(
    // output
    float *output,
    // inputs
    float *input,
    float *weight,
    float *bias,
    // operation information
    ConvInfo cinfo
) {

    int N = cinfo.ifmDim[0];
    int C = cinfo.ifmDim[1];
    int H = cinfo.ifmDim[2];
    int W = cinfo.ifmDim[3];
    int O = cinfo.output_num;
    int KW = cinfo.kernel_size_w;
    int KH = cinfo.kernel_size_h;
    int SW = cinfo.stride_size_w;
    int SH = cinfo.stride_size_h;
    int PW = cinfo.pad_size_w;
    int PH = cinfo.pad_size_h;

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
#endif
