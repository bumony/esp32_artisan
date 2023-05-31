#include <max31865.hpp>
#include <Adafruit_MAX31865.h>

class TEMP
{
public:
    TEMP()
    {
        thermo_et = Adafruit_MAX31865(PIN_NUM_CS_ET, PIN_NUM_MOSI, PIN_NUM_MISO, PIN_NUM_CLK);
        thermo_bt = Adafruit_MAX31865(PIN_NUM_CS_BT, PIN_NUM_MOSI, PIN_NUM_MISO, PIN_NUM_CLK);
    }
    void init();
    double getTemp(Adafruit_MAX31865 thermo);
    // double getDeltaTemp(Adafruit_MAX31865 thermo, double last_et);

private:
    Adafruit_MAX31865 thermo_et;
    Adafruit_MAX31865 thermo_bt;

    static double last_et;
    static double last_bt;


};

void TEMP::init()
{
    if (!(thermo_et.begin(MAX31865_2WIRE) && thermo_bt.begin(MAX31865_2WIRE)))
    {
        Serial.println(F("MAX31865 allocation failed"));
    }
};

double TEMP::getTemp(Adafruit_MAX31865 thermo)
{
    return thermo.temperature(RNOMINAL, RREF);
}

// // TODO 添加对时间的处理逻辑
// double TEMP::getDeltaTemp(Adafruit_MAX31865 thermo)
// {
//     static double last_t=getTemp(thermo);
//     static int last_time=0;

//     int now_time = millis() / 1000;
//     if (now_time - last_time == 1)
//     {
//         last_time = now_time;

//         double detla_t = getTemp(thermo) - last_t;
//         last_Bt = Bt;
//     };

//     return thermo.temperature(RNOMINAL, RREF);
// }