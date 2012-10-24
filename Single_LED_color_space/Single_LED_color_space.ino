#include <ColorSpace.h>

ColorSpace color;

int CKI = 2;
int SDI = 3;

#define STRIP_LENGTH 1 // Number of RGBLED modules connected
long strip_colours[STRIP_LENGTH];

int previousHue= 0;
int stepSize = 5;


void setup()
{
  //Serial.begin(9600);
  randomSeed(analogRead(0));
  pinMode(SDI, OUTPUT);
  pinMode(CKI, OUTPUT);

}

float dist(float a, float b, float c, float d)
{
  return sqrt((c-a)*(c-a)+(d-b)*(d-b));
}

void loop()
{
  // get a random hue
  int hue = random(0, 255);
  //int hue = 20;
  /*Serial.print("Previous: ");
  Serial.println(previousHue);
  Serial.print("Hue: ");
  Serial.println(hue);*/
  
  
    
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
  
  /*Serial.print("NumSteps: ");
  Serial.println(numSteps);*/
  // set up array to contain the hue steps
  unsigned long steps[numSteps];
  
  int hueStep;

  for (int i = 0; i < numSteps; i++)
  {
    hueStep = (i * stepSize) + previousHue; 
    if (hueStep > 360)
    {
      hueStep = hueStep - 360;

    }
    
    /*Serial.print("Hue Step: ");
    Serial.println(hueStep);*/
    
    ColorRGB colorRGB;
    ColorHSV colorHSV = {(unsigned char)(map(hueStep, 1, 360, 0, 255)), 255, 255};
    color.HSVtoRGB(&colorRGB, &colorHSV);
    /*Serial.print("RGB: ");
    Serial.print(colorRGB.r);
    Serial.print(", ");
    Serial.print(colorRGB.g);
    Serial.print(", ");
    Serial.println(colorRGB.b);*/
//    unsigned long rgbVal = (map(colorRGB.r, 0, 127, 0, 255) << 16 | map(colorRGB.g, 0, 127, 0, 255) << 8 | map(colorRGB.b, 0, 127, 0, 255)) & 0xFFFFFF;
    unsigned long rgbVal = (colorRGB.r << 16 | colorRGB.g << 8 | colorRGB.b) & 0xFFFFFF;
    /*Serial.print("RGB: ");
    Serial.println(rgbVal, HEX);*/
    /*Serial.print("Value: ");
    Serial.println((unsigned char)((value) * 128)&0xff);*/
    steps[i] = rgbVal;

  }
  
  //post_frame(0);
  
  for (int i = 0; i < numSteps; i++)
  {
    doFade(i, steps, numSteps);
  }//
  previousHue = hue;
  //Serial.println("=====");
  delay(500);
}


void doFade (int colour_id, unsigned long *steps, int numSteps) {
  
  
  for(int LED_number = 0; LED_number < STRIP_LENGTH; LED_number++)
  {
    unsigned long this_led_colour = steps[colour_id]; //24 bits of color data
    //Serial.print("this LED colour: ");
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
    
    delay(500);
    
  }
  

  //Pull clock low to put strip into reset/post mode
  digitalWrite(CKI, LOW);
  delayMicroseconds(500); //Wait for 500us to go into reset
}
