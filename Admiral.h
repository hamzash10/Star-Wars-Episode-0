//
// Created by 2022 on 4/23/2024.
//

#ifndef FINAL_PROJECT_ADMIRAL_H
#define FINAL_PROJECT_ADMIRAL_H


#include "ImperialAgent.h"

class Admiral: public ImperialAgent {
public:
    explicit Admiral(const string& name);
    Admiral(const Admiral& rhs)=delete; // cant copy agent
    Admiral& operator=(const Admiral& rhs)=delete; // cant copy agent
    Admiral(Admiral&& rhs)=default;
    Admiral& operator=(Admiral&& rhs)=delete;
    ~Admiral();
};


#endif //FINAL_PROJECT_ADMIRAL_H
