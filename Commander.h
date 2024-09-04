//
// Created by 2022 on 4/23/2024.
//

#ifndef FINAL_PROJECT_COMMANDER_H
#define FINAL_PROJECT_COMMANDER_H


#include "ImperialAgent.h"

class Commander: public ImperialAgent {
public:
    explicit Commander(const string& name);
    Commander(const Commander& rhs)=delete; // cant copy agent
    Commander& operator=(const Commander& rhs)=delete; // cant copy agent
    Commander(Commander&& rhs)=default;
    Commander& operator=(Commander&& rhs)=default;
    ~Commander();
};


#endif //FINAL_PROJECT_COMMANDER_H
