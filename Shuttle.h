//
// Created by 2022 on 4/23/2024.
//

#ifndef FINAL_PROJECT_SHUTTLE_H
#define FINAL_PROJECT_SHUTTLE_H


#include "SpaceShip.h"
#include "SpaceStation.h"
#include "FortressStar.h"



const int MAX_STRENGTH=20;
const int CAPACITY=5;
using namespace std;


class Shuttle : public SpaceShip {
    queue<shared_ptr<Station>> orders; // each start_supply call adds two new destinations
    int strength;
    int cargo; // the number of crystals the ship is carrying
    float loading_time_left;// how many loading time left to finish
public:
    Shuttle(const string& name,const string& drv,const float& x, const float& y);
    Shuttle(const Shuttle&)=delete;
    Shuttle& operator=(const Shuttle&)=delete;
    Shuttle(Shuttle&& other) noexcept =default;
    Shuttle& operator=(Shuttle&& other) =default;
    ~Shuttle()=default;
    void status() override;
    void start_supply(const shared_ptr<Station>& source,const shared_ptr<Station>& dest);
    void go() override;
    void hit();
    int getStrngth() const;

private: //can't delete a non-deleted base function, so I made them private with an empty implementation
    void position(const float& x,const float& y,const float & spd=0) override;
    void course(const float& angle,const float & spd=0) override;
};


#endif //FINAL_PROJECT_SHUTTLE_H
