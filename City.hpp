//
// Created by Jackie Wang on 2019-03-21.
//

#ifndef ASSIGNMENT2_CITY_HPP
#define ASSIGNMENT2_CITY_HPP

#include <iostream>
#include <string>
#include <math.h>


using namespace std;

class City {
public:
    //City name
    string name;
    //Coordinate x
    double x;
    //Coordinate y
    double y;

    //Constructor with name, coordinate x, coordinate y
    City(string n, double xx, double yy);


};

//method to calculate distance between 2 cities
inline double get_distance_between_cities(City c1, City c2) {
    return sqrt((c1.x - c2.x) * (c1.x - c2.x) + (c1.y - c2.y) * (c1.y - c2.y));
}

//print city information
inline ostream &operator<<(ostream &os, const City &obj) {
    os << obj.name << " " << obj.x << " " << obj.y;
    return os;
}

#endif //ASSIGNMENT2_CITY_HPP
