//
// Created by 2022 on 4/23/2024.
//

#include "StarDestroyer.h"

StarDestroyer::StarDestroyer(const string &name, const string& drv, const float &x, const float &y):
        SpaceShip(name,"StarDestroyer",drv,x,y),cur_dest(nullptr){

}


void StarDestroyer::shoot(shared_ptr<MillenniumFalcon> trg) {
    this->target=trg;
    missiles.insert(make_shared<Missile>(MISSILE_SPEED,target,curX,curY)); //launch the missile
}

void StarDestroyer::status() {
    cout<<"destroyer "<<name<<" at ("<<curX<<", "<<curY<<"), ";
    switch (current_state) {

        case Stopped:
            cout<<"Stopped";
            break;
        case Docked:
            cout<<"Docked at "<<dest;
            break;
        case Dead:
            cout<<"Dead";
            break;
        case Moving:
            cout<<"Heading to "<<dest<<" speed "<<STARDESTROYER_SPEED<<"km/h";
            break;
        case Attack:
            cout<<"Stopped";
            break;
        case Position:
            cout<<"Heading to ("<<destX<<", "<<destY<<"), speed "<<STARDESTROYER_SPEED<<"km/h";
            break;
        case Course:
            cout<<"Heading on course "<<angle<<" deg, speed "<<STARDESTROYER_SPEED<<"km/h";
            break;
    }

}

void StarDestroyer::destination(shared_ptr<Station> destination) {
    SpaceShip::destination(destination);
    cur_dest=destination;
    stopped=false;
}


void StarDestroyer::go() {
    float arrival_time; // time needed to arrive to destination
    float radian;
    float distance;
    current_hour=HOUR; //minutes left for the current hour to end

    updateMissiles();// update the position of all the missile launched by this star destroyer

    if(!stopped) {
        while (current_hour > 0) {


            switch (current_state) {

                case Stopped: //this means we are stopped, but we got here because there is an order to move
                    current_state = Moving; //meaning we have a destination and ready to go
                    break;


                case Docked: // the start destroyer is currently docked and there is nothing to do
                    current_hour=0;
                    break;


                case Moving: //we are currently moving to a specific station
                    dest = cur_dest->getName();
                    destX = cur_dest->getX();
                    destY = cur_dest->getY();
                    arrival_time = arrivalTime(destX, destY);
                    if (arrival_time > current_hour) {// if we need more than the time left in this hour
                        calculateCoordinates(current_hour); //fix the new coordinates after the time left in this hour
                        current_hour = 0;
                    } else {//there is less than or equal to an hour to finish
                        calculateCoordinates(arrival_time); //fix the new coordinates after the time left
                        if(cur_dest!= nullptr) { // if we arrived to a station
                            current_state = Docked;
                            cur_dest= nullptr;
                        }
                        else //if we arrived to a custom coordinates
                            current_state=Stopped;

                        stopped= true;
                        current_hour=0;
                    }
                    break;


                case Position: // we are heading to a specific coordinates
                    arrival_time = arrivalTime(destX,destY);
                    if (arrival_time > current_hour) {// if we need more than the time left in this hour
                        calculateCoordinates(current_hour);
                        current_hour=0;
                    }else{
                        calculateCoordinates(arrival_time);
                        current_state=Stopped;
                        current_hour = 0;
                        stopped= true;
                    }
                    break;


                case Course: //we are traveling on by an angle
                    radian = angle * M_PI / 180.0; //converting angle to radians
                    distance = (STARDESTROYER_SPEED / 1000) * 1; //relative distance
                    curX = curX + distance * cos(radian); // x+deltaX
                    curY = curY + distance * sin(radian);// y+deltaY
                    current_hour = 0;
                    break;

                case Dead:
                    break;
                case Attack:
                    break;
            }
        }
    }
}

void StarDestroyer::updateMissiles() {
    auto tmp=missiles;
    for(const auto& it:tmp) {
        if(it->missionEnded()) // if the missile got to the coordinates
            missiles.erase(it);
        else
            it->go();
    }
}



