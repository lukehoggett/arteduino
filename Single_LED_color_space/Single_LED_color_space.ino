#include <ColorSpace.h>

ColorSpace color;

int CKI = 2;
int SDI = 3;

#define STRIP_LENGTH 1 // Number of RGBLED modules connected
long strip_colours[STRIP_LENGTH];

int previousHue= 0;
int stepSize = 1;


void setup()
{
  Serial.begin(9600);
  randomSeed(analogRead(0));
  pinMode(SDI, OUTPUT);
  pinMode(CKI, OUTPUT);

}

void loop()
{
  // get a random hue
  int hue = random(0, 360);
  //int hue = 20;
  Serial.println("Previous");
  Serial.println(previousHue);
  Serial.println("Hue");
  Serial.println(hue);
  
  
    
  // establish the number of steps between the current and previous hue
  int numSteps;
  if (previousHue > hue)
  {
    numSteps = (hue - previousHue + 360) / stepSize;  
  }
  else
  {
    numSteps = (hue - previousHue) / stepSize;
  }
  
  //Serial.println("NumSteps");
  //Serial.println(numSteps);
  // set up array to contain the hue steps
  int steps[numSteps];
  
  int hueStep;

  for (int i = 0; i < numSteps; i++)
  {
    hueStep = (i * stepSize) + previousHue; 
    if (hueStep > 360)
    {
      hueStep = hueStep - 360;

    }
    //Serial.println("Hue Step");
    //Serial.println(hueStep);
    struct HSL hsl = {hueStep, 100, 50};
    struct RGB rgb = color.HSLtoRGB(hsl);
    /*Serial.println("RGB");
    Serial.println(rgb.r);
    Serial.println(rgb.g);
    Serial.println(rgb.b);*/
    unsigned long rgbVal = (rgb.r << 16 | rgb.g << 8 | rgb.b) & 0xFFFFFF;
    Serial.println("RGB");
    Serial.println(rgbVal, HEX);
    steps[i] = rgbVal;
  }
  
  //post_frame(0);
  
  for (int i = 0; i < numSteps; i++)
  {
    doFade(i, steps, numSteps);
  }
  previousHue = hue;
  Serial.println("=====");
  delay(500);
}


void doFade (int colour_id, int* steps, int numSteps) {
  
  
  for(int LED_number = 0; LED_number < numSteps; LED_number++)
  {
    long this_led_colour = steps[colour_id]; //24 bits of color data
    //Serial.println(this_led_colour, HEX);
    for(byte colour_bit = 23 ; colour_bit != 255 ; colour_bit--) {
      //Feed color bit 23 first (red data MSB)

      digitalWrite(CKI, LOW); //Only change data when clock is low

      long mask = 1L << colour_bit;
      //The 1'L' forces the 1 to start as a 32 bit number, otherwise it defaults to 16-bit.
      
      if(this_led_colour & mask) {
        //Serial.print(1);
        digitalWrite(SDI, HIGH);
      } else {
        //Serial.print(0);
        digitalWrite(SDI, LOW);
      }
      digitalWrite(CKI, HIGH); //Data is latched when clock goes high
    }
    
  }
  

  //Pull clock low to put strip into reset/post mode
  digitalWrite(CKI, LOW);
  delayMicroseconds(500); //Wait for 500us to go into reset
}

void post_frame (int colour_id) {
  
  
  for(int LED_number = 0; LED_number < STRIP_LENGTH; LED_number++)
  {
    long this_led_colour = strip_colours[colour_id]; //24 bits of color data
    
    for(byte colour_bit = 23 ; colour_bit != 255 ; colour_bit--) {
      //Feed color bit 23 first (red data MSB)

      digitalWrite(CKI, LOW); //Only change data when clock is low

      long mask = 1L << colour_bit;
      //The 1'L' forces the 1 to start as a 32 bit number, otherwise it defaults to 16-bit.
      
      if(this_led_colour & mask) {
        //Serial.print(1);
        digitalWrite(SDI, HIGH);
      } else {
        //Serial.print(0);
        digitalWrite(SDI, LOW);
      }
      digitalWrite(CKI, HIGH); //Data is latched when clock goes high
    }
    
  }

  //Pull clock low to put strip into reset/post mode
  digitalWrite(CKI, LOW);
  delayMicroseconds(500); //Wait for 500us to go into reset
}
