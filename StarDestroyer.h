//
// Created by 2022 on 4/23/2024.
//

#ifndef FINAL_PROJECT_STARDESTROYER_H
#define FINAL_PROJECT_STARDESTROYER_H


#include "SpaceShip.h"
#include "MillenniumFalcon.h"
#include "Missile.h"


using namespace std;
class StarDestroyer: public SpaceShip {
    shared_ptr<Station> cur_dest;
    shared_ptr<MillenniumFalcon> target;
    unordered_set<shared_ptr<Missile>> missiles;
public:
    StarDestroyer(const string& name, const string& drv, const float& x, const float& y);
    StarDestroyer(const StarDestroyer&)=delete;
    StarDestroyer& operator=(const StarDestroyer&)=delete;
    StarDestroyer(StarDestroyer&& other)=default;
    StarDestroyer& operator=(StarDestroyer&& other)=default;
    ~StarDestroyer()=default;
    void shoot(shared_ptr<MillenniumFalcon> target);
    void destination(shared_ptr<Station> destination) override;
    void status() override;
    void updateMissiles();
    void go() override;
};


#endif //FINAL_PROJECT_STARDESTROYER_H
