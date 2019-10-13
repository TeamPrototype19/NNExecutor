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
    auto convinfo = inst->operand_as_Relu();

    decode_fb_data( convinfo );

    return 0;
}

int Kernel_nn_relu::postProc(void) {
    return 0;
}

int Kernel_nn_relu::Run( RunContext &rcontext) {
    return 0;
}

int Kernel_nn_relu::decode_fb_data(const Relu *opinfo) {
    logfs << "-------- Kernel_opinfo fb data decode result --------\n";
    logfs << "name           = " << opinfo->kernel_name()->c_str() << "\n";
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
