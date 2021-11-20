#include "CreditsScreen.h"
#include "Texts.h"
#include "InputHandler.h"
#include "GameStatus.h"
#include "TitleScreen.h"
#include "TextRenderer.h"
#include "Renderer.h"

CreditsScreen::CreditsScreen(int width, int height) : Screen(ScreenType::Credits, width, height) {
}

void CreditsScreen::updateGameStatus() {
    if (InputHandler::getInstance().isKeyPressed(GLFW_KEY_ENTER)) {
        GameStatus::getInstance().changeCurrentScreen(new TitleScreen(this->width, this->height, false));
    }
}

void CreditsScreen::draw() {

    Renderer::ClearBackground(BLACK);
    TextRenderer::getInstance().draw(Texts::Programming, 115, 220, 20, YELLOW);
    TextRenderer::getInstance().draw(Texts::MyName, 115, 240, 20, LIGHTGRAY);
    TextRenderer::getInstance().draw(Texts::Assets, 115, 330, 20, YELLOW);
    TextRenderer::getInstance().draw(Texts::FontCredits, 115, 350, 20, LIGHTGRAY);
    TextRenderer::getInstance().draw(Texts::GoBackToTitleScreen, 115, 500, 20, YELLOW);

}