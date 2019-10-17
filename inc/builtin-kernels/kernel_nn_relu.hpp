#include "kernel.hpp"

using namespace std;

namespace NNFramework {

class Kernel_nn_relu : Kernel {
public:
    Kernel_nn_relu();
    ~Kernel_nn_relu();

    int GetOpCode(void) override;
    int preProc( const Instruction * ) override;
    int postProc(void) override;
    int Run( RunContext &rcontext ) override;

private:
    /* TEST CPU kernel (not-optimized)
     */
    void test_kernel_relu(
        float *output,
        float *input
    );

    string _kernel_name;
    int decode_fb_data(const Relu *);
};

}
