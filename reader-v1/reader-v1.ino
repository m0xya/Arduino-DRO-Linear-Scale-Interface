const int pinA = 2;
const int pinB = 3;

volatile bool A = false;
volatile bool B = false;
volatile bool updated = false;
volatile int counter = 0;
volatile int phaN = 0;
volatile int phaO = 0;

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
    updated = false;
    Serial.println(String(counter));
  }
}

void trig()
{
  A = digitalRead(pinA);
  B = digitalRead(pinB);

  phaN = A ? (B ? 3 : 4) : (B ? 2 : 1);

  if (phaO == 4 && phaN == 1)
  {
    counter -= 1;
  }
  else if (phaO == 1 && phaN == 4)
  {
    counter += 1;
  }
  else if (phaN > phaO)
  {
    counter -= 1;
  }
  else if (phaN < phaO)
  {
    counter += 1;
  }

  phaO = phaN;
  updated = true;
}