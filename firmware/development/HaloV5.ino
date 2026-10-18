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

int IndicatorState;          // the current reading from the input pin
int lastIndicatorState;      // the previous reading from the input pin

// the following variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 100;   // the debounce time; increase if the output flickers



// the setup routine runs once on boot:
void setup()  
{ 
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  
  pinMode(8, INPUT);
  digitalWrite(8, HIGH);
  
  pinMode(7, INPUT);
  digitalWrite(7, HIGH);
  
  // set Indicator pin as input
  pinMode(2, INPUT);

  TCCR2B = TCCR2B & 0b11111000 | 0x01; // Timer Frequency for Pin 11
  TCCR1B = TCCR1B & 0b11111000 | 0x01; // Timer Frequency for Pins 9 & 10
} 

// Startup routine
void launch(int qq)  
{
  for (int q=0; q<qq; q++)
  // Led 1 Fade Sequence
  {
    for (int p=0; p<=255; p+=1)
    {
      analogWrite(led1, p);
      delay(leddelay);
    }
    for (int q=255; q>=150; q-=1)
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
        analogWrite(led3, t);
        delay(leddelay);
    }
    for (int u=255; u>=150; u-=1)
    {
        analogWrite(led3, u);
        delay(leddelay);
    }
  } 

  // initialise indicator states
  IndicatorState = digitalRead(2);
  lastIndicatorState = IndicatorState;
}

// normal use
void running()
{
  dayORnight = digitalRead(8);
  mainBeam = digitalRead(7);
  
  if (mainBeam == LOW) 
  {
      digitalWrite(led1,HIGH);
      digitalWrite(led2,HIGH);
      digitalWrite(led3,HIGH);
  }
  else if (dayORnight == HIGH) 
  {
      analogWrite(led1, dayLevel);
      analogWrite(led2, dayLevel);
      analogWrite(led3, dayLevel);
  } 
  else 
  {
      analogWrite(led1, nightLevel);
      analogWrite(led2, nightLevel);
      analogWrite(led3, nightLevel);
  }
        
  // read the state of the indicator into a local variable:
  int Indicator_reading = digitalRead(2);

  // If indicator changed, due to noise or change of state:
  if (Indicator_reading != lastIndicatorState) 
  {
    // reset the debouncing timer
    lastDebounceTime = millis();
  } 
  
  if ((millis() - lastDebounceTime) > debounceDelay) 
  {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    // if the indicator state has changed:
    if (Indicator_reading != IndicatorState) 
    {
      IndicatorState = Indicator_reading;

      // check state of indicator
      if (IndicatorState == LOW) 
      { while(IndicatorState == HIGH) {
        if (IndicatorState == LOW)
        { break;
        }
        analogWrite(led1, nightSignal);
        analogWrite(led2, nightCentre);
        analogWrite(led3, nightSignal);
       }
        // indicator on delay
       //delay(4000);
      }
      else if (IndicatorState == HIGH)
      {
//        analogWrite(led1, nightSignal);
//        analogWrite(led2, nightCentre);
//        analogWrite(led3, nightSignal);
      } 
    }
  }
  
  // save the reading.  Next time through the loop,
  // it'll be the lastIndicatorState:
  lastIndicatorState = Indicator_reading;
}


// the loop routine runs over and over again forever:
void loop()  
{ 
  launch(1);
  while(1)
    running();
}

