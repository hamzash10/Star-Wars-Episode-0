//
// Created by 2022 on 4/23/2024.
//

#include "Station.h"


Station::Station(const string& name,const string& type,const float &x, const float &y,const int& crystals_number):
            name(name),type(type),x(x),y(y),crystals_number(crystals_number) {

}

Station::~Station() = default;

void Station::status() {
}

const string& Station::getName() {
    return name;
}

float Station::getX() const {
    return x;
}

float Station::getY() const {
    return y;
}

const string &Station::getType() {
    return type;
}

void Station::go() {
    //the fortress do nothing and the space station overrides
}

void Station::setDistance(float dist,shared_ptr<Station> st) {
    distances.insert({dist,st});
}


shared_ptr<Station> Station::getClosest(const int &i) {

    auto it=distances.begin();
    advance(it,i);
    return it->second;
}

Station::Station(Station &&other) noexcept :
name(std::move(other.name)),type(std::move(other.type)),x(other.x),
y(other.y),crystals_number(other.crystals_number),distances(std::move(other.distances)) {

}

Station &Station::operator=(Station &&other) noexcept{
    if (this != &other) {
        name = std::move(other.name);
        type = std::move(other.type);
        x = other.x;
        y = other.y;
        crystals_number = other.crystals_number;
        distances = std::move(other.distances);
    }
    return *this;
}

