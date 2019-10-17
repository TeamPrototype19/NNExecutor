#include "kernel.hpp"

using namespace std;

namespace NNFramework {

class Kernel_nn_fc : Kernel {
public:
    Kernel_nn_fc();
    ~Kernel_nn_fc();

    int GetOpCode(void) override;
    int preProc( const Instruction * ) override;
    int postProc(void) override;
    int Run( RunContext &rcontext ) override;

private:
    /* CPU not-optimized code
     */
    void test_kernel_fc(
        float *output,
        float *input,
        float *weight,
        float *bias
    );

    int _weight_size;
    int _bias_size;
    float *_weight;
    float *_bias;
    int decode_fb_data(const FC *);
};

}
