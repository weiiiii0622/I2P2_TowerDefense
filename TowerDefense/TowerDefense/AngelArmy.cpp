//
//  AngelArmy.cpp
//  TowerDefense
//
//  Created by wei on 2022/5/20.
//


#include <allegro5/base.h>
#include <allegro5/color.h>
#include <allegro5/allegro_primitives.h>
#include <cmath>
#include <string>

#include "AudioHelper.hpp"
#include "Collider.hpp"
#include "Army.hpp"
#include "Group.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"
#include "AngelArmy.hpp"
#include "AngelBullet.hpp"
#include "Defense.hpp"
#include "LOG.hpp"


//Army(std::string img, float x, float y, float radius, float coolDown, float speed, float hp, int id, float shootRadius);
AngelArmy::AngelArmy(float x, float y) :
    Army("play/angel.png", x, y, 20, 2, 10, 10, 3, 300) {
    max_HP = 10;
    // Move center downward, since we the army head is slightly biased upward.
    Anchor.y += 8.0f / GetBitmapHeight();
}
void AngelArmy::Update(float deltaTime) {
    PlayScene* scene = getPlayScene();
    //Engine::LOG() << "Hi Army";

    if (isPreview) return ;
    
    // position
    int x = static_cast<int>(floor(Position.x / PlayScene::BlockSize));
    int y = static_cast<int>(floor(Position.y / PlayScene::BlockSize));
    
    if (!Heal_Target) {
        // Lock closet target
        // Can be improved by Spatial Hash, Quad Tree, ...
        // However simply loop through all enemies is enough for this program.
        
        int maxDis = INT_MAX;
        Army* tgt = nullptr;
        for (auto& it : scene->ArmyGroup->GetObjects()) {
            Army* tmp = dynamic_cast<Army*>(it);
            if(tmp->id == 3) continue;
            int dis = ManHattanDistance(it->Position);
            if (dis < maxDis) {
                maxDis = dis;
                tgt = tmp;
            }
        }
        if(tgt) Engine::LOG() << "Heal Target: " << tgt->id;
        
        if(tgt == nullptr){
            Position.x += 0;
            Position.y += 0;
            return;
        }
        
        if (tgt) {
            Heal_Target = tgt;
        }

    }
    if (Heal_Target) {
        Rotation = UpdateRotation(deltaTime, Heal_Target->Position);
        reload -= deltaTime;
        if(Heal_Target->GetHP() <= 0){
            Heal_Target = nullptr;
        }
        else{
            Engine::LOG() <<"current HP" <<Heal_Target->GetHP();
            
            if (reload <= 0) {
                // shoot.
                reload = coolDown;
                if (InShootingRange(Heal_Target->Position))
                    CreateBullet(Heal_Target->Position);
            }
            if (InShootingRange(Heal_Target->Position)) {
                Velocity = Engine::Point(0, 0);
            }
            else{
                int dx = Heal_Target->Position.x - Position.x;
                int dy = Heal_Target->Position.y - Position.y;
                double len = sqrt(pow(dx, 2) + pow(dy, 2));
                Velocity = speed * Engine::Point(dx / len, dy / len);
            }
        }

    }
    Velocity = Velocity * speed;
    Position.x += Velocity.x * deltaTime;
    Position.y += Velocity.y * deltaTime;
}

// Since the tank army cannot shoot, the function doesn't need to do anything.
void AngelArmy::CreateBullet(Engine::Point pt) {
    Engine::LOG() << "Angel Bullet created";
    int dx = pt.x - Position.x;
    int dy = pt.y - Position.y;
    double len = sqrt(pow(dx, 2) + pow(dy, 2));
    Engine::Point diff = Engine::Point(dx / len, dy / len);
    Engine::Point rotateDiff = Engine::Point(cos(Rotation - ALLEGRO_PI / 2), sin(Rotation - ALLEGRO_PI / 2));
    float rotation = atan2(rotateDiff.y, rotateDiff.x) + ALLEGRO_PI / 2;
    getPlayScene()->BulletGroup->AddNewObject(new AngelBullet(Position, diff, rotation, this));
    AudioHelper::PlayAudio("missile.wav");
}

void AngelArmy::Hit(float damage) {
    HP -= damage;
    if (HP <= 0) {
        //OnExplode();
        // Remove all Defense's reference to target.
        for (auto& it: lockedDefenses)
            it->Target = nullptr;
        getPlayScene()->ArmyGroup->RemoveObject(objectIterator);
        AudioHelper::PlayAudio("explosion.wav");
    }
}
