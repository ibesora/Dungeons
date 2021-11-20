#define _CRT_SECURE_NO_DEPRECATE
#include "ImageHandler.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Image ImageHandler::LoadImage(const char *fileName)
{
    Image image = { 0 };
    const char *fileExt;

    if ((fileExt = strrchr(fileName, '.')) != NULL)
    {
        // Check if file extension is supported
        if (strcmp(fileExt, ".bmp") == 0) image = ImageHandler::LoadBMP(fileName);
    }

    return image;
}

// Unload image data from CPU memory (RAM)
void  ImageHandler::UnloadImage(Image image)
{
    if (image.data != NULL) free(image.data);
}

Image ImageHandler::LoadBMP(const char *fileName)
{
    Image image = { 0 };

    int imgWidth;
    int imgHeight;
    short imgBpp;
    int imgDataOffset;

    FILE *bmpFile = fopen(fileName, "rb");

    fseek(bmpFile, 10, SEEK_SET);
    fread(&imgDataOffset, 4, 1, bmpFile);   // Read bmp data offset
    fseek(bmpFile, 18, SEEK_SET);
    fread(&imgWidth, 4, 1, bmpFile);        // Read bmp width
    fread(&imgHeight, 4, 1, bmpFile);       // Read bmp height
    fseek(bmpFile, 28, SEEK_SET);
    fread(&imgBpp, 2, 1, bmpFile);          // Read bmp bit-per-pixel (usually 24bpp - B8G8R8)

    Color *imgData = (Color *)malloc(imgWidth * imgHeight * sizeof(Color));

    fseek(bmpFile, imgDataOffset, SEEK_SET);

    // Calculate image padding per line
    int padding = (imgWidth * imgBpp) % 32;
    int unusedData = 0;
    int extraBytes = 0;

    if ((padding / 8) > 0) extraBytes = 4 - (padding / 8);

    // Read image data
    for (int j = 0; j < imgHeight; j++)
    {
        for (int i = 0; i < imgWidth; i++)
        {
            fread(&imgData[j * imgWidth + i].b, 1, 1, bmpFile);
            fread(&imgData[j * imgWidth + i].g, 1, 1, bmpFile);
            fread(&imgData[j * imgWidth + i].r, 1, 1, bmpFile);
            imgData[j * imgWidth + i].a = 255;    // Set alpha to fully opaque by default

            // NOTE: We consider a color key: MAGENTA RGB{ 255, 0, 255 },
            // in that case, pixel will be transparent
            if ((imgData[j * imgWidth + i].r == 255) &&
                (imgData[j * imgWidth + i].g == 0) &&
                (imgData[j * imgWidth + i].b == 255)) imgData[j * imgWidth + i].a = 0;
        }

        fread(&unusedData, extraBytes, 1, bmpFile);
    }

    fclose(bmpFile);

    image.data = (Color *)malloc(imgWidth * imgHeight * sizeof(Color));

    // Flip image vertically
    for (int j = 0; j < imgHeight; j++)
    {
        for (int i = 0; i < imgWidth; i++)
        {
            image.data[j * imgWidth + i] = imgData[((imgHeight - 1) - j) * imgWidth + i];
        }
    }

    free(imgData);

    image.width = imgWidth;
    image.height = imgHeight;

    TraceLog(LOG_INFO, "[%s] BMP Image loaded successfully (%ix%i)", fileName, imgWidth, imgHeight);

    return image;
}