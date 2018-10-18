#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_TFTLCD.h> // Hardware-specific library
#include <TouchScreen.h>

#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
// optional
#define LCD_RESET A4


#define YP A1  // must be an analog pin, use "An" notation!
#define XM A2  // must be an analog pin, use "An" notation!
#define YM 7   // can be a digital pin
#define XP 6   // can be a digital pin

#define TS_MINX 150
#define TS_MINY 120
#define TS_MAXX 920
#define TS_MAXY 940

// For better pressure precision, we need to know the resistance
// between X+ and X- Use any multimeter to read it
// For the one we're using, its 300 ohms across the X plate
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 298);

// Assign human-readable names to some common 16-bit color values:
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
//#define ROZ     0xFD20
#define ROZ     0xFBE0
#define GRI     0xBDF7
// http://stackoverflow.com/questions/13720937/c-defined-16bit-high-color
// http://wiibrew.org/wiki/U16_colors

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);;

#define BOXSIZE 40
#define PENRADIUS 3
int oldcolor, currentcolor;
int ics;


#define BUTTONS A10

int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin

// the following variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 50;    // the debounce time; increase if the output flickers


void setup(void) {

   pinMode(BUTTONS, INPUT);
   Serial.begin(9600);
  
#ifdef DEBUG
  Serial.begin(9600);
  Serial.println(F("Paint!"));
#endif // DEBUG
  tft.reset();

  uint16_t identifier = tft.readID();

if(identifier == 0x9325) {
#ifdef DEBUG
    Serial.println(F("Found ILI9325 LCD driver"));
  } else if(identifier == 0x9328) {

    Serial.println(F("Found ILI9328 LCD driver"));
  } else if(identifier == 0x7575) {

    Serial.println(F("Found HX8347G LCD driver"));
  } else if(identifier == 0x9341) {

    Serial.println(F("Found ILI9341 LCD driver"));
  } else if(identifier == 0x8357) {

    Serial.println(F("Found HX8357D LCD driver"));
#endif // DEBUG
    } else {
    #ifdef DEBUG
    Serial.print(F("Unknown LCD driver chip: "));
    Serial.println(identifier, HEX);
    Serial.print(F("I try use ILI9341 LCD driver "));
    Serial.println(F("If using the Adafruit 2.8\" TFT Arduino shield, the line:"));
    Serial.println(F("  #define USE_ADAFRUIT_SHIELD_PINOUT"));
    Serial.println(F("should appear in the library header (Adafruit_TFT.h)."));
    Serial.println(F("If using the breakout board, it should NOT be #defined!"));
    Serial.println(F("Also if using the breakout, double-check that all wiring"));
    Serial.println(F("matches the tutorial."));
    #endif // DEBUG
    identifier = 0x9341;
  }


  tft.begin(identifier);

  tft.fillScreen(BLACK);
  tft.fillRect(0, 0, 320, 240, BLACK);
  tft.setRotation(3);
  tft.setCursor(30, 100);
  tft.setTextColor(RED);  tft.setTextSize(3);
  tft.println("LCD driver chip: ");
  tft.setCursor(100, 150);
  tft.setTextColor(BLUE);
  tft.println(identifier, HEX);
  pinMode(13, OUTPUT);
}

void loop(){
   int reading = analogRead(BUTTONS);
   Serial.println(reading);
   
   /*
   Not needed while getting the values.
   
   int tmpButtonState = LOW;             // the current reading from the input pin
   
   if(reading>BUTTON5LOW && reading<BUTTON5HIGH){
     //Read switch 5
     tmpButtonState = BUTTON5;
   }else if(reading>BUTTON4LOW && reading<BUTTON4HIGH){
     //Read switch 4
     tmpButtonState = BUTTON4;
   }else if(reading>BUTTON3LOW && reading<BUTTON3HIGH){
     //Read switch 3
     tmpButtonState = BUTTON3;
   }else if(reading>BUTTON2LOW && reading<BUTTON2HIGH){
     //Read switch 2
     tmpButtonState = BUTTON2;
   }else if(reading>BUTTON1LOW && reading<BUTTON1HIGH){
     //Read switch 1
     tmpButtonState = BUTTON1;
   }else{
     //No button is pressed;
     tmpButtonState = LOW;
   }

   // check to see if you just pressed the button 
   // (i.e. the input went from LOW to a buttonState),  and you've waited 
   // long enough since the last press to ignore any noise:  

   // If the switch changed, due to noise or pressing:
   if (tmpButtonState != lastButtonState) {
     // reset the debouncing timer
     lastDebounceTime = millis();
   } 

   if ((millis() - lastDebounceTime) > debounceDelay) {
     // whatever the reading is at, it's been there for longer
     // than the debounce delay, so take it as the actual current state:
     buttonState = tmpButtonState;
     Serial.println(buttonState);
   }

   // save the reading.  Next time through the loop,
   // it'll be the lastButtonState:
   lastButtonState = tmpButtonState;
   
   // set the LED using the state of the button for testing:
   switch(buttonState){
     case BUTTON1:
     digitalWrite(ledPin, buttonState>0);
     break;
     case BUTTON2:
     digitalWrite(ledPin, buttonState>0);
     break;
     case BUTTON3:
     digitalWrite(ledPin, buttonState>0);
     break;
     case BUTTON4:
     digitalWrite(ledPin, buttonState>0);
     break;
     case BUTTON5:
     digitalWrite(ledPin, buttonState>0);
     break;
   }
   */
}
