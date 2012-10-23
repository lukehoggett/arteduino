int CKI = 2;
int SDI = 3;
int colour_id = 0;
int transitionSteps = 2000;

unsigned long previousColour = 0xFFFFFF;


#define STRIP_LENGTH 1 // Number of RGBLED modules connected
long strip_colours[STRIP_LENGTH];

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));
  pinMode(SDI, OUTPUT);
  pinMode(CKI, OUTPUT);
}

void loop()
{
  //Serial.println("LOOP");
  // Pre-fill the color array with known values. Define as many entries as you have modules.
  //Serial.println("ZERO");
  //Serial.println(0x000000, HEX);
  //Serial.println("MAX");
  //Serial.println(0xFFFFFF, HEX);
  
  unsigned long colour = random(0x000000, 0x888888);
//  Serial.println("RAND");
  //Serial.println(colour, HEX);
  strip_colours[0] = colour;

  //post_frame(colour_id); //Push the current color frame to the strip
  
  Serial.println("colors");
  Serial.println(previousColour, HEX);
  Serial.println(colour, HEX);
  
  
  
  unsigned long steps[transitionSteps];
  xfade(colour, steps);
  previousColour = colour;
  for (int i = 1; i <= transitionSteps; i++)
  {
    //Serial.println("step val");
    //Serial.println(steps[i], HEX);
    doFade(i, steps);
    delay(10);
  }
  
  //Serial.println("##############################");

  
  
  //delay(100);
}

void xfade(unsigned long colour, unsigned long* steps)
{
    
    byte red = colour >> 16;
    byte green = colour >> 8 & 0xFF;
    byte blue = colour & 0xFF;
    
    byte prevRed = previousColour >> 16;
    byte prevGreen = previousColour >> 8 & 0xFF;
    byte prevBlue = previousColour & 0xFF;

    unsigned long val = 0;
    float dist = 0;
    //float ratio = transitionSteps / 100;
    float ratio = 0.0005;
    //Serial.println(ratio);
    for (int i = 1; i <= transitionSteps; i++)
    {
      dist = ratio * i;
      
      byte r = prevRed + ((red - prevRed) * dist);
      byte g = prevGreen + ((green - prevGreen) * dist);
      byte b = prevBlue + ((blue - prevBlue) * dist);
      val = (r << 16 | g << 8 | b) & 0xFFFFFF;
      steps[i] = val;
      
      /*Serial.println("i");
      Serial.println(i);
      
      Serial.println("Red");
      Serial.println(red, HEX);
      Serial.println("prevRed");
      Serial.println(prevRed, HEX);
      Serial.println("r");
      Serial.println(r, HEX);
    
      Serial.println("Greens");
      Serial.println(green, HEX);
      Serial.println(prevGreen, HEX);
      Serial.println(g, HEX);
        
      Serial.println("Blues");
      Serial.println(blue, HEX);
      Serial.println(prevBlue, HEX);
      Serial.println(b, HEX);
      
      Serial.println("Ratio");
      Serial.println(ratio);
      
      Serial.println("Dist");
      Serial.println(dist);
      
      Serial.println("Val");
      Serial.println(val, HEX);*/
          
    }
    /*Serial.println("Val");*/
    
    
    /*Serial.println("Red");
    Serial.println(red, HEX);
    
    Serial.println("Green");
    Serial.println(green, HEX);
        
    Serial.println("Blue");
    Serial.println(blue, HEX);*/
    
}

void doFade (int colour_id, unsigned long* steps) {
  
  
  for(int LED_number = 0; LED_number < transitionSteps; LED_number++)
  {
    long this_led_colour = steps[colour_id]; //24 bits of color data
    
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
