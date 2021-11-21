#define SUPPORT_FILEFORMAT_MP3
#define RAUDIO_STANDALONE
#include "AssetStore.h"
#include "WindowHandler.h"
#include "GameStatus.h"
#include "Screen.h"
#include "LogoScreen.h"
#include "raudio.h"

#define _CRT_SECURE_NO_DEPRECATE
#define RLGL_STANDALONE
#define RLGL_IMPLEMENTATION
#include "rlgl.h"
#include "Map.h"

const int ScreenWidth = 1080;
const int ScreenHeight = 810;

int main(void)
{

    WindowHandler::getInstance().initWindowAndDevice(ScreenWidth, ScreenHeight, "DUNGEONS", 60);
    InitAudioDevice();
    Map::getInstance().setScreenSize(ScreenWidth, ScreenHeight);

    AssetStore::getInstance().loadMusic();

    GameStatus::getInstance().setInitialScreen(new LogoScreen(ScreenWidth, ScreenHeight));

    while (!WindowHandler::getInstance().shouldClose())
    {
        UpdateMusicStream(GameStatus::getInstance().getCurrentSong());
        GameStatus::getInstance().update();

        WindowHandler::getInstance().beginDrawing();
        GameStatus::getInstance().getCurrentScreen()->draw();
        WindowHandler::getInstance().endDrawing();

    }

    AssetStore::getInstance().unloadFonts();
    AssetStore::getInstance().unloadMusic();
    AssetStore::getInstance().unloadTextures();
    Map::getInstance().unload();
  
    CloseAudioDevice();
    WindowHandler::getInstance().closeWindow();

    return 0;
}