//
// Created by 2022 on 4/23/2024.
//

#include "MillenniumFalcon.h"

MillenniumFalcon::MillenniumFalcon(const string &name, const float &x, const float &y):
                        SpaceShip(name,"MillenniumFalcon","MillenniumFalcon",x,y),strength(5),speed(0),success(false) {

}

void MillenniumFalcon::position(const float &x, const float &y, const float &spd) {
    if(spd>MAX_SPEED)
        throw Exceptions("ERROR: Max speed is 3000km/h");
    if(current_state!=Dead) {
        SpaceShip::position(x, y);
        this->speed = spd;
    }
}

void MillenniumFalcon::course(const float &angle, const float &spd) {
    if(spd>MAX_SPEED)
        throw Exceptions("ERROR: Max speed is 3000km/h");
    if(current_state!=Dead) {
        SpaceShip::course(angle);
        this->speed = spd;
    }
}

void MillenniumFalcon::attack(shared_ptr<Shuttle> trg,const bool& successful) {
    if(current_state!=Dead) {
        this->target = trg;
        destX=destY=0;
        this->success = successful;
        current_state = Attack;
        stopped = false;
    }
}

void MillenniumFalcon::status() {
    cout<<"falcon "<<name<<" at ("<<curX<<", "<<curY<<"), ";
    switch (current_state) {

        case Stopped:
            cout<<"Stopped, Strength: "<<strength;
            break;
        case Dead:
            cout<<"Dead";
            break;
        case Attack:
            cout<<"Stopped, Strength: "<<strength;
            break;
        case Position:
            cout<<"Heading to ("<<destX<<", "<<destY<<"), speed "<<speed<<"km/h, Strength: "<<strength;
            break;
        case Course:
            cout<<"Heading on course "<<angle<<" deg, speed "<<speed<<"km/h, Strength: "<<strength;
            break;
        case Docked:
            break;
        case Moving:
            break;
    }

}

void MillenniumFalcon::go() {
    float radian;
    float distance;
    float arrival_time; // time needed to arrive to destination
    current_hour=HOUR; //minutes left for the current hour to end

    if(!stopped) {
        while (current_hour > 0) {


            switch (current_state) {

                case Stopped:
                    current_hour=0;
                    break;


                case Docked:
                    current_hour=0;
                    break;


                case Dead:
                    current_hour=0;
                    break;


                case Moving: //this works for destination function which falcon dosen't have
                    current_hour=0;
                    break;


                case Position: // we are heading to a specific coordinates
                    arrival_time = arrivalTime(destX,destY,speed);
                    if (arrival_time > current_hour) {// if we need more than the time left in this hour
                        calculateCoordinates(current_hour,speed);
                        current_hour=0;
                    }else{
                        calculateCoordinates(arrival_time,speed);
                        current_state=Stopped;
                        current_hour = 0;
                        stopped= true;
                    }
                    break;


                case Course: //we are traveling on by an angle
                    radian = angle * M_PI / 180.0; //converting angle to radians
                    distance = (speed / 1000) * 1; //relative distance
                    curX = curX + distance * cos(radian); // x+deltaX
                    curY = curY + distance * sin(radian);// y+deltaY
                    current_hour = 0;
                    break;

                case Attack:
                    if(success){
                        target->hit();
                        if(strength<MAX_ATTACK)
                            strength++;
                    }else{
                        strength--;
                        if(strength==0) {
                            die();
                            current_hour=0;
                            target= nullptr;
                            break;
                        }
                    }
                    target= nullptr;
                    current_state=Stopped;
                    current_hour=0;
                    stopped=true;
                    break;
            }
        }
    }
}


void MillenniumFalcon::die() {
    current_state=Dead;
    target= nullptr;
    destX=destY=angle=0;
    dest = "";
    stopped=true;
}

int MillenniumFalcon::getStrngth() const {
    return strength;
}

void MillenniumFalcon::destination(shared_ptr<Station> destination) {

}
