//
// Created by 2022 on 4/23/2024.
//

#ifndef FINAL_PROJECT_STATION_H
#define FINAL_PROJECT_STATION_H

#include <iostream>
#include <memory>
#include <set>

using namespace std;

class Station {
protected:
    string name,type;
    float x;
    float y;
    int crystals_number;
    class Comparator{
    public:
        bool operator()(pair<float,shared_ptr<Station>> lhs,pair<float,shared_ptr<Station>> rhs){ //custom comparator for storing in order
            if (lhs.first < rhs.first) {
                return true;
            } else if (lhs.first > rhs.first) {
                return false;
            } else {
                // if keys are equal, compare strings alphabetically
                return lhs.second->getName() < rhs.second->getName();
            }
        }
    };
    set< pair<float, shared_ptr<Station>> ,Comparator> distances; //here I will save the distance between this station and all the others
public:
    Station(const string& name,const string& type,const float& x,const float& y,const int& crystals_number);
    virtual ~Station()=0;
    Station(const Station&)=delete;
    Station& operator=(const Station&)=delete;
    Station(Station&& other) noexcept;
    Station& operator=(Station&& other) noexcept;
    virtual void status();
    const string& getName();
    float getX() const;
    float getY() const;
    virtual void go();
    const string& getType();
    virtual int load(const int& num=0)=0;
    void setDistance(float dist,shared_ptr<Station> st); // add a distance between this station and an old one
    shared_ptr<Station> getClosest(const int& i); //get the i'th closest station
};


#endif //FINAL_PROJECT_STATION_H
