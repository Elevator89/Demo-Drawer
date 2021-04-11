#pragma once

#include <stdint.h>

uint32_t ColorEncode(float r, float g, float b, float a);
uint32_t ColorEncode(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
void ColorDecode(uint32_t intData, float& r, float& g, float& b, float& a);
void ColorDecode(uint32_t intData, unsigned char& r, unsigned char& g, unsigned char& b, unsigned char& a);
