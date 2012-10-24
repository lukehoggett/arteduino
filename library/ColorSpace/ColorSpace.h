#ifndef ColorSpace_h
#define ColorSpace_h

#include "Arduino.h"


typedef struct
{
	unsigned char r;
 	unsigned char g;
	unsigned char b;
} ColorRGB;

//a color with 3 components: h, s and v
typedef struct
{
	unsigned char h;
	unsigned char s;
	unsigned char v;
} ColorHSV;

typedef unsigned int uint;

class ColorSpace
{
	public:
		

		ColorSpace();
		void RGBtoHSV(void *vRGB, void *vHSV);
		void HSVtoRGB(void *vRGB, void *vHSV);
			
		//struct RGB HSLtoRGB(struct HSL hsl);
	private:
		//void _hslTempConversion(unsigned int& c, const double& temp1, const double& temp2, const double& temp3);

};

#endif
