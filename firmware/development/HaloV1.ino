/*
Project Halo UK

Brought to you by Jabawoki
www.jabawoki.com
 */
#include < avr/io.h >
#include <avr/interrupt.h>    // Needed to use interrupts

int led1 = 9;           // the pin that the inner ring is attached to
int led2 = 10;           // the pin that the middle ring is attached to
int led3 = 11;           // the pin that the outer ring is attached to
int leddelay = 2;
int mainBeamIn = 2;

// the setup routine runs once when you press reset:
void setup()  { 
  // declare pin 9 to be an output:
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  attachInterrupt(mainBeamIn, MainBeamOn, RISING);
} 

// Main Beam Interupt
void MainBeamOn()
{
  
  analogWrite(led1, 255);
  analogWrite(led2, 255);
  analogWrite(led3, 255);
}


// Startup routine
void launch(volatile int qq)  {
  for (volatile int q=0; q<qq; q++)
  // Led 1 Fade Sequence
  {
    for (volatile int p=0; p<=255; p+=1)
      {
        analogWrite(led1, p);
        delay(leddelay);
      }
      for (volatile int q=255; q>=100; q-=1)
        {
          analogWrite(led1, q);
          delay(leddelay);
        }
  }
  // Led 2 Fade Sequence
  {
    for (volatile int r=0; r<=255; r+=1)
      {
        analogWrite(led2, r);
        delay(leddelay);
      }
      for (volatile int s=255; s>=100; s-=1)
        {
          analogWrite(led2, s);
          delay(leddelay);
        }
  }
   // Led 3 Fade Sequence
  {
    for (volatile int t=0; t<=255; t+=1)
      {
        analogWrite(led3, t);
        delay(leddelay);
      }
      for (volatile int u=255; u>=100; u-=1)
        {
          analogWrite(led3, u);
          delay(leddelay);
        }
  } 
}

// Daylight Running
void daylight()  {
  analogWrite(led1, 100);
  analogWrite(led2, 100);
  analogWrite(led3, 100);
}

// the loop routine runs over and over again forever:
void loop()  { 
  launch(1);
  while(1) {
  daylight();
  }
}
