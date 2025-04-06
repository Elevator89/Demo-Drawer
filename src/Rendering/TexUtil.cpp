#include "TexUtil.h"

#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

void PrintTex(unsigned int width, unsigned int height, const unsigned char* image)
{
	stringstream ss;
	ss << fixed << setprecision(2);
	for(unsigned int y = 0; y < height; ++y)
	{
		for(unsigned int x = 0; x < width; ++x)
		{
			unsigned int index = 4 * (y * height + x);
			ss
			<< image[index]/2 << ' '
			<< image[index+1]/2 << ' '
			<< image[index+2]/2 << ' '
			<< image[index+3]/2 << "    ";
		}
		ss << endl;
	}

	cout << ss.str() << endl;
}
