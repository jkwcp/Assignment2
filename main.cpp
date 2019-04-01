#include <iostream>

#include "Tour.hpp"

// the minimum number of times the algorithm should iterate
#define ITERATIONS 1000
// the largest legal coordinate
#define MAP_BOUNDARY 1000
// the number of members randomly selected from the population when
//choosing a parent, from which the fittest is made a ’parent’
#define PARENT_POOL_SIZE 20
//number of fittest tour which will be kept unchanged
#define NUMBER_OF_ELITES 1
// the actual number of ’parent’ tours crossed to generate each ’offspring’
//tour
#define NUMBER_OF_PARENTS 3
//Implement the genetic algorithm iteratively until we observe a predetermined improvement
#define improvement_factor 0.95
// the number of cities we are using in each simulation
int CITIES_IN_TOUR;
// the number of candidate tours in our population
int POPULATION_SIZE;
//possibility for tours to mutate
double MUTATION_RATE;
//the new shortest distance of tours
double best_distance;
//the shortest distance of tours
double base_distance;

// a vector list of cities
vector<City> citylist;
// a vector list of tours
vector<Tour> tourlist;
// new vector list of tours made by genetic method
vector<Tour> newtourlist;
//random engine to get random number
default_random_engine e((unsigned int) time(0));

//method to create cities
void create_cities() {
    for (int i = 0; i < CITIES_IN_TOUR; i++) {
        double rd = e() % MAP_BOUNDARY;
        double rd2 = e() % MAP_BOUNDARY;
        City c = City("city" + to_string(i + 1), rd, rd2);
        citylist.push_back(c);
    }
}

//method to use city list to create random tours
void create_tours() {
    for (int i = 0; i < POPULATION_SIZE; i++) {
        Tour t = Tour(citylist);
        tourlist.push_back(t);
    }
}

//compare method for tours
bool comp(const Tour &a, const Tour &b) {
    return a.fitness > b.fitness;
}

//calculate the shortest total distance from the tour list
void get_bestdistance() {
    sort(tourlist.begin(), tourlist.end(), comp);
    best_distance = tourlist[0].distance;
}

//genetic method that changes the list of tours
void genetic() {

    //selection:
    sort(tourlist.begin(), tourlist.end(), comp);
    for (int i = 0; i < NUMBER_OF_ELITES; i++) {
        newtourlist.push_back(tourlist[i]);
    }
    //Crossover
    //When NUMBER_OF_PARENTS is 2
    if (NUMBER_OF_PARENTS == 2) {
        for (int i = NUMBER_OF_ELITES; i < POPULATION_SIZE; i++) {
            //first random parent
            int p1 = e() % PARENT_POOL_SIZE;
            //second random parent
            int p2 = e() % PARENT_POOL_SIZE;
            //random index
            int index = e() % CITIES_IN_TOUR;
            //crossover parents to make a new tour
            Tour t = Tour(tourlist[p1], tourlist[p2], index);
            //save new tour
            newtourlist.push_back(t);
        }
    }
        //When NUMBER_OF_PARENTS is 3
    else if (NUMBER_OF_PARENTS == 3) {
        for (int i = NUMBER_OF_ELITES; i < POPULATION_SIZE; i++) {
            //first random parent
            int p1 = e() % PARENT_POOL_SIZE;
            //second random parent
            int p2 = e() % PARENT_POOL_SIZE;
            //third random parent
            int p3 = e() % PARENT_POOL_SIZE;
            // first random index
            int index1 = e() % CITIES_IN_TOUR;
            //second random index
            int index2 = e() % CITIES_IN_TOUR;
            //crossover parents to make a new tour
            Tour t = Tour(tourlist[p1], tourlist[p2], tourlist[p3], index1, index2);
            //save new tour
            newtourlist.push_back(t);
        }
    }
    //Mutation
    for (int i = NUMBER_OF_ELITES; i < POPULATION_SIZE; i++) {
        //judge if the tour will mutate
        int rd1 = e() % 100;
        if (rd1 < MUTATION_RATE) {
            for (int j = 0; j < CITIES_IN_TOUR; j++) {
                //judge if the city will be moved in a tour
                int rd2 = e() % 100;
                if (rd2 < MUTATION_RATE) {
                    //move the city
                    if (j == 0) {
                        swap(newtourlist[i].list[j], newtourlist[i].list[j + 1]);
                    } else if (j == CITIES_IN_TOUR - 1) {
                        swap(newtourlist[i].list[j], newtourlist[i].list[j - 1]);
                    } else {
                        //judge to move the city forward or back
                        int rd3 = e() % 2;
                        if (rd3 == 0) {
                            swap(newtourlist[i].list[j], newtourlist[i].list[j - 1]);
                        } else if (rd3 == 1) {
                            swap(newtourlist[i].list[j], newtourlist[i].list[j + 1]);
                        }
                    }


                }
            }
        }
    }


    //Evaluation
    for (int i = 0; i < newtourlist.size(); i++) {
        newtourlist[i].fitness = newtourlist[i].determine_fitness();
    }
    //Report
    tourlist = newtourlist;
    get_bestdistance();
    cout << "Best distance is: " << best_distance << endl;
    newtourlist.clear();
}

int main() {
    //ask user to input number of cities
    cout << "Input number of cities:" << endl;
    cin >> CITIES_IN_TOUR;
    create_cities();

    //ask user to input number of tours
    cout << "Input number of tours:" << endl;
    cin >> POPULATION_SIZE;
    create_tours();

    //ask user to input mutation rate
    cout << "Input mutation rate:(%)" << endl;
    cin >> MUTATION_RATE;

    //get shortest total distance from tours as base distance
    get_bestdistance();
    base_distance = best_distance;
    cout << "Base distance is: " << base_distance << endl;

    //do genetic method at least 1000 times until no big improvement happen
    int count = 0;
    do {
        base_distance = best_distance;
        genetic();
        count++;
    } while (count < ITERATIONS || best_distance / base_distance < improvement_factor);

    //print city list
    cout << "City list: " << endl;
    for (int i = 0; i < citylist.size(); i++) {
        cout << citylist[i] << endl;
    }

    //print best tour plan with shortest total distance
    cout << "Best tour plan is:" << endl << tourlist[0] << endl;
    return 0;
}