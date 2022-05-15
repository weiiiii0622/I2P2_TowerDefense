//
//  IceTurretBullet.hpp
//  TowerDefense
//
//  Created by wei on 2022/5/15.
//

#ifndef IceTurretBullet_hpp
#define IceTurretBullet_hpp

#include "Bullet.hpp"

class Army;
class Defense;
namespace Engine {
struct Point;
}  // namespace Engine

class IceTurretBullet : public Bullet {
public:
    explicit IceTurretBullet(Engine::Point position, Engine::Point forwardDirection, float rotation, Defense* parent);
    void Update(float deltaTime) override;
};

#endif /* IceTurretBullet_hpp */
