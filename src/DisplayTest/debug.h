#ifndef DEBUG_H
#define DEBUG_H
/** Debug output */

  #define DEBUG
  
  #ifdef DEBUG
    #define DEBUG_INIT Serial.begin(115200);
    #define DEBUG_PRINT(val) Serial.print(val)
    #define DEBUG_PRINTF(val, format) Serial.print(val, format)
    #define DEBUG_PRINTLN(val) Serial.println(val)
    #define DEBUG_PRINTLNF(val, format) Serial.println(val, format)
  #else
    #define DEBUG_INIT
    #define DEBUG_PRINT(val) 
    #define DEBUG_PRINTF(val, format) 
    #define DEBUG_PRINTLN(val) 
    #define DEBUG_PRINTLNF(val, format) 
  #endif

  #warning included 

#endif
