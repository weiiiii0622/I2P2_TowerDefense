//
//  IceSpell.cpp
//  TowerDefense
//
//  Created by wei on 2022/5/15.
//


#include <allegro5/base.h>
#include <allegro5/color.h>
#include <allegro5/allegro_primitives.h>
#include <cmath>
#include <string>
#include <limits>

#include "AudioHelper.hpp"
#include "Collider.hpp"
#include "Army.hpp"
#include "Group.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"
#include "IceSpell.hpp"
#include "Defense.hpp"

#include "LOG.hpp"


//Army(std::string img, float x, float y, float radius, float coolDown, float speed, float hp, int id, float shootRadius);
IceSpell::IceSpell(float x, float y) :
    Army("play/icecube.png", x, y, 20, 0, 0, 0, 10, 3) {
    // Move center downward, since we the army head is slightly biased upward.
    Anchor.y += 8.0f / GetBitmapHeight();
    death_counter = al_create_timer(1.0f / 60);
    init = false;
    
}
void IceSpell::Update(float deltaTime) {
    // PlayScene
    PlayScene* scene = getPlayScene();
    bool die = 0;
    if (isPreview) return ;
    
    if(!init){
        init = true;
        al_start_timer(death_counter);
        getPlayScene()->EffectGroup->AddNewObject(img[0] = new Engine::Sprite("play/snowflake.png", Position.x-PlayScene::BlockSize, Position.y-PlayScene::BlockSize));
        getPlayScene()->EffectGroup->AddNewObject(img[1] = new Engine::Sprite("play/snowflake.png", Position.x, Position.y-PlayScene::BlockSize));
        getPlayScene()->EffectGroup->AddNewObject(img[2] = new Engine::Sprite("play/snowflake.png", Position.x+PlayScene::BlockSize, Position.y-PlayScene::BlockSize));
        getPlayScene()->EffectGroup->AddNewObject(img[3] = new Engine::Sprite("play/snowflake.png", Position.x-PlayScene::BlockSize, Position.y));
        getPlayScene()->EffectGroup->AddNewObject(img[4] = new Engine::Sprite("play/snowflake.png", Position.x, Position.y));
        getPlayScene()->EffectGroup->AddNewObject(img[5] = new Engine::Sprite("play/snowflake.png", Position.x+PlayScene::BlockSize, Position.y));
        getPlayScene()->EffectGroup->AddNewObject(img[6] = new Engine::Sprite("play/snowflake.png", Position.x-PlayScene::BlockSize, Position.y+PlayScene::BlockSize));
        getPlayScene()->EffectGroup->AddNewObject(img[7] = new Engine::Sprite("play/snowflake.png", Position.x, Position.y+PlayScene::BlockSize));
        getPlayScene()->EffectGroup->AddNewObject(img[8] = new Engine::Sprite("play/snowflake.png", Position.x+PlayScene::BlockSize, Position.y+PlayScene::BlockSize));
    }
    
    
    if(al_get_timer_count(death_counter)/60.0 >= 3.0){
        al_stop_timer(death_counter);
        al_set_timer_count(death_counter, 0);
        Hit(999);
        die = true;
    }
    
    if(die) return;
    
    
    //getPlayScene()->ArmyGroup->RemoveObject(objectIterator);
    // position
    int x = static_cast<int>(floor(Position.x / PlayScene::BlockSize));
    int y = static_cast<int>(floor(Position.y / PlayScene::BlockSize));
    

    
    // Lock closet target
    // Can be improved by Spatial Hash, Quad Tree, ...
    // However simply loop through all enemies is enough for this program.

    // TODO 2 (6/8): Lock the closet wall. If there's no wall on the map, it will lock the closet defense.
    // For the simplicity, we use manHattan distance to measure the distance bewteen objects. You can use the ManHattanDistance() function in Army class directly for calculation.

    int maxDis = INT_MAX;
    Defense* tgt = nullptr;

    maxDis = INT_MAX;
    for (auto& it : scene->DefenseGroup->GetObjects()) {
        int dis = ManHattanDistance(it->Position);
        //Engine::LOG() << "Hi: " << dis;
        if(dis <= 2){
            tgt = dynamic_cast<Defense*>(it);
            tgt->setReload(MAXFLOAT);
            lockedDefenses.push_back(tgt);
        }
    }


    // TODO 2 (7/8): Store the closet target in Target, and update lockedArmyIterator. You can imitate the same part in Defense::Update().
    // Also, record the target is wall or a noraml defense.

    if (tgt) {
        Target = tgt;
    }
}
// Since the bomb army cannot shoot, the function doesn't need to do anything.
void IceSpell::CreateBullet(Engine::Point pt) {}

// TODO 2 (5/8): You can imitate the hit function in Army class. Notice that the bomb army won't have explosion effect.
void IceSpell::Hit(float damage) {
    HP -= damage;
    if (HP <= 0) {
        //OnExplode();
        // Remove all Defense's reference to target.
        for (auto& it: lockedDefenses){
            it->setReload(it->getCooldown());
            //Engine::LOG() << "reload: " << it->getCooldown();
        }
        for(int i=0; i<9; i++){
            getPlayScene()->EffectGroup->RemoveObject(img[i]->GetObjectIterator());
        }
        getPlayScene()->ArmyGroup->RemoveObject(objectIterator);
        AudioHelper::PlayAudio("explosion.wav");
    }
}
