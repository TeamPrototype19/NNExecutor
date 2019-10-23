#include "kernel_nn_pool.hpp"
#include "log.h"

#include <iomanip>

namespace NNFramework {

Kernel_nn_pool kernel_nn_pool;

Kernel_nn_pool::Kernel_nn_pool(void) : Kernel() {
    REGISTER_KERNEL();
}

Kernel_nn_pool::~Kernel_nn_pool(void) {
}

int Kernel_nn_pool::GetOpCode(void) {
    return OpCode_Pooling;
}

int Kernel_nn_pool::preProc( const Instruction *inst ) {
    auto opinfo = inst->operand_as_Pooling();

    decode_fb_data( opinfo );

    return 0;
}

int Kernel_nn_pool::postProc(void) {
    logfs << "\n";
    return 0;
}

int Kernel_nn_pool::Run( RunContext &rcontext ) {
    _input  = (rcontext.main_buffer + _itinfo[0].mem_addr);
    _output = (rcontext.main_buffer + _otinfo[0].mem_addr);

    // DEBUG
    dump_data( _kernel_name+"_i.dat", _input, _input_size, sizeof(float));

    test_kernel_pool( (float*)_output, (float*)_input );

    // DEBUG
    dump_data( _kernel_name+"_o.dat", (char*)_output, _output_size, sizeof(float));

    return 0;
}

int Kernel_nn_pool::decode_fb_data(const Pooling *opinfo) {
    /* Decoder flatbuffer contents
     */
    _kernel_name = opinfo->kernel_name()->c_str();
    _kernel_size_w = opinfo->kernel_size_w();
    _kernel_size_h = opinfo->kernel_size_h();
    _stride_size_w = opinfo->stride_size_w();
    _stride_size_h = opinfo->stride_size_h();
    _pad_size_w = opinfo->pad_size_w();
    _pad_size_h = opinfo->pad_size_h();
    _global_pooling = opinfo->global_pooling();

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
    display_tile_info( logfs );
 
    return 0;
}

void Kernel_nn_pool::test_kernel_pool(
    float *output,
    float *input
) {

    //int dbg_out_cnt = 0;

    int N = _itinfo[0].dim[0];
    int C = _itinfo[0].dim[1];
    int H = _itinfo[0].dim[2];
    int W = _itinfo[0].dim[3];
    int KW = _kernel_size_w;
    int KH = _kernel_size_h;
    int SW = _stride_size_w;
    int SH = _stride_size_h;
    int PW = _pad_size_w;
    int PH = _pad_size_h;

    int TP = 0;//pinfo.pool_type;
    //int GP = pinfo.global_pooling;
    

    if( _global_pooling ) {
        int size = W*H;
        for(int n = 0 ; n < N ; n++) {
        for(int c = 0 ; c < C ; c++) {
            if( TP == 0 ) { // MAX_POOL
                float elem = -NFDBITS;
                for(int i = 0; i < size; i++, input++)
                    elem = (elem < *input) ? *input : elem;
                *output++ = elem;
            }
            else if( TP == 1 ) { // AVG_POOL
                float elem = -NFDBITS;
                for(int i = 0; i < size; i++, input++)
                    elem += *input;
                *output++ = elem / (float)size;
            }
        }
        }
        return;
    }

    for(int n = 0 ; n < N ; n++) {
    for(int c = 0 ; c < C ; c++) {
        for(int h = -PH ; h < (H+PH) ; h += SH) {
        for(int w = -PW ; w < (W+PW) ; w += SW) {

            /* Kernel loop
             */
            if( (w+KW) <= (W+PW) && (h+KH) <= (H+PH) ) {
                float elem = -NFDBITS;
                int   elem_cnt = 0;

                //std::cout << "[" << dbg_out_cnt++ << "]\t";

                for(int kh = 0 ; kh < KH ; kh++) {
                    if( (h+kh) >= 0 && (h+kh) < H ) {
                        float *inp = input + (W*(h+kh)) + (W*H*c) + w + (C*H*W*n);
                        for(int kw = 0 ; kw < KW ; kw++) {
                            if( (w+kw) >= 0 && (w+kw) < W ) {
                                if( TP == 0 ) { // MAX_POOL
                                    elem = (elem < (*inp)) ? (*inp) : elem;
                                    //std::cout << *inp << "\t";
                                }
                                else if( TP == 1 ) { // AVG_POOL
                                    elem += (*inp);
                                    elem_cnt++;
                                }
                            }
                            inp++;
                        }
                    }
                }

                if( TP == 1 )
                    elem /= (float)elem_cnt;

                *output++ = elem;

                //std::cout << "Final = " << elem << std::endl;

            }
        }
        }
    }
    }
}
}

