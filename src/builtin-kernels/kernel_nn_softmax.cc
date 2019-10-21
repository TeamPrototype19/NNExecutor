#include "kernel_nn_softmax.hpp"
#include "log.h"

#include <iomanip>
#include <cmath>

namespace NNFramework {

Kernel_nn_softmax kernel_nn_softmax;

Kernel_nn_softmax::Kernel_nn_softmax(void) : Kernel() {
    REGISTER_KERNEL();
}

Kernel_nn_softmax::~Kernel_nn_softmax(void) {
}

int Kernel_nn_softmax::GetOpCode(void) {
    return OpCode_Softmax;
}

int Kernel_nn_softmax::preProc( const Instruction *inst ) {
    auto opinfo = inst->operand_as_Softmax();

    decode_fb_data( opinfo );

    return 0;
}

int Kernel_nn_softmax::postProc(void) {
    // DEBUG
    dump_data( _kernel_name+"_o.dat", (char*)_output, _output_size, sizeof(float));
    logfs << "\n";

    return 0;
}

int Kernel_nn_softmax::Run( RunContext &rcontext ) {
    _input  = (rcontext.main_buffer + _itinfo[0].mem_addr);
    _output = (rcontext.main_buffer + _otinfo[0].mem_addr);

    // DEBUG
    dump_data( _kernel_name+"_i.dat", _input, _input_size, sizeof(float));

    test_kernel_softmax( (float*)_output, (float*)_input );

    return 0;
}

int Kernel_nn_softmax::decode_fb_data(const Softmax *opinfo) {
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

void Kernel_nn_softmax::test_kernel_softmax(
    float *output,
    float *input
) {

    //int dbg_out_cnt = 0;

    int N = _itinfo[0].dim[0];

    int size = 1;
    for(auto a : _itinfo[0].dim)
        size *= a;
    size /= N;

    for(int n = 0 ; n < N; n++) {
        float sum = 0;
        float *op = output;
        /* Calculate sum
         */
        for(int i = 0 ; i < size ; i++) {
            *op = exp(*input++);
            sum += *op++;
        }
        for(int i = 0 ; i < size ; i++) {
            *output++ /= sum;
        }
    }

    return;
}

}
