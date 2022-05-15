//
//  TankArmy.hpp
//  TowerDefense
//
//  Created by wei on 2022/5/15.
//

#ifndef TankArmy_hpp
#define TankArmy_hpp

#include "Army.hpp"

class TankArmy: public Army {
public:
    TankArmy(float x, float y);
    void Update(float deltaTime) override;
    void CreateBullet(Engine::Point pt) override;
    void Hit(float damage) override;
};

#endif /* TankArmy_hpp */
