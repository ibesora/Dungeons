#include <cstdlib>
#include "Player.h"
#include "GameplayScreen.h"
#include "PauseScreen.h"
#include "GameStatus.h"
#include "InputHandler.h"
#include "AssetStore.h"
#include "Texts.h"
#include "Map.h"
#include "TextRenderer.h"

const int FadeInFramesNum = 60;
const int VisibleFramesNum = 300;
const int FadeOutFramesNum = 60;
const int FadeOutStartFramesNum = FadeInFramesNum + VisibleFramesNum;
const int TotalFramesNum = FadeInFramesNum + VisibleFramesNum + FadeOutFramesNum;

GameplayScreen::GameplayScreen(int width, int height) : Screen(ScreenType::Gameplay, width, height) {
    this->currentFrameRec = { 0, 0, AssetStore::getInstance().getPlayerTexture().width, AssetStore::getInstance().getPlayerTexture().height };
    this->textAnimFrame = 0;
    this->textAlpha = 0.0f;
    this->timesAtTheBeginning = 0;
    this->timesWTF = 0;
    this->showingText = false;
    this->showingWTFText = false;
}

void GameplayScreen::updateGameStatus() {
    if (InputHandler::getInstance().isKeyPressed(GLFW_KEY_ENTER)) {
        GameStatus::getInstance().changeCurrentScreen(new PauseScreen(this->width, this->height));
    }
    else {
        this->updatePlayerTexture();
        this->updateText();
    }
}

void GameplayScreen::updatePlayerTexture() {
    // TODO: Add player sprite animation
}

void GameplayScreen::updateText() {
    if (!this->showingText && Map::getInstance().getTimesAtTheBeginning() != this->timesAtTheBeginning) {
        this->showingText = true;
        this->textAnimFrame = 0;
        this->textAlpha = 0;
        this->timesAtTheBeginning = Map::getInstance().getTimesAtTheBeginning();
    }
    else if (!this->showingWTFText && Map::getInstance().getTimesWTF() != this->timesWTF) {
        this->showingWTFText = true;
        this->textAnimFrame = 0;
        this->textAlpha = 0;
        this->timesWTF = Map::getInstance().getTimesWTF();
    }
    if (this->showingText || showingWTFText) {
        this->textAnimFrame++;

        if (this->textAnimFrame < FadeInFramesNum) {
            this->textAlpha = (float)this->textAnimFrame / (float)FadeInFramesNum;
        }
        else if (this->textAnimFrame < FadeOutStartFramesNum) {
            this->textAlpha = 1.0f;
        }
        else if (this->textAnimFrame < TotalFramesNum) {
            this->textAlpha = 1.0f - (this->textAnimFrame - FadeOutStartFramesNum) / (float)FadeOutFramesNum;
        }
        else {
            this->textAlpha = 0.0f;
            this->showingText = 0;
            this->showingWTFText = 0;
        }

    }
}

const char *GameplayScreen::getTextFromId(int id) {
    if (id == 1) return Texts::Beginning1;
    else if (id == 2) return Texts::Beginning2;
    else if (id == 3) return Texts::Beginning3;
    else if (id == 4) return Texts::Beginning4;
    else if (id >= 5 && id < 15) return Texts::Beginning5;
    return Texts::Beginning6;
}

const char *GameplayScreen::getWTFTextFromId(int id) {
    if (id == 1) return Texts::WTF1;
    else if (id == 2) return Texts::WTF2;
    else if (id == 3) return Texts::WTF3;
    return Texts::WTF4;
}

void GameplayScreen::draw() {

    Renderer::ClearBackground(BLACK);
    this->drawBackground();
    this->drawPlayer();
    this->drawBullets();
    this->drawText();
}

void GameplayScreen::drawBackground() {
    Map::getInstance().draw();
}

void GameplayScreen::drawPlayer() {
    GameStatus::getInstance().getPlayer()->draw();
}

void GameplayScreen::drawBullets() {
    for (int i = 0; i < GameStatus::getInstance().getEnemyBulletsNumber(); ++i) {
        GameStatus::BulletInfo bullet = GameStatus::getInstance().getEnemyBullet(i);
        Renderer::DrawRectangle(bullet.position.x, bullet.position.y, 15, 15, BLUE);
        Renderer::DrawRectangle(bullet.position.x + 3, bullet.position.y + 3, 12, 12, YELLOW);
    }
}

void GameplayScreen::drawText() {
    const char *text = "";
    if (this->showingText) {
        text = this->getTextFromId(this->timesAtTheBeginning);
    }
    else if (this->showingWTFText) {
        text = this->getWTFTextFromId(this->timesWTF);
    }
    const int sizeInPx = strlen(text) * 20;
    Color color = { WHITE.r, WHITE.g, WHITE.b, this->textAlpha * 255.0f };
    TextRenderer::getInstance().draw(text, this->width / 2 - sizeInPx / 2, this->height - 100, 20, color);
}
