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
    dump_data( _kernel_name+"_o.dat", (char*)_output, _output_size);
    logfs << "\n";

    return 0;
}

int Kernel_nn_conv::Run( RunContext &rcontext ) {
    _input  = (float*)(rcontext.main_buffer + _itinfo[0].mem_addr);
    _output = (float*)(rcontext.main_buffer + _otinfo[0].mem_addr);

    // DEBUG
    dump_data( _kernel_name+"_i.dat", (char*)_input, _input_size);

    test_kernel_conv3d( _output, _input, _weight, _bias );

    return 0;
}

int Kernel_nn_conv::decode_fb_data(const Conv *conv) {
    _kernel_name = conv->kernel_name()->c_str();
    _kernel_size_w = conv->kernel_size_w();
    _kernel_size_h = conv->kernel_size_h();
    _stride_size_w = conv->stride_size_w();
    _stride_size_h = conv->stride_size_h();
    _pad_size_w = conv->pad_size_w();
    _pad_size_h = conv->pad_size_h();
    _weight = (float*)conv->weight()->data();
    _bias = (float*)conv->bias()->data();
    _weight_size = conv->weight()->size();
    _bias_size = conv->bias()->size();

    auto iti = conv->itile();
    for(unsigned int i = 0 ; i < iti->Length() ; i++) {
        auto ti = iti->Get(i);
        tileinfo_t t;
        t.mem_addr = ti->addr();
        t.dim.push_back( ti->tsize_n() );
        t.dim.push_back( ti->tsize_c() );
        t.dim.push_back( ti->tsize_h() );
        t.dim.push_back( ti->tsize_w() );
        _itinfo.push_back( t );
    }
    _input_size = _itinfo[0].size( _itinfo[0].dim ) * sizeof(float);
    
    auto oti = conv->otile();
    for(unsigned int i = 0 ; i < oti->Length() ; i++) {
        auto ti = oti->Get(i);
        tileinfo_t t;
        t.mem_addr = ti->addr();
        t.dim.push_back( ti->tsize_n() );
        t.dim.push_back( ti->tsize_c() );
        t.dim.push_back( ti->tsize_h() );
        t.dim.push_back( ti->tsize_w() );
        _otinfo.push_back( t );
    }
    _output_size = _otinfo[0].size( _otinfo[0].dim ) * sizeof(float);


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
    logfs << "*** tile info ***\n";
    for(unsigned int i = 0 ; i < _itinfo.size() ; i++) {
        auto ti = _itinfo[i];
        logfs << "Input tile info => " << i << "'th\n";
        logfs << "memory address = 0x" << setfill('0') << right << setw(8) << hex << ti.mem_addr << dec << "\n";
        logfs << "tsize[n,c,h,w] = [";
        logfs << ti.dim[0] << ",";
        logfs << ti.dim[1] << ",";
        logfs << ti.dim[2] << ",";
        logfs << ti.dim[3] << "]\n";
    }
    for(unsigned int i = 0 ; i < _otinfo.size() ; i++) {
        auto ti = _otinfo[i];
        logfs << "Output tile info => " << i << "'th\n";
        logfs << "memory address = 0x" << setfill('0') << right << setw(8) << hex << ti.mem_addr << dec << "\n";
        logfs << "tsize[n,c,h,w] = [";
        logfs << ti.dim[0] << ",";
        logfs << ti.dim[1] << ",";
        logfs << ti.dim[2] << ",";
        logfs << ti.dim[3] << "]\n";
    }
    
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
