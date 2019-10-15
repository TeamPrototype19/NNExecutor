#include <iostream>
#include <fstream>

#include "log.h"
#include "kernel.hpp"
#include "instPacket_generated.h"

using namespace std;

namespace NNFramework {

class NNExecutor {
public:
    NNExecutor(string cgo_file_name);
    ~NNExecutor();

    void set_input_data(char *in, int &size);
    void set_output_data(char *out, int &size);
    void run(void);
private:
    int    _input_size;
    char  *_input;
    int    _output_size;
    char  *_output;
    char  *_cgo_buf;
    int    _cgo_buf_size;
    const NNFramework::InstPacket* cgo;
    RunContext rcontext;
};

}
