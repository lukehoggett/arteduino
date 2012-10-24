#include "Arduino.h"
#include "ColorSpace.h"


ColorSpace::ColorSpace()
{

}



//Converts an HSV color to RGB color
void ColorSpace::HSVtoRGB(void *vRGB, void *vHSV)
{
  float r, g, b, h, s, v; //this function works with floats between 0 and 1
  float f, p, q, t;
  int i;
  ColorRGB *colorRGB=(ColorRGB *)vRGB;
  ColorHSV *colorHSV=(ColorHSV *)vHSV;

  h = (float)(colorHSV->h / 256.0);
  s = (float)(colorHSV->s / 256.0);
  v = (float)(colorHSV->v / 256.0);

  //if saturation is 0, the color is a shade of grey
  if(s == 0.0) {
    b = v;
    g = b;
    r = g;
  }
  //if saturation > 0, more complex calculations are needed
  else
  {
    h *= 6.0; //to bring hue to a number between 0 and 6, better for the calculations
    i = (int)(floor(h)); //e.g. 2.7 becomes 2 and 3.01 becomes 3 or 4.9999 becomes 4
    f = h - i;//the fractional part of h

    p = (float)(v * (1.0 - s));
    q = (float)(v * (1.0 - (s * f)));
    t = (float)(v * (1.0 - (s * (1.0 - f))));

    switch(i)
    {
      case 0: r=v; g=t; b=p; break;
      case 1: r=q; g=v; b=p; break;
      case 2: r=p; g=v; b=t; break;
      case 3: r=p; g=q; b=v; break;
      case 4: r=t; g=p; b=v; break;
      case 5: r=v; g=p; b=q; break;
      default: r = g = b = 0; break;
    }
  }
  colorRGB->r = (int)(r * 255.0);
  colorRGB->g = (int)(g * 255.0);
  colorRGB->b = (int)(b * 255.0);
}

// This is a subfunction of HSLtoRGB
/*void ColorSpace::_hslTempConversion(unsigned int& c, const double& temp1, const double& temp2, const double& temp3)
{
  if((temp3 * 6) < 1)
    c = (unsigned int)((temp2 + (temp1 - temp2)*6*temp3)*100);
  else
  if((temp3 * 2) < 1)
    c = (unsigned int)(temp1*100);
  else
  if((temp3 * 3) < 2)
    c = (unsigned int)((temp2 + (temp1 - temp2)*(.66666 - temp3)*6)*100);
  else
    c = (unsigned int)(temp2*100);
  return;
}

struct RGB ColorSpace::HSLtoRGB(struct HSL hsl)
{
  
  uint r = 0;
  uint g = 0;
  uint b = 0;
  
  double L = ((double)hsl.l)/100;
  double S = ((double)hsl.s)/100;
  double H = ((double)hsl.h)/360;

  if(hsl.s == 0)
  {
    r = hsl.l;
    g = hsl.l;
    b = hsl.l;
  }
  else
  {
    double temp1 = 0;
    if(L < .50)
    {
      temp1 = L*(1 + S);
    }
    else
    {
      temp1 = L + S - (L*S);
    }

    double temp2 = 2*L - temp1;

    double temp3 = 0;
    for(int i = 0 ; i < 3 ; i++)
    {
      switch(i)
      {
        case 0: // red
        {
          temp3 = H + .33333;
          if(temp3 > 1)
            temp3 -= 1;
          _hslTempConversion(r,temp1,temp2,temp3);
          break;
        }
        case 1: // green
        {
          temp3 = H;
          _hslTempConversion(g,temp1,temp2,temp3);
          break;
        }
        case 2: // blue
        {
          temp3 = H - .33333;
          if(temp3 < 0)
            temp3 += 1;
          _hslTempConversion(b,temp1,temp2,temp3);
          break;
        }
        default:
        {
  
        }
      }
    }
  }
  struct RGB rgb;
  rgb.r = (uint)((((double)r)/100)*255);
  rgb.g = (uint)((((double)g)/100)*255);
  rgb.b = (uint)((((double)b)/100)*255);

  return rgb;
  
}*/

