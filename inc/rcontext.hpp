#ifndef __RCONTEXT_H__
#define __RCONTEXT_H__

#include <iostream>

using namespace std;

namespace NNFramework {

typedef struct _RunContext {
    char *in_data;
    char *out_data;
    char *main_buffer;
} RunContext;

}

#endif
