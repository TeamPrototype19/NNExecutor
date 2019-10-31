#include "kernel_nn_input.hpp"
#include "log.h"

#include <iomanip>

namespace NNFramework {

Kernel_nn_input kernel_nn_input;

Kernel_nn_input::Kernel_nn_input(void) : Kernel() {
    REGISTER_KERNEL();
}

Kernel_nn_input::~Kernel_nn_input(void) {
}

int Kernel_nn_input::GetOpCode(void) {
    return OpCode_Input;
}

int Kernel_nn_input::preProc( const Instruction *inst ) {
    auto opinfo = inst->operand_as_Input();

    decode_fb_data( opinfo );

    return 0;
}

int Kernel_nn_input::postProc(void) {
#if defined(DUMP_LEVEL) && DUMP_LEVEL > 0
    dump_data( _kernel_name+"_o.dat", _output, _output_size, sizeof(float));
#endif

#if LOG_LEVEL > 1
    logfs << "\n";
#endif
    return 0;
}

int Kernel_nn_input::Run( RunContext &rcontext ) {
    _output  = (rcontext.main_buffer + _otinfo[0].mem_addr);

    memcpy( _output, rcontext.in_data, rcontext.in_data_size );

    return 0;
}

int Kernel_nn_input::decode_fb_data(const Input *opinfo) {
    /* Decoder flatbuffer contents
     */
    _kernel_name = opinfo->kernel_name()->c_str();

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

}
