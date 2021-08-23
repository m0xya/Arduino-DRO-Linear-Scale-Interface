#include <LedControl.h>

const int pinA = 2, pinB = 3, phaseLookup[] = {0,-1,1,-1,1,0,-1,-1,-1,1,0,1,1,1,-1,0};

volatile bool A = false, B = false, updated = false;
volatile int phase = 0;
volatile long counter = 0;

LedControl lc=LedControl(12,11,10,1);

void printNumber(long v)
{  
    int ones;
    int tens;
    int hundreds;
    int thousands;
    int ten_thou;
    int hundred_thou;
    int millions;

    boolean negative=false;
    
    if(v<0)
    {  
        negative=true;
        v=v*-1;
    }
    
    ones=v%10;
    v=v/10;
    
    tens=v%10;
    v=v/10;
    
    hundreds=v%10;
    v=v/10;
    
    thousands=v%10;
    v=v/10;
    
    ten_thou=v%10;
    v=v/10;
    
    hundred_thou=v%10;
    v=v/10;
    
    millions=v;
    
    if(negative)
    {
        lc.setChar(0,7,'-',false);
    } 
    else
    {
        lc.setChar(0,7,' ',false);  
    }

    lc.setDigit(0,6,(byte)millions,false);
    lc.setDigit(0,5,(byte)hundred_thou,false);
    lc.setDigit(0,4,(byte)ten_thou,false);
    lc.setDigit(0,3,(byte)thousands,false);
    lc.setDigit(0,2,(byte)hundreds,false);
    lc.setDigit(0,1,(byte)tens,false); 
    lc.setDigit(0,0,(byte)ones,false); 
} 

void setup()
{
  Serial.begin(115200);

  lc.shutdown(0,false);
  lc.setIntensity(0,8);
  lc.clearDisplay(0);
  
  pinMode(pinA, INPUT);
  pinMode(pinB, INPUT);
  
  attachInterrupt(digitalPinToInterrupt(pinA), trig, CHANGE);
  attachInterrupt(digitalPinToInterrupt(pinB), trig, CHANGE);
}

void loop()
{
  if (updated)
  {
    updated = false;
    Serial.println(String(counter));
    printNumber(counter);
  }
}

void trig()
{
  A = digitalRead(pinA);
  B = digitalRead(pinB);

  phase <<= 1;
  phase |= A;
  phase <<= 1;
  phase |= B;
  phase &= 0xF;

  counter += phaseLookup[phase];

  updated = true;
}