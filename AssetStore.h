#pragma once
#define SUPPORT_FILEFORMAT_MP3
#define RAUDIO_STANDALONE
#include "Renderer.h"
#include "Tilemap.h"
#include "raudio.h"

class AssetStore {
public:
    AssetStore(AssetStore &other) = delete;
    void operator=(const AssetStore &) = delete;
    static AssetStore &getInstance();
    Texture2D getPlayerTexture() { return this->playerTexture; }
    Texture2D getTitleTexture() { return this->titleTexture; }
    Texture2D getYouWonTexture() { return this->youWonTexture; }
    Texture2D getYouDiedTexture() { return this->youDiedTexture; }
    Texture2D getFontTexture() { return this->fontTexture; }
    Texture2D getLogoTexture() { return this->logoTexture; }
    Texture2D getTilesetTexture() { return this->tilesetTexture; }
    Texture2D getHeartTexture() { return this->heartTexture; }
    Music getMenuSong() { return this->menuSong; }
    Music getGameSong() { return this->gameSong; }
    void unloadTextures();
    void unloadFonts();
    void loadMusic();
    void unloadMusic();
protected:
    AssetStore();
    Texture2D playerTexture;
    Texture2D titleTexture;
    Texture2D youWonTexture;
    Texture2D youDiedTexture;
    Texture2D tilesetTexture;
    Texture2D fontTexture;
    Texture2D logoTexture;
    Texture2D heartTexture;
    Music menuSong;
    Music gameSong;
};
