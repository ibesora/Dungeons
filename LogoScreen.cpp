#include "LogoScreen.h"
#include "TitleScreen.h"
#include "AssetStore.h"

const int FadeInFramesNum = 60;
const int VisibleFramesNum = 300;
const int FadeOutFramesNum = 60;
const int FadeOutStartFramesNum = FadeInFramesNum + VisibleFramesNum;
const int TotalFramesNum = FadeInFramesNum + VisibleFramesNum + FadeOutFramesNum;

LogoScreen::LogoScreen(int width, int height) : Screen(ScreenType::Logo, width, height) {
    this->currentFrame = 0;
}

void LogoScreen::updateGameStatus() {
    this->currentFrame++;
    if (this->currentFrame >= TotalFramesNum) {
        GameStatus::getInstance().changeCurrentScreen(new TitleScreen(this->width, this->height));
    }
}

void LogoScreen::draw() {
    Renderer::ClearBackground(WHITE);
    float alpha = 0.0;
    if (this->currentFrame < FadeInFramesNum) {
        alpha = (float)this->currentFrame / (float)FadeInFramesNum;
    }
    else if (this->currentFrame < FadeOutStartFramesNum) {
        alpha = 1.0f;
    }
    else if (this->currentFrame < TotalFramesNum) {
        alpha = 1.0f - (this->currentFrame - FadeOutStartFramesNum) / (float)FadeOutFramesNum;
    }

    Color color = { WHITE.r, WHITE.g, WHITE.b, alpha*255.0f };
    Texture2D logo = AssetStore::getInstance().getLogoTexture();
    Renderer::DrawTexture(logo, this->width / 2 - logo.width / 2, this->height / 2 - logo.height / 2, color);
}