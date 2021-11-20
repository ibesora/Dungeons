#include "TextureHandler.h"
#include "ImageHandler.h"

Texture2D TextureHandler::LoadTexture(const char *filename) {
    Image im = ImageHandler::LoadImage(filename);
    Texture2D tex = TextureHandler::LoadTextureFromImage(im);
    ImageHandler::UnloadImage(im);
    return tex;
}

Texture2D TextureHandler::LoadTextureFromImage(Image image)
{
#define UNCOMPRESSED_R8G8B8A8    7      // Texture format (must match image.data)

    Texture2D texture = { 0 };

    texture.width = image.width;
    texture.height = image.height;
    texture.format = UNCOMPRESSED_R8G8B8A8;
    texture.mipmaps = 1;

    texture.id = rlLoadTexture(image.data, image.width, image.height, UNCOMPRESSED_R8G8B8A8, 1);

    return texture;
}

// Unload texture data from GPU memory (VRAM)
void TextureHandler::UnloadTexture(Texture2D texture)
{
    if (texture.id > 0) rlDeleteTextures(texture.id);
}