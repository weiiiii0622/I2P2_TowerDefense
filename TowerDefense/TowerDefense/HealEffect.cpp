//
//  HealEffect.cpp
//  TowerDefense
//
//  Created by wei on 2022/5/20.
//


#include <cmath>
#include <string>

#include "HealEffect.hpp"
#include "GameEngine.hpp"
#include "Group.hpp"
#include "IScene.hpp"
#include "PlayScene.hpp"
#include "Resources.hpp"
// TODO 3 (2/2): You can imitate the 2 files: '"ExplosionEffect.hpp', '"ExplosionEffect.cpp' to create a Shoot Effect.
PlayScene* HealEffect::getPlayScene() {
    return dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetActiveScene());
}
HealEffect::HealEffect(float x, float y) : Sprite("play/heal-1.png", x, y), timeTicks(0) {
    for (int i = 1; i <= 5; i++) {
        bmps.push_back(Engine::Resources::GetInstance().GetBitmap("play/heal-" + std::to_string(i) + ".png"));
    }
}
void HealEffect::Update(float deltaTime) {
    timeTicks += deltaTime;
    if (timeTicks >= timeSpan) {
        getPlayScene()->EffectGroup->RemoveObject(objectIterator);
        return;
    }
    int phase = floor(timeTicks / timeSpan * bmps.size());
    bmp = bmps[phase];
    Sprite::Update(deltaTime);
}
