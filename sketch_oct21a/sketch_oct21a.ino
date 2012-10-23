#include <ColorSpace.h>

ColorSpace color();
void setup()
{
  Serial.begin(9600);
  
  struct RGB rgb = {1, 2, 3};
  
  Serial.println(rgb.r);
  
  
}

void loop()
{
  
}


