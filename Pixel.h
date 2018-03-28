#ifndef PIXEL_h
#define PIXEL_h
#include <Adafruit_NeoPixel.h>

class Pixel {
public:
  bool blinking = false;
  bool scanning = false;
  int selectedIndex = -1;
  int step = 1;
  int totalPixels;
  int color;
  int number = 0;

  Pixel (uint8_t pin, int numPixels, int txRate) {
    init(pin, numPixels, txRate, NEO_GRB);
  }; 
  
  Pixel (uint8_t pin, int numPixels, int txRate, int colorOrder) {
    init(pin, numPixels, txRate, colorOrder);
  }; 

  void init (uint8_t pin, int numPixels, int txRate, int colorOrder) {
    TXRATE = txRate;
    totalPixels = numPixels;
    number = numPixels; 
    pixels = Adafruit_NeoPixel(numPixels, pin, colorOrder + NEO_KHZ800);    
    pixels.begin();    
    pixels.setBrightness (80);    
    timeout = 1;
  }; 

  void plus() {
    if (number < totalPixels) {
       number = number + 1;
    }
    selectedIndex = -1;
    scanning = false;
  }
  
  void minus () {
    if (number > 0) {
       number = number - 1;
    }
    selectedIndex = -1;
    scanning = false;
  }
  
  void scan () {
     scanning = !scanning;
     selectedIndex = -1;
     blinking = false;     
  }
  
  void blink () {
    blinking = !blinking;
    selectedIndex = -1;
    scanning = false;
  }
  
  void red () {
     color = 0;
  }
  
  void green() {
     color = 1;
  }
  
  void blue() {
     color = 2;
  } 
  
  void selectPixel (int which, int rgb ) {
    int red = 0;
    int green = 0;
    int blue = 0;
    switch (rgb) {
       case 0: 
         red = 250;
         break;
       case 1:
         green = 250;
         break;
       case 2:
         blue = 250;
         break;          
    }
    pixels.setPixelColor (which,pixels.Color (red,green,blue));                
  }
    
  void selectOne () {
    if (selectedIndex != -1) { 
       for (int i=0; i<totalPixels; i++) {
          selectPixel (i,-1);
       }      
       selectPixel (selectedIndex,color);   
       pixels.show();
    }   
  }
  
  void select (int index) {
    selectedIndex = index;
    scanning = false;
    blinking = false;
  }
    
  void setPixels (int rgb) {
    for (int i=0; i<totalPixels; i++) {
       selectPixel (i,-1);
    }          
    for (int i=0; i<number; i++) {
       selectPixel (i,rgb);
    }   
    
    pixels.show();
  }  
  
  void update() {
    if (timeout) { 
       if (millis() > timeout) { 
          if (scanning) {
             selectedIndex = selectedIndex + step;
             if (selectedIndex >= (totalPixels-1) ) {
                step = -1;
                selectedIndex = totalPixels - 1;
             } else if (selectedIndex <= 0) {
                selectedIndex = 0;
                step = 1;
             }              
          }
          if (selectedIndex != -1) {
             selectOne ();
          } else if (blinking) {
             if (onOff) { 
                setPixels (-1);
             } else {
                setPixels (color);
             } 
             onOff = 1 - onOff;
          } else {
             setPixels (color);
          }   
          timeout = millis() + TXRATE;
       }
    }
  } 
  
  void showPixelInfo() {
    Serial.print ( "selectedIndex: " );
    Serial.print ( selectedIndex );
    Serial.print ( ", number: " );
    Serial.print ( number );
    Serial.print ( ", color: " );
    Serial.print ( color );
    Serial.print ( ", blinking: " );
    Serial.print ( blinking );
    Serial.print ( ", scanning: " );
    Serial.println ( scanning );
  }  
    
private:  
  unsigned long timeout;
  int TXRATE;
  Adafruit_NeoPixel pixels;  
  int onOff = 1;
};
#endif