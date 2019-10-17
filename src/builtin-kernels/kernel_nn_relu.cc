#include "kernel_nn_relu.hpp"
#include "log.h"

#include <iomanip>

namespace NNFramework {

Kernel_nn_relu kernel_nn_relu;

Kernel_nn_relu::Kernel_nn_relu(void) : Kernel() {
    REGISTER_KERNEL();
}

Kernel_nn_relu::~Kernel_nn_relu(void) {
}

int Kernel_nn_relu::GetOpCode(void) {
    return OpCode_Relu;
}

int Kernel_nn_relu::preProc( const Instruction *inst ) {
    auto reluinfo = inst->operand_as_Relu();

    decode_fb_data( reluinfo );

    return 0;
}

int Kernel_nn_relu::postProc(void) {
    // DEBUG
    dump_data( _kernel_name+"_o.dat", (char*)_output, _output_size, sizeof(float));
    logfs << "\n";

    return 0;
}

int Kernel_nn_relu::Run( RunContext &rcontext) {
    _input  = (float*)(rcontext.main_buffer + _itinfo[0].mem_addr);
    _output = (float*)(rcontext.main_buffer + _otinfo[0].mem_addr);

    // DEBUG
    dump_data( _kernel_name+"_i.dat", (char*)_input, _input_size, sizeof(float));

    //test_kernel_relu( _output, _input );

    return 0;
}

int Kernel_nn_relu::decode_fb_data(const Relu *opinfo) {
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

void Kernel_nn_relu::test_kernel_relu(
    float *output,
    float *input
) {

    //int dbg_out_cnt = 0;

    int N = _itinfo[0].dim[0];
    int C = _itinfo[0].dim[1];
    int H = _itinfo[0].dim[2];
    int W = _itinfo[0].dim[3];

    int size = N*C*H*W;

    for(int n = 0 ; n < size ; n++) {
        /* Kernel loop
         */
        if( *input < 0 )
            *output++ = 0;
        else
            *output++ = *input;
        input++;
    }

    return;
}

}
