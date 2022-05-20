//
//  AngelArmy.hpp
//  TowerDefense
//
//  Created by wei on 2022/5/20.
//

#ifndef AngelArmy_hpp
#define AngelArmy_hpp

#include "Army.hpp"

class AngelArmy: public Army {
public:
    AngelArmy(float x, float y);
    void Update(float deltaTime) override;
    void CreateBullet(Engine::Point pt) override;
    void Hit(float damage) override;
};

#endif /* AngelArmy_hpp */
