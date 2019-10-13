#include "kernel_nn_memfree.hpp"
#include "log.h"

#include <iomanip>

namespace NNFramework {

Kernel_nn_memfree kernel_nn_memfree;

Kernel_nn_memfree::Kernel_nn_memfree(void) : Kernel() {
    REGISTER_KERNEL();
}

Kernel_nn_memfree::~Kernel_nn_memfree(void) {
}

int Kernel_nn_memfree::GetOpCode(void) {
    return OpCode_MemFree;
}

int Kernel_nn_memfree::preProc(void) {
    return 0;
}

int Kernel_nn_memfree::postProc(void) {
    return 0;
}

int Kernel_nn_memfree::Run(const Instruction *inst) {
    auto opinfo = inst->operand_as_MemFree();

    // DEBUG
    decode_fb_data( opinfo );

    return 0;
}

int Kernel_nn_memfree::decode_fb_data(const MemFree *opinfo) {
    logfs << "-------- Kernel_opinfo fb data decode result --------\n";
    logfs << "name           = " << opinfo->kernel_name()->c_str() << "\n";
    logfs << "\n";
    
    return 0;
}

}
