//
// Created by 2022 on 5/8/2024.
//

#ifndef FINAL_PROJECT_MISSILE_H
#define FINAL_PROJECT_MISSILE_H


#include "MillenniumFalcon.h"

class Missile :public SpaceShip{
    shared_ptr<MillenniumFalcon> target;
    bool mission_ended;
public:
    Missile(const float& speed,shared_ptr<MillenniumFalcon> target,const float &curX,const float &curY);
    Missile(const Missile&)=delete;
    Missile& operator=(const Missile&)=delete;
    Missile(Missile&& other)=default;
    Missile& operator=(Missile&& other)=default;
    ~Missile()=default;
    void go() override;
    bool missionEnded() const;
private://can't delete a non-deleted base function, so I made them private with an empty implementation
    void position(const float& x,const float& y,const float & spd=0) override;
    void destination(shared_ptr<Station> destination)override;
    void course(const float& angle,const float & spd=0)override;
    void status()override;
};


#endif //FINAL_PROJECT_MISSILE_H
