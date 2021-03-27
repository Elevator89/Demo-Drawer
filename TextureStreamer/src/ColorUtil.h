#ifndef COLORUTIL_H
#define COLORUTIL_H

#include <stdint.h>

enum class Color : uint32_t
{
    Black = 0x000000FF,
    White = 0xFFFFFFFF,
    Red = 0xFF0000FF,
    Green = 0x00FF00FF,
    Blue = 0x0000FFFF,
    Cyan = 0x00FFFFFF,
    Magenta = 0xFF00FFFF,
    Yellow = 0xFFFF00FF,
};

uint32_t ColorEncode(float r, float g, float b, float a);
uint32_t ColorEncode(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
void ColorDecode(uint32_t intData, float& r, float& g, float& b, float& a);
void ColorDecode(uint32_t intData, unsigned char& r, unsigned char& g, unsigned char& b, unsigned char& a);

#endif // COLORUTIL_H
