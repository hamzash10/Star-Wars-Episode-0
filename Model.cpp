//
// Created by 2022 on 4/23/2024.
//

#include <limits>
#include "Model.h"
#include "MidshipmanFactory.h"
#include "CommanderFactory.h"
#include "AdmiralFactory.h"
#include "FortressStar.h"
#include "SpaceStation.h"
#include "Exceptions.h"
#include "StarDestroyer.h"
#include "Shuttle.h"
#include "TIEBomber.h"
#include "MillenniumFalcon.h"

shared_ptr<Model> Model::instance = nullptr;


shared_ptr<Model> Model::getInstance() {
    if(instance == nullptr) {
        shared_ptr<Model> tmp(new Model);
        instance.swap(tmp);
    }
    return instance;
}

Model::Model(): stations_number(0), current_time(0) {
    midshipmanFactory= make_shared<MidshipmanFactory>();
    commanderFactory = make_shared<CommanderFactory>();
    admiralFactory= make_shared<AdmiralFactory>();
    stations["DS"]=make_shared<FortressStar>("DS",40,10,100000);
}

void Model::addStation(const string &type, const string &name, const float &x, const float &y, const int &cap,
                       const int &pro) {
    if(type=="station")
        stations[name]=make_shared<SpaceStation>(name,x,y,cap,pro);
    else if(type=="fortress"){
        stations[name]=make_shared<FortressStar>(name,x,y,cap);
    }else
        throw Exceptions("Invalid input type "+type);

    stations_number++;
    //for each station calculate the distance between it and the new station and save it in both
    for(const auto& station:stations){ // run through all the stations
        float dist= distance(x,y,station.second->getX(),station.second->getY());
        stations[name]->setDistance(dist,station.second); //saving the distance to the new station
        station.second->setDistance(dist,stations[name]); // saving the distance to the old station
    }

    SpaceShip::setStationsNumber(stations_number);
}

int Model::getTime() const {
    return current_time;
}

void Model::status() {
    for (const auto& station: stations) {
        station.second->status();
        cout << endl;
    }
    for (const auto& ship: ships) {
        ship.second->status();
        cout << endl;
    }
}

void Model::go() {
    for(const auto& station:stations)
        station.second->go();
    for(const auto& ship:ships)
        ship.second->go();
}

void Model::create(const string &type, const string &name, const string &driver_name, const float &x, const float &y) {

    //Imperial agents
    if(type=="admiral")
        agents.push_back(admiralFactory->createAgent(name));
    else if(type=="commander")
        agents.push_back(commanderFactory->createAgent(name));
    else if(type=="midshipman")
        agents.push_back(midshipmanFactory->createAgent(name));
    else {
        //Spaceships
        if (ships.find(name) != ships.end()) // if the ship already exist
            throw Exceptions("ERROR: Spaceship already exist");
        else if (type == "destroyer")
            ships[name] = make_shared<StarDestroyer>(name, driver_name, x, y);
        else if (type == "bomber")
            ships[name] = make_shared<TIEBomber>(name, driver_name, x, y);
        else if (type == "shuttle")
            ships[name] = make_shared<Shuttle>(name, driver_name, x, y);
        else if (type == "falcon")
            ships[name] = make_shared<MillenniumFalcon>(name, x, y);
        else {
            throw Exceptions("ERROR: Invalid input.");
        }
    }


}

pair<float, float> Model::create(const string &type, const string &name, const string &driver_name, const string &station) {
    if(stations.find(station) != stations.end()){
        if(type=="bomber")
            ships[name]=make_shared<TIEBomber>(name, driver_name, station,stations[station]->getX(),stations[station]->getY());
        else
            throw Exceptions("ERROR: Creating a ship by a starting station is only valid for TIEBombers");
    }else
        throw Exceptions("ERROR: Station doesn't exist");
    return pair<float, float>{stations[station]->getX(),stations[station]->getY()};
}

void Model::setCourse(const string &shipname, const float &angel, const float &spd) {
    if(ships.find(shipname)!=ships.end()) {
        if (ships[shipname]->getType() == "MillenniumFalcon" && spd == 0)
            throw Exceptions("ERROR: No falcon speed sent");
        ships[shipname]->course(angel, spd);
    }
    else
        throw Exceptions("ERROR: Ship doesn't exist");
}

pair<float, float> Model::getCoordinates(const string &shipname) {

    for(const auto& ship: ships){
        if(ship.first.substr(0,2)==shipname){
            return ship.second->getCoordinates();
        }
    }
    return pair<float, float>{numeric_limits<float>::max(),numeric_limits<float>::min()}; //null value
}

void Model::setPosition(const string &shipname, const float &x, const float &y, const float &spd) {
    if(ships.find(shipname)!=ships.end()) {
        if (ships[shipname]->getType() == "MillenniumFalcon" && spd == 0)
            throw Exceptions("ERROR: No falcon speed sent");
        ships[shipname]->position(x, y, spd);
    }
    else
        throw Exceptions("ERROR: Ship doesn't exist");
}

void Model::setDestination(const string& shipname,const string &dest) {
    if(ships.find(shipname)!=ships.end() && stations.find(dest)!=stations.end()) {
        if (ships[shipname]->getType() == "MillenniumFalcon")
            throw Exceptions("ERROR: Falcon doesn't support destination function");
        ships[shipname]->destination(stations[dest]);
    }
    else
        throw Exceptions("ERROR: Ship doesn't exist");
}

void Model::attack(const string &shipname, const string &target) {
    shared_ptr<MillenniumFalcon> falcon;
    shared_ptr<Shuttle> shuttle;
    if(ships[shipname]->getType()=="MillenniumFalcon" && ships[target]->getType()=="Shuttle"){
        falcon= dynamic_pointer_cast<MillenniumFalcon>(ships[shipname]);
        shuttle=dynamic_pointer_cast<Shuttle>(ships[target]);
    }else
        throw Exceptions("ERROR: One or two of ships isn't valid");

    //calculate distance between the shuttle and the falcon
    auto falcon_coor=falcon->getCoordinates();
    auto shuttle_coor=shuttle->getCoordinates();
    float dist= distance(falcon_coor.first,falcon_coor.second,shuttle_coor.first,shuttle_coor.second);

    //checking if there is a TIEBomber in 250 km radios.
    bool bomber=false;
    for(const auto& it:ships){
        if(it.second->getType()=="TIEBomber"){
            auto bomber_coor=it.second->getCoordinates();
            if(distance(shuttle_coor.first,shuttle_coor.second,bomber_coor.first,bomber_coor.second) <250 ){
                bomber= true;
                break;
            }
        }
    }
    //if the distance between the shuttle and the falcon is less or equal to 100km
    //and that the falcon's strength is bigger than the shuttle's
    //and there isn't a TIEBomber in a 250km radios
    //the attack succeeds
    if( dist<=100 && falcon->getStrngth()>shuttle->getStrngth() && !bomber)
        falcon->attack(shuttle, true);
    else //else it succeeds
        falcon->attack(shuttle, false);

}

void Model::start_supply(const string &shipname, const string &src, const string &dest) {
    if(ships.find(shipname)!=ships.end() && stations.find(src)!=stations.end() && stations.find(dest)!=stations.end()) {
        if (ships[shipname]->getType() != "Shuttle")
            throw Exceptions("ERROR: Function start_supply is only for shuttles");
        dynamic_pointer_cast<Shuttle>(ships[shipname])->start_supply(stations[src], stations[dest]);
    }
    else
        throw Exceptions("ERROR: Ship or station doesn't exist");

}

void Model::stop(const string &shipname) {
    if(ships.find(shipname)!=ships.end()){
        ships[shipname]->stop();
    }else{
        throw Exceptions("ERROR: Ship doesn't exist");
    }
}

void Model::shoot(const string &shipname, const float &x, const float &y) {
    if(ships.find(shipname)!=ships.end()){
        if(ships[shipname]->getType()=="StarDestroyer") {
            for (const auto& falcon: ships) { //search for the falcon by coordinates
                if (falcon.second->getType() == "MillenniumFalcon") {
                    if (falcon.second->getCoordinates().first == x && falcon.second->getCoordinates().second == y) {
                        dynamic_pointer_cast<StarDestroyer>(ships[shipname])->shoot(dynamic_pointer_cast<MillenniumFalcon>(falcon.second));
                        break;
                    }
                }else
                    throw Exceptions("ERROR: Target isn't a Millennium Falcon");
            }
        }else
            throw Exceptions("ERROR: Function shoot only for Star Destroyer");
    }else{
        throw Exceptions("ERROR: Ship doesn't exist");
    }
}

float Model::distance(const float &x1, const float &y1, const float &x2, const float &y2) {
    return sqrt(pow((x2-x1),2)+pow((y2-y1),2));
}



