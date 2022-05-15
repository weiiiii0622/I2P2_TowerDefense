//
//  IceSpell.hpp
//  TowerDefense
//
//  Created by wei on 2022/5/15.
//

#ifndef IceSpell_hpp
#define IceSpell_hpp

#include "Bullet.hpp"

#include "Army.hpp"

class IceSpell: public Army {
public:
    IceSpell(float x, float y);
    
    ALLEGRO_TIMER* death_counter;
    Engine::Sprite* img[9];
    bool init;
    
    void Update(float deltaTime) override;
    void CreateBullet(Engine::Point pt) override;
    void Hit(float damage) override;
};


#endif /* IceSpell_hpp */
