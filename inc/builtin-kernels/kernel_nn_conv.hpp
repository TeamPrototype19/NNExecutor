#include "kernel.hpp"

using namespace std;

namespace NNFramework {

class Kernel_nn_conv : Kernel {
public:
    Kernel_nn_conv();
    ~Kernel_nn_conv();

    int GetOpCode(void) override;
    int preProc( const Instruction * ) override;
    int postProc(void) override;
    int Run( RunContext &rcontext ) override;

private:
    int decode_fb_data(const Conv *);
};

}
