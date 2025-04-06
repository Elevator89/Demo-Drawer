#include "Filters.h"
#include "ColorUtil.h"

void Darken(Field<uint32_t>& field, float power)
{
	for (int y = 0; y < field.GetHeight(); ++y)
		for (int x = 0; x < field.GetWidth(); ++x)
		{
			unsigned char r, g, b, a;
			ColorDecode(field.GetCell(x, y), r, g, b, a);
			r *= power;
			g *= power;
			b *= power;

			field.SetCell(x, y, ColorEncode(r, g, b, a));
		}
}