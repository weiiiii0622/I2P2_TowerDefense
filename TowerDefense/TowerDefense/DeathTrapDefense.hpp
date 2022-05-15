//
//  DeathTrapDefense.hpp
//  TowerDefense
//
//  Created by wei on 2022/5/15.
//

#ifndef DeathTrapDefense_hpp
#define DeathTrapDefense_hpp

#include "Defense.hpp"

class DeathTrapDefense: public Defense {
public:
    DeathTrapDefense(float x, float y);
    void CreateBullet(Engine::Point pt) override;
    
    void Hit(float damage) override;
    void Update(float deltaTime) override;
};

#endif /* DeathTrapDefense_hpp */
