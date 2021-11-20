#include "EndingScreen.h"
#include "GameplayScreen.h"
#include "TitleScreen.h"
#include "GameStatus.h"
#include "AssetStore.h"
#include <stdlib.h>
#include "Texts.h"
#include "TextRenderer.h"
#include "Renderer.h"
#include "InputHandler.h"

const int FadeInFramesNum = 60;
const int VisibleFramesNum = 0;
const int FadeOutFramesNum = 0;
const int FadeOutStartFramesNum = FadeInFramesNum + VisibleFramesNum;
const int TotalFramesNum = FadeInFramesNum + VisibleFramesNum + FadeOutFramesNum;

EndingScreen::EndingScreen(int width, int height) : Screen(ScreenType::Pause, width, height) {
    this->currentFrame = 0;
    this->currentSelectedOption = Option::NextRun;
}

void EndingScreen::updateGameStatus() {
    if (this->currentFrame >= TotalFramesNum) {
        const int selectedOption = static_cast<int>(this->currentSelectedOption);
        const int optionNum = static_cast<int>(Option::End);
        if (InputHandler::getInstance().isKeyPressed(GLFW_KEY_DOWN)) {
            this->currentSelectedOption = static_cast<Option>((selectedOption + 1) % optionNum);
        }
        else if (InputHandler::getInstance().isKeyPressed(GLFW_KEY_UP)) {
            this->currentSelectedOption = static_cast<Option>(abs((selectedOption - 1) % optionNum));
        }
        else if (InputHandler::getInstance().isKeyPressed(GLFW_KEY_ENTER)) {
            Screen *nextScreen = this->currentSelectedOption == Option::NextRun ? (Screen *)(new GameplayScreen(this->width, this->height)) : (Screen *)(new TitleScreen(this->width, this->height, false));
            GameStatus::getInstance().reset();
            GameStatus::getInstance().changeCurrentScreen(nextScreen);
        }
    }
    else {
        this->currentFrame++;
    }
}

void EndingScreen::draw() {
    Renderer::ClearBackground(BLACK);
    float alpha = 0.0f;
    if (this->currentFrame < FadeInFramesNum) {
        alpha = (float)this->currentFrame / (float)FadeInFramesNum;
    }
    else if (this->currentFrame <= FadeOutStartFramesNum) {
        alpha = 1.0f;
    }

    Color color = { WHITE.r, WHITE.g, WHITE.b, alpha*255.0f };
    Renderer::DrawTexture(AssetStore::getInstance().getYouDiedTexture(), 5, this->height / 2 - 400, color);

    if (this->currentFrame >= FadeOutStartFramesNum) {
        TextRenderer::getInstance().draw(Texts::TryAgainText, 190, 650, 20, currentSelectedOption == Option::NextRun ? RED : LIGHTGRAY);
        TextRenderer::getInstance().draw(Texts::BackToTitleText, 190, 670, 20, currentSelectedOption == Option::BackToTitle ? RED : LIGHTGRAY);
    }

}