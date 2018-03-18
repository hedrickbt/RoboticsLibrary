#ifndef TextStream_h
#define TextStream_h

#include <SoftwareSerial.h>
class TextStream {
public:
  TextStream (SoftwareSerial * _textStream) {
      textStream = _textStream;
      textStream->begin (9600);
  };
  
  bool ready(void) { 
     bool rdy = textStream->available();
     return rdy;
  }
  
  bool available(void) { 
     return textStream->available();
  }
  
  String read(void) {
    char ch = lastCh;   
    if (!hasRead) {
      ch = textStream->read();
    }
    lastCh = ch;
    hasRead = true;
    return (String)ch;
  }    
      
  void update (void) {
     hasRead = false;
  };
    
private:
  
  char lastCh;
  bool hasRead = false;
  SoftwareSerial * textStream;  
};
#endif