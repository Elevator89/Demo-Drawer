#include "TexUtil.h"

#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include "../Field.h"

using namespace std;

GLuint CreateTexture(const Field<uint32_t>& field) {
	GLuint newTexture;
	glGenTextures(1, &newTexture);
	glBindTexture(GL_TEXTURE_2D, newTexture); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// Set texture filtering
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		// Load, create texture and generate mipmaps
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, field.GetWidth(), field.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, field.GetData());
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	// Set our texture parameters
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
	return newTexture;
}

GLuint CreateTexture(const Field<bool>& field) {
	GLuint newTexture;
	glGenTextures(1, &newTexture);
	glBindTexture(GL_TEXTURE_2D, newTexture); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// Set texture filtering
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		// Load, create texture and generate mipmaps
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, field.GetWidth(), field.GetHeight(), 0, GL_RED, GL_RED_INTEGER, field.GetData());
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	// Set our texture parameters
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
	return newTexture;
}

void ModifyTexture(GLuint textureId, const Field<uint32_t>& field) {
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, field.GetWidth(), field.GetHeight(), GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, field.GetData());
	glBindTexture(GL_TEXTURE_2D, 0);
}

void ModifyTexture(GLuint textureId, const Field<bool>& field) {
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, field.GetWidth(), field.GetHeight(), GL_RED, GL_RED_INTEGER, field.GetData());
	glBindTexture(GL_TEXTURE_2D, 0);
}


void PrintTex(unsigned int width, unsigned int height, const unsigned char* image)
{
	stringstream ss;
	ss << fixed << setprecision(2);
	for (unsigned int y = 0; y < height; ++y)
	{
		for (unsigned int x = 0; x < width; ++x)
		{
			unsigned int index = 4 * (y * height + x);
			ss
				<< image[index] / 2 << ' '
				<< image[index + 1] / 2 << ' '
				<< image[index + 2] / 2 << ' '
				<< image[index + 3] / 2 << "    ";
		}
		ss << endl;
	}

	cout << ss.str() << endl;
}
