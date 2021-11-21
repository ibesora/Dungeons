#pragma once
#include "BulletPattern.h"

class CircleBulletPattern : public BulletPattern {
public:
    CircleBulletPattern() : BulletPattern(BulletPatterns::Circle, 60, 2) {}
    void createBullet(int currentFrame, Vector2 position, std::vector<GameStatus::BulletInfo> *bullets);
};
