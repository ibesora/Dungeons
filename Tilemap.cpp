#define _CRT_SECURE_NO_DEPRECATE
#include "Tilemap.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ImageHandler.h"
#include "Renderer.h"
#include <vector>

#define PLAYER_COLLISION_PADDING    12
#define SPRITESHEET_COLUMNS 19


Tilemap::Tilemap(const char *valuesMap, const char *collidersMap, Texture2D tileMapTexture) {
    this->valuesMapFilePath = valuesMap;
    this->collidersMapFilePath = collidersMap;
    this->spritesheet = tileMapTexture;
    this->map = { 0 };
    this->map.tileScale = 1;
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
            this->loadCollidersFromImage();
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

    this->map.tileCountX = 16;
    this->map.tileCountY = 16;
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
    this->map.tiles = (Tile *)malloc(image.width * image.height * sizeof(Tile));
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            const int index = i * image.width + j;
            const Color cellColor = image.data[index];
            this->map.tiles[index].value = cellColor.b;
        }
    }
}

void Tilemap::loadCollidersFromImage() {
    Image image = ImageHandler::LoadImage(this->collidersMapFilePath);

    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            const int index = i * image.width + j;
            const Color cellColor = image.data[index];
            this->map.tiles[index].collider = cellColor.b;
        }
    }
}

void Tilemap::draw() {
    for (int x = 0; x < this->map.tileCountX; x++)
    {
        for (int y = 0; y < this->map.tileCountY; y++)
        {
            // Draw each piece of the tileset in the right position to build map
            const int tileIndex = this->map.tiles[x * this->map.tileCountY + y].value - 1;
            const int tileY = tileIndex / SPRITESHEET_COLUMNS;
            const int tileX = tileIndex % SPRITESHEET_COLUMNS;
            const Rectangle srcRect = { tileX * this->map.tileSize, tileY * this->map.tileSize, this->map.tileSize, this->map.tileSize  };
            const Rectangle destRect = { this->map.position.x + y * this->map.tileSize * this->map.tileScale , this->map.position.y + x * this->map.tileSize * this->map.tileScale , this->map.tileSize * this->map.tileScale, this->map.tileSize * this->map.tileScale };
            Renderer::DrawTexturePro(this->spritesheet, srcRect, destRect, { 0, 0 }, 0, WHITE);
        }
    }
}

void Tilemap::unload() {
    if (this->map.tiles != NULL) free(this->map.tiles);
}

void Tilemap::setTileSize(int tileSize) { this->map.tileSize = tileSize; }
void Tilemap::setScreenSize(int screenWidth, int screenHeight) {
    this->map.position = Vector2{ screenWidth / 2.f - this->map.tileCountX * this->map.tileSize,
                                  screenHeight / 2.f - this->map.tileCountY * this->map.tileSize};
}

bool Tilemap::checkCollision(Rectangle player) {
    const std::vector<int> values = this->getRectValues(player);
    std::vector<int>::const_iterator it = std::find(values.begin(), values.end(), 1);
    return it != values.end();
}

bool Tilemap::checkCollisionRecs(Rectangle rec1, Rectangle rec2)
{
    bool collision = false;

    int dx = abs((rec1.x + rec1.width / 2) - (rec2.x + rec2.width / 2));
    int dy = abs((rec1.y + rec1.height / 2) - (rec2.y + rec2.height / 2));

    if ((dx <= (rec1.width / 2 + rec2.width / 2)) && ((dy <= (rec1.height / 2 + rec2.height / 2)))) collision = true;

    return collision;
}

const std::vector<int> Tilemap::getRectValues(Rectangle player) {
    //TODO: Optimize this to only look for collisions on the cells surrounding the player and not everything
    Rectangle playerPadding = Rectangle{ player.x + PLAYER_COLLISION_PADDING, player.y + PLAYER_COLLISION_PADDING, player.width, player.height };
    std::vector<int> collisionValues = std::vector<int>();
    for (int y = 0; y < this->map.tileCountY; y++)
    {
        for (int x = 0; x < this->map.tileCountX; x++)
        {
            Rectangle cell = Rectangle{
               (int)this->map.position.x + x * this->map.tileSize * this->map.tileScale + PLAYER_COLLISION_PADDING, (int)this->map.position.y + y * this->map.tileSize * this->map.tileScale + PLAYER_COLLISION_PADDING, this->map.tileSize*this->map.tileScale, this->map.tileSize*this->map.tileScale
            };
            if (this->checkCollisionRecs(playerPadding, cell))
            {
                collisionValues.push_back(this->map.tiles[y * this->map.tileCountX + x].collider);
            }
        }
    }
    return collisionValues;
}