#include "kernel.hpp"

using namespace std;

namespace NNFramework {

class Kernel_cpu_conv : Kernel {
public:
    Kernel_cpu_conv();
    ~Kernel_cpu_conv();

    int preProc(void) override;
    int postProc(void) override;
    int Run(flatbuffers::Offset<NNFramework::Instruction>) override;

private:
    int decode_fb_data(const Conv *);
};

}
