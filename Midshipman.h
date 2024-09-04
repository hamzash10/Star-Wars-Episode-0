//
// Created by 2022 on 4/23/2024.
//

#ifndef FINAL_PROJECT_MIDSHIPMAN_H
#define FINAL_PROJECT_MIDSHIPMAN_H


#include "ImperialAgent.h"

class Midshipman: public ImperialAgent{
public:
    explicit Midshipman(const string& name);
    Midshipman(const Midshipman& rhs)=delete; // cant copy agent
    Midshipman& operator=(const Midshipman& rhs)=delete; // cant copy agent
    Midshipman(Midshipman&& rhs)=default;
    Midshipman& operator=(Midshipman&& rhs)=default;
    ~Midshipman();
};


#endif //FINAL_PROJECT_MIDSHIPMAN_H
