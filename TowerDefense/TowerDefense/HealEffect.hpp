//
//  HealEffect.hpp
//  TowerDefense
//
//  Created by wei on 2022/5/20.
//

#ifndef HealEffect_hpp
#define HealEffect_hpp

#include <allegro5/bitmap.h>
#include <memory>
#include <vector>

#include "Sprite.hpp"

class PlayScene;

class HealEffect : public Engine::Sprite {
protected:
    PlayScene* getPlayScene();
    float timeTicks;
    std::vector<std::shared_ptr<ALLEGRO_BITMAP>> bmps;
    float timeSpan = 0.5;
public:
    HealEffect(float x, float y);
    void Update(float deltaTime) override;
};

#endif /* HealEffect_hpp */
