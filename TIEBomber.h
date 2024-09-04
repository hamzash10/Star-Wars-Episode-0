//
// Created by 2022 on 4/23/2024.
//

#ifndef FINAL_PROJECT_TIEBOMBER_H
#define FINAL_PROJECT_TIEBOMBER_H


#include "SpaceShip.h"


using namespace std;


class TIEBomber : public SpaceShip {
    string start_station;
    shared_ptr<Station> starting_dest;
    shared_ptr<Station> cur_dest;
    bool patrol_started,patrol_done;
    unordered_set<string> visited;
public:
    TIEBomber(const string& name,const string& drv,const string& start,const float& x, const float& y);
    TIEBomber(const string& name,const string& drv,const float& x, const float& y);
    TIEBomber(const TIEBomber&)=delete;
    TIEBomber& operator=(const TIEBomber&)=delete;
    TIEBomber(TIEBomber&& other)=default;
    TIEBomber& operator=(TIEBomber&& other)=default;
    ~TIEBomber()=default;
    void destination(shared_ptr<Station> destination) override;
    void status() override;
    void go() override;
};


#endif //FINAL_PROJECT_TIEBOMBER_H
