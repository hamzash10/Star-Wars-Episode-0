//
// Created by 2022 on 4/23/2024.
//

#ifndef FINAL_PROJECT_IMPERIALAGENT_H
#define FINAL_PROJECT_IMPERIALAGENT_H

#include <iostream>
using namespace std;
class ImperialAgent {
    string name;
public:
    explicit ImperialAgent(const string& name);
    ImperialAgent(const ImperialAgent& rhs)=delete; // cant copy agent
    ImperialAgent& operator=(const ImperialAgent& rhs)=delete; // cant copy agent
    ImperialAgent(ImperialAgent&& rhs)=default;
    ImperialAgent& operator=(ImperialAgent&& rhs)=default;
    ~ImperialAgent();
};


#endif //FINAL_PROJECT_IMPERIALAGENT_H
