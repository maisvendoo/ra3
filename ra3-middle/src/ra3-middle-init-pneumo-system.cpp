#include    "ra3-middle.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3Middle::initPneumoSystem()
{
    main_res = new Reservoir(0.3);

    aux_res = new Reservoir(0.1);
}
