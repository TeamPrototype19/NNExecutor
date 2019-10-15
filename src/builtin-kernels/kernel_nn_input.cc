#include "kernel_nn_input.hpp"
#include "log.h"

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

int Kernel_nn_input::preProc( const Instruction *inst ) {
    auto inputinfo = inst->operand_as_Input();

    decode_fb_data( inputinfo );

    return 0;
}

int Kernel_nn_input::postProc(void) {
    // DEBUG
    dump_data( _kernel_name+"_o.dat", (char*)_output, _output_size);

    logfs << "\n";
    return 0;
}

int Kernel_nn_input::Run( RunContext &rcontext ) {
    _output  = (rcontext.main_buffer + _otinfo[0].mem_addr);

    memcpy( _output, rcontext.in_data, rcontext.in_data_size );

    return 0;
}

int Kernel_nn_input::decode_fb_data(const Input *opinfo) {
    _kernel_name = opinfo->kernel_name()->c_str();
    auto oti = opinfo->otile();
    for(unsigned int i = 0 ; i < oti->Length() ; i++) {
        auto ti = oti->Get(i);
        tileinfo_t t;
        t.mem_addr = ti->addr();
        t.dim.push_back( ti->tsize_n() );
        t.dim.push_back( ti->tsize_c() );
        t.dim.push_back( ti->tsize_h() );
        t.dim.push_back( ti->tsize_w() );
        _otinfo.push_back( t );
    }
    _output_size = _otinfo[0].size( _otinfo[0].dim ) * sizeof(float);

    logfs << "-------- Kernel_opinfo fb data decode result --------\n";
    logfs << "name           = " << _kernel_name << "\n";
    logfs << "*** tile info ***\n";
    for(unsigned int i = 0 ; i < _otinfo.size() ; i++) {
        auto ti = _otinfo[i];
        logfs << "Output tile info => " << i << "'th\n";
        logfs << "memory address = 0x" << setfill('0') << right << setw(8) << hex << ti.mem_addr << dec << "\n";
        logfs << "tsize[n,c,h,w] = [";
        logfs << ti.dim[0] << ",";
        logfs << ti.dim[1] << ",";
        logfs << ti.dim[2] << ",";
        logfs << ti.dim[3] << "]\n";
    }
   
    return 0;
}

}
