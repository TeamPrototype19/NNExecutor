#include "kernel.hpp"

using namespace std;

namespace NNFramework {

class Kernel_nn_pool : Kernel {
public:
    Kernel_nn_pool();
    ~Kernel_nn_pool();

    int GetOpCode(void) override;
    int preProc( const Instruction * ) override;
    int postProc(void) override;
    int Run( RunContext &rcontext ) override;

private:
    int decode_fb_data(const Pooling *);
};

}
