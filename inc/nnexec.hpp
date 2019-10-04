#include <iostream>

#include "log.h"

using namespace std;

namespace NNFramework {

class NNExecutor {
public:
    NNExecutor(string cgo_file_name);
    ~NNExecutor();

    void set_input_nocopy(float *in);
    void get_output_copy(float *out);
    void run(void);
private:
    float *_input;
    float *_output;
};

}
