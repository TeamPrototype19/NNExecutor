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
    void test_kernel_pool(
        float *output,
        float *input
    );

    int _kernel_size_w;
    int _kernel_size_h;
    int _stride_size_w;
    int _stride_size_h;
    int _pad_size_w;
    int _pad_size_h;
    bool _global_pooling;

    int decode_fb_data(const Pooling *);
};

}
