#include "kernel_nn_output.hpp"
#include "log.h"

#include <iomanip>

namespace NNFramework {

Kernel_nn_output kernel_nn_output;

Kernel_nn_output::Kernel_nn_output(void) : Kernel() {
    REGISTER_KERNEL();
}

Kernel_nn_output::~Kernel_nn_output(void) {
}

int Kernel_nn_output::GetOpCode(void) {
    return OpCode_Output;
}

int Kernel_nn_output::preProc( const Instruction *inst ) {
    auto opinfo = inst->operand_as_Output();

    decode_fb_data( opinfo );

    return 0;
}

int Kernel_nn_output::postProc(void) {
#if LOG_LEVEL > 1
    logfs << "\n";
#endif
    return 0;
}

int Kernel_nn_output::Run( RunContext &rcontext ) {
    return 0;
}

int Kernel_nn_output::decode_fb_data(const Output *opinfo) {
    /* Decoder flatbuffer contents
     */
    _kernel_name = opinfo->kernel_name()->c_str();

    get_itile_info( opinfo->itile() );


#if LOG_LEVEL > 1
    /* Print decoded content on log file
     */
    logfs << "-------- Kernel_opinfo fb data decode result --------\n";
    logfs << "name           = " << _kernel_name << "\n";
    display_tile_info( logfs );
#endif
    
    return 0;
}

}
