#include "kernel.hpp"

#include <thread>

using namespace std;

namespace NNFramework {

class Kernel_nn_concat : Kernel {
    typedef struct _KernelArg {
        float *output;
        float *input;
        tileinfo_t  iti, oti;
    } KernelArgs_t;
public:
    Kernel_nn_concat();
    ~Kernel_nn_concat();

    int GetOpCode(void) override;
    int preProc( const Instruction * ) override;
    int postProc(void) override;
    int Run( RunContext &rcontext ) override;
    static void cpu_kernel_thread_wrapper(Kernel_nn_concat *handle, int arg_index) {
        handle->cpu_kernel_concat( arg_index );
    }
    static void gpu_kernel_thread_wrapper(Kernel_nn_concat *handle, int arg_index) {
        handle->gpu_kernel_concat( arg_index );
    }

private:
    // TEMP----------------------
    vector<char*> _input_cc;
    // --------------------------
    
    /* CPU not-optimized code
     */
    void cpu_kernel_concat(
        int args_list_index
    );
    /* GPU kernel code
     */
    void gpu_kernel_concat(
        int args_list_index
    );

    vector<KernelArgs_t> kernel_args_list;
    void create_kernel_args_list(void);
    void run_kernel(void);

    /* Thread related members
     */
    vector<thread>  thread_list;
    vector<int>     cpu_thread_arg_index;
    vector<int>     gpu_thread_arg_index;
    void create_threads(void);
    void wait_threads(void);

    /* Flatbuffer decoder
     */
    int decode_fb_data(const Concat *);
};

}
