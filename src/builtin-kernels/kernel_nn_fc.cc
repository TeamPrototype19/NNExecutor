#include "kernel_nn_fc.hpp"
#include "log.h"

#include <iomanip>

namespace NNFramework {

Kernel_nn_fc kernel_nn_fc;

Kernel_nn_fc::Kernel_nn_fc(void) : Kernel() {
    REGISTER_KERNEL();
}

Kernel_nn_fc::~Kernel_nn_fc(void) {
}

int Kernel_nn_fc::GetOpCode(void) {
    return OpCode_FullyConnected;
}

int Kernel_nn_fc::preProc( const Instruction *inst ) {
    auto opinfo = inst->operand_as_FC();

    decode_fb_data( opinfo );

    return 0;
}

int Kernel_nn_fc::postProc(void) {
    logfs << "\n";
    return 0;
}

int Kernel_nn_fc::Run( RunContext &rcontext ) {
    _input  = (rcontext.main_buffer + _itinfo[0].mem_addr);
    _output = (rcontext.main_buffer + _otinfo[0].mem_addr);

    // DEBUG
    dump_data( _kernel_name+"_i.dat", _input, _input_size, sizeof(float));
    dump_data( _kernel_name+"_w.dat", (char*)_weight, _weight_size, sizeof(float));
    dump_data( _kernel_name+"_b.dat", (char*)_bias, _bias_size, sizeof(float));

    test_kernel_fc( (float*)_output, (float*)_input, _weight, _bias );

    // DEBUG
    dump_data( _kernel_name+"_o.dat", (char*)_output, _output_size, sizeof(float));

    return 0;
}

int Kernel_nn_fc::decode_fb_data(const FC *opinfo) {
    /* Decoder flatbuffer contents
     */
    _kernel_name = opinfo->kernel_name()->c_str();
    _weight = (float*)opinfo->weight()->data();
    _bias = (float*)opinfo->bias()->data();
    _weight_size = opinfo->weight()->size();
    _bias_size = opinfo->bias()->size();

    if( _weight_size == 0 ) _weight = nullptr;
    if( _bias_size   == 0 ) _bias = nullptr;

    get_itile_info( opinfo->itile() );
    get_otile_info( opinfo->otile() );


    /* Print decoded content on log file
     */
    logfs << "-------- Kernel_opinfo fb data decode result --------\n";
    logfs << "name           = " << _kernel_name << "\n";
    logfs << "weight_size    = " << _weight_size << "\n";
    logfs << "bias_size      = " << _bias_size << "\n";
    display_tile_info( logfs );
   
    return 0;
}

void Kernel_nn_fc::test_kernel_fc(
    // output
    float *output,
    // inputs
    float *input,
    float *weight,
    float *bias
) {
    int N = _itinfo[0].dim[0];

    int ifm_size = 1;
    for(auto a : _itinfo[0].dim)
        ifm_size *= a;
    ifm_size /= N;

    int ofm_size = 1;
    for(auto a : _otinfo[0].dim)
        ofm_size *= a;
    ofm_size /= N;


    float *wg = weight;

    for(int n = 0 ; n < N ; n++) {
        for(int o = 0 ; o < ofm_size ; o++) {
            float *in = input + ifm_size * n;
            float sum = 0;
            for(int i = 0 ; i < ifm_size ; i++) {
                sum += (*in++) * (*wg++);
            }
            *output++ = sum + (*bias++);
        }
    }

    return;
}

}

