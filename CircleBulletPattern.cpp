#define _USE_MATH_DEFINES
#include <cmath>
#include "CircleBulletPattern.h"

void CircleBulletPattern::createBullet(int currentFrame, Vector2 position, std::vector<GameStatus::BulletInfo> *bullets) {
    const int numBulletSources = 20;
    for (int i = 0; i <= numBulletSources; ++i) {
        float angle = (float)(i * 2.0f * M_PI / numBulletSources);
        bullets->push_back(GameStatus::BulletInfo({ cos(angle) * this->bulletSpeed, sin(angle) * this->bulletSpeed }, position));
    }
}