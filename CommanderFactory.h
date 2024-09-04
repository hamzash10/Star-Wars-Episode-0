//
// Created by 2022 on 4/23/2024.
//

#ifndef FINAL_PROJECT_COMMANDERFACTORY_H
#define FINAL_PROJECT_COMMANDERFACTORY_H


#include "AgentFactory.h"
#include "Commander.h"

class CommanderFactory: public AgentFactory {
    shared_ptr<ImperialAgent> createAgent(const string& name) override;
};


#endif //FINAL_PROJECT_COMMANDERFACTORY_H
