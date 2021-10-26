#ifndef     BLOK_H
#define     BLOK_H

#include    "device.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
enum
{
    WHITE_LAMP = 0,
    RED_LAMP = 1,
    RED_YELLOW_LAMP = 2,
    YELLOW_LAMP = 3,
    GREEN_LAMP1 = 4,
    GREEN_LAMP2 = 5,
    GREEN_LAMP3 = 6,
    GREEN_LAMP4 = 7,
};

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class BLOK : public Device
{
public:

    BLOK(QObject *parent = Q_NULLPTR);

    ~BLOK();

    void step(double t, double dt) override;

   /// Прием кода АЛСН
   void setAlsnCode(int code_alsn)
   {
       old_code_alsn = this->code_alsn;
       this->code_alsn = code_alsn - 1;
   };

   /// Прием состояния РБ
   void setRBstate(bool state) { state_RB = state; };

   /// Прием состояния РБС
   void setRBSstate(bool state) { state_RBS = state; };

   /// Прием скорости от ДПС
   void setVelocity(double v) { v_kmh = v * Physics::kmh; }

   void setKeyEPK(bool key_epk) { this->key_epk = key_epk; }

   /// Выдача состояния цепи удерживающей катушки ЭПК
   bool getEPKstate() { return epk_state.getState(); };

   /// Получить состояние лампы локомотивного световора
   float getLampState(size_t lamp_idx)
   {
       if (lamp_idx < lamps.size())
           return lamps[lamp_idx];

        return 0.0f;
   }

   double getCurrentSpeedLimit() const { return 120.0; }

   double getNextSpeedLimit() const { return 120.0; }

   bool isDisplayON() const { return is_dislplay_ON; }

   void setVoltage(double U_pow) { this->U_pow = U_pow; }

private:

   double U_pow;

   int code_alsn;

   int old_code_alsn;

   bool state_RB;

   bool state_RBS;

   bool state_EPK;

   double v_kmh;

   bool key_epk;

   bool is_dislplay_ON;

   enum
   {
       NUM_LAMPS = 8
   };

   Timer *safety_timer;

   std::array<float, NUM_LAMPS> lamps;

   Trigger epk_state;

   Trigger is_red;

   void preStep(state_vector_t &Y, double t) override;

   void ode_system(const state_vector_t &Y,
                   state_vector_t &dYdt,
                   double t) override;

   void load_config(CfgReader &cfg) override;

   void alsn_process(int code_alsn);

private slots:

   void onSafetyTimer();
};

#endif // BLOK_H
