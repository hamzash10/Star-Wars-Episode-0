//
// Created by 2022 on 4/23/2024.
//

#include "CommanderFactory.h"

shared_ptr<ImperialAgent> CommanderFactory::createAgent(const string &name) {
    return make_shared<Commander>(name);
}
