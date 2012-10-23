



int CKI = 2;
int SDI = 3;
int colour_id = 0;

#define STRIP_LENGTH 2 // Number of RGBLED modules connected
long strip_colours[STRIP_LENGTH];
long strip_start_colours[STRIP_LENGTH];
long strip_end_colours[STRIP_LENGTH];

void setup() {
  Serial.begin(9600);
  Serial.println("SETUP");
  pinMode(SDI, OUTPUT);
  pinMode(CKI, OUTPUT);
}

void loop() {
  Serial.println("LOOP");
  // Pre-fill the color array with known values. Define as many entries as you have modules.
  strip_colours[0] = generateRandomColour();   // Set module 1 to Red
Serial.println("RandomNumber");
Serial.println(generateRandomColour());
Serial.println(String(generateRandomColour(), HEX));


  // set the start and end colours for each led in the strip
  for(int LED_number = 0; LED_number < STRIP_LENGTH; LED_number++) {
    strip_start_colours[LED_number] = generateRandomColour();
    strip_end_colours[LED_number] = generateRandomColour();
    strip_colurs[LED_number] = 
  }


  post_frame(colour_id); //Push the current color frame to the strip
  colour_id++;
  if(colour_id == 3) {
    colour_id = 0;
  }
  delay(2500);
}


int lurp(startColour, endColour, percent)
{
      
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
        Serial.print(1);
        digitalWrite(SDI, HIGH);
      } else {
        Serial.print(0);
        digitalWrite(SDI, LOW);
      }
      digitalWrite(CKI, HIGH); //Data is latched when clock goes high
    }
    Serial.println(" end bit loop ");
  }
  Serial.println(" end LED loop ");

  //Pull clock low to put strip into reset/post mode
  digitalWrite(CKI, LOW);
  delayMicroseconds(500); //Wait for 500us to go into reset
}

int generateRandomColour()
{
  randomSeed(analogRead(0));
  return random(0x030303, 0xffffff);
}
