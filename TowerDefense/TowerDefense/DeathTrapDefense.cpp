//
//  DeathTrapDefense.cpp
//  TowerDefense
//
//  Created by wei on 2022/5/15.
//


#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "DeathTrapDefense.hpp"
#include "AudioHelper.hpp"
#include "Group.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"
#include "Army.hpp"
#include "Defense.hpp"
#include "Collider.hpp"

#include "LOG.hpp"

//Defense(std::string imgDefense, float x, float y, float radius, float coolDown, int hp, int id, float shootRadius);
DeathTrapDefense::DeathTrapDefense(float x, float y) :
    Defense("play/skeleton.png", x, y, 20, 0.5, 1, 4, 100) {
    // Move center downward, since we the turret head is slightly biased upward.
    Anchor.y += 8.0f / GetBitmapHeight();
    Visible = false;
    Engine::LOG() << "Init Death Trap";
}

void DeathTrapDefense::CreateBullet(Engine::Point pt) {
//    int dx = pt.x - Position.x;
//    int dy = pt.y - Position.y;
//    double len = sqrt(pow(dx, 2) + pow(dy, 2));
//    Engine::Point diff = Engine::Point(dx / len, dy / len);
//    Engine::Point rotateDiff = Engine::Point(cos(Rotation - ALLEGRO_PI / 2), sin(Rotation - ALLEGRO_PI / 2));
//    float rotation = atan2(rotateDiff.y, rotateDiff.x) + ALLEGRO_PI / 2;
//    getPlayScene()->BulletGroup->AddNewObject(new IceTurretBullet(Position , diff, rotation, this));
//    AudioHelper::PlayAudio("laser.wav");
}

// Update at Group.cpp
void DeathTrapDefense::Update(float deltaTime){
    Sprite::Update(deltaTime);
    // PlayScene
    PlayScene* scene = getPlayScene();
    
    //Engine::LOG() << getPlayScene()->DebugMode;
    if(scene->DebugMode == true){
        Visible = true;
    }
    else{
        Visible = false;
    }
    
    for (auto& it : scene->ArmyGroup->GetObjects()) {
        Army* army= dynamic_cast<Army*>(it);
        if (!army->Visible)
            continue;
        if (Engine::Collider::IsCircleOverlap(Position, CollisionRadius, army->Position, army->CollisionRadius)) {
            Hit(999);
            return;
        }
    }
    
}

void DeathTrapDefense::Hit(float damage){
    HP -= damage;
    if (HP <= 0) {
        PlayScene* scene = getPlayScene();
        OnExplode();
        // Remove all armies' reference to target
        for (auto& it : lockedArmies)
            it->Target = nullptr;
        int x = static_cast<int>(floor(Position.x / PlayScene::BlockSize));
        int y = static_cast<int>(floor(Position.y / PlayScene::BlockSize));
        
        Army* tgt = nullptr;
        for (auto& it : scene->ArmyGroup->GetObjects()) {
            if(InShootingRange(it->Position)){
                tgt = dynamic_cast<Army*>(it);
                tgt->Hit(999);
            }
        }
        
        getPlayScene()->ClearMapState(x, y);
        getPlayScene()->DefenseGroup->RemoveObject(objectIterator);
        AudioHelper::PlayAudio("explosion.wav");
    }
}
