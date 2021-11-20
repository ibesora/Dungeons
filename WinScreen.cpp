#include "WinScreen.h"
#include "GameplayScreen.h"
#include "TitleScreen.h"
#include "GameStatus.h"
#include "AssetStore.h"
#include <stdlib.h>
#include "Texts.h"
#include "TextRenderer.h"
#include "InputHandler.h"
#include "TextureHandler.h"

const int FadeInFramesNum = 60;
const int VisibleFramesNum = 0;
const int FadeOutFramesNum = 0;
const int FadeOutStartFramesNum = FadeInFramesNum + VisibleFramesNum;
const int TotalFramesNum = FadeInFramesNum + VisibleFramesNum + FadeOutFramesNum;

WinScreen::WinScreen(int width, int height) : Screen(ScreenType::Pause, width, height) {
    this->currentFrame = 0;
}

void WinScreen::updateGameStatus() {
    if (this->currentFrame >= TotalFramesNum) {
        if (InputHandler::getInstance().isKeyPressed(GLFW_KEY_ENTER)) {
            GameStatus::getInstance().reset();
            GameStatus::getInstance().changeCurrentScreen(new TitleScreen(this->width, this->height, false));
        }
    }
    else {
        this->currentFrame++;
    }
}

void WinScreen::draw() {
    Renderer::ClearBackground(BLACK);
    float alpha = 0.0f;
    if (this->currentFrame < FadeInFramesNum) {
        alpha = (float)this->currentFrame / (float)FadeInFramesNum;
    }
    else if (this->currentFrame <= FadeOutStartFramesNum) {
        alpha = 1.0f;
    }

    Color color = { WHITE.r, WHITE.g, WHITE.b, alpha*255.0f };
    Renderer::DrawTexture(AssetStore::getInstance().getYouWonTexture(), 5, this->height / 2 - 400, color);

    if (this->currentFrame >= FadeOutStartFramesNum) {
        TextRenderer::getInstance().draw(Texts::GoBackToTitleScreen, 190, 670, 20, YELLOW);
    }

}