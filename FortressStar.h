//
// Created by 2022 on 4/23/2024.
//

#ifndef FINAL_PROJECT_FORTRESSSTAR_H
#define FINAL_PROJECT_FORTRESSSTAR_H


#include "Station.h"

class FortressStar: public Station {
public:
    FortressStar(const string& name,const float& x,const float& y,const int& crystals_number);
    ~FortressStar() override=default;
    FortressStar(const FortressStar&)=delete;
    FortressStar& operator=(const FortressStar&)=delete;
    FortressStar(FortressStar&& other) noexcept ;
    FortressStar& operator=(FortressStar&& other)noexcept;
    void status() override;
    int load(const int& num) override;
};


#endif //FINAL_PROJECT_FORTRESSSTAR_H
