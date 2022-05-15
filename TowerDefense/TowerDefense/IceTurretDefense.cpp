//
//  IceTurretDefense.cpp
//  TowerDefense
//
//  Created by wei on 2022/5/15.
//


#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "IceTurretDefense.hpp"
#include "AudioHelper.hpp"
#include "IceTurretBullet.hpp"
#include "Group.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"
#include "Army.hpp"

//Defense(std::string imgDefense, float x, float y, float radius, float coolDown, int hp, int id, float shootRadius);
IceTurretDefense::IceTurretDefense(float x, float y) :
    Defense("play/bullet-1.png", x, y, 20, 0.5, 25, 3, 525) {
    // Move center downward, since we the turret head is slightly biased upward.
    Anchor.y += 8.0f / GetBitmapHeight();
}

void IceTurretDefense::CreateBullet(Engine::Point pt) {
    int dx = pt.x - Position.x;
    int dy = pt.y - Position.y;
    double len = sqrt(pow(dx, 2) + pow(dy, 2));
    Engine::Point diff = Engine::Point(dx / len, dy / len);
    Engine::Point rotateDiff = Engine::Point(cos(Rotation - ALLEGRO_PI / 2), sin(Rotation - ALLEGRO_PI / 2));
    float rotation = atan2(rotateDiff.y, rotateDiff.x) + ALLEGRO_PI / 2;
    getPlayScene()->BulletGroup->AddNewObject(new IceTurretBullet(Position , diff, rotation, this));
    AudioHelper::PlayAudio("laser.wav");
}
