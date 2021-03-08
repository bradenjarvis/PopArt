#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel strand(24, 0);
#include <Bounce2.h>



//  0 = all off.
//  1 = Static Visualizer
//  2 = Animation
//  3 = Mapped Animation

int favorite = 0;

#define pin_switch 1
Bounce debouncer = Bounce();


// variables to hold switch states
boolean oldSwitchState = LOW;
boolean newSwitchState = LOW;
byte state = 0;

#include "frames1.h"

int colors[2][3] {
  {0, 255, 0},
  {255, 0, 0}
};

int whichFrame = 0;



void setup()
{
  Serial.begin(9600);
  pinMode(pin_switch, INPUT_PULLUP);
  debouncer.attach(pin_switch);
  debouncer.interval(5);
strand.setBrightness(255);
  strand.begin();
  strand.clear();
  
}


void loop() {


  newSwitchState = digitalRead(pin_switch);
  if ( newSwitchState != oldSwitchState )
  {
    
    if ( newSwitchState == HIGH )
    {
      // increase the value of state
      state++;
      if (state > 3) {
        state = 0;
      }
    }
  }

//state 1
  if (state == 1) {
    int animation[1][24] {

      {
        0, 0, 0, 0, 0, 0,
        0, 0,       0, 0,
        1,       1,
        0,             0,
        0, 0, 0, 0, 0, 0,
        0, 0,
        0, 0,


      },

    };
    for (int i = 0; i < strand.numPixels(); i++) {
      int whichColor = animation [whichFrame][i];



      int gold = colors [whichColor] [0];
      int red = colors [whichColor] [1];

      strand.setPixelColor(i, red, 0, gold);
    }

    whichFrame = (whichFrame + 1) % 1;
  }


//state 2
  if (state == 2) {

    for (int i = 0; i < strand.numPixels(); i++ / 2) {
      strand.setPixelColor(i, 255, 215, 0);
    
    }
  }



//state 3
  if (state == 3) {
    for (int i = 0; i < strand.numPixels(); i++) {
      int whichColor1 = animation1 [whichFrame][i];

      int gold = colors [whichColor1] [0];
      int red = colors [whichColor1] [1];

      strand.setPixelColor(i, red, 0, gold);
    }

    whichFrame = (whichFrame + 1)  % 3 ;
    delay(500);

  }
  strand.show();
  oldSwitchState = newSwitchState;


}
