#include    "ra3-middle.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3Middle::initSME()
{
    // Инициализация связей системы многих единиц (СМЕ)
    sme_fwd = new RA3SME();
    sme_fwd->setCustomConfigDir(config_dir);
    forward_connectors.push_back(sme_fwd);

    sme_bwd = new RA3SME();
    sme_bwd->setCustomConfigDir(config_dir);
    backward_connectors.push_back(sme_bwd);
}
