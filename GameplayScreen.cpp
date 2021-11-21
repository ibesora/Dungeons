#include <cstdlib>
#include "Player.h"
#include "GameplayScreen.h"
#include "PauseScreen.h"
#include "GameStatus.h"
#include "InputHandler.h"
#include "AssetStore.h"
#include "Texts.h"
#include "Map.h"

GameplayScreen::GameplayScreen(int width, int height) : Screen(ScreenType::Gameplay, width, height) {
    this->currentFrameRec = { 0, 0, AssetStore::getInstance().getPlayerTexture().width, AssetStore::getInstance().getPlayerTexture().height };
    this->textAnimFrame = 0;
}

void GameplayScreen::updateGameStatus() {
    if (InputHandler::getInstance().isKeyPressed(GLFW_KEY_ENTER)) {
        GameStatus::getInstance().changeCurrentScreen(new PauseScreen(this->width, this->height));
    }
    else {
        this->updatePlayerTexture();
    }
}

void GameplayScreen::updatePlayerTexture() {
}

void GameplayScreen::draw() {

    Renderer::ClearBackground(BLACK);
    this->drawBackground();
    this->drawPlayer();
}

void GameplayScreen::drawBackground() {
    Map::getInstance().draw();
}

void GameplayScreen::drawPlayer() {
    GameStatus::getInstance().getPlayer()->draw();
}
