#include "AssetStore.h"
#include "TextureHandler.h"
#include "Renderer.h"

const int ScreenWidth = 1080;
const int ScreenHeight = 810;

AssetStore::AssetStore() {
    this->playerTexture = TextureHandler::LoadTexture("resources/player.bmp");
    this->titleTexture = TextureHandler::LoadTexture("resources/title.bmp");
    this->youDiedTexture = TextureHandler::LoadTexture("resources/lose.bmp");
    this->youWonTexture = TextureHandler::LoadTexture("resources/win.bmp");
    this->tilesetTexture = TextureHandler::LoadTexture("resources/tileset.bmp");
    this->fontTexture = TextureHandler::LoadTexture("resources/font.bmp");
    this->logoTexture = TextureHandler::LoadTexture("resources/logo.bmp");
    this->heartTexture = TextureHandler::LoadTexture("resources/heart.bmp");
    this->menuSong = LoadMusicStream("resources/scottaltham_-_Never_Heard_a_Rhyme_Like_This_Before.mp3");
    this->gameSong = LoadMusicStream("resources/Karstenholymoly_-_The_Thunderstorm.mp3");
    this->gameSong = LoadMusicStream("resources/Karstenholymoly_-_The_Thunderstorm.mp3");
    this->enemyLaserSound = LoadSound("resources/laserSmall_004.ogg");

    SetMusicVolume(this->menuSong, 0.1f);
    SetMusicVolume(this->gameSong, 0.1f);
    SetSoundVolume(this->enemyLaserSound, 0.05f);
}

void AssetStore::unloadTextures() {
    TextureHandler::UnloadTexture(this->playerTexture);
    TextureHandler::UnloadTexture(this->titleTexture);
    TextureHandler::UnloadTexture(this->youWonTexture);
    TextureHandler::UnloadTexture(this->youDiedTexture);
    TextureHandler::UnloadTexture(this->tilesetTexture);
    TextureHandler::UnloadTexture(this->fontTexture);
    TextureHandler::UnloadTexture(this->heartTexture);
}

void AssetStore::loadMusic() {
    PlayMusicStream(this->menuSong);
    PlayMusicStream(this->gameSong);
}

void AssetStore::unloadMusic() {
    UnloadMusicStream(this->menuSong);
    UnloadMusicStream(this->gameSong);
    UnloadSound(this->enemyLaserSound);
}

void AssetStore::unloadFonts() {
}

AssetStore &AssetStore::getInstance() {
    static AssetStore instance;
    return instance;
}