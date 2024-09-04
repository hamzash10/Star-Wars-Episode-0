//
// Created by 2022 on 4/23/2024.
//

#ifndef FINAL_PROJECT_MODEL_H
#define FINAL_PROJECT_MODEL_H

#include <iostream>
#include <memory>
#include <vector>
#include <unordered_map>
#include "ImperialAgent.h"
#include "AgentFactory.h"
#include "SpaceShip.h"
#include "Station.h"


const int UNIT=1000; //1000km
const int NORTH=0; //0 degrees
const int EAST=90; //0 degrees
const int SOUTH=180; //0 degrees
const int WEST=270; //0 degrees

using namespace std;
class Model {
private:
    static shared_ptr<Model> instance;
    Model();
    int stations_number;
    int current_time;
    shared_ptr<AgentFactory> midshipmanFactory;
    shared_ptr<AgentFactory> commanderFactory;
    shared_ptr<AgentFactory> admiralFactory;
    vector<shared_ptr<ImperialAgent>> agents;
    unordered_map<string,shared_ptr<SpaceShip>> ships; //storing each ship by name makes searching much more efficient
    unordered_map<string,shared_ptr<Station>> stations; //storing each station by name makes searching much more efficient

public:
    static shared_ptr<Model> getInstance();
    // Disabling the copy/move semantics
    Model(const Model &) = delete;
    Model& operator=(const Model &) = delete;
    Model(Model &&) = delete;
    Model& operator=(Model &&) = delete;
    ~Model()=default;

    void addStation(const string& type,const string& name,const float& x,const float& y,const int& cap,const int& pro=0);
    int getTime() const;
    void status();
    void go();
    void create(const string& type,const string& name,const string& driver_name,const float& x,const float& y);
    pair<float,float> create(const string& type,const string& name,const string& driver_name,const string& station);
    void setCourse(const string& shipname,const float& angel,const float& spd=0);
    void setPosition(const string& shipname,const float& x,const float& y,const float & spd=0);
    void setDestination(const string& shipname,const string& dest);
    pair<float,float> getCoordinates(const string& shipname);
    void attack(const string& shipname,const string& target);
    void start_supply(const string& shipname,const string& src,const string& dest);
    void stop(const string& shipname);
    void shoot(const string& shipname,const float& x,const float& y);
    float distance(const float& x1,const float& y1,const float& x2,const float& y2);
};




#endif //FINAL_PROJECT_MODEL_H
