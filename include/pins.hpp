#ifndef _pins_h
#define _pins_h

// #define PIN_NUM_CS   15
// #define PIN_NUM_MISO 12
// #define PIN_NUM_MOSI 13
// #define PIN_NUM_CLK  14

//ssd1306
#define displaySDA 22
#define displaySCL 21

//buzzer
#define BUZZER_PIN  25     //蜂鳴器控制腳位

//ET MAX31865
#define thermoSO1  18 //SO1
#define thermoCS1  19 //CS1
#define thermoSCK1  23 //SCK1

//BT MAX31865
#define thermoSO2  15  //SO2
#define thermoCS2  4 //CS2
#define thermoSCK2  5 //SCK2

#define PIN_NUM_CS_ET   15 
#define PIN_NUM_CS_BT   2

#define PIN_NUM_MISO 12
#define PIN_NUM_MOSI 13
#define PIN_NUM_CLK  14

//Hottop
#define Pin_Fan  26 
#define Pin_Drop  27
#define Pin_Cooler  14
#define Pin_Drum  12
#define Pin_Heater  13

//For L293D
#define Pin_FAN_PWM  32
#define Pin_FAN_INPUT  33

//For Reset WiFi Button
#define btnWiFiResetPin  17  //TX2
//For DROP Button
#define btnDROPPin  16  //RX2


#endif