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
#if defined(DUMP_LEVEL) && DUMP_LEVEL > 0
    dump_data( _kernel_name+"_o.dat", (char*)_output, _output_size, sizeof(float));
#endif
#if LOG_LEVEL > 1
    logfs << "\n";
#endif

    return 0;
}

int Kernel_nn_relu::Run( RunContext &rcontext) {
    _input  = (rcontext.main_buffer + _itinfo[0].mem_addr);
    _output = (rcontext.main_buffer + _otinfo[0].mem_addr);

#if defined(DUMP_LEVEL) && DUMP_LEVEL > 0
    dump_data( _kernel_name+"_i.dat", _input, _input_size, sizeof(float));
#endif

    test_kernel_relu( (float*)_output, (float*)_input );

    return 0;
}

int Kernel_nn_relu::decode_fb_data(const Relu *opinfo) {
    /* Decoder flatbuffer contents
     */
    _kernel_name = opinfo->kernel_name()->c_str();

    get_itile_info( opinfo->itile() );
    get_otile_info( opinfo->otile() );


#if LOG_LEVEL > 1
    /* Print decoded content on log file
     */
    logfs << "-------- Kernel_opinfo fb data decode result --------\n";
    logfs << "name           = " << _kernel_name << "\n";
    display_tile_info( logfs );
#endif
    
    return 0;
}

void Kernel_nn_relu::test_kernel_relu(
    float *output,
    float *input
) {

    int size = 1;
    for(auto a : _itinfo[0].dim)
        size *= a;

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
