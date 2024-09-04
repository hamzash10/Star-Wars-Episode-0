//
// Created by 2022 on 4/23/2024.
//

#ifndef FINAL_PROJECT_SPACESTATION_H
#define FINAL_PROJECT_SPACESTATION_H


#include "Station.h"

class SpaceStation : public Station{
private:
    int production_cap;
public:
    SpaceStation(const string& name,const float& x,const float& y,const int& crystals_number,const int& production_cap);
    ~SpaceStation() override= default;
    SpaceStation(const SpaceStation&)=delete;
    SpaceStation& operator=(const SpaceStation&)=delete;
    SpaceStation(SpaceStation&& other) noexcept;
    SpaceStation& operator=(SpaceStation&& other) noexcept;
    void status() override;
    void go() override;
    int load(const int& num=0) override;

};


#endif //FINAL_PROJECT_SPACESTATION_H
