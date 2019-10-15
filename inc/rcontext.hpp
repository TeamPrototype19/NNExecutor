#ifndef __RCONTEXT_H__
#define __RCONTEXT_H__

#include <iostream>

using namespace std;

namespace NNFramework {

typedef struct _RunContext {
    char *in_data;
    int   in_data_size;
    char *out_data;
    int   out_data_size;
    char *main_buffer;
} RunContext;

}

#endif
