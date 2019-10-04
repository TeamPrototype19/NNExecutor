#include <iostream>

#include "instPacket_generated.h"

namespace NNFramework {

class Kernel {
public:
    Kernel() {}
    virtual ~Kernel() = default;

    virtual int preProc(void) = 0;
    virtual int postProc(void) = 0;
    virtual int Run(flatbuffers::Offset<NNFramework::Instruction>) = 0;

private:
};

}
