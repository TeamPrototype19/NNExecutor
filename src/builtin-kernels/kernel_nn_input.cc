#include "kernel_nn_input.hpp"

#include <iomanip>

namespace NNFramework {

Kernel_nn_input kernel_nn_input;

Kernel_nn_input::Kernel_nn_input(void) : Kernel() {
    REGISTER_KERNEL();
}

Kernel_nn_input::~Kernel_nn_input(void) {
}

int Kernel_nn_input::GetOpCode(void) {
    return OpCode_Input;
}

int Kernel_nn_input::preProc(void) {
    return 0;
}

int Kernel_nn_input::postProc(void) {
    return 0;
}

int Kernel_nn_input::Run(const Instruction *inst) {
    auto inputinfo = inst->operand_as_Input();

    // DEBUG
    decode_fb_data( inputinfo );

    return 0;
}

int Kernel_nn_input::decode_fb_data(const Input *opinfo) {
    cout << "-------- Kernel_opinfo fb data decode result --------\n";
    cout << "name           = " << opinfo->kernel_name()->c_str() << "\n";
    cout << "*** tile info ***\n";
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
