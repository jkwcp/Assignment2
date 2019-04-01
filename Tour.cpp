//
// Created by Jackie Wang on 2019-03-21.
//

#include "Tour.hpp"

void Tour::shuffle_cities() {
    random_shuffle(list.begin(), list.end());
}

Tour::Tour(std::vector <City> l) {
    list = l;
    shuffle_cities();
    distance = get_tour_distance();
    fitness = determine_fitness();
}

double Tour::get_tour_distance() {
    double total = 0;
    for (int i = 0; i < list.size() - 1; i++) {
        total += get_distance_between_cities(list[i], list[i + 1]);
    }
    total += get_distance_between_cities(list[0], list[list.size() - 1]);
    return total;
}

double Tour::determine_fitness() {
    return 10000 / distance;
}

Tour::Tour(Tour t1, Tour t2, int index) {
    for (int i = 0; i < index; i++) {
        list.push_back(t1.list[i]);
    }
    for (int i = 0; i < t2.list.size(); i++) {
        bool exist = false;
        for (int j = 0; j < list.size(); j++) {
            if (list[j].name == t2.list[i].name) {
                exist = true;
            }
        }
        if (!exist) {
            list.push_back(t2.list[i]);
        }
    }
    distance = get_tour_distance();
    fitness = determine_fitness();
}

Tour::Tour(Tour t1, Tour t2, Tour t3, int index1, int index2) {
    for (int i = 0; i < index1; i++) {
        list.push_back(t1.list[i]);
    }
    for (int i = 0; i < index2; i++) {
        bool exist = false;
        for (int j = 0; j < list.size(); j++) {
            if (list[j].name == t2.list[i].name) {
                exist = true;
            }
        }
        if (!exist) {
            list.push_back(t2.list[i]);
        }
    }
    for (int i = 0; i < t3.list.size(); i++) {
        bool exist = false;
        for (int j = 0; j < list.size(); j++) {
            if (list[j].name == t3.list[i].name) {
                exist = true;
            }
        }
        if (!exist) {
            list.push_back(t3.list[i]);
        }
    }
    distance = get_tour_distance();
    fitness = determine_fitness();
}

