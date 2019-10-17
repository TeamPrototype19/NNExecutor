#include <iostream>
#include <fstream>
#include <map>
#include <stdexcept>

#include "instPacket_generated.h"
#include "rcontext.hpp"

namespace NNFramework {

#define REGISTER_KERNEL()    {\
    int opcode = GetOpCode();\
    if( KernelList.find( opcode ) != KernelList.end() ) {\
        std::cerr << "Kernel opcode = " << opcode << "\n";\
        throw runtime_error("Kernel opcode is already exist!");\
    }\
    KernelList[ opcode ] = this;\
}

typedef struct _tileinfo_t {
    unsigned long mem_addr;
    vector<int> dim;

    int size( vector<int> d ) {
        int tsize = 1;
        for(auto a : d)
            tsize *= a;
        return tsize;
    }
} tileinfo_t;

class Kernel {
public:
    Kernel() {}
    virtual ~Kernel() = default;

    virtual int GetOpCode(void) = 0;
    virtual int preProc( const Instruction* ) = 0;
    virtual int postProc(void) = 0;
    virtual int Run( RunContext &rcontext ) = 0;

    void get_itile_info(const flatbuffers::Vector<flatbuffers::Offset<TileInfo>> *ti);
    void get_otile_info(const flatbuffers::Vector<flatbuffers::Offset<TileInfo>> *ti);
    void display_tile_info(std::ofstream &ofs);

protected:
    void dump_data(string fileName, char *data, int data_num, int data_size);

    string _kernel_name;
    float *_input;
    float *_output;
    int _input_size;
    int _output_size;
    vector<tileinfo_t> _itinfo, _otinfo;
};

extern std::map<int, Kernel*> KernelList;


}
