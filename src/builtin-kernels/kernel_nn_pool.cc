#include "kernel_nn_pool.hpp"
#include "log.h"

#include <iomanip>

namespace NNFramework {

Kernel_nn_pool kernel_nn_pool;

Kernel_nn_pool::Kernel_nn_pool(void) : Kernel() {
    REGISTER_KERNEL();
}

Kernel_nn_pool::~Kernel_nn_pool(void) {
}

int Kernel_nn_pool::GetOpCode(void) {
    return OpCode_Pooling;
}

int Kernel_nn_pool::preProc(void) {
    return 0;
}

int Kernel_nn_pool::postProc(void) {
    return 0;
}

int Kernel_nn_pool::Run(const Instruction *inst) {
    auto opinfo = inst->operand_as_Pooling();

    // DEBUG
    decode_fb_data( opinfo );

    return 0;
}

int Kernel_nn_pool::decode_fb_data(const Pooling *opinfo) {
    logfs << "-------- Kernel_opinfo fb data decode result --------\n";
    logfs << "name           = " << opinfo->kernel_name()->c_str() << "\n";
    logfs << "kernel_size_w  = " << opinfo->kernel_size_w() << "\n";
    logfs << "kernel_size_h  = " << opinfo->kernel_size_h() << "\n";
    logfs << "stride_size_w  = " << opinfo->stride_size_w() << "\n";
    logfs << "stride_size_h  = " << opinfo->stride_size_h() << "\n";
    logfs << "pad_size_w     = " << opinfo->pad_size_w()    << "\n";
    logfs << "pad_size_h     = " << opinfo->pad_size_h()    << "\n";
    logfs << "*** tile info ***\n";
    auto iti = opinfo->itile();
    for(unsigned int i = 0 ; i < iti->Length() ; i++) {
        auto ti = iti->Get(i);
        logfs << "Input tile info => " << i << "'th\n";
        logfs << "memory address = 0x" << setfill('0') << right << setw(8) << hex << ti->addr() << "\n";
        logfs << "tsize[n,c,h,w] = [";
        logfs << ti->tsize_n() << ",";
        logfs << ti->tsize_c() << ",";
        logfs << ti->tsize_h() << ",";
        logfs << ti->tsize_w() << "]\n";
    }
    auto oti = opinfo->otile();
    for(unsigned int i = 0 ; i < oti->Length() ; i++) {
        auto ti = oti->Get(i);
        logfs << "Output tile info => " << i << "'th\n";
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

