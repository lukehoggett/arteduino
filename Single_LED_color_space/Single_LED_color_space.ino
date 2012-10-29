#include <ColorSpace.h>

ColorSpace color;

int CKI = 2;
int SDI = 3;

#define STRIP_LENGTH 1 // Number of RGBLED modules connected
long strip_colours[STRIP_LENGTH];

int currentHue;
int stepSize = 1;


void setup()
{
  Serial.begin(9600);
  randomSeed(analogRead(0) + analogRead(2));
  currentHue = random(0, 255);
  pinMode(SDI, OUTPUT);
  pinMode(CKI, OUTPUT);

}

void loop()
{
  // get a random nextHue
  int nextHue = random(0, 255);
  int distance;
  boolean up;
  if (currentHue > nextHue)
  {
    up = false;
    distance = nextHue - currentHue;
  }
  else if (nextHue >= currentHue) 
  {
    up = true;
    distance = currentHue - nextHue;    
  }
  
  
  // establish the number of steps between the current and previous nextHue
  int numSteps = distance / stepSize;
  if (currentHue > nextHue)
  {
    numSteps = (nextHue - currentHue + 256) / stepSize;  
  }
  else
  {
    numSteps = (nextHue - currentHue) / stepSize;
  }
  
  nextHue = numSteps * stepSize;
  int hue;
  if (up)
  {
    for (int i = 0; i < numSteps; i = i + stepSize)
    {
      hue = currentHue + i;
      ColorRGB colorRGB;
      ColorHSV colorHSV = {(unsigned char)(hue), 255, 255};
      color.HSVtoRGB(&colorRGB, &colorHSV);
    
      unsigned long rgbVal = ((unsigned long)colorRGB.r << 16 | colorRGB.g << 8 | colorRGB.b) & 0xFFFFFF;
    
      Serial.println(rgbVal, HEX);
      write(rgbVal);
    
      delay(100);
    }
  }
  else
  {
    for (int i = 0; i < numSteps; i = i + stepSize)
    {
      hue = currentHue - i;
      ColorRGB colorRGB;
      ColorHSV colorHSV = {(unsigned char)(hue), 255, 255};
      color.HSVtoRGB(&colorRGB, &colorHSV);
    
      unsigned long rgbVal = ((unsigned long)colorRGB.r << 16 | colorRGB.g << 8 | colorRGB.b) & 0xFFFFFF;
    
      Serial.println(rgbVal, HEX);
      write(rgbVal);
    
      delay(100);
    }
  }
  
  
  currentHue = nextHue;

  delay(1500);
}


void write(unsigned long colour)
{
  unsigned long this_led_colour = colour; //24 bits of color data
    
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
    
    //Pull clock low to put strip into reset/post mode
  digitalWrite(CKI, LOW);
  delayMicroseconds(500); //Wait for 500us to go into reset
} 
