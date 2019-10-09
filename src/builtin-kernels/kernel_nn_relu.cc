#include "kernel_nn_relu.hpp"

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

int Kernel_nn_relu::preProc(void) {
    return 0;
}

int Kernel_nn_relu::postProc(void) {
    return 0;
}

int Kernel_nn_relu::Run(const Instruction *inst) {
    auto convinfo = inst->operand_as_Relu();

    // DEBUG
    decode_fb_data( convinfo );

    return 0;
}

int Kernel_nn_relu::decode_fb_data(const Relu *opinfo) {
    cout << "-------- Kernel_opinfo fb data decode result --------\n";
    cout << "name           = " << opinfo->kernel_name()->c_str() << "\n";
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
