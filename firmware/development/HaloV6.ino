/*
 ____  ____  _____   ____  ____  ___  ____    _   _    __    __    _____    __  __  _  _ 
(  _ \(  _ \(  _  ) (_  _)( ___)/ __)(_  _)  ( )_( )  /__\  (  )  (  _  )  (  )(  )( )/ )
 )___/ )   / )(_)( .-_)(   )__)( (__   )(     ) _ (  /(__)\  )(__  )(_)(    )(__)(  )  ( 
(__)  (_)\_)(_____)\____) (____)\___) (__)   (_) (_)(__)(__)(____)(_____)  (______)(_)\_)
                                Brought to you by Jabawoki
                                    www.jabawoki.com
*/
 
// Definition of interrupt names
#include < avr/io.h >
// ISR interrupt service routine
#include < avr/interrupt.h >

volatile int led1 = 9;           // the pin that the inner ring is attached to
volatile int led2 = 10;           // the pin that the middle ring is attached to
volatile int led3 = 11;           // the pin that the outer ring is attached to
int leddelay = 2;
int dayORnight = 0;
int mainBeam = 0;
volatile int dayLevel = 150;
volatile int nightLevel = 75;
volatile int nightSignal = 50;
volatile int nightCentre = 0;
volatile int indiState;

// the setup routine runs once on boot:
void setup()  { 
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(8, INPUT);
  digitalWrite(8, HIGH);
  pinMode(7, INPUT);
  digitalWrite(7, HIGH);
  attachInterrupt(0, signal, HIGH);
  TCCR2B = TCCR2B & 0b11111000 | 0x01; // Timer Frequency for Pin 11
  TCCR1B = TCCR1B & 0b11111000 | 0x01; // Timer Frequency for Pins 9 & 10
  } 

// Startup routine
void launch(int qq)  {
  for (int q=0; q<qq; q++)
  // Led 1 Fade Sequence
  {
    for (int p=0; p<=255; p+=1)
      {
        analogWrite(led3, p);
        delay(leddelay);
      }
      for (int q=255; q>=150; q-=1)
        {
          analogWrite(led3, q);
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
      for (int s=255; s>=150; s-=1)
        {
          analogWrite(led2, s);
          delay(leddelay);
        }
  }
   // Led 3 Fade Sequence
  {
    for (int t=0; t<=255; t+=1)
      {
        analogWrite(led1, t);
        delay(leddelay);
      }
      for (int u=255; u>=150; u-=1)
        {
          analogWrite(led1, u);
          delay(leddelay);
        }
  } 
}

// normal use
void running()
{
  dayORnight = digitalRead(8);
  mainBeam = digitalRead(7);
  if (mainBeam == LOW) {
        digitalWrite(led1,HIGH);
        digitalWrite(led2,HIGH);
        digitalWrite(led3,HIGH);
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

// Indicator Interupt
void signal()
{
  static unsigned long last_interupt_time = 0;
  unsigned long interupt_time = millis();
  indiState = digitalRead(2);
  
  if (interupt_time - last_interupt_time > 200)
  {  while(indiState == HIGH);
    analogWrite(led1, nightSignal);
    analogWrite(led2, nightCentre);
    analogWrite(led3, nightSignal);
//    delayMicroseconds(1000000000);
  }
  last_interupt_time = interupt_time;
}

// the loop routine runs over and over again forever:
void loop()  { 
  launch(1);
  while(1)
    running();
  }

