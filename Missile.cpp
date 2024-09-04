//
// Created by 2022 on 5/8/2024.
//

#include "Missile.h"

Missile::Missile(const float &speed,shared_ptr<MillenniumFalcon> target,const float &curX,const float &curY):
                SpaceShip("Missile","Missile","Missile",curX,curY,target->getCoordinates().first,target->getCoordinates().second)
                ,target(target),mission_ended(false){
    current_state=Moving;
    stopped=false;
}

void Missile::go() {
    if(!stopped) {
        float arrival_time = arrivalTime(destX, destY);
        if (arrival_time > current_hour) {// if we need more than the time left in this hour
            calculateCoordinates(current_hour); //fix the new coordinates after the time left in this hour
        } else {//there is less than or equal to an hour to finish
            calculateCoordinates(arrival_time); //fix the new coordinates after the time left
            //check if the missile hit the target
            auto target_coordinates = target->getCoordinates();
            if (destX == target_coordinates.first && destY == target_coordinates.second) //check if the missile coordinates hit the new falcon coordinates
                target->die();
            mission_ended = true;
            stopped = true;
        }
    }
}


bool Missile::missionEnded() const {
    return mission_ended;
}

void Missile::position(const float &x, const float &y, const float &spd) {
}

void Missile::destination(shared_ptr<Station> destination) {
}

void Missile::course(const float &angle, const float &spd) {
}

void Missile::status() {

}
