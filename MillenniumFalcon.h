//
// Created by 2022 on 4/23/2024.
//

#ifndef FINAL_PROJECT_MILLENNIUMFALCON_H
#define FINAL_PROJECT_MILLENNIUMFALCON_H


#include "SpaceShip.h"
#include "Shuttle.h"

const int MAX_ATTACK=20;
const int MAX_SPEED=3000;// km/h
using namespace std;
class MillenniumFalcon : public SpaceShip {
    int strength;
    float speed;
    shared_ptr<Shuttle> target;
    bool success;
public:
    MillenniumFalcon(const string& name,const float& x,const float& y);
    MillenniumFalcon(const MillenniumFalcon&)=delete;
    MillenniumFalcon& operator=(const MillenniumFalcon&)=delete;
    MillenniumFalcon(MillenniumFalcon&& other) noexcept =default;
    MillenniumFalcon& operator=(MillenniumFalcon&& other) =default;
    ~MillenniumFalcon()=default;
    void position(const float&x,const float& y, const float& spd) override;
    void course(const float& angle, const float& spd) override;
    void attack(shared_ptr<Shuttle> target,const bool& successful);
    void status() override;
    void die();
    void go() override;
    int getStrngth() const;

private://can't delete a non-deleted base function, so I made them private with an empty implementation
    void destination(shared_ptr<Station> destination)override;
};


#endif //FINAL_PROJECT_MILLENNIUMFALCON_H
