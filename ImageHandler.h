#pragma once
#include "Renderer.h"
typedef struct Image {
    unsigned int width;         // Image width
    unsigned int height;        // Image height
    Color *data;                // Image data (Color - 32 bpp - R8G8B8A8)
} Image;

class ImageHandler
{
public:
	static Image LoadImage(const char *fileName);
	static void UnloadImage(Image image);
    static Image LoadBMP(const char *fileName);
};

