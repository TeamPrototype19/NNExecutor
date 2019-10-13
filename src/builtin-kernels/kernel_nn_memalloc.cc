#include "kernel_nn_memalloc.hpp"
#include "log.h"

#include <iomanip>

namespace NNFramework {

Kernel_nn_memalloc kernel_nn_memalloc;

Kernel_nn_memalloc::Kernel_nn_memalloc(void) : Kernel() {
    REGISTER_KERNEL();
}

Kernel_nn_memalloc::~Kernel_nn_memalloc(void) {
}

int Kernel_nn_memalloc::GetOpCode(void) {
    return OpCode_MemAlloc;
}

int Kernel_nn_memalloc::preProc(void) {
    return 0;
}

int Kernel_nn_memalloc::postProc(void) {
    return 0;
}

int Kernel_nn_memalloc::Run(const Instruction *inst) {
    auto opinfo = inst->operand_as_MemAlloc();

    // DEBUG
    decode_fb_data( opinfo );

    return 0;
}

int Kernel_nn_memalloc::decode_fb_data(const MemAlloc *opinfo) {
    logfs << "-------- Kernel_opinfo fb data decode result --------\n";
    logfs << "name           = " << opinfo->kernel_name()->c_str() << "\n";
    logfs << "total_buf_size = " << opinfo->total_buff_size() << "\n";
    logfs << "\n";
    
    return 0;
}

}
