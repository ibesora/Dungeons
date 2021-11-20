#pragma once
#include "Renderer.h"

typedef struct Tile {
    int value;                  // Tile index value (in tileset)
    bool collider;              // Tile collider (0 -> walkable)
    Color color;                // Tile color (could be useful)
} Tile;

typedef struct TilemapStruct {
    Tile* tiles;                // Tiles data
    int tileCountX;             // Tiles counter X
    int tileCountY;             // Tiles counter Y
    int tileSize;               // Tile size (XY)
    Vector2 position;           // Tilemap position in screen
} TilemapStruct;

class Tilemap {
public:
    Tilemap(const char *valuesMap, const char *collidersMap, Texture2D tilemapTexture);
    void load();
    void draw();
    void unload();
    void setTileSize(int size);
    void setPosition(int screenWidth, int screenHeight);
    Vector2 getPosition() { return this->map.position; }
    int getTileSize() { return this->map.tileSize; }
    Vector2 getTileCount() { return Vector2{ (float)this->map.tileCountX, (float)this->map.tileCountY }; }
    bool checkCollision(Rectangle position);

protected:
    const char *valuesMapFilePath;
    const char *collidersMapFilePath;
    Texture2D spritesheet;
    TilemapStruct map;

private:
    void loadValuesFromText();
    void loadCollidersFromText();
    void loadValuesFromImage();
    void loadCollidersFromImage();
    bool checkCollisionRecs(Rectangle, Rectangle);
};
