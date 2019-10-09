#include "kernel_nn_pool.hpp"

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
    cout << "-------- Kernel_opinfo fb data decode result --------\n";
    cout << "name           = " << opinfo->kernel_name()->c_str() << "\n";
    cout << "kernel_size_w  = " << opinfo->kernel_size_w() << "\n";
    cout << "kernel_size_h  = " << opinfo->kernel_size_h() << "\n";
    cout << "stride_size_w  = " << opinfo->stride_size_w() << "\n";
    cout << "stride_size_h  = " << opinfo->stride_size_h() << "\n";
    cout << "pad_size_w     = " << opinfo->pad_size_w()    << "\n";
    cout << "pad_size_h     = " << opinfo->pad_size_h()    << "\n";
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

