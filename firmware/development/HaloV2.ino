/*
Project Halo UK

Brought to you by Jabawoki
www.jabawoki.com
 */

int led1 = 9;           // the pin that the inner ring is attached to
int led2 = 10;           // the pin that the middle ring is attached to
int led3 = 11;           // the pin that the outer ring is attached to
int leds[] = {9,10,11};
int leddelay = 2;
int dayORnight = 0;
int lastState = 0;
int mainBeam = 0;
int signal = 0;
volatile int dayLevel = 100;
volatile int nightLevel = 25;
volatile int fullPower = 255;


// the setup routine runs once at boot:
void setup()  { 
  // declare pin 9 to be an output:
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(8, INPUT);
  digitalWrite(8, HIGH);
  pinMode(7, INPUT);
  digitalWrite(7, HIGH);
  pinMode(6, INPUT);
  digitalWrite(6, HIGH);
  pinMode(2, INPUT);
  digitalWrite(2, HIGH);    // Enable pullup resistor
  bitSet(TCCR1B, WGM12);
} 

// Startup routine
void launch(int qq)  {
  for (int q=0; q<qq; q++)
  // Led 1 Fade Sequence
  {
    for (int p=0; p<=255; p+=1)
      {
        analogWrite(led1, p);
        delay(leddelay);
      }
      for (int q=255; q>=100; q-=1)
        {
          analogWrite(led1, q);
          delay(leddelay);
        }
  }
  // Led 2 Fade Sequence
  {
    for (int r=0; r<=255; r+=1)
      {
        analogWrite(led2, r);
        delay(leddelay);
      }
      for (int s=255; s>=100; s-=1)
        {
          analogWrite(led2, s);
          delay(leddelay);
        }
  }
   // Led 3 Fade Sequence
  {
    for (int t=0; t<=255; t+=1)
      {
        analogWrite(led3, t);
        delay(leddelay);
      }
      for (int u=255; u>=100; u-=1)
        {
          analogWrite(led3, u);
          delay(leddelay);
        }
  } 
}


// normal use
void running()
{
  dayORnight = digitalRead(8);
  mainBeam = digitalRead(7);
  signal = digitalRead(6);
  if (signal == LOW) {
    analogWrite(led1, nightLevel);
    analogWrite(led2, 0);
    analogWrite(led3, nightLevel);
  } else if (mainBeam == LOW) {
    analogWrite(led1, fullPower);
    analogWrite(led2, fullPower);
    analogWrite(led3, fullPower);
  }
    else if (dayORnight == HIGH) {
      analogWrite(led1, dayLevel);
      analogWrite(led2, dayLevel);
      analogWrite(led3, dayLevel);
  } else {
          analogWrite(led1, nightLevel);
          analogWrite(led2, nightLevel);
          analogWrite(led3, nightLevel);
        }
}


// the loop routine runs over and over again forever:
void loop()  { 
  launch(1);
  while(1)
    running();
  }
