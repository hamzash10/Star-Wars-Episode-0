//
// Created by 2022 on 4/23/2024.
//

#include "FortressStar.h"

FortressStar::FortressStar(const string& name,const float &x, const float &y, const int &crystals_number) :
Station(name,"FortressStar",x, y, crystals_number) {

}

void FortressStar::status() {
    cout<<"fortress "<<name<<" at position ("<<x<<", "<<y<<"), Inventory: "<<crystals_number;
}

int FortressStar::load(const int& num) {
    crystals_number+=num;
    return crystals_number;
}

FortressStar::FortressStar(FortressStar &&other) noexcept: Station(std::move(other)) {

}

FortressStar &FortressStar::operator=(FortressStar &&other)  noexcept {
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

