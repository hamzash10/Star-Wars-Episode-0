//
// Created by 2022 on 4/23/2024.
//

#ifndef FINAL_PROJECT_AGENTFACTORY_H
#define FINAL_PROJECT_AGENTFACTORY_H
#include <iostream>
#include <memory>
#include "ImperialAgent.h"

using namespace std;
class AgentFactory {
public:
    virtual shared_ptr<ImperialAgent> createAgent(const string& name)=0;
};


#endif //FINAL_PROJECT_AGENTFACTORY_H
