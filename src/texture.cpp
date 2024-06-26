#include <texture.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace opengles_workspace
{

	texture::texture()
	{
		textureID = 0;
		width = 0;
		height = 0;
		bitDepth = 0;
		fileLocation = "";
	}

	texture::texture(char *fileLoc)
	{
		textureID = 0;
		width = 0;
		height = 0;
		bitDepth = 0;
		fileLocation = fileLoc;
	}

	void texture::LoadTexture()
	{
		unsigned char *texData = stbi_load(fileLocation, &width, &height, &bitDepth, 0);
		if (!texData)
		{
			printf("Failed to find: %s\n", fileLocation);
			return;
		}

		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);

		stbi_image_free(texData);
	}

	void texture::UseTexture()
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureID);
	}

	void texture::ClearTexture()
	{
		glDeleteTextures(1, &textureID);
		textureID = 0;
		width = 0;
		height = 0;
		bitDepth = 0;
		fileLocation = "";
	}

	texture::~texture()
	{
		ClearTexture();
	}
}