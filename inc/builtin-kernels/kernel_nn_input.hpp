#include "kernel.hpp"

using namespace std;

namespace NNFramework {

class Kernel_nn_input : Kernel {
public:
    Kernel_nn_input();
    ~Kernel_nn_input();

    int GetOpCode(void) override;
    int preProc(void) override;
    int postProc(void) override;
    int Run(const Instruction *) override;

private:
    int decode_fb_data(const Input *);
};

}
