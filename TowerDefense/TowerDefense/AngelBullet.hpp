//
//  AngelBullet.hpp
//  TowerDefense
//
//  Created by wei on 2022/5/20.
//

#ifndef AngelBullet_hpp
#define AngelBullet_hpp

#include "ArmyBullet.hpp"

class Army;
class Defense;
namespace Engine {
struct Point;
}  // namespace Engine

class AngelBullet: public ArmyBullet{
public:
    explicit AngelBullet(Engine::Point position, Engine::Point forwardDirection, float rotation, Army* parent);
    void OnExplode(Defense* defense) override;
    void OnHeal(Army* army);
    void Update(float deltaTime) override;
};

#endif /* AngelBullet_hpp */
