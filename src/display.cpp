#include <display.hpp>
#include <global_var.hpp>

// #include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET 16    // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

/**
 * 初始化SSD306
*/
Adafruit_SSD1306 Display_INIT()
{
    TwoWire twi = TwoWire(1); // our own TwoWire instance on bus 1
    Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &twi, OLED_RESET);
    twi.begin(displaySDA, displaySCL); // Needs to come before display.begin is used
    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
    {
        // Address 0x3C for 128x32
        Serial.println(F("SSD1306 allocation failed"));
        // for(;;); // Don't proceed, loop forever
    }
    display.clearDisplay();
    display.setTextSize(3);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println("hello");
    display.println("display..");
    display.display();
    delay(500);

    return display;
}

void Display_WRITE(Adafruit_SSD1306 display, float et, float bt, float ror, int min,int second)
{
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);




    display.print("ET ");
    display.println(et);

    display.print("BT ");
    display.println(bt);

    display.print("ROR ");
    display.println(ror * 60);

    // display.print("TIME ");
    display.print(min);
    display.print("m");
    display.print(second);
    display.println("s");
    display.display();
}




class SCREEN {
    public:
        SCREEN() { 
          display = Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
        } 
        void init();
        void drawAPmode();
        void drawError(String text);
        void drawText(String text);
        void drawHotTopmode(String text);
    private:
        Adafruit_SSD1306 display;
};

void SCREEN::init() {
    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS, OLED_RESET, true)) {
    Serial.println(F("SSD1306 allocation failed"));
  }
}

void SCREEN::drawAPmode(){
  display.clearDisplay();
  display.setTextSize(2);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner
  display.println(F("AP Mode"));
  display.setTextSize(1);
  char text[64];
  sprintf(&text[0], "\nSSID:%s\nPassword:%s", DeviceId, APPassword);
  display.println(text);
  display.display();
}


void SCREEN::drawError(String text){
  display.clearDisplay();
  display.setTextSize(2);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner
  display.println(text);
  display.display();
}


void SCREEN::drawText(String text){
  display.clearDisplay();
  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner
  display.println(text);
  display.display();
}

String IpAddress2String(const IPAddress& ipAddress){
  return String(ipAddress[0]) + String(".") +\
  String(ipAddress[1]) + String(".") +\
  String(ipAddress[2]) + String(".") +\
  String(ipAddress[3])  ;
}

void SCREEN::drawHotTopmode(String stat){
  IPAddress ip = WiFi.localIP();
  String ws_msg = "ws://"+IpAddress2String(ip)+"/ws";
  
  display.clearDisplay();
  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner
  display.println(ws_msg);
  display.println(stat);
  display.display();
}