#ifndef ColorSpace_h
#define ColorSpace_h

#include "Arduino.h"


struct RGB {
		  	byte r;
		  	byte g;
		  	byte b;
		};

		struct HSL {
		  	int h;
		  	byte s;
		  	byte l;
		};

		typedef unsigned int uint;

class ColorSpace
{
	public:
		

		ColorSpace();
		struct HSL RGBtoHSL(struct RGB rgb);
		struct RGB HSLtoRGB(struct HSL hsl);
	private:
		void _hslTempConversion(unsigned int& c, const double& temp1, const double& temp2, const double& temp3);

};

#endif
