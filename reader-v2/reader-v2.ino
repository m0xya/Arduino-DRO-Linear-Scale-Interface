const int pinA = 2, pinB = 3, phaseLookup[] = {0,-1,1,-1,1,0,-1,-1,-1,1,0,1,1,1,-1,0};

volatile bool A = false, B = false, updated = false;
volatile int counter = 0, phase = 0;

void setup()
{
  Serial.begin(115200);
  
  pinMode(pinA, INPUT);
  pinMode(pinB, INPUT);
  
  attachInterrupt(digitalPinToInterrupt(pinA), trig, CHANGE);
  attachInterrupt(digitalPinToInterrupt(pinB), trig, CHANGE);
}

void loop()
{
  if (updated)
  {
    Serial.println(String(counter));
    updated = false;
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