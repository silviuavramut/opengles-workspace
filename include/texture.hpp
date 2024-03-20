#pragma once

#include <glad/gl.h>

namespace opengles_workspace
{

	class texture
	{
	public:
		texture();
		texture(char *fileLoc);

		void LoadTexture();
		void UseTexture();
		void ClearTexture();

		~texture();

	private:
		GLuint textureID;
		int width, height, bitDepth;

		char *fileLocation;
	};
}
