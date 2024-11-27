#include    "ra3-head.h"
#include    <QTime>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void RA3HeadMotor::blokSignalsOutput(double t, double dt)
{
    Q_UNUSED(t);
    Q_UNUSED(dt);

    analogSignal[BLOK_DISPLAY_ON] = static_cast<float>(blok->isDisplayON());

    analogSignal[BLOK_RAILWAY_COORD] = static_cast<float>(blok->getRailCoord());
    int cur_time = QTime::currentTime().hour() * 3600 +
                   QTime::currentTime().minute() * 60 +
                   QTime::currentTime().second();
    analogSignal[BLOK_TIME] = static_cast<float>(cur_time);
    //analogSignal[BLOK_M_P_RDT_CASSETE] = 2.0f;
    //analogSignal[BLOK_ALS_CHANNEL] = 25.0f;
    //analogSignal[BLOK_TRACK_NUM] = 1.0f;
    analogSignal[BLOK_ACCELERATION] = static_cast<float>(blok->getAcceleration());
    //analogSignal[BLOK_SAUT_DISTANCE] = 0.0f;
    //analogSignal[BLOK_BREAKING_COEFF] = 0.0f;
    int is_vigilance = blok->isCheckVigilanse();
    int is_tskbm = true;
    int is_vigilance_tskbm = false;
    analogSignal[BLOK_VIGILANCE_TSKBM] = static_cast<float>(is_vigilance + is_tskbm * 10 + is_vigilance_tskbm * 100);
    analogSignal[BLOK_BP_PRESS] = static_cast<float>(brakepipe->getPressure());
    analogSignal[BLOK_BC_PRESS] = static_cast<float>(brake_mech[TROLLEY_BWD]->getBCpressure());
    analogSignal[BLOK_FL_PRESS] = static_cast<float>(main_reservoir->getPressure());
    analogSignal[BLOK_REVERS] = static_cast<float>(hydro_trans->getReversState());
    analogSignal[BLOK_SPEED] = static_cast<float>(blok->getVelocityKmh());
    analogSignal[BLOK_SPEED_CUR_LIMIT] = static_cast<float>(blok->getCurrentSpeedLimit());
    analogSignal[BLOK_SPEED_NEXT_LIMIT] = static_cast<float>(blok->getNextSpeedLimit());
    analogSignal[BLOK_TARGET_DIST] = static_cast<float>(blok->getTargetDistance());

    QString text = blok->getStationText();
    for (size_t i = 0; i < text.size(); ++i)
    {
        analogSignal[BLOK_STATION_SYMB1 + i] = static_cast<float>(text[i].unicode());
    }

    text = blok->getInfoText();
    for (size_t i = 0; i < text.size(); ++i)
    {
        analogSignal[BLOK_STRING_SYMB1 + i] = static_cast<float>(text[i].unicode());
    }    
}
