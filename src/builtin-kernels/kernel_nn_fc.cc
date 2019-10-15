#include "kernel_nn_fc.hpp"
#include "log.h"

#include <iomanip>

namespace NNFramework {

Kernel_nn_fc kernel_nn_fc;

Kernel_nn_fc::Kernel_nn_fc(void) : Kernel() {
    REGISTER_KERNEL();
}

Kernel_nn_fc::~Kernel_nn_fc(void) {
}

int Kernel_nn_fc::GetOpCode(void) {
    return OpCode_FullyConnected;
}

int Kernel_nn_fc::preProc( const Instruction *inst ) {
    auto opinfo = inst->operand_as_FC();

    decode_fb_data( opinfo );

    return 0;
}

int Kernel_nn_fc::postProc(void) {
    logfs << "\n";
    return 0;
}

int Kernel_nn_fc::Run( RunContext &rcontext ) {

    return 0;
}

int Kernel_nn_fc::decode_fb_data(const FC *opinfo) {
    logfs << "-------- Kernel_opinfo fb data decode result --------\n";
    logfs << "name           = " << opinfo->kernel_name()->c_str() << "\n";
    logfs << "weight_size    = " << opinfo->weight()->size() << "\n";
    logfs << "bias_size      = " << opinfo->bias()->size() << "\n";
    logfs << "*** tile info ***\n";
    auto iti = opinfo->itile();
    for(unsigned int i = 0 ; i < iti->Length() ; i++) {
        auto ti = iti->Get(i);
        logfs << "Input tile info => " << i << "'th\n";
        logfs << "memory address = 0x" << setfill('0') << right << setw(8) << hex << ti->addr() << dec <<"\n";
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
    
    return 0;
}

}

