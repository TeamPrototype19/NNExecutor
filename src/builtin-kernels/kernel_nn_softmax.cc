#include "kernel_nn_softmax.hpp"
#include "log.h"

#include <iomanip>

namespace NNFramework {

Kernel_nn_softmax kernel_nn_softmax;

Kernel_nn_softmax::Kernel_nn_softmax(void) : Kernel() {
    REGISTER_KERNEL();
}

Kernel_nn_softmax::~Kernel_nn_softmax(void) {
}

int Kernel_nn_softmax::GetOpCode(void) {
    return OpCode_Softmax;
}

int Kernel_nn_softmax::preProc( const Instruction *inst ) {
    auto opinfo = inst->operand_as_Softmax();

    decode_fb_data( opinfo );

    return 0;
}

int Kernel_nn_softmax::postProc(void) {
    return 0;
}

int Kernel_nn_softmax::Run( RunContext &rcontext ) {
    return 0;
}

int Kernel_nn_softmax::decode_fb_data(const Softmax *opinfo) {
    logfs << "-------- Kernel_opinfo fb data decode result --------\n";
    logfs << "name           = " << opinfo->kernel_name()->c_str() << "\n";
    logfs << "*** tile info ***\n";
    auto iti = opinfo->itile();
    for(unsigned int i = 0 ; i < iti->Length() ; i++) {
        auto ti = iti->Get(i);
        logfs << "Input tile info => " << i << "'th\n";
        logfs << "memory address = 0x" << setfill('0') << right << setw(8) << hex << ti->addr() << dec << "\n";
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
        logfs << "memory address = 0x" << setfill('0') << right << setw(8) << hex << ti->addr() << dec << "\n";
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
