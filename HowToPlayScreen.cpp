#include "HowToPlayScreen.h"
#include "Texts.h"
#include "InputHandler.h"
#include "GameStatus.h"
#include "TitleScreen.h"
#include "AssetStore.h"
#include "TextRenderer.h"


HowToPlayScreen::HowToPlayScreen(int width, int height) : Screen(ScreenType::Credits, width, height) {
}

void HowToPlayScreen::updateGameStatus() {
    if (InputHandler::getInstance().isKeyPressed(GLFW_KEY_ENTER)) {
        GameStatus::getInstance().changeCurrentScreen(new TitleScreen(this->width, this->height, false));
    }
}

void HowToPlayScreen::draw() {

    const int left = 90;
    const int bottomMargin = 90;
    const int textSize = 20;
    int top = 200;

    Renderer::ClearBackground(BLACK);
    TextRenderer::getInstance().draw(Texts::Controls, left, top, textSize, YELLOW);
    top += textSize;
    TextRenderer::getInstance().draw(Texts::GoUpOrDown, left, top, textSize, LIGHTGRAY);
    top += textSize;
    TextRenderer::getInstance().draw(Texts::GoLeftOrRight, left, top, textSize, LIGHTGRAY);
    top += textSize;
    TextRenderer::getInstance().draw(Texts::PressEnterToPause, left, top, textSize, LIGHTGRAY);
    top += textSize*2;
    TextRenderer::getInstance().draw(Texts::MissionTitle, left, top, textSize, YELLOW);
    top += textSize;
    TextRenderer::getInstance().draw(Texts::MissionText, left, top, textSize * 1.5, RED);
    top += textSize * 1.5;
    TextRenderer::getInstance().draw(Texts::MissionText2, left, top, textSize, RED);
    top = this->height - bottomMargin;
    TextRenderer::getInstance().draw(Texts::GoBackToTitleScreen, left * 2, top, textSize, YELLOW);

}