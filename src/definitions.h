#ifndef DEFINITIONS_H_
#define DEFINITIONS_H_

#include <cstddef> // for size_t

// const size_t N_ALGORITHMS = 512;
const size_t MAX_CALO_OBJ = 12;
const size_t MAX_MUON_OBJ = 8;
const size_t MAX_REQ = 4;
// const size_t N_BX_DATA = 5;

const size_t ORBIT_BX_SIZE = 3564;

enum comparison_mode_t
{
    GE,
    NE,
    EQ,
};

enum comb_obj_t
{
    eg,
    jet,
    tau,
    muon,
};

#endif
