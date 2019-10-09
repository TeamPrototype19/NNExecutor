#include "nnexec.hpp"
#include "log.h"

using namespace std;

namespace NNFramework {

NNExecutor::NNExecutor(string cgo_file_name) {
    /* flat buffer file open 
     */
    ifstream fbfile;
    fbfile.open( cgo_file_name.c_str(), ios::in | ios::binary );

    if( ! fbfile.is_open() )
        throw runtime_error("NNExecutor::NNExecutor; Can't open cgo file.");

    /* Get buffer size from file stream
     */
    fbfile.seekg( 0, ios::end );
    _cgo_buf_size = fbfile.tellg();
    fbfile.seekg( 0, ios::beg );
    cout << "'cgo' file size = " << _cgo_buf_size << "\n";

    /* Read cgo flatbuffer data file
     * and parses the data file.
     */
    _cgo_buf = new char [ _cgo_buf_size ];
    fbfile.read( _cgo_buf, _cgo_buf_size );
    fbfile.close();

    /* Get a pointer to the root object of the buffer
     */
    cgo = GetInstPacket( _cgo_buf );
}

NNExecutor::~NNExecutor(void) {
}

void NNExecutor::copy_input_data(char *in, int &size) {
}

void NNExecutor::copy_output_data(char *out, int &size) {
}

void NNExecutor::run(void) {
    /* Get Packet from flatbuffer root object
     */
    auto packets = cgo->packet();
    auto packet_size = packets->Length();
    for(unsigned int i = 0 ; i < packet_size ; i++) {
        /* Get 'Instruction' data
         */
        auto inst = packets->Get(i);
        auto opcode = inst->opcode();

        /* Get Kernel handler for the Instruction.OpCode
         */
        if( KernelList.find( opcode ) == KernelList.end() ) {
            cerr << "Instruction number = " << i << "'th\n";
            cerr << "           .opcode = " << opcode << "\n";
            throw runtime_error("[ERROR] Unknown instruction opcode.");
        }
            
        cout << "opcode is " << opcode << "\n";
        Kernel* khandler = KernelList[ opcode ];
        khandler->Run( inst );

        /*
        if( opcode == OpCode_Input ) {
            cout << "opcode is Input type.\n";
        }
        else if( opcode == OpCode_Convolution ) {
            cout << "opcode is Conv type.\n";
        }
        else if( opcode == OpCode_Relu ) {
            cout << "opcode is Relu type.\n";
        }
        else if( opcode == OpCode_Pooling ) {
            cout << "opcode is Pooling type.\n";
        }
        else if( opcode == OpCode_FullyConnected ) {
            cout << "opcode is FC type.\n";
        }
        else if( opcode == OpCode_Softmax ) {
            cout << "opcode is Softmax type.\n";
        }
        else {
            cout << "opcode is unknown type.\n";
        }
        */
    }
}

}
