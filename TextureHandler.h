#pragma once
#include "ImageHandler.h"

class TextureHandler
{
public: 
	static Texture2D LoadTexture(const char *filename);
	static Texture2D LoadTextureFromImage(Image image);
	static void UnloadTexture(Texture2D texture);
};

