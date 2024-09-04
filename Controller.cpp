//
// Created by 2022 on 4/23/2024.
//

#include "Controller.h"


using namespace std;
Controller::Controller() {
    model=Model::getInstance();
    view= make_shared<View>();
    view->addStation("DS",40,10);
}


void Controller::run(int argc, char *argv[]) {
    try {
        //reading the input file
        if(argc==2){

            ifstream input(argv[1]);
            if(!input.is_open())
                throw Exceptions("Couldn't Open File sites.dat");

            string line,w1,w2,w3,w4,w5,w6;
            float x,y;
            int cap,pro=0;
            while(getline(input,line)){
                ss.str(line);
                ss>>w1>>w2>>w3>>w4>>w5;
                w1=w1.substr(0,w1.size()-1);
                w2=w2.substr(0,w2.size()-1);
                x=stof(w3.substr(1,w3.size()-1));
                y=stof(w4.substr(0,w4.size()-1));
                cap=stoi(w5.substr(0,w5.size()-1));
                if(!ss.eof()){
                    ss>>w6;
                    pro=stoi(w6);
                }

                model->addStation(w1,w2,x,y,cap,pro); //throws exception
                view->addStation(w2,int(x),int(y));
                //clearing the string stream for reuse
                ss.clear();
                ss.str("");
            }
        }else{
            if(argc==1)
                throw Exceptions("ERROR: No input file.");
            else
                throw Exceptions("ERROR: Too many arguments.");
        }
    }catch (Exceptions& e){
        cerr<<e.what()<<endl;
    }

    orders();

}

void Controller::orders() {
    while(true) {
        try {
            string line,word,arg1,arg2,arg3,arg4,arg5;
            int num1;
            double dnum1;
            float fnum1,fnum2,fnum3;


            cout << "Time " << model->getTime() << ":  Enter command : ";
            cout.flush();
            getline(cin, line);
            ss.str(line);

            ss >> word;

            if (word == "exit") {
                if (ss.eof())
                    return;
                else
                    throw Exceptions("ERROR: Invalid input");
            }



                //------------VIEW ORDERS------------
            else if (word == "default") {
                if (ss.eof()) {
                    view->setDefault();
                } else
                    throw Exceptions("ERROR: Invalid input");
            }


            else if (word == "size") {
                if (ss >> num1) {
                    if (ss.eof())
                        view->setSize(num1);
                    else
                        throw Exceptions("ERROR: Invalid input");
                } else
                    throw Exceptions("ERROR: Expected an integer.");
            }


            else if (word == "zoom") {
                if (ss >> dnum1) {
                    if (ss.eof())
                        view->setScale(dnum1);
                    else
                        throw Exceptions("ERROR: Invalid input");
                } else
                    throw Exceptions("ERROR: Expected a double.");
            }


            else if (word == "pan") {
                if (ss >> fnum1 >> fnum2) {
                    if (ss.eof())
                        view->setOrigin(fnum1, fnum2);
                    else
                        throw Exceptions("ERROR: Invalid input");
                } else
                    throw Exceptions("ERROR: Expected a float.");

            }


            else if (word == "show") {
                if (ss.eof()) {
                    view->show();
                } else
                    throw Exceptions("Error: Invalid Input");
            }

                //------------MODEL ORDERS------------

            else if (word == "status") {
                if (ss.eof()) {
                    model->status();
                } else
                    throw Exceptions("Error: Invalid Input");
            }


            else if (word == "go") {
                if (ss.eof()) {
                    model->go();
                } else
                    throw Exceptions("Error: Invalid Input");
            }


            else if (word == "create") {
                //read other arguments before
                ss>>arg1>>arg2>>arg3>>arg4>>arg5;
                float x = 0, y = 0;
                pair<float,float> coords;
                //check if arg4 is a string
                istringstream ss1;
                if(!arg4.empty())
                    ss1.str(arg4.substr(1, arg4.size() - 1));
                if(arg4.empty() || ss1>>x){
                    if (arg1 != "falcon") {
                        if (!arg4.empty()) {
                            x = stof(arg4.substr(1, arg4.size() - 1));
                            y = stof(arg5.substr(0, arg5.size() - 1));
                        }
                    } else {
                        if (!arg4.empty()) {
                            x = stof(arg3.substr(1, arg3.size() - 1));
                            y = stof(arg4.substr(0, arg4.size() - 1));
                        }
                    }
                    if (ss.eof()) {
                        model->create(arg1,
                                      arg2,
                                      arg3, x, y);
                    } else
                        throw Exceptions("Error: Invalid Input");
                }
                else {// this means that arg4 is a station name, and we are creating a bomber
                    coords=model->create(arg1,arg2,arg3,arg4);
                    x=coords.first;
                    y=coords.second;
                }


                if(arg1=="destroyer" || arg1=="bomber" || arg1=="shuttle" || arg1=="falcon")
                   view->addShip(arg2,int(x),int(y));
            }


                //------------STARSHIP ORDERS------------
            else {
                ss >> arg1;

                if (arg1 == "course") {

                    if (ss>>fnum1) { // read the angel
                        if(ss.eof()){
                            model->setCourse(word, fnum1);
                        }else{
                            if(ss>>fnum2){ // if falcon read the speed
                                if(ss.eof())
                                    model->setCourse(word, fnum1,fnum2);
                                else
                                    throw Exceptions("Error: Invalid Input");
                            }else{
                                throw Exceptions("ERROR: Expected a float.");
                            }
                        }
                    } else {
                        throw Exceptions("ERROR: Expected a float.");
                    }


                }


                else if (arg1 == "position") {

                    if (ss>>fnum1>>fnum2) { // read x and y
                        if(ss.eof()){
                            model->setPosition(word, fnum1,fnum2);
                        }else{
                            if(ss>>fnum3){ // if falcon read the speed
                                if(ss.eof())
                                    model->setPosition(word, fnum1,fnum2,fnum3);
                                else
                                    throw Exceptions("Error: Invalid Input");
                            }else{
                                throw Exceptions("ERROR: Expected a float.");
                            }
                        }
                    } else {
                        throw Exceptions("ERROR: Expected a float.");
                    }
                }


                else if (arg1 == "destination") {
                    if (ss >> arg2)
                        if(ss.eof())
                            model->setDestination(word,arg2);
                        else
                            throw Exceptions("Error: Invalid Input");
                    else
                        throw Exceptions("ERROR: Expected a float.");
                }

                //only for shuttle
                else if(arg1=="start_supply"){
                    if (ss>>arg2>>arg3)
                        if(ss.eof())
                            model->start_supply(word,arg2,arg3);
                        else
                            throw Exceptions("Error: Invalid Input");
                    else
                        throw Exceptions("ERROR: Expected a float.");
                }

                //only for a falcon
                else if (arg1 == "attack"){
                    if (ss >> arg2 && ss.eof()) {
                        model->attack(word,arg2);
                    } else {
                        throw Exceptions("ERROR: Expected a float.");
                    }
                }


                //only for destroyer
                else if (arg1 == "shoot") {
                    if (ss>>fnum1>>fnum2) {  // read x and y
                        if (ss.eof())
                            model->shoot(word, fnum1, fnum2);
                        else
                            throw Exceptions("Error: Invalid Input");
                    }else
                        throw Exceptions("ERROR: Expected a float.");

                }


                else if (arg1 == "stop") {
                    if (ss.eof()) {
                        model->stop(word);
                    } else {
                        throw Exceptions("Error: Invalid Input");
                    }
                }


                else {
                    throw Exceptions("ERROR: Invalid input.");
                }


            }



            //clearing the string stream for reuse
            ss.clear();
            ss.str("");
        }catch (Exceptions& e) {
            cerr << e.what() << endl;
            //clearing the string stream for reuse
            ss.clear();
            ss.str("");
        }
    }
}


