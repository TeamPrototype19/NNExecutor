#include "kernel_nn_conv.hpp"
#include "log.h"

#include <iomanip>
#include "ssg_kernel.h"

namespace NNFramework {

#define CPU_THREAD_NUM 1

Kernel_nn_conv kernel_nn_conv;

Kernel_nn_conv::Kernel_nn_conv(void) : Kernel() {
    REGISTER_KERNEL();
}

Kernel_nn_conv::~Kernel_nn_conv(void) {
}

int Kernel_nn_conv::GetOpCode(void) {
    return OpCode_Convolution;
}

int Kernel_nn_conv::preProc( const Instruction *inst ) {
    auto convinfo = inst->operand_as_Conv();

    decode_fb_data( convinfo );

    return 0;
}

int Kernel_nn_conv::postProc(void) {
#if LOG_LEVEL > 1
    logfs << "\n";
#endif
#if 0
    const char * tmp_char= _kernel_name.c_str();
    char  filename[200] ;
    sprintf(filename,"./to_mnist/%s_out.txt",tmp_char);
    printf("%s\n",filename);

    FILE * fp_tmp = fopen(filename,"w");
    float * ptr_out = (float *)_output;
    for(int iter=0;iter<_output_size;iter++){
        fprintf(fp_tmp,"%f\n",ptr_out[iter]);
    }

    fclose(fp_tmp);
#endif

    return 0;
}

int Kernel_nn_conv::Run( RunContext &rcontext ) {
    _input  = (rcontext.main_buffer + _itinfo[0].mem_addr);
    _output = (rcontext.main_buffer + _otinfo[0].mem_addr);

#if defined(DUMP_LEVEL) && DUMP_LEVEL > 0
    dump_data( _kernel_name+"_i.dat", _input, _input_size, sizeof(float));
    dump_data( _kernel_name+"_w.dat", (char*)_weight, _weight_size, sizeof(float));
    dump_data( _kernel_name+"_b.dat", (char*)_bias, _bias_size, sizeof(float));
#endif
    
#if 0
    int img_n = _itinfo[0].dim[0];
    int img_c = _itinfo[0].dim[1];//1;
    int img_h = _itinfo[0].dim[2];//28;
    int img_w = _itinfo[0].dim[3];//28;
    int f_n =_otinfo[0].dim[1];//20
    int f_c =_itinfo[0].dim[1];
    int f_h=_kernel_size_h;
    int f_w=_kernel_size_w;
    int stride_= _stride_size_w;
    int padding_ =_pad_size_w;
    int weight_h = _kernel_size_w*_kernel_size_w*img_c;
    int weight_w = _otinfo[0].dim[1];//20;//
   
    float *weight_in = (float *)_weight;
    float *img_in = (float *) _input;
    float *b_in = (float *)_bias;
    float *col_out =(float *)_output; 
    float * weight_in_ = new float[weight_h*weight_w];
    
    for(int h=0;h<weight_h;h++){
        for(int w=0;w<weight_w;w++){
            weight_in_[h*weight_w+w]=weight_in[w*weight_h+h];
        }
    }

    printf("opencl input\n");
    for(int iter=0; iter<20;iter++)
        printf("%f  %f  %f\n",img_in[iter],weight_in[iter],b_in[iter]);


    //ssg_kernel mkernel(img_in,img_w,img_h,img_c,img_n,weight_in_,weight_w,weight_h,b_in,col_out);
    ssg_kernel mkernel(img_in,img_w,img_h,img_c,img_n,weight_in_,weight_w,weight_h,b_in,col_out);
    //mkernel.get_cl_info();
    mkernel.init_device();
    mkernel.compile_program();

    printf("log================================\n");
    printf("weight_h : %d\n",weight_h);
    printf("weight_w : %d\n",weight_w);
    printf("img_n    : %d\n",img_n);
    printf("img_c    : %d\n",img_c);
    printf("img_h    : %d\n",img_h);
    printf("img_w    : %d\n",img_w);
    printf("f_n      : %d\n",f_n);
    printf("f_c      : %d\n",f_c);
    printf("f_h      : %d\n",f_h);
    printf("f_w      : %d\n",f_w);
    printf("stride   : %d\n",stride_);
    printf("padding  : %d\n",padding_);
    printf("log================================\n");
    
 
    mkernel.Im2col.im2col_init(f_n,f_h,stride_,padding_,0);
    mkernel.Im2col.im2col_gpu();
    mkernel.Gemm.gemm_init();
    mkernel.Gemm.gemm_cpu();
    mkernel.Gemm.gemm_gpu();

    float * gemm_out_ = (float *)mkernel.img_in;
    char tmp_name[200];
    sprintf(tmp_name,"./to_mnist/%s_gemm_out.txt",_kernel_name.c_str());
    FILE * fp_gemm_out = fopen(tmp_name,"w");
    int gemm_out_size_ = mkernel.img_n*mkernel.img_c*mkernel.img_h*mkernel.img_w;

    if(gemm_out_size_ !=_output_size)
        printf("size miss match!!\n");

    for(int iter =0;iter<_output_size;iter++)
        fprintf(fp_gemm_out,"%f\n",gemm_out_[iter]);    

    fclose(fp_gemm_out);


    printf("finish gemm!!\n");
    delete [] weight_in_;
#endif

    /* Generates kernel threiads 
     */
#if 1   // multi-thread mode (CPU-only)
    create_kernel_args_list( 4, 0, 1, 0 );
    create_threads();
#else   // singletone mode
    create_kernel_args_list( 1, 0, 1, 0 );
    run_kernel();
#endif
    wait_threads();

#if defined(DUMP_LEVEL) && DUMP_LEVEL > 0
    // DEBUG
    dump_data( _kernel_name+"_o.dat", (char*)_output, _output_size, sizeof(float));
#endif

    return 0;
}

int Kernel_nn_conv::decode_fb_data(const Conv *opinfo) {
    /* Decoder flatbuffer contents
     */
    _kernel_name = opinfo->kernel_name()->c_str();
    _kernel_size_w = opinfo->kernel_size_w();
    _kernel_size_h = opinfo->kernel_size_h();
    _stride_size_w = opinfo->stride_size_w();
    _stride_size_h = opinfo->stride_size_h();
    _pad_size_w = opinfo->pad_size_w();
    _pad_size_h = opinfo->pad_size_h();
    _weight = (float*)opinfo->weight()->data();
    _bias = (float*)opinfo->bias()->data();
    _weight_size = opinfo->weight()->size();
    _bias_size = opinfo->bias()->size();
    _relu_op_en = opinfo->relu_op_en();

    if( _weight_size == 0 ) _weight = nullptr;
    if( _bias_size   == 0 ) _bias = nullptr;

    get_itile_info( opinfo->itile() );
    get_otile_info( opinfo->otile() );


    //arg.output = (float*) (_output + t_ot_mem_addr * i);
    //arg.input  = (float*) _input;
    //arg.weight = _weight + t_weight_addr * i;
    //arg.bias   = _bias   + t_bias_addr;

    //printf("start gpu\n");
    //for(int iter= 0; iter<10;iter++)
    //    printf("%f          %f           %f\n",_input[iter],_weight[iter],_bias[iter]);



#if LOG_LEVEL > 1
    /* Print decoded content on log file
     */
    logfs << "-------- Kernel_opinfo fb data decode result --------\n";
    logfs << "name           = " << _kernel_name << "\n";
    logfs << "kernel_size_w  = " << _kernel_size_w << "\n";
    logfs << "kernel_size_h  = " << _kernel_size_h << "\n";
    logfs << "stride_size_w  = " << _stride_size_w << "\n";
    logfs << "stride_size_h  = " << _stride_size_h << "\n";
    logfs << "pad_size_w     = " << _pad_size_w    << "\n";
    logfs << "pad_size_h     = " << _pad_size_h    << "\n";
    logfs << "weight_size    = " << _weight_size << "\n";
    logfs << "bias_size      = " << _bias_size << "\n";
    logfs << "relu_op_en     = " << _relu_op_en << "\n";
    display_tile_info( logfs );
#endif
   
    return 0;
}

void Kernel_nn_conv::wait_threads(void)
{
    for(auto& thread : thread_list)
        thread.join();

    kernel_args_list.clear();
    thread_list.clear();
    cpu_thread_arg_index.clear();
    gpu_thread_arg_index.clear();
}

void Kernel_nn_conv::create_kernel_args_list(
    int thread_num_cpu,     // total number of cpu thread
    int thread_num_gpu,
    int thread_ratio_cpu,   // processing ratio by cpu thread
    int thread_ratio_gpu
)
{
    assert( _itinfo.size() == 1 );
    assert( _otinfo.size() == 1 );
    assert( _itinfo[0].dim.size() == 4 );
    assert( _otinfo[0].dim.size() == 4 );
    assert( _itinfo[0].dim[0] == 1 );
    assert( _otinfo[0].dim[0] == 1 );

    /* Check tile sizes
     */
    int iC = _itinfo[0].dim[1]; // IFM ch size
    int oN = _otinfo[0].dim[0]; // OFM num size
    int oC = _otinfo[0].dim[1]; // OFM ch size
    int oH = _otinfo[0].dim[2]; // OFM height size
    int oW = _otinfo[0].dim[3]; // OFM width size

    /* Calculates each processing ratio of cpu/gpu
     */
    int total_ratio = thread_ratio_cpu + thread_ratio_gpu;
    int och_by_cpu = (oC * thread_ratio_cpu) / total_ratio;
    int och_by_gpu = oC - och_by_cpu;

#if LOG_LEVEL > 1
    logfs << "kernel_nn_conv::create_kernel_args_list() debug\n";
    logfs << "oC = " << oC << "\toch_by_cpu = " << och_by_cpu\
          << "\toch_by_gpu = " << och_by_gpu << "\n";
#endif

    int och_base_addr_cpu = 0;
    int och_base_addr_gpu = (oW * oH) * och_by_cpu;
    int wgt_base_addr_cpu = 0;
    int wgt_base_addr_gpu = (_kernel_size_w * _kernel_size_h) * iC * och_by_cpu;
    int bias_base_addr_cpu = 0;
    int bias_base_addr_gpu = och_by_cpu;

    /* Creates kernel argument list for CPU
     */
    int och_per_Cthread = (och_by_cpu + (thread_num_cpu-1)) / thread_num_cpu;
    int och_offset_per_Cthread = oN * (oH * oW) * och_per_Cthread * sizeof(float);
    int wgt_offset_per_Cthread = (_kernel_size_h * _kernel_size_w) * iC * och_per_Cthread;
    int bias_offset_per_Cthread = och_per_Cthread;

    int oC_org = och_by_cpu;
    int arg_idx = 0;
    for(int i = 0; arg_idx < thread_num_cpu; arg_idx++, i++) {
        KernelArgs_t arg;
        tileinfo_t iti, oti;

        iti = _itinfo[0];
        oti = _otinfo[0];
        // set output tile channel size
        oC_org -= och_per_Cthread;
        oti.dim[1] = (oC_org >= 0) ? och_per_Cthread : (och_per_Cthread + oC_org);
        // set output tile memory address
        oti.mem_addr = oti.mem_addr + och_base_addr_cpu + (och_offset_per_Cthread * i);
        arg.iti    = iti;
        arg.oti    = oti;

        arg.output = (float*) (_output + och_base_addr_cpu + (och_offset_per_Cthread * i));
        arg.input  = (float*) _input;
        arg.weight = _weight + wgt_base_addr_cpu  + (wgt_offset_per_Cthread * i);
        arg.bias   = _bias   + bias_base_addr_cpu + (bias_offset_per_Cthread * i);

        kernel_args_list.push_back( arg );
        cpu_thread_arg_index.push_back( arg_idx );
    }


#if 0
    logfs << "---------------- Kernel_args list ---------------------\n";
    logfs << "thread_num_cpu   = " << thread_num_cpu << "\n";
    logfs << "thread_num_gpu   = " << thread_num_gpu << "\n";
    logfs << "thread_ratio_cpu = " << thread_ratio_cpu << "\n";
    logfs << "thread_ratio_gpu = " << thread_ratio_gpu << "\n";
    int j = 0;
    for(j = 0; j < thread_num_cpu ; j++) {
        auto a = kernel_args_list[ j ];
        logfs << "+++++ CPU thread info [" << j << "] +++++\n";
        logfs << "output = 0x" << std::setw(8) << std::setfill('0') << std::hex \
              << a.output << std::setfill(' ') << std::dec << "\n";
        logfs << "input  = 0x" << std::setw(8) << std::setfill('0') << std::hex \
              << a.input  << std::setfill(' ') << std::dec << "\n";
        logfs << "weight = 0x" << std::setw(8) << std::setfill('0') << std::hex \
              << a.weight << std::setfill(' ') << std::dec << "\n";
        logfs << "bias   = 0x" << std::setw(8) << std::setfill('0') << std::hex \
              << a.bias   << std::setfill(' ') << std::dec << "\n";
        logfs << "it.addr= 0x" << std::setw(8) << std::setfill('0') << std::hex \
              << a.iti.mem_addr << std::setfill(' ') << std::dec << "\n";
        logfs << "it.dim = [";
        for(unsigned int k = 0; k < a.iti.dim.size()-1; k++)
            logfs << a.iti.dim[k] << ",";
        logfs << a.iti.dim.back() << "]\n";
        logfs << "ot.addr= 0x" << std::setw(8) << std::setfill('0') << std::hex \
              << a.oti.mem_addr << std::setfill(' ') << std::dec << "\n";
        logfs << "ot.dim = [";
        for(unsigned int k = 0; k < a.oti.dim.size()-1; k++)
            logfs << a.oti.dim[k] << ",";
        logfs << a.oti.dim.back() << "]\n";
    }
#endif


    /* Creates kernel argument list for GPU
     */
    if( thread_ratio_gpu == 0 )
        return;
    int och_per_Gthread = (och_by_gpu + (thread_num_gpu-1)) / thread_num_gpu;
    int och_offset_per_Gthread = oN * (oH * oW) * och_per_Gthread * sizeof(float);
    int wgt_offset_per_Gthread = (_kernel_size_h * _kernel_size_w) * iC * och_per_Gthread;
    int bias_offset_per_Gthread = och_per_Gthread;

    oC_org = och_by_gpu;
    int thread_num_total = thread_num_cpu + thread_num_gpu;
    for(int i = 0; arg_idx < thread_num_total; arg_idx++, i++) {
        KernelArgs_t arg;
        tileinfo_t iti, oti;

        iti = _itinfo[0];
        oti = _otinfo[0];
        // set output tile channel size
        oC_org -= och_per_Gthread;
        oti.dim[1] = (oC_org >= 0) ? och_per_Gthread : (och_per_Gthread + oC_org);
        // set output tile memory address
        oti.mem_addr = oti.mem_addr + och_base_addr_gpu + (och_offset_per_Gthread * i);
        arg.iti    = iti;
        arg.oti    = oti;

        arg.output = (float*) (_output + oti.mem_addr);
        arg.input  = (float*) _input;
        arg.weight = _weight + wgt_base_addr_gpu  + (wgt_offset_per_Gthread * i);
        arg.bias   = _bias   + bias_base_addr_gpu + (bias_offset_per_Gthread * i);

        kernel_args_list.push_back( arg );
        gpu_thread_arg_index.push_back( arg_idx );
    }

#if 0
    j = thread_num_cpu;
    for(j = 0; j < thread_num_total; j++) {
        auto a = kernel_args_list[ j ];
        logfs << "+++++ GPU thread info [" << j << "] +++++\n";
        logfs << "output = 0x" << std::setw(8) << std::setfill('0') << std::hex \
              << a.output << std::setfill(' ') << std::dec << "\n";
        logfs << "input  = 0x" << std::setw(8) << std::setfill('0') << std::hex \
              << a.input  << std::setfill(' ') << std::dec << "\n";
        logfs << "weight = 0x" << std::setw(8) << std::setfill('0') << std::hex \
              << a.weight << std::setfill(' ') << std::dec << "\n";
        logfs << "bias   = 0x" << std::setw(8) << std::setfill('0') << std::hex \
              << a.bias   << std::setfill(' ') << std::dec << "\n";
        logfs << "it.addr= 0x" << std::setw(8) << std::setfill('0') << std::hex \
              << a.iti.mem_addr << std::setfill(' ') << std::dec << "\n";
        logfs << "it.dim = [";
        for(unsigned int k = 0; k < a.iti.dim.size()-1; k++)
            logfs << a.iti.dim[k] << ",";
        logfs << a.iti.dim.back() << "]\n";
        logfs << "ot.addr= 0x" << std::setw(8) << std::setfill('0') << std::hex \
              << a.oti.mem_addr << std::setfill(' ') << std::dec << "\n";
        logfs << "ot.dim = [";
        for(unsigned int k = 0; k < a.oti.dim.size()-1; k++)
            logfs << a.oti.dim[k] << ",";
        logfs << a.oti.dim.back() << "]\n";
    }
#endif


    return;
}

void Kernel_nn_conv::create_threads(void)
{
    /* Creates CPU kernel threads
     */
    for(auto index : cpu_thread_arg_index)
        thread_list.push_back( thread(cpu_kernel_thread_wrapper, this, index) );

    /* Creates GPU kernel threads
     */
    for(auto index : gpu_thread_arg_index)
        thread_list.push_back( thread(gpu_kernel_thread_wrapper, this, index) );

    return;
}

void Kernel_nn_conv::run_kernel(void) 
{
    cpu_kernel_conv3d( 0 );
}

void Kernel_nn_conv::gpu_kernel_conv3d(
    int args_list_index
)
{
}

void Kernel_nn_conv::cpu_kernel_conv3d(
    int args_list_index
) {

    auto& args = kernel_args_list[ args_list_index ];
    int N = args.iti.dim[0];
    int C = args.iti.dim[1];
    int H = args.iti.dim[2];
    int W = args.iti.dim[3];
    int O = args.oti.dim[1];
    int KW = _kernel_size_w;
    int KH = _kernel_size_h;
    int SW = _stride_size_w;
    int SH = _stride_size_h;
    int PW = _pad_size_w;
    int PH = _pad_size_h;

    float *output = args.output;
    float *input  = args.input;
    float *weight = args.weight;
    float *bias   = args.bias;

    if( _relu_op_en ) {
        for(int n = 0 ; n < N ; n++) {
        float *bp = bias;
        for(int o = 0 ; o < O ; o++) {

            /* IFM loop (3D)
             */
            for(int h = -PH ; h < (H+PH) ; h += SH) {
                for(int w = -PW ; w < (W+PW) ; w += SW) {

                    /* Kernel loop
                     */
                    if( (w+KW) <= (W+PW) && (h+KH) <= (H+PH) ) {
                        float sum = 0;
                        for(int c = 0 ; c < C ; c++) {
                            for(int kh = 0 ; kh < KH ; kh++) {
                                if( (h+kh) >= 0 && (h+kh) < H ) {
                                    float *inp = input + (W*(h+kh)) + (W*H*c) + w + (C*H*W*n);
                                    float *wgt = weight + (KW*kh) + (KW*KH*c) + (KW*KH*C*o);
                                    for(int kw = 0 ; kw < KW ; kw++) {
                                        if( (w+kw) >= 0 && (w+kw) < W )
                                            sum += (*inp) * (*wgt);
                                        inp++;
                                        wgt++;
                                    }
                                }
                            }
                        }
                        sum += *bp;
                        *output++ = (sum < 0) ? 0 : sum;    // _relu_op_en = true case
                    }
                }
            }
            bp++;
        }
        }
    }
    else {
        for(int n = 0 ; n < N ; n++) {
        float *bp = bias;
        for(int o = 0 ; o < O ; o++) {

            /* IFM loop (3D)
             */
            for(int h = -PH ; h < (H+PH) ; h += SH) {
                for(int w = -PW ; w < (W+PW) ; w += SW) {

                    /* Kernel loop
                     */
                    if( (w+KW) <= (W+PW) && (h+KH) <= (H+PH) ) {
                        float sum = 0;
                        for(int c = 0 ; c < C ; c++) {
                            for(int kh = 0 ; kh < KH ; kh++) {
                                if( (h+kh) >= 0 && (h+kh) < H ) {
                                    float *inp = input + (W*(h+kh)) + (W*H*c) + w + (C*H*W*n);
                                    float *wgt = weight + (KW*kh) + (KW*KH*c) + (KW*KH*C*o);
                                    for(int kw = 0 ; kw < KW ; kw++) {
                                        if( (w+kw) >= 0 && (w+kw) < W )
                                            sum += (*inp) * (*wgt);
                                        inp++;
                                        wgt++;
                                    }
                                }
                            }
                        }
                        *output++ = sum + *bp;
                    }
                }
            }
            bp++;
        }
        }
    }
}

}
