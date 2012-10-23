



int CKI = 2;
int SDI = 3;
int colour_id = 0;

#define STRIP_LENGTH 2 // Number of RGBLED modules connected
long strip_colours[STRIP_LENGTH];

void setup() {
  Serial.begin(9600);
  Serial.println("SETUP");
  pinMode(SDI, OUTPUT);
  pinMode(CKI, OUTPUT);
}

void loop() {
  Serial.println("LOOP");
  // Pre-fill the color array with known values. Define as many entries as you have modules.
  strip_colours[0] = 0xFF0000;   // Set module 1 to Red

  if(STRIP_LENGTH > 1)
    strip_colours[1] = 0x00FF00; // Set module 2 to Green

//  if(STRIP_LENGTH > 2)
    strip_colours[2] = 0x0000FF; // Set module 3 to Blue

//  if(STRIP_LENGTH > 3)
   strip_colours[3] = 0xFFFFFF; // Set module 4 to White

  post_frame(colour_id); //Push the current color frame to the strip
  colour_id++;
  if(colour_id == 3) {
    colour_id = 0;
  }
  delay(500);
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
