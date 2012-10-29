#include <ColorSpace.h>

ColorSpace color;

int POT = 0;
int CKI = 2;
int SDI = 3;

int sensorValue = 0;


void setup()
{
  //Serial.begin(9600);

  pinMode(SDI, OUTPUT);
  pinMode(CKI, OUTPUT);

}



void loop()
{
 sensorValue = analogRead(POT);
 int mappedValue = map(sensorValue, 0, 1023, 0, 255);

 ColorRGB colorRGB;
 ColorHSV colorHSV = {mappedValue, 255, 255};
 color.HSVtoRGB(&colorRGB, &colorHSV);

 unsigned long rgbVal = ((unsigned long)colorRGB.r << 16 | colorRGB.g << 8 | colorRGB.b) & 0xFFFFFF;

 write(rgbVal);
 delay(100);

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


/*void doFade (int colour_id, unsigned long *steps, int numSteps) {
  
  
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
    
    delay(50);
    
  }
  

  //Pull clock low to put strip into reset/post mode
  digitalWrite(CKI, LOW);
  delayMicroseconds(500); //Wait for 500us to go into reset
}*/
