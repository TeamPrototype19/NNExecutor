#include "kernel_cpu_conv.hpp"

namespace NNFramework {

Kernel_cpu_conv::Kernel_cpu_conv(void) : Kernel() {
}

Kernel_cpu_conv::~Kernel_cpu_conv(void) {
}

int Kernel_cpu_conv::preProc(void) {
    return 0;
}

int Kernel_cpu_conv::postProc(void) {
    return 0;
}

int Kernel_cpu_conv::Run(flatbuffers::Offset<NNFramework::Instruction>) {
    return 0;
}

int Kernel_cpu_conv::decode_fb_data(const Conv *) {
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
