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

int Kernel_nn_memalloc::preProc( const Instruction *inst ) {
    auto opinfo = inst->operand_as_MemAlloc();
    decode_fb_data( opinfo );

    return 0;
}

int Kernel_nn_memalloc::postProc(void) {
    logfs << "\n";
    return 0;
}

int Kernel_nn_memalloc::Run( RunContext &rcontext ) {
    rcontext.main_buffer = new char [ _total_buff_size ];

    if( rcontext.main_buffer == nullptr )
        throw runtime_error("[ERROR] memory allcation is failed at MemAlloc kernel.");

    return 0;
}

int Kernel_nn_memalloc::decode_fb_data(const MemAlloc *opinfo) {
    _kernel_name = opinfo->kernel_name()->c_str();
    _total_buff_size = opinfo->total_buff_size();


    logfs << "-------- Kernel_opinfo fb data decode result --------\n";
    logfs << "name           = " << _kernel_name << "\n";
    logfs << "total_buf_size = " << _total_buff_size << "\n";
    
    return 0;
}

}
