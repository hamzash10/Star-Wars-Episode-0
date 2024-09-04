//
// Created by 2022 on 4/23/2024.
//

#ifndef FINAL_PROJECT_MIDSHIPMANFACTORY_H
#define FINAL_PROJECT_MIDSHIPMANFACTORY_H


#include "AgentFactory.h"
#include "Midshipman.h"

class MidshipmanFactory: public AgentFactory{
public:
    shared_ptr<ImperialAgent> createAgent(const string& name) override;
};


#endif //FINAL_PROJECT_MIDSHIPMANFACTORY_H
