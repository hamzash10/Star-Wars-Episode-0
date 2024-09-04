//
// Created by 2022 on 4/23/2024.
//

#ifndef FINAL_PROJECT_VIEW_H
#define FINAL_PROJECT_VIEW_H

#include <iostream>
#include <array>
#include <vector>
#include <unordered_map>
#include "Exceptions.h"
#include "Model.h"

const int DEFAULT_SIZE=25;
const int MAX_SIZE=30;
const int MIN_SIZE=6;
const float DEFAULT_SCALE=2;
const float DEFAULT_X=0;
const float DEFAULT_Y=0;

class View {
    int size;
    int scale;
    float X,Y;
    shared_ptr<Model> model;
    struct PairHash {
        size_t operator()(const pair<int, int>& p) const {
            //this trick gives me a way to store and retrieve keys, by storing each pair by a unique hash number
            return hash<int>()(p.first) ^ hash<int>()(p.second);
        }
    };
    unordered_map<pair<int,int>,string,PairHash> stations;
    unordered_map<pair<int,int>,string,PairHash> ships;
    int getDigits(int num);
    void correctSpace(); //translate the ships coordinates to my space, so it becomes easier to show.
public:
    View();
    View(const View&)=delete;
    View& operator=(const View&)=delete;
    View(View&& other)=delete;
    View& operator=(View&& other)=delete;
    ~View()=default;
    void show();
    void setDefault();
    void setSize(const int& nsize);
    void setScale(const int& nscale);
    void setOrigin(const float& nx,const float& ny);
    void addStation(const string& name,const int& x,const int& y);
    void addShip(const string& name,const int& x,const int& y);

};


#endif //FINAL_PROJECT_VIEW_H
