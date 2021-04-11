#pragma once

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
