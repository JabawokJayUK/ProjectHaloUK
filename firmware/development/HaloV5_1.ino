/*
 ____  ____  _____   ____  ____  ___  ____    _   _    __    __    _____    __  __  _  _ 
(  _ \(  _ \(  _  ) (_  _)( ___)/ __)(_  _)  ( )_( )  /__\  (  )  (  _  )  (  )(  )( )/ )
 )___/ )   / )(_)( .-_)(   )__)( (__   )(     ) _ (  /(__)\  )(__  )(_)(    )(__)(  )  ( 
(__)  (_)\_)(_____)\____) (____)\___) (__)   (_) (_)(__)(__)(____)(_____)  (______)(_)\_)
                                Brought to you by Jabawoki
                                    www.jabawoki.com
                                    
On boot up, they run Mode 1 once, then default to Mode 2 below

Mode 1:           Fade from 0% to 100% to 80% in sequence from Led 1 (inside) to Led 3 (outside)

Mode 2:           Daytime operation – all Leds at 80%

Mode 3:           Night operation – all Leds at 70%

Mode 4:           Signal Mode – Outer Led & inner Led rings at 70% - middle ring off

Mode 5:           All rings at full power (digitalWrite HIGH)


Modes 3,4 & 5 are selected by +12 signal on each of the 3 opto’s.

Revision History:

V5.0  Added Indicator debouncing routine and 10ms timer
V5.1  IndicatorState variable is now set correctly on startup

*/
 
// Definition of interrupt names
#include < avr/io.h >
// ISR interrupt service routine
#include < avr/interrupt.h >

#define TIMER_EXPIRED  0
#define INDICATOR_DEBOUNCEDELAY  10   // 100ms debounce time; increase if required
#define INDICATOR_LOCKOUTDELAY  100   // 1s
#define TIMER_TICK  10                // 10ms timer tick interval 

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

int CurrentIndicatorState = 0;   // the current reading from the input pin
int LastIndicatorState = 0;      // the previous reading from the input pin
bool IndicatorState;             // debounced indicator state

// the following variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long IndicatorDebounceTimer = 0;    // Indicator noise debounce timer
long IndicatorLockoutTimer = 0;     // Indicator lockout timer

long previousMillis = 0;      // will store last timer was updated




// the setup routine runs once on boot:
void setup()  
{ 
  // set Ring control output pins
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  
  // set Sidelight pin as input
  pinMode(8, INPUT);
  
  // set Main Beam pin as input
  pinMode(7, INPUT);
  
  // set Indicator pin as input
  pinMode(2, INPUT);

  TCCR2B = TCCR2B & 0b11111000 | 0x01; // Timer Frequency for Pin 11
  TCCR1B = TCCR1B & 0b11111000 | 0x01; // Timer Frequency for Pins 9 & 10
} 

void msTimers(void) {
  
  unsigned long currentMillis = millis();
 
  if( currentMillis - previousMillis > TIMER_TICK ) 
  {
    // save the last timer 
    previousMillis = currentMillis;  
    
    // decrement any system timers that are running
    if ( IndicatorDebounceTimer != 0 )
      IndicatorDebounceTimer--; 
    if ( IndicatorLockoutTimer != 0 )
      IndicatorLockoutTimer--; 
  }
  
}

// Startup routine
void launch(int qq)  
{
  for ( int q=0; q<qq; q++ )
  // Led 1 Fade Sequence
  {
    for ( int p=0; p<=255; p+=1 )
    {
      analogWrite(led1, p);
      delay(leddelay);
    }
    for ( int q=255; q>=150; q-=1 )
    {
      analogWrite(led1, q);
      delay(leddelay);
    }
    // Led 2 Fade Sequence
    for ( int r=0; r<=255; r+=1 )
    {
        analogWrite(led2, r);
        delay(leddelay);
    }
    for ( int s=255; s>=150; s-=1 )
    {
        analogWrite(led2, s);
        delay(leddelay);
    }
    // Led 3 Fade Sequence
    for ( int t=0; t<=255; t+=1 )
    {
        analogWrite(led3, t);
        delay(leddelay);
    }
    for ( int u=255; u>=150; u-=1 )
    {
        analogWrite(led3, u);
        delay(leddelay);
    }
  } 

  // initialise indicator states
  CurrentIndicatorState = digitalRead(2);
  LastIndicatorState = CurrentIndicatorState;
  if (CurrentIndicatorState == HIGH) 
  {
    IndicatorState = false;
  }
  else
  {
    IndicatorState = true;
  }
}

void DebounceIndicator(void) {
  
  // read the state of the indicator into a local variable:
  int Indicator_reading = digitalRead(2);

  // If indicator changed, due to noise or change of state:
  if (Indicator_reading != LastIndicatorState) 
  {
    // reset the indicator debouncing timer
    IndicatorDebounceTimer = INDICATOR_DEBOUNCEDELAY;
  } 
  
  if (IndicatorDebounceTimer == TIMER_EXPIRED) 
  {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    // if the indicator state has changed:
    if (Indicator_reading != CurrentIndicatorState) 
    {
      CurrentIndicatorState = Indicator_reading;
      // start indicator lockout timer
      IndicatorLockoutTimer = INDICATOR_LOCKOUTDELAY;
      
      // check the state of indicator is ON
      if (CurrentIndicatorState == LOW) 
      {
        // indicator state is in transition
        IndicatorState = true;
      }
    }
  }
  
  if (IndicatorLockoutTimer == TIMER_EXPIRED) 
  {
      // check the state of indicator is still OFF
      if (CurrentIndicatorState == HIGH) 
      {
        IndicatorState = false;
      }
  }
  
  // save the reading.  Next time through the loop,
  // it'll be the lastIndicatorState:
  LastIndicatorState = Indicator_reading;
}




// normal use
void Running()
{
  dayORnight = digitalRead(8);
  mainBeam = digitalRead(7);
  
  if (mainBeam == LOW && IndicatorState == false) 
  {
      digitalWrite(led1,HIGH);
      digitalWrite(led2,HIGH);
      digitalWrite(led3,HIGH);
  }
  else if (dayORnight == HIGH  && IndicatorState == false) 
  {
      analogWrite(led1, dayLevel);
      analogWrite(led2, dayLevel);
      analogWrite(led3, dayLevel);
  } 
  else if (IndicatorState == false)
  {
      analogWrite(led1, nightLevel);
      analogWrite(led2, nightLevel);
      analogWrite(led3, nightLevel);
  }
  else if (IndicatorState == true)
  {
      analogWrite(led1, nightSignal);
      analogWrite(led2, nightCentre);
      analogWrite(led3, nightSignal);
  }
        

}


// the loop routine runs over and over again forever:
void loop()  
{ 
  launch(1);
  while(1) {
    msTimers();
    DebounceIndicator();
    Running();
  }
}

