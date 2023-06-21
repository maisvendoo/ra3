#include    "ra3-middle.h"

#include    <QDir>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3Middle::initBrakesEquipment()
{
    // Тормозная магистраль
    double volume_bp = length * 0.0343 * 0.0343 * Physics::PI / 4.0;
    brakepipe = new Reservoir(volume_bp);
    brakepipe->setLeakCoeff(3e-6);

    // Блок тормозного оборудования БТО-092
    brake_module = new BTO092();
    brake_module->setCustomConfigDir(config_dir);
    brake_module->read_custom_config(config_dir + QDir::separator() + "bto092");

    // Тройник на питание СТ
    pb_split = new PneumoSplitter();
    pb_split->read_config("pneumo-splitter");

    // Тормозные рычажные передачи
    brake_mech[TROLLEY_FWD] = new RA3BrakeMech(NUM_AXIS_PER_TROLLEY);
    brake_mech[TROLLEY_FWD]->read_custom_config(
                config_dir + QDir::separator() + "brake-mech");
    brake_mech[TROLLEY_FWD]->setWheelRadius(rk[0]);
    brake_mech[TROLLEY_FWD]->setEffFricRadius(rk[0]);

    brake_mech[TROLLEY_BWD] = new RA3BrakeMech(NUM_AXIS_PER_TROLLEY);
    brake_mech[TROLLEY_BWD]->read_custom_config(
                config_dir + QDir::separator() + "brake-mech");
    brake_mech[TROLLEY_BWD]->setWheelRadius(rk[NUM_AXIS_PER_TROLLEY]);
    brake_mech[TROLLEY_BWD]->setEffFricRadius(rk[NUM_AXIS_PER_TROLLEY]);

    // Концевые краны тормозной магистрали
    anglecock_bp_fwd = new PneumoAngleCock();
    anglecock_bp_fwd->read_config("pneumo-anglecock-BP");
    anglecock_bp_fwd->setPipeVolume(volume_bp);

    anglecock_bp_bwd = new PneumoAngleCock();
    anglecock_bp_bwd->read_config("pneumo-anglecock-BP");
    anglecock_bp_bwd->setPipeVolume(volume_bp);

    // Рукава тормозной магистрали
    hose_bp_fwd = new PneumoHose();
    hose_bp_fwd->read_config("pneumo-hose-BP");
    forward_connectors.push_back(hose_bp_fwd);

    hose_bp_bwd = new PneumoHose();
    hose_bp_bwd->read_config("pneumo-hose-BP");
    backward_connectors.push_back(hose_bp_bwd);
}
