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

int Kernel_nn_memfree::preProc( const Instruction *inst ) {
    auto opinfo = inst->operand_as_MemFree();
    decode_fb_data( opinfo );

    return 0;
}

int Kernel_nn_memfree::postProc(void) {
    logfs << "\n";
    return 0;
}

int Kernel_nn_memfree::Run( RunContext &rcontext ) {
    delete [] rcontext.main_buffer;

    return 0;
}

int Kernel_nn_memfree::decode_fb_data(const MemFree *opinfo) {
    _kernel_name = opinfo->kernel_name()->c_str();

#if LOG_LEVEL > 1
    logfs << "-------- Kernel_opinfo fb data decode result --------\n";
    logfs << "name           = " << _kernel_name << "\n";
#endif
    
    return 0;
}

}
