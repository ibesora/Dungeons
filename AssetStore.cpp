#include "AssetStore.h"
#include "TextureHandler.h"
#include "Renderer.h"

const int ScreenHeight = 1080;
const int ScreenWidth = 450;

AssetStore::AssetStore() {
    this->playerTexture = TextureHandler::LoadTexture("resources/player.bmp");
    this->titleTexture = TextureHandler::LoadTexture("resources/title.bmp");
    this->youDiedTexture = TextureHandler::LoadTexture("resources/lose.bmp");
    this->youWonTexture = TextureHandler::LoadTexture("resources/win.bmp");
    this->tilesetTexture = TextureHandler::LoadTexture("resources/tileset.bmp");
    this->fontTexture = TextureHandler::LoadTexture("resources/font.bmp");
    this->logoTexture = TextureHandler::LoadTexture("resources/logo.bmp");
    this->menuSong = LoadMusicStream("resources/scottaltham_-_Never_Heard_a_Rhyme_Like_This_Before.mp3");
    this->gameSong = LoadMusicStream("resources/Karstenholymoly_-_The_Thunderstorm.mp3");
    this->tileMap = new Tilemap("resources/tilemap.txt", "resources/tilemap_colliders.txt", tilesetTexture);
    this->tileMap->load();
    this->tileMap->setTileSize(32);
    this->tileMap->setPosition(ScreenWidth / 2.f - this->tileMap->getTileCount().x * this->tileMap->getTileSize() / 2,
                                  ScreenHeight / 2.f - this->tileMap->getTileCount().y * this->tileMap->getTileSize() / 2);

    SetMusicVolume(this->menuSong, 0.1f);
    SetMusicVolume(this->gameSong, 0.1f);
}

void AssetStore::unloadTextures() {
    TextureHandler::UnloadTexture(this->playerTexture);
    TextureHandler::UnloadTexture(this->titleTexture);
    TextureHandler::UnloadTexture(this->youWonTexture);
    TextureHandler::UnloadTexture(this->youDiedTexture);
    TextureHandler::UnloadTexture(this->tilesetTexture);
    TextureHandler::UnloadTexture(this->fontTexture);
}

void AssetStore::loadMusic() {
    PlayMusicStream(this->menuSong);
    PlayMusicStream(this->gameSong);
}

void AssetStore::unloadMusic() {
    UnloadMusicStream(this->menuSong);
    UnloadMusicStream(this->gameSong);
}

void AssetStore::unloadFonts() {
}

void AssetStore::unloadTilemap() {
    delete this->tileMap;
}

AssetStore &AssetStore::getInstance() {
    static AssetStore instance;
    return instance;
}