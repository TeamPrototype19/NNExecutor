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
    auto inputinfo = inst->operand_as_Input();

    decode_fb_data( inputinfo );

    return 0;
}

int Kernel_nn_input::postProc(void) {
    logfs << "\n";
    return 0;
}

int Kernel_nn_input::Run( RunContext &rcontext ) {
    return 0;
}

int Kernel_nn_input::decode_fb_data(const Input *opinfo) {
    logfs << "-------- Kernel_opinfo fb data decode result --------\n";
    logfs << "name           = " << opinfo->kernel_name()->c_str() << "\n";
    logfs << "*** tile info ***\n";
    auto oti = opinfo->otile();
    for(unsigned int i = 0 ; i < oti->Length() ; i++) {
        auto ti = oti->Get(i);
        logfs << "Output tile info => " << i << "'th\n";
        logfs << "memory address = 0x" << setfill('0') << right << setw(8) << hex << ti->addr() << dec << "\n";
        logfs << "tsize[n,c,h,w] = [";
        logfs << ti->tsize_n() << ",";
        logfs << ti->tsize_c() << ",";
        logfs << ti->tsize_h() << ",";
        logfs << ti->tsize_w() << "]\n";
    }
    
    return 0;
}

}
