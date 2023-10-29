#include <TM1637Display.h>    

#define CLK 2   
#define DIO 3   
#define IR_DETECTOR 4   


bool RUN = false;
int MIN = 0;
int SEC = 0;
int HALFSEC = 0;

unsigned long LAST_COUNT_TIME, GET_COUNT_TIME;

TM1637Display display(CLK, DIO);

void setup() {
  pinMode(IR_DETECTOR, INPUT);
  display.setBrightness(0x0f);
  display.clear();
  
}

void loop() {
  if(digitalRead(IR_DETECTOR) == LOW){        
    RUN = !RUN;                    
    delay(100);                     
    LAST_COUNT_TIME = millis();     
  }

  
  if(RUN == true){
    delay(100);
    MAIN_COUNT();
  }

  
  else{
    RESET_PROGRAM();
  }
}


void MAIN_COUNT(){
  GET_COUNT_TIME = millis();
  if(GET_COUNT_TIME - LAST_COUNT_TIME >= 500){
    HALFSEC++;
    
    if(HALFSEC%2 == 0){
      SEC++;
      if(SEC > 59){
        SEC = SEC - 60;
        MIN++;
      }
      display.showNumberDec(MIN, true, 2, 0);
      display.showNumberDec(SEC, true, 2, 2);
    }

    if(HALFSEC%2 == 1){
      display.showNumberDecEx(MIN, 0b01000000, true, 2, 0);
      display.showNumberDecEx(SEC, 0b01000000, true, 2, 2);
    }
    
    LAST_COUNT_TIME = millis();
  }

  if(MIN == 3){
    delay(100);
    RESET_PROGRAM();
  }
}


void RESET_PROGRAM(){
  RUN = false;
  delay(250);
  display.clear();
  HALFSEC = 0;
  SEC = 0;
  MIN = 0;
}