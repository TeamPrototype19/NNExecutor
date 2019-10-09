#include "kernel.hpp"

using namespace std;

namespace NNFramework {

class Kernel_nn_fc : Kernel {
public:
    Kernel_nn_fc();
    ~Kernel_nn_fc();

    int GetOpCode(void) override;
    int preProc(void) override;
    int postProc(void) override;
    int Run(const Instruction *) override;

private:
    int decode_fb_data(const FC *);
};

}
