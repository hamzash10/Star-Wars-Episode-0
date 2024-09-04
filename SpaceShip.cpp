//
// Created by 2022 on 4/23/2024.
//

#include "SpaceShip.h"
int SpaceShip::stations_number=0;

SpaceShip::SpaceShip(const string& name,const string& type,const string& driver,const float& startX,const float& startY,const float &destX, const float &destY, const float &angle):
                        name(name),type(type),driver(driver),dest(),current_state(Stopped),curX(startX),curY(startY),
                        destX(destX),destY(destY),angle(angle),current_hour(HOUR),stopped(true) {

}

void SpaceShip::stop() {
    if(current_state!=Dead) {
        current_state = Stopped;
        destX = destY = 0;
        dest = "";
        angle = 0;
        stopped = true;
    }
}

void SpaceShip::position(const float &x, const float &y,const float & spd) {
    if(current_state!=Dead) {
        destX = x;
        destY = y;
        current_state = Position;
        stopped = false;
    }
}

void SpaceShip::course(const float &ang,const float & spd) {
    if(current_state!=Dead) {
        this->angle = ang;
        current_state = Course;
        stopped = false;
    }
}

void SpaceShip::status() {

}


pair<float, float> SpaceShip::getCoordinates() {
    return pair<float,float>{curX,curY};
}

void SpaceShip::destination(shared_ptr<Station> destination) {
    if(current_state!=Dead) {
        this->dest = destination->getName();
        destX = destination->getX();
        destY = destination->getY();
    }
}

const string &SpaceShip::getType() {
    return type;
}


float SpaceShip::arrivalTime(const float &x, const float &y,const float& falcon_speed) {
    float distance=sqrt(pow((x-curX)*1000,2)+pow((y-curY)*1000,2));
    if(type=="Shuttle")
        return distance/SHUTTLE_SPEED;
    else if(type=="TIEBomber")
        return distance/TIEBOMBER_SPEED;
    else if(type=="StarDestroyer")
        return distance/STARDESTROYER_SPEED;
    else if(type=="Missile")
        return distance/MISSILE_SPEED;
    //else is falcon
    return distance/falcon_speed;
}

void SpaceShip::calculateCoordinates(const float &time,const float& falcon_speed) {
    float distance; //distance after time and converting to the correct scale
    float correct_time=time/60;
    if(type=="Shuttle")
        distance=SHUTTLE_SPEED*correct_time/1000;
    else if(type=="TIEBomber")
        distance=TIEBOMBER_SPEED*correct_time/1000;
    else if(type=="StarDestroyer")
        distance= STARDESTROYER_SPEED*correct_time/1000;
    else if(type=="Missile")
        distance= MISSILE_SPEED*correct_time/1000;
    else //falcon
        distance=falcon_speed*correct_time/1000;

    float total_distance=sqrt(pow((destX - curX), 2) + pow((destY - curY), 2)); // total distance between the current and the destination coordinates
    double ration = distance / total_distance; // the traveled ration of the total distance

    //new coordinates
    curX= curX  + ration * (destX - curX);
    curY= curY + ration * (destY - curY);
}

void SpaceShip::setStationsNumber(const int &n) {
    stations_number=n;
}

