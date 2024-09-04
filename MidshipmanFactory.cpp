//
// Created by 2022 on 4/23/2024.
//

#include "MidshipmanFactory.h"


shared_ptr<ImperialAgent> MidshipmanFactory::createAgent(const string &name) {
    return make_shared<Midshipman>(name);
}
