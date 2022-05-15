//
//  IceTurretDefense.hpp
//  TowerDefense
//
//  Created by wei on 2022/5/15.
//

#ifndef IceTurretDefense_hpp
#define IceTurretDefense_hpp

#include "Defense.hpp"

class IceTurretDefense: public Defense {
public:
    IceTurretDefense(float x, float y);
    void CreateBullet(Engine::Point pt) override;
};

#endif /* IceTurretDefense_hpp */
