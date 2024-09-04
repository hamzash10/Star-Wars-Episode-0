//
// Created by 2022 on 4/23/2024.
//

#include "Shuttle.h"

Shuttle::Shuttle(const string &name, const string& drv, const float &x, const float &y):
            SpaceShip(name,"Shuttle",drv,x,y),strength(10),cargo(0),loading_time_left(HOUR){
}

void Shuttle::status() {
    cout<<"shuttle "<<name<<" at ("<<curX<<", "<<curY<<"), ";
    switch (current_state) {

        case Stopped:
            cout<<"Stopped, Strength: "<<strength;
            break;
        case Docked:
            cout<<"Docked at "<<dest<<", Strength: "<<strength;
            break;
        case Dead:
            cout<<"Dead";
            break;
        case Moving:
            cout<<"Heading to "<<dest<<" speed "<<SHUTTLE_SPEED<<"km/h, Strength: "<<strength;
            break;
        case Attack:
            cout<<"Stopped, Strength: "<<strength;
            break;
        case Position:
            cout<<"Heading to ("<<destX<<", "<<destY<<"), speed "<<SHUTTLE_SPEED<<"km/h, Strength: "<<strength;
            break;
        case Course:
            cout<<"Heading on course "<<angle<<" deg, speed "<<SHUTTLE_SPEED<<"km/h, Strength: "<<strength;
            break;
    }

}

void Shuttle::start_supply(const shared_ptr<Station>& source,const shared_ptr<Station>& dest) {
    if(current_state!=Dead) {
        orders.push(source);
        orders.push(dest);
        stopped = false;
    }
}

//skips one hour of time
void Shuttle::go() {
    float arrival_time=0; // time needed to arrive to destination

    current_hour=HOUR; //minutes left for the current hour to end
    if(!stopped) {
        while (current_hour > 0) {

            if (orders.empty()) // if there is no orders do nothing
                return;

            switch (current_state) {

                case Stopped:
                    current_state = Moving;
                    break;


                case Docked:
                    destX = destY = 0;
                    if (orders.front()->getType() == "SpaceStation") { //if we arrived at a space station

                        if (current_hour >= loading_time_left) {
                            cargo = orders.front()->load(); //load as many crystals as possible then move
                            orders.pop(); //delete the order
                            if (!orders.empty())
                                current_state = Moving;
                            current_hour -= loading_time_left;
                            loading_time_left = HOUR;
                        } else {
                            loading_time_left -= current_hour;
                            current_hour = 0;
                        }


                    } else { //if we arrived at a space fortress

                        if (current_hour >= loading_time_left) { // if there is enough time to unload the crystals
                            orders.front()->load(cargo); //unload
                            cargo = 0;
                            orders.pop(); //remove the order
                            if (strength < MAX_STRENGTH) //add strength
                                strength++;
                            current_state = Moving;
                            current_hour -= loading_time_left;
                            loading_time_left = HOUR;
                        } else {
                            loading_time_left -= current_hour;
                            current_hour = 0;
                        }
                    }
                    break;


                case Moving: //if we are moving then there is a task being progressed
                    dest = orders.front()->getName();
                    destX = orders.front()->getX();
                    destY = orders.front()->getY();
                    arrival_time = arrivalTime(destX, destY);
                    if (arrival_time > current_hour) {// if we need more than the time left in this hour
                        calculateCoordinates(current_hour); //fix the new coordinates after the time left in this hour
                        current_hour = 0;
                    } else {//there is less than or equal to an hour to finish
                        calculateCoordinates(arrival_time); //fix the new coordinates after the time left
                        current_state = Docked;
                        current_hour -= arrival_time; //time left of the hour after arriving
                    }
                    break;

                case Dead:
                    break;
                case Attack:
                    break;
                case Position:
                    break;
                case Course:
                    break;
            }
        }
    }

}

void Shuttle::hit() {
    strength--;
    if(strength==0)
        current_state=Dead;
    cargo=0;
    while(!orders.empty())
        orders.pop();
    current_state=Stopped;
    stopped= true;
}

int Shuttle::getStrngth() const {
    return strength;
}



void Shuttle::position(const float &x, const float &y, const float &spd) {
}

void Shuttle::course(const float &angle, const float &spd) {

}


