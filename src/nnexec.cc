#include "nnexec.hpp"
#include "rcontext.hpp"
#include "log.h"

using namespace std;

namespace NNFramework {

NNExecutor::NNExecutor(string cgo_file_name, ExecOpt eopt) : _eopt(eopt) {
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
    logfs << "NNExecutor::NNExecutor() 'cgo' file size = " << _cgo_buf_size << "\n";

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

void NNExecutor::set_input_data(char *in, int &size) {
    _input = in;
    _input_size = size;
    rcontext.in_data = in;
    rcontext.in_data_size = size;
}

void NNExecutor::set_output_data(char *out, int &size) {
    _output = out;
    _output_size = size;
    rcontext.out_data = out;
    rcontext.out_data_size = size;
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
            
        logfs << "NNExecutor::run() opcode is " << opcode << "\n";
        cout  << "Executing... opcode(" << opcode << ")\t";
        /* Get kernel handler
         */
        Kernel* khandler = KernelList[ opcode ];
        /* Executing kernel 
         */
        khandler->preProc( inst );
        if( _eopt.do_not_run_kernel == false )
            khandler->Run( rcontext );
        khandler->postProc();

        cout << "opname = " << khandler->get_kernel_name() << "\n";
    }
}

}
