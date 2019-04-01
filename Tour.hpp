//
// Created by Jackie Wang on 2019-03-21.
//

#ifndef ASSIGNMENT2_TOUR_HPP
#define ASSIGNMENT2_TOUR_HPP

#include <vector>
#include "City.hpp"
#include <random>
#include <ctime>
#include <algorithm>

class Tour {
public:
    // vector list of cities by the order of tour
    vector <City> list;
    // total distance of the tour
    double distance;
    // less distance, more fitness
    double fitness;

    // shuffle the city list randomly
    void shuffle_cities();

    //calculate total distance of the tour
    double get_tour_distance();

    //calculate fitness
    double determine_fitness();

    //Constructor with a city vector list(then shuffle the list)
    Tour(vector <City> l);

    // Constructor by crossover 2 tours
    Tour(Tour t1, Tour t2, int index);

    // Constructor by crossover 3 tours
    Tour(Tour t1, Tour t2, Tour t3, int index1, int index2);
};

//print tour information
inline ostream &operator<<(std::ostream &os, const Tour &obj) {
    for (int i = 0; i < obj.list.size(); i++) {
        os << obj.list[i] << endl;
    }
    os << "Total distance is: " << obj.distance << endl;
    return os;
}

#endif //ASSIGNMENT2_TOUR_HPP
