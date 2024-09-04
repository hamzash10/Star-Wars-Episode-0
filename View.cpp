//
// Created by 2022 on 4/23/2024.
//

#include <cmath>
#include "View.h"



View::View():size(DEFAULT_SIZE),scale(DEFAULT_SCALE),X(DEFAULT_X),Y(DEFAULT_Y) {
    model=Model::getInstance();
}

void View::setDefault() {
    size=DEFAULT_SIZE;
    scale=DEFAULT_SCALE;
    X=DEFAULT_X;
    Y=DEFAULT_Y;
}

void View::setSize(const int &nsize) {
    if (nsize > MIN_SIZE && nsize <= MAX_SIZE) {
        size=nsize;
    } else if(nsize < MIN_SIZE)
        throw Exceptions("ERROR: New map size is too small.");
    else
        throw Exceptions("ERROR: New map size is too big.");
}

void View::setScale(const int &nscale) {
    if(nscale<0)
        throw Exceptions("ERROR: New map scale must be positive.");
    scale=nscale;
}

void View::setOrigin(const float &nx, const float &ny) {
    X=nx;
    Y=ny;
}

void View::show() {
    correctSpace(); //update the spaceships places
    cout<<"Display size: "<<size<<", scale: "<<scale<<" , origin: ("<<X<<", "<<Y<<")"<<endl;

    //calculate the margin before the y-axis
    int y=size*scale+Y-scale;
    int margin;
    int no_dots=0;
    if((Y>-1))
        margin=(y>-1)? getDigits(y)+1: getDigits(y)+2; // this means that the number of digits of y is bigger or equal to the lowest Y
    else
        margin=(getDigits(y)> getDigits(Y)+1)? getDigits(y)+1: getDigits(Y)+2; //else get the max number of digits for each one


    //print the lines top-down
    for (int row = y; row >=Y; row-=scale) {

        //each three lines print the line number before the y-axis
        if((row-int(Y))%3==0) {
            int curMargin = (row>-1)? getDigits(row): getDigits(row)+1;
            cout << row;
            if (curMargin < margin)
                for (int j = 0; j < margin - curMargin; ++j)
                    cout << ' ';
        }else
            for (int j = 0; j < margin; ++j)
                cout << ' ';


        //for each coordinates check if there is a ship or a station, if not print a dot
        for (int j = X; j < size*scale+X; j+=scale) {
            string names;
            //printing every thing in a scale^2
            //for each entity in the same coordinates remove a future dot. (fixes the graph)
            for (int i = 0; i < scale; ++i) {
                for (int k = 0; k < scale; ++k) {
                    if (!ships[{j+i, row+k}].empty()) {
                        cout << ships[{j+i, row+k}];
                        names=ships[{j+i, row+k}];
                        no_dots++;
                        while(names.size()>2){ //for each ship delete a future dot
                            names.erase(0,2);
                            no_dots++;
                        }
                    }
                    if (!stations[{j+i, row+k}].empty()) {
                        cout << stations[{j+i, row+k}];
                        no_dots++;
                        names=stations[{j+i, row+k}];
                        while(names.size()>2){
                            names.erase(0,2);
                            no_dots++;
                        }
                    }

                }

            }
            if(no_dots==0)
                cout<<". ";
            else
                no_dots--;
        }
        cout<<endl;
    }

    //printing the last line
    int x=X;//to run on all Y's
    int x_digits=(x>-1)? getDigits(x): getDigits(x)+1;
    for (int i = 0; i < margin -x_digits+1; ++i) {
        cout<<' ';
    }
    cout<<x;
    for (int col = 1; col < size; ++col) {
        x+=scale;
        if(col%3==0)
            if(getDigits(x)>1)
                cout<<x;
            else
                cout<<' '<<x;
        else{
            if((col+1)%3==0){
                if(x>-1) {
                    if (getDigits(x + scale) != 3)
                        cout << "  ";
                    else
                        cout << ' ';
                }else{
                    cout << ' ';
                }
            }else
                cout<<"  ";
        }
    }
    cout<<endl;
}

int View::getDigits(int num) {
    if(num==0)
        return 1;
    int i=0;
    while(num){
        num/=10;
        i++;
    }
    return i;
}

void View::addStation(const string &name, const int &x, const int &y) {
    stations[{x,y}]=name.substr(0,2);
}

void View::addShip(const string &name, const int &x, const int &y) {
    ships[{x,y}]+=name.substr(0,2);
}

void View::correctSpace() {
    auto tmp =ships; // copy of the ships, so I can change the ships while running on it
    for(const auto& ship:tmp){
        for (int i = 0; i < int(ship.second.size()); i+=2) { //iterate through each two letters
            string name=ship.second.substr(i,2);
            pair<float,float> new_coordinates=model->getCoordinates(name); //get the coordinates
            pair<int,int> convert= make_pair( static_cast<int>(round(new_coordinates.first)),static_cast<int>(round(new_coordinates.second)) );
            if(ship.first.first!=convert.first || ship.first.second!=convert.second) {//check if the ship changed place
                //remove the ship's name
                ships[ship.first].erase(i, 2);
                //add the ship to the new coordinates
                ships[convert]+=name;
                if(ship.second.empty()){ //if there is no ships left in the old coordinates
                    ships.erase(ship.first);
                }
            }

        }

    }
}



