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
    /* CPU not-optimized code
     */
    void test_kernel_conv3d(
        float *output,
        float *input,
        float *weight,
        float *bias
    );

    int _kernel_size_w;
    int _kernel_size_h;
    int _stride_size_w;
    int _stride_size_h;
    int _pad_size_w;
    int _pad_size_h;
    int _weight_size;
    int _bias_size;
    float *_weight;
    float *_bias;
    int decode_fb_data(const Conv *);
};

}
