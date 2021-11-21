#pragma once
#include "Renderer.h"
#include <vector>

typedef struct Tile {
    int value;                  // Tile index value (in tileset)
    int collider;              // Tile collider (0 -> walkable)
    Color color;                // Tile color (could be useful)
} Tile;

typedef struct TilemapStruct {
    Tile* tiles;                // Tiles data
    int tileCountX;             // Tiles counter X
    int tileCountY;             // Tiles counter Y
    int tileSize;               // Tile size (XY)
    int tileScale;              // Scale factor
    Vector2 position;           // Tilemap position in screen
} TilemapStruct;

class Tilemap {
public:
    enum class FloorValues : int { Empty = 0, Collision, UpDoor, RightDoor, DownDoor, LeftDoor, Start};
    Tilemap(const char *valuesMap, const char *collidersMap, Texture2D tilemapTexture);
    void load();
    void draw();
    void unload();
    void setTileSize(int size);
    void setScreenSize(int screenWidth, int screenHeight);
    void setTileScale(int scale) { this->map.tileScale = scale; }
    Vector2 getPosition() { return this->map.position; }
    int getTileSize() { return this->map.tileSize; }
    Vector2 getTileCount() { return Vector2{ (float)this->map.tileCountX, (float)this->map.tileCountY }; }
    bool checkCollision(Rectangle position);
    const std::vector<int> getRectValues(Rectangle player);

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
    void loadCollidersFromValues();
    bool checkCollisionRecs(Rectangle, Rectangle);
};
