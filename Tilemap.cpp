#define _CRT_SECURE_NO_DEPRECATE
#include "Tilemap.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ImageHandler.h"
#include "Renderer.h"

#define TILESET_TILES  32
#define PLAYER_COLLISION_PADDING    12

// NOTE: Tileset rectangles are directly provided in this array but
// they can also be loaded from a file... usually generated with
// a tilemap editor software
static Rectangle TilesetRecs[TILESET_TILES] = {
    { 0, 0, 32, 32 }, { 32, 0, 32, 32 },        // 1, 2
    { 64, 0, 32, 32 }, { 0, 32, 32, 32 },       // 3, 4
    { 32, 32, 32, 32 }, { 64, 32, 32, 32 },     // 5, 6
    { 0, 64, 32, 32 }, { 32, 64, 32, 32 },      // 7, 8
    { 64, 64, 32, 32 }, { 96, 0, 32, 32 },      // 9, 10
    { 128, 0, 32, 32 }, { 96, 32, 32, 32 },     // 11, 12
    { 128, 32, 32, 32 }, { 96, 64, 32, 32 },    // 13, 14
    { 128, 64, 32, 32 }, { 128, 96, 32, 32 },   // 15, 16
    { 0, 96, 32, 32 }, { 32, 96, 32, 32 },      // 17, 18
    { 64, 96, 32, 32 }, { 96, 96, 32, 32 },     // 19, 20
    { 160, 96, 32, 32 }, { 160, 0, 32, 32 },    // 21, 22
    { 160, 32, 32, 32 }, { 160, 64, 32, 32 },   // 23, 24
    { 192, 0, 32, 32 }, { 224, 0, 32, 32 },     // 25, 26
    { 192, 32, 32, 32 }, { 224, 32, 32, 32 },   // 27, 28
    { 192, 64, 32, 32 }, { 224, 64, 32, 32 },   // 29, 30
    { 192, 96, 32, 32 }, { 224, 96, 32, 32 }    // 31, 32
};

Tilemap::Tilemap(const char *valuesMap, const char *collidersMap, Texture2D tileMapTexture) {
    this->valuesMapFilePath = valuesMap;
    this->collidersMapFilePath = collidersMap;
    this->spritesheet = tileMapTexture;
    this->map = { 0 };
};

void Tilemap::load() {
    const char *fileExt;

    if ((fileExt = strrchr(this->valuesMapFilePath, '.')) != NULL)
    {
        // Check if file extension is supported
        if (strcmp(fileExt, ".txt") == 0)
        {
            this->loadValuesFromText();
            this->loadCollidersFromText();

        }
        else if (strcmp(fileExt, ".bmp") == 0)
        {
            this->loadValuesFromImage();
        }
    }
}

void Tilemap::loadValuesFromText() {
    int counter = 0;
    int temp = 0;

    // Read values from text file
    FILE *valuesFile = fopen(this->valuesMapFilePath, "rt");

    while (!feof(valuesFile))
    {
        fscanf(valuesFile, "%i", &temp);
        counter++;
    }

    rewind(valuesFile);        // Return to the beginning of the file, to read again

    this->map.tiles = (Tile *)malloc(counter * sizeof(Tile));

    this->map.tileCountX = 12;
    this->map.tileCountY = 8;
    counter = 0;

    while (!feof(valuesFile))
    {
        fscanf(valuesFile, "%i", &this->map.tiles[counter].value);
        counter++;
    }

    fclose(valuesFile);
}

void Tilemap::loadCollidersFromText() {
    int counter = 0;
    int temp = 0;

    // Read values from text file
    // NOTE: Colliders map data MUST match values data, 
    // or we need to do a previous check like done with values data
    FILE *collidersFile = fopen(this->collidersMapFilePath, "rt");

    while (!feof(collidersFile))
    {
        fscanf(collidersFile, "%i", &temp);
        this->map.tiles[counter].collider = temp;

        counter++;
    }

    fclose(collidersFile);
}

void Tilemap::loadValuesFromImage() {
    Image image = ImageHandler::LoadImage(this->valuesMapFilePath);

    this->map.tileCountX = image.width;
    this->map.tileCountY = image.height;
}

void Tilemap::draw() {
    for (int y = 0; y < this->map.tileCountY; y++)
    {
        for (int x = 0; x < this->map.tileCountX; x++)
        {
            // Draw each piece of the tileset in the right position to build map
            Renderer::DrawTextureRec(this->spritesheet, TilesetRecs[this->map.tiles[y * this->map.tileCountX + x].value - 1],
                Vector2{
                this->map.position.x + x * this->map.tileSize, this->map.position.y + y * this->map.tileSize
                }, WHITE);
        }
    }
}

void Tilemap::unload() {
    if (this->map.tiles != NULL) free(this->map.tiles);
}

void Tilemap::setTileSize(int tileSize) { this->map.tileSize = tileSize; }
void Tilemap::setPosition(int screenWidth, int screenHeight) {
    this->map.position = Vector2{ screenWidth / 2.f - this->map.tileCountX * this->map.tileSize / 2,
                                  screenHeight / 2.f - this->map.tileCountY * this->map.tileSize / 2 };
}

bool Tilemap::checkCollision(Rectangle player) {
    Rectangle playerPadding = Rectangle{ player.x + PLAYER_COLLISION_PADDING, player.y + PLAYER_COLLISION_PADDING, player.width, player.height };
    for (int y = 0; y < this->map.tileCountY; y++)
    {
        for (int x = 0; x < this->map.tileCountX; x++)
        {
            Rectangle cell = Rectangle{
               (int)this->map.position.x + x * this->map.tileSize + PLAYER_COLLISION_PADDING, (int)this->map.position.y + y * this->map.tileSize + PLAYER_COLLISION_PADDING, this->map.tileSize, this->map.tileSize
            };
            if ((this->map.tiles[y * this->map.tileCountX + x].collider == 0) &&
                this->checkCollisionRecs(playerPadding, cell))
            {
                return true;
            }
        }
    }
    return false;
}

bool Tilemap::checkCollisionRecs(Rectangle rec1, Rectangle rec2)
{
    bool collision = false;

    int dx = abs((rec1.x + rec1.width / 2) - (rec2.x + rec2.width / 2));
    int dy = abs((rec1.y + rec1.height / 2) - (rec2.y + rec2.height / 2));

    if ((dx <= (rec1.width / 2 + rec2.width / 2)) && ((dy <= (rec1.height / 2 + rec2.height / 2)))) collision = true;

    return collision;
}