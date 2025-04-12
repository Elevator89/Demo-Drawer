#pragma once

#include <glad/gl.h>
#include <stdint.h>
#include "../Color4b.h"
#include "../Color4f.h"
#include "../Field.h"

GLuint CreateTexture(const Field<Color4b>& field);
GLuint CreateTexture(const Field<Color4f>& field);
GLuint CreateTexture(const Field<uint32_t>& field);
GLuint CreateTexture(const Field<bool>& field);

void ModifyTexture(GLuint textureId, const Field<Color4b>& field);
void ModifyTexture(GLuint textureId, const Field<Color4f>& field);
void ModifyTexture(GLuint textureId, const Field<uint32_t>& field);
void ModifyTexture(GLuint textureId, const Field<bool>& field);

void PrintTex(unsigned int width, unsigned int height, const unsigned char* image);
