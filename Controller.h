//
// Created by 2022 on 4/23/2024.
//

#ifndef FINAL_PROJECT_CONTROLLER_H
#define FINAL_PROJECT_CONTROLLER_H


#include <sstream>
#include "Model.h"
#include "Exceptions.h"
#include "View.h"
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

using namespace std;

class Controller {
    void orders();
    shared_ptr<Model> model;
    shared_ptr<View> view;
    istringstream ss;
public:
    Controller();
    void run(int argc, char *argv[]);
    ~Controller()=default;
    Controller(const Controller&)=delete;
    Controller(Controller&&)=delete;
    Controller& operator=(Controller&)=delete;
    Controller& operator=(Controller&&)=delete;
};



#endif //FINAL_PROJECT_CONTROLLER_H
