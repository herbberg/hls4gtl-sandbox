#ifndef hls4gtl_sandbox_types_h
#define hls4gtl_sandbox_types_h

#include "definitions.h"
#include <ap_int.h>

struct input_type
{
    typedef object::eg eg_type;
    typedef object::jet jet_type;
    typedef object::tau tau_type;
    typedef object::muon muon_type;
    typedef size_t size_type;
    
    const static size_type EG_SIZE = MAX_CALO_OBJ;
    const static size_type JET_SIZE = MAX_CALO_OBJ;
    const static size_type TAU_SIZE = MAX_CALO_OBJ;
    const static size_type MUON_SIZE = MAX_MUON_OBJ;

    eg_type eg[EG_SIZE];
    jet_type jet[JET_SIZE];
    tau_type tau[TAU_SIZE];
    muon_type muon[MUON_SIZE];
};

struct requirement_type
{
    typedef cut::eg eg_req_type;
    typedef cut::jet jet_req_type;
    typedef cut::tau tau_req_type;
    typedef cut::muon muon_req_type;
    typedef size_t size_type;
    
    const static size_type EG_REQ = MAX_REQ;
    const static size_type JET_REQ = MAX_REQ;
    const static size_type TAU_REQ = MAX_REQ;
    const static size_type MUON_REQ = MAX_REQ;

    eg_req_type eg[EG_REQ];
    jet_req_type jet[JET_REQ];
    tau_req_type tau[TAU_REQ];
    muon_req_type muon[MUON_REQ];
};

#endif
