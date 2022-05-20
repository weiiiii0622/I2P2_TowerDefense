//
//  AngelBullet.cpp
//  TowerDefense
//
//  Created by wei on 2022/5/20.
//

#include <allegro5/base.h>
#include <random>
#include <string>

#include "AudioHelper.hpp"
#include "Army.hpp"
#include "Collider.hpp"
#include "DirtyEffect.hpp"
#include "AngelBullet.hpp"
#include "HealEffect.hpp"
#include "Group.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"
#include "Defense.hpp"
#include "LOG.hpp"

class Defense;

//ArmyBullet::ArmyBullet(std::string img, float speed, float damage, Engine::Point position, Engine::Point forwardDirection, float rotation, Army* parent)
AngelBullet::AngelBullet(Engine::Point position, Engine::Point forwardDirection, float rotation, Army* parent) :
    ArmyBullet("play/hp.png", 75, -5, position, forwardDirection, rotation - ALLEGRO_PI / 2, parent) {
}

void AngelBullet::OnExplode(Defense *defense) {
    // TODO 3 (1/2): Add a ShootEffect here. Remember you need to include the class.
    //getPlayScene()->EffectGroup->AddNewObject(new HealEffect(defense->Position.x , defense->Position.y));
}

void AngelBullet::OnHeal(Army *army){
    getPlayScene()->EffectGroup->AddNewObject(new HealEffect(army->Position.x , army->Position.y));
}

void AngelBullet::Update(float deltaTime){
    Sprite::Update(deltaTime);
    PlayScene* scene =   getPlayScene();
    // Can be improved by Spatial Hash, Quad Tree, ...
    // However simply loop through all enemies is enough for this program.
    
    for (auto& it : scene->ArmyGroup->GetObjects()) {
        Army* tgt = dynamic_cast<Army*>(it);
        if(tgt->id == 3) continue;
        if (Engine::Collider::IsCircleOverlap(Position, CollisionRadius, tgt->Position, tgt->CollisionRadius)) {
            //OnExplode(defense);
            AudioHelper::PlayAudio("heal.wav");
            OnHeal(tgt);
            Engine::LOG() << "Heal id: " << tgt->id << " hp: " << -damage;
            tgt->Hit(damage);
            getPlayScene()->BulletGroup->RemoveObject(objectIterator);
            return;
        }
    }
    // Check if out of boundary.
    if (Position.x < 0 || Position.x > PlayScene::GetClientSize().x || Position.y < 0 || Position.y > PlayScene::GetClientSize().y)
        getPlayScene()->BulletGroup->RemoveObject(objectIterator);
}
