#include "kernel.hpp"

#include <thread>

using namespace std;

namespace NNFramework {

class Kernel_nn_conv : Kernel {
    typedef struct _KernelArg {
        float *output;
        float *input;
        float *weight;
        float *bias;
        tileinfo_t  iti, oti;
    } KernelArgs_t;
public:
    Kernel_nn_conv();
    ~Kernel_nn_conv();

    int GetOpCode(void) override;
    int preProc( const Instruction * ) override;
    int postProc(void) override;
    int Run( RunContext &rcontext ) override;
    static void cpu_kernel_wrapper(Kernel_nn_conv *handle, int arg_index) {
        handle->cpu_kernel_conv3d( arg_index );
    }

private:
    /* CPU not-optimized code
     */
    void cpu_kernel_conv3d(
        int args_list_index
    );
    /* GPU kernel code
     */
    void gpu_kernel_conv3d(
        int args_list_index
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

    /* Thread related members
     */
    vector<thread>       thread_list;
    vector<KernelArgs_t> thread_args_list;
    void creates_threads(void);
    void wait_threads(void);

    /* Flatbuffer decoder
     */
    int decode_fb_data(const Conv *);
};

}
