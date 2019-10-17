#include "kernel.hpp"

using namespace std;

namespace NNFramework {

class Kernel_nn_memalloc : Kernel {
public:
    Kernel_nn_memalloc();
    ~Kernel_nn_memalloc();

    int GetOpCode(void) override;
    int preProc( const Instruction * ) override;
    int postProc(void) override;
    int Run( RunContext &rcontext ) override;

private:
    unsigned long _total_buff_size;
    int decode_fb_data(const MemAlloc *);
};

}
