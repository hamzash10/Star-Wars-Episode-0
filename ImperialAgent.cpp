//
// Created by 2022 on 4/23/2024.
//

#include "ImperialAgent.h"
#include "Exceptions.h"

ImperialAgent::ImperialAgent(const string &name) {
    if(name.size()<=16){
        this->name=name;
    }else{
        throw Exceptions("ERROR: Agent name must be below 16 characters");
    }
}

ImperialAgent::~ImperialAgent() = default;
