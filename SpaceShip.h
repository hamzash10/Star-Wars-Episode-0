//
// Created by 2022 on 4/23/2024.
//

#ifndef FINAL_PROJECT_SPACESHIP_H
#define FINAL_PROJECT_SPACESHIP_H
#include <iostream>
#include <memory>
#include "Station.h"
#include <cmath>
#include <unordered_set>
#include <queue>
#include "Exceptions.h"


const float SHUTTLE_SPEED=500;// km/h
const float TIEBOMBER_SPEED=1000;// km/h
const float STARDESTROYER_SPEED=2000;//2000km
const int MISSILE_SPEED=3000;// km/h

using namespace std;
enum state{
    Stopped,
    Docked,
    Dead,
    Moving,
    Attack, //the same as Stopped but when attacking
    Position, // Moving using coordinates
    Course //moving using an angel
};

const int HOUR=60;

class SpaceShip {
protected:
    string name,type,driver,dest;
    state current_state;
    float curX,curY;
    float destX,destY;
    float angle;
    float current_hour;// how many minutes left in the current hour
    float arrivalTime(const float& x, const float& y,const float& falcon_speed=0);
    void calculateCoordinates(const float& time,const float& falcon_speed=0);
    static int stations_number;
    bool stopped;
public:
    SpaceShip(const string& name,const string& type,const string& driver,const float& startX=0,const float& startY=0,const float& destX=0,const float& destY=0,const float& angle=0);
    SpaceShip(const SpaceShip&)=delete;
    SpaceShip& operator=(const SpaceShip&)=delete;
    SpaceShip(SpaceShip&& other)=default;
    SpaceShip& operator=(SpaceShip&& other)=default;
    ~SpaceShip()=default;
    void stop();
    const string& getType();
    virtual void position(const float& x,const float& y,const float & spd=0); //set the destination by (x,y)
    virtual void destination(shared_ptr<Station> destination);
    virtual void course(const float& ang,const float & spd=0);
    virtual void status();
    pair<float,float> getCoordinates();
    virtual void go()=0;
    static void setStationsNumber(const int& n);

};


#endif //FINAL_PROJECT_SPACESHIP_H
