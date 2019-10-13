#include <iostream>
#include <map>
#include <stdexcept>

#include "instPacket_generated.h"
#include "rcontext.hpp"

namespace NNFramework {

#define REGISTER_KERNEL()    {\
    int opcode = GetOpCode();\
    if( KernelList.find( opcode ) != KernelList.end() ) {\
        std::cerr << "Kernel opcode = " << opcode << "\n";\
        throw runtime_error("Kernel opcode is already exist!");\
    }\
    KernelList[ opcode ] = this;\
}

class Kernel {
public:
    Kernel() {}
    virtual ~Kernel() = default;

    virtual int GetOpCode(void) = 0;
    virtual int preProc( const Instruction* ) = 0;
    virtual int postProc(void) = 0;
    virtual int Run( RunContext &rcontext ) = 0;

private:
};

extern std::map<int, Kernel*> KernelList;


}
