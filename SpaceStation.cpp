//
// Created by 2022 on 4/23/2024.
//

#include "SpaceStation.h"

SpaceStation::SpaceStation(const string& name,const float &x, const float &y, const int &crystals_number, const int &production_cap):
        Station(name,"SpaceStation",x,y,crystals_number),production_cap(production_cap){
}

void SpaceStation::status() {
    cout<<"station "<<name<<" at position ("<<x<<", "<<y<<"), Inventory: "<<crystals_number;
}

void SpaceStation::go() {
    crystals_number+=production_cap;
}

int SpaceStation::load(const int &num) {
    if(crystals_number>=5){
        crystals_number-=5;
        return 5;
    }
    int tmp=crystals_number;
    crystals_number=0;
    return tmp;
}

SpaceStation::SpaceStation(SpaceStation &&other) noexcept: Station(std::move(other)),production_cap(other.production_cap) {

}

SpaceStation &SpaceStation::operator=(SpaceStation &&other) noexcept {
    if (this != &other) {
        name = std::move(other.name);
        type = std::move(other.type);
        x = other.x;
        y = other.y;
        crystals_number = other.crystals_number;
        distances = std::move(other.distances);
        production_cap=other.production_cap;
    }
    return *this;
}
