//
// Created by 2022 on 4/23/2024.
//

#include "AdmiralFactory.h"

shared_ptr<ImperialAgent> AdmiralFactory::createAgent(const string &name) {
    return make_shared<Admiral>(name);
}
