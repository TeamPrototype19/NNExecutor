#include "kernel.hpp"

using namespace std;

namespace NNFramework {

class Kernel_nn_softmax : Kernel {
public:
    Kernel_nn_softmax();
    ~Kernel_nn_softmax();

    int GetOpCode(void) override;
    int preProc( const Instruction * ) override;
    int postProc(void) override;
    int Run( RunContext &rcontext ) override;

private:
    /* CPU not-optimized code
     */
    void test_kernel_softmax(
        float *output,
        float *input
    );

    int decode_fb_data(const Softmax *);
};

}
