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

int Kernel_nn_output::preProc(void) {
    return 0;
}

int Kernel_nn_output::postProc(void) {
    return 0;
}

int Kernel_nn_output::Run(const Instruction *inst) {
    auto opinfo = inst->operand_as_Output();

    // DEBUG
    decode_fb_data( opinfo );

    return 0;
}

int Kernel_nn_output::decode_fb_data(const Output *opinfo) {
    logfs << "-------- Kernel_opinfo fb data decode result --------\n";
    logfs << "name           = " << opinfo->kernel_name()->c_str() << "\n";
    logfs << "*** tile info ***\n";
    auto iti = opinfo->itile();
    for(unsigned int i = 0 ; i < iti->Length() ; i++) {
        auto ti = iti->Get(i);
        logfs << "Input tile info  => " << i << "'th\n";
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
