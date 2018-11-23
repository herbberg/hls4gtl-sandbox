#include "top.h"

void top(const comb_input_type obj, const requirement_type req, ap_uint<1> cond_out)
{
#pragma HLS INTERFACE ap_none port=obj
#pragma HLS INTERFACE ap_none port=req
#pragma HLS INTERFACE ap_ctrl_none port=return

    cond_out = gtl::condition::comb<gtl::cut::req[0].comb_obj, gtl::object::req[0].comb_obj, req[0].n_cuts, req[0].slice[0], req[0].slice[1]>(req, obj.req[0].comb_obj);
    
}
