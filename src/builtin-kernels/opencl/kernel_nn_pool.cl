
// =================================================================================================
// Project: 
// 
//
// File information:
// Institution.... 
// Author......... 
// Changed at..... 
// License........ 
// Tab-size....... 
// Line length.... 
//
// =================================================================================================
//
//
// =================================================================================================

//#if KERNEL == 1

// =================================================================================================

__kernel void maxpool_gpu_kernel(const int col_height, const int col_h, const int col_w, const int img_c, const int kernel_size, 
        __global float * data_col, __global float * max_pool_out)
{
    const int row = get_local_id(0);
    const int col = get_local_id(1);
    const int globalRow = get_global_id(0);
    const int globalCol = get_global_id(1);

    int img_n = col_height / (col_h*col_w);
    int in_step = kernel_size * img_c;
    int in_size = kernel_size * img_c*col_h*col_w;
    int out_step = img_c;
    int out_size = img_c * col_h*col_w;
    int out_t_step = col_h*col_w;

    for(int iter_n =0; iter_n<img_n ;iter_n++)
    {
        float max_val = -1.0;
        for(int iter_row =0; iter_row < kernel_size;iter_row++) {
            float tmp_val = data_col[globalRow*in_step + globalCol*kernel_size+iter_row+iter_n*in_size];
            if(max_val < tmp_val)
            max_val =tmp_val;

        }

        barrier(CLK_LOCAL_MEM_FENCE);
        int col_index = globalRow*out_step+globalCol;

        int row_t = col_index/out_step;
        int col_t = col_index%out_step;
        max_pool_out[col_t*out_t_step + row_t + iter_n*out_size] = max_val;

        barrier(CLK_LOCAL_MEM_FENCE);
    }
}


//#endif


/*
// Simple transpose kernel for a P * Q matrix
__kernel void transpose(const int P, const int Q,
                        const __global float* input,
                        __global float* output) {
    
    // Thread identifiers
    const int tx = get_local_id(0);
    const int ty = get_local_id(1);
    const int ID0 = get_group_id(0)*TRANSPOSEX + tx; // 0..P
    const int ID1 = get_group_id(1)*TRANSPOSEY + ty; // 0..Q

    // Set-up the local memory for shuffling
    __local float buffer[TRANSPOSEX][TRANSPOSEY];

    // Swap the x and y coordinates to perform the rotation (coalesced)
    if (ID0 < P && ID1 < Q) {
        buffer[ty][tx] = input[ID1*P + ID0];
    }

    // Synchronise all threads
    barrier(CLK_LOCAL_MEM_FENCE);

    // We don't have to swap the x and y thread indices here,
    // because that's already done in the local memory
    const int newID0 = get_group_id(1)*TRANSPOSEY + tx;
    const int newID1 = get_group_id(0)*TRANSPOSEX + ty;

    // Store the transposed result (coalesced)
    if (newID0 < Q && newID1 < P) {
        output[newID1*Q + newID0] = buffer[tx][ty];
    }
}
*/

// =================================================================================================
/*
// Pad the P * Q matrix with zeroes to form a P_XL * Q_XL matrix
__kernel void paddingAddZeroes(const int P, const int Q,
                               const __global float* input,
                               const int P_XL, const int Q_XL,
                               __global float* output) {
    
    // Thread identifiers
    const int tx = get_group_id(0)*PADDINGX + get_local_id(0); // 0..P_XL in blocks of PADDINGX
    const int ty = get_group_id(1)*PADDINGY + get_local_id(1); // 0..Q_XL in blocks of PADDINGY

    // Check whether we are within bounds of the XL matrix
    if (tx < P_XL && ty < Q_XL) {

        // Copy the input or pad a zero
        float value;
        if (tx < P && ty < Q) {
            value = input[ty*P + tx];
        }
        else {
            value = 0.0f;
        }

        // Store the result
        output[ty*P_XL + tx] = value;
    }
}
*/
// =================================================================================================
/*
// Remove padded values from a P_XL * Q_XL matrix to form a P * Q matrix
__kernel void paddingRemoveZeroes(const int P_XL, const int Q_XL,
                                  const __global float* input,
                                  const int P, const int Q,
                                  __global float* output) {
    
    // Thread identifiers
    const int tx = get_group_id(0)*PADDINGX + get_local_id(0); // 0..P in blocks of PADDINGX
    const int ty = get_group_id(1)*PADDINGY + get_local_id(1); // 0..Q in blocks of PADDINGY


    // Only store the result if within P * Q bounds
    if (tx < P && ty < Q) {
        output[ty*P + tx] = input[ty*P_XL + tx];
    }
}
*/





// =================================================================================================


// =================================================================================================


