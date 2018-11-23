#ifndef gtl_condition_comb_h
#define gtl_condition_comb_h

#include <cstdio>

namespace gtl {
namespace condition {
   
template<typename T, size_t X, size_t Y>
void init_2d(T data[X][Y], const T value)
{
    for (size_t i = 0; i < X; ++i)
#pragma HLS UNROLL
        for (size_t j = 0; j < Y; ++j)
#pragma HLS UNROLL
            data[i][j] = value;
}

template<typename T1, typename T2, typename T3, size_t NREQ, size_t SLICE_MIN, size_t SLICE_MAX>
void comb_matrix(T1 data[MAX_REQ][SLICE_MAX-SLICE_MIN+1], const T2 requirements[MAX_REQ], const T3 objects[SLICE_MAX-SLICE_MIN+1])
{
#pragma HLS INTERFACE ap_ctrl_none port=data
#pragma HLS ARRAY_PARTITION variable=requirements complete dim=0
#pragma HLS ARRAY_PARTITION variable=objects complete dim=0
#pragma HLS ARRAY_PARTITION variable=data complete dim=0

    init_2d<ap_uint<1>, MAX_REQ, SLICE_MAX-SLICE_MIN+1>(data, 0x1);
    for (size_t i = 0; i < NREQ; i++)
#pragma HLS UNROLL
        for (size_t j = SLICE_MIN; j <= SLICE_MAX; j++)
#pragma HLS UNROLL
            data[i][j] = requirements[i].comp(objects[j]);
}

/* Workaround to trick HLS loop unrolling */
template<size_t SLICE_MIN, size_t SLICE_MAX>
ap_uint<1> comb_partial(const size_t i, const ap_uint<1> matrix[MAX_REQ][SLICE_MAX-SLICE_MIN+1])
{
#pragma HLS INTERFACE ap_ctrl_none port=return

    ap_uint<1> result = false;

    for (size_t j = SLICE_MIN; j <= SLICE_MAX; j++)
    {
#pragma HLS UNROLL
        for (size_t k = SLICE_MIN; k <= SLICE_MAX; k++)
        {
#pragma HLS UNROLL
            for (size_t l = SLICE_MIN; l <= SLICE_MAX; l++)
            {
#pragma HLS UNROLL
                if (j != i and k != i and k != j and l != i and l != j and l != k)
                {
                    result |= matrix[0][i] and matrix[1][j] and matrix[2][k] and matrix[3][l];
                }
            }
        }
    }
    
    return result;
}

/* Combination condition */
template<typename T1, typename T2, size_t NREQ, size_t SLICE_MIN, size_t SLICE_MAX>
ap_uint<1> comb(const T1 requirements[MAX_REQ], const T2 objects[MAX_OBJ])    
{
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS ARRAY_PARTITION variable=requirements complete dim=0
#pragma HLS ARRAY_PARTITION variable=objects complete dim=0

    ap_uint<1> result = false;
    ap_uint<1> matrix[MAX_REQ][SLICE_MAX-SLICE_MIN+1];

    // calculate result matrix
    comb_matrix<ap_uint<1>, T1, T2, NREQ, SLICE_MIN, SLICE_MAX>(matrix, requirements, objects);
    
    for (size_t i = SLICE_MIN; i <= SLICE_MAX; i++)
    {
#pragma HLS UNROLL
        result |= comb_partial<SLICE_MIN, SLICE_MAX>(i, matrix);
    }

    return result;
}

} // namespace condition
} // namespace gtl

#endif
