#include "PauseScreen.h"
#include "TitleScreen.h"
#include "GameplayScreen.h"
#include "GameStatus.h"
#include "TextRenderer.h"
#include "Texts.h"
#include <stdlib.h>
#include "InputHandler.h"

PauseScreen::PauseScreen(int width, int height) : Screen(ScreenType::Pause, width, height) {
    this->currentSelectedOption = Option::Continue;
}

void PauseScreen::updateGameStatus() {
    const int selectedOption = static_cast<int>(this->currentSelectedOption);
    const int optionNum = static_cast<int>(Option::End);
    if (InputHandler::getInstance().isKeyPressed(GLFW_KEY_DOWN)) {
        this->currentSelectedOption = static_cast<Option>((selectedOption + 1) % optionNum);
    }
    else if (InputHandler::getInstance().isKeyPressed(GLFW_KEY_UP)) {
        this->currentSelectedOption = static_cast<Option>(abs((selectedOption - 1) % optionNum));
    }
    else if (InputHandler::getInstance().isKeyPressed(GLFW_KEY_ENTER)) {
        Screen *nextScreen = this->currentSelectedOption == Option::Continue ? (Screen *)(new GameplayScreen(this->width, this->height)) : (Screen *)(new TitleScreen(this->width, this->height, false));
        GameStatus::getInstance().changeCurrentScreen(nextScreen);
    }
}

void PauseScreen::draw() {

    Renderer::ClearBackground(BLACK);
    TextRenderer::getInstance().draw(Texts::PausedText, 115, 610, 20, YELLOW);
    TextRenderer::getInstance().draw(Texts::ContinueText, 115, 630, 20, currentSelectedOption == Option::Continue ? RED : LIGHTGRAY);
    TextRenderer::getInstance().draw(Texts::BackToTitleText, 115, 650, 20, currentSelectedOption == Option::BackToTitleScreen ? RED : LIGHTGRAY);

}