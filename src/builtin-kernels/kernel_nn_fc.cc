#include "kernel_nn_fc.hpp"

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

int Kernel_nn_fc::preProc(void) {
    return 0;
}

int Kernel_nn_fc::postProc(void) {
    return 0;
}

int Kernel_nn_fc::Run(const Instruction *inst) {
    auto opinfo = inst->operand_as_FC();

    // DEBUG
    decode_fb_data( opinfo );

    return 0;
}

int Kernel_nn_fc::decode_fb_data(const FC *opinfo) {
    cout << "-------- Kernel_opinfo fb data decode result --------\n";
    cout << "name           = " << opinfo->kernel_name()->c_str() << "\n";
    cout << "weight_size    = " << opinfo->weight()->size() << "\n";
    cout << "bias_size      = " << opinfo->bias()->size() << "\n";
    cout << "*** tile info ***\n";
    auto iti = opinfo->itile();
    for(unsigned int i = 0 ; i < iti->Length() ; i++) {
        auto ti = iti->Get(i);
        cout << "Input tile info => " << i << "'th\n";
        cout << "memory address = 0x" << setfill('0') << right << setw(8) << hex << ti->addr() << "\n";
        cout << "tsize[n,c,h,w] = [";
        cout << ti->tsize_n() << ",";
        cout << ti->tsize_c() << ",";
        cout << ti->tsize_h() << ",";
        cout << ti->tsize_w() << "]\n";
    }
    auto oti = opinfo->otile();
    for(unsigned int i = 0 ; i < oti->Length() ; i++) {
        auto ti = oti->Get(i);
        cout << "Output tile info => " << i << "'th\n";
        cout << "memory address = 0x" << setfill('0') << right << setw(8) << hex << ti->addr() << "\n";
        cout << "tsize[n,c,h,w] = [";
        cout << ti->tsize_n() << ",";
        cout << ti->tsize_c() << ",";
        cout << ti->tsize_h() << ",";
        cout << ti->tsize_w() << "]\n";
    }
    
    return 0;
}

}

