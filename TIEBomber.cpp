//
// Created by 2022 on 4/23/2024.
//

#include "TIEBomber.h"

TIEBomber::TIEBomber(const string &name, const string& drv, const string& start,const float& x, const float& y):
                        SpaceShip(name,"TIEBomber",drv,x,y),start_station(start),patrol_started(false),patrol_done(false) {

}

TIEBomber::TIEBomber(const string &name, const string &drv, const float &x, const float &y):
        SpaceShip(name,"TIEBomber",drv,x,y),patrol_started(false),patrol_done(false){

}

void TIEBomber::status() {
    cout<<"bomber "<<name<<" at ("<<curX<<", "<<curY<<"), ";
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
            cout<<"Heading to "<<dest<<" speed "<<TIEBOMBER_SPEED<<"km/h";
            break;
        case Attack:
            cout<<"Stopped";
            break;
        case Position:
            cout<<"Heading to ("<<destX<<", "<<destY<<"), speed "<<TIEBOMBER_SPEED<<"km/h";
            break;
        case Course:
            cout<<"Heading on course "<<angle<<" deg, speed "<<TIEBOMBER_SPEED<<"km/h";
            break;
    }
}



void TIEBomber::destination(shared_ptr<Station> destination) {
    SpaceShip::destination(destination);
    starting_dest=destination;
    cur_dest=destination;
    patrol_started= true;// new patrol
    patrol_done=false;
    visited.clear(); //start over
    stopped=false;
}




void TIEBomber::go() {
    float radian;
    float distance;
    float arrival_time=0; // time needed to arrive to destination
    bool skip;
    current_hour=HOUR; //minutes left for the current hour to end

    if(!stopped) {
        while (current_hour > 0) {

            if (!patrol_started && patrol_done) // if the patrol is over and there is nothing to do
                return;

            switch (current_state) {

                case Stopped: //meaning we have a destination and ready to go
                    cur_dest = starting_dest;
                    current_state = Moving;
                    break;


                case Docked: //we arrived at a destination and getting checking the closest unvisited station
                    if (!patrol_done) {
                        skip = false;
                        for (int i = 0; i < stations_number; ++i) {
                            if (visited.find(cur_dest->getClosest(i)->getName()) ==
                                visited.end()) { //if the closest station isn't visited
                                cur_dest = cur_dest->getClosest(i);
                                current_state = Moving;
                                skip = true;
                                break;
                            }
                        }
                        if (!skip) {
                            current_state = Moving; //moving back to the staring station
                            cur_dest = starting_dest;
                            patrol_started = false;
                        }
                    }
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
                        current_state = Docked;
                        current_hour -= arrival_time; //time left of the hour after arriving
                        visited.insert(cur_dest->getName());
                        if (!patrol_started && cur_dest == starting_dest)
                            patrol_done = true;
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


                case Course: //we are traveling on a by an angle
                    radian = angle * M_PI / 180.0; //converting angle to radians
                    distance = (TIEBOMBER_SPEED / 1000) * 1; //relative distance
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
