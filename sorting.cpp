#include <iostream>
#include <iomanip>
#include "car.h"
#include "sorting.h"
#include "Helpers.h"

#include <vector>
#include <algorithm>

using namespace std;
using namespace Helpers;

Sorting::Sorting() {
#ifndef NDEBUG
    cout << "[CONSTRUCTOR] Sorting object is created" << endl;
#endif
}

Sorting::Sorting(int field, int type) {
    this->setField(field);
    this->setType(type);
#ifndef NDEBUG
    cout << "[CONSTRUCTOR] Sorting object is created with parameters" << endl;
#endif
}

Sorting::~Sorting() {
#ifndef NDEBUG
    cout << "[DESTRUCTOR] Sorting object is destroyed" << endl;
#endif
}

void Sorting::setField(int field) {
    switch(field) {
        case SortingConstants::MAKE:
        case SortingConstants::MODEL:
        case SortingConstants::YEAR:
        case SortingConstants::PRICE:
        case SortingConstants::MAXSPEED:
        case SortingConstants::RACETIME:
        case SortingConstants::ID:
            this->field = static_cast<SortingConstants::Fields>(field);
            break;
        default:
            throw std::invalid_argument("Please make sure that field value is within bounds");
    }
}

void Sorting::setType(int type) {
    switch(type) {
        case SortingConstants::ASCENDING: case SortingConstants::DESCENDING:
            this->type = static_cast<SortingConstants::Types>(type);
            break;
        default:
            throw std::invalid_argument("Please make sure that type value is within bounds");
    }
}


void Sorting::sort_by_year(vector<Car*> &cars, int first, int last) const {

    Car* temp;
    int pivot, j, i;

    if (first < last) {
        pivot = first;
        i = first;
        j = last;

        while (i < j) {
            while (
                cars[i]->getCarYear() <= cars[pivot]->getCarYear() && i < last) {
                i++;
            }
            while (cars[j]->getCarYear() > cars[pivot]->getCarYear()) {
                j--;
            }
            if (i < j) {
                temp = cars[i];
                cars[i] = cars[j];
                cars[j] = temp;
            }
        }

        temp = cars[pivot];
        cars[pivot] = cars[j];
        cars[j] = temp;

        sort_by_year(cars, first, j - 1);
        sort_by_year(cars, j + 1, last);
    }
}

void Sorting::sort_by_price(vector<Car*> &cars, int first, int last) const {

    Car* temp;
    int pivot, j, i;

    if (first < last) {
        pivot = first;
        i = first;
        j = last;

        while (i < j) {
            while (
                cars[i]->getCarPrice() <= cars[pivot]->getCarPrice() && i < last) {
                i++;
            }
            while (cars[j]->getCarPrice() > cars[pivot]->getCarPrice()) {
                j--;
            }
            if (i < j) {
                temp = cars[i];
                cars[i] = cars[j];
                cars[j] = temp;
            }
        }

        temp = cars[pivot];
        cars[pivot] = cars[j];
        cars[j] = temp;

        sort_by_price(cars, first, j - 1);
        sort_by_price(cars, j + 1, last);
    }
}

void Sorting::sort_by_max_speed(vector<Car*> &cars, int first, int last) const
{

    Car* temp;
    int pivot, j, i;

    if (first < last) {
        pivot = first;
        i = first;
        j = last;

        while (i < j) {
            while (
                cars[i]->getMaxSpeed() <= cars[pivot]->getMaxSpeed() && i < last) {
                i++;
            }
            while (cars[j]->getMaxSpeed() > cars[pivot]->getMaxSpeed()) {
                j--;
            }
            if (i < j) {
                temp = cars[i];
                cars[i] = cars[j];
                cars[j] = temp;
            }
        }

        temp = cars[pivot];
        cars[pivot] = cars[j];
        cars[j] = temp;

        sort_by_max_speed(cars, first, j - 1);
        sort_by_max_speed(cars, j + 1, last);
    }
}


void Sorting::sort_by_race_time(vector<Car*> &cars, int first, int last) const
{

    Car* temp;
    int pivot, j, i;

    if (first < last) {
        pivot = first;
        i = first;
        j = last;

        while (i < j) {
            while (
                cars[i]->getRaceTime() <= cars[pivot]->getRaceTime() && i < last) {
                i++;
            }
            while (cars[j]->getRaceTime() > cars[pivot]->getRaceTime()) {
                j--;
            }
            if (i < j) {
                temp = cars[i];
                cars[i] = cars[j];
                cars[j] = temp;
            }
        }

        temp = cars[pivot];
        cars[pivot] = cars[j];
        cars[j] = temp;

        sort_by_race_time(cars, first, j - 1);
        sort_by_race_time(cars, j + 1, last);
    }
}


void Sorting::sort_by_id(vector<Car*> &cars, int first, int last) const
{

    Car* temp;
    int pivot, j, i;

    if (first < last) {
        pivot = first;
        i = first;
        j = last;

        while (i < j) {
            while (
                cars[i]->getID() <= cars[pivot]->getID() && i < last) {
                i++;
            }
            while (cars[j]->getID() > cars[pivot]->getID()) {
                j--;
            }
            if (i < j) {
                temp = cars[i];
                cars[i] = cars[j];
                cars[j] = temp;
            }
        }

        temp = cars[pivot];
        cars[pivot] = cars[j];
        cars[j] = temp;

        sort_by_id(cars, first, j - 1);
        sort_by_id(cars, j + 1, last);
    }
}



void Sorting::sort(vector<Car*> &cars) {

    this->first = 0;
    this->last = cars.size() - 1;

    vector<string> temp;

    switch(this->field) {
        case SortingConstants::MAKE:

            for (size_t i = 0; i < cars.size(); i++) {
                temp.push_back(cars[i]->getCarMake());
            }

            Helpers::sort_lexicographically(temp);

            cout << "Sorted by make:" << endl << endl;

            for (size_t i = 0; i < temp.size(); i++) {
                cout << i << ". " << temp[i] << endl;
            }

            break;
        case SortingConstants::MODEL:

            for (size_t i = 0; i < cars.size(); i++) {
                temp.push_back(cars[i]->getCarModel());
            }

            Helpers::sort_lexicographically(temp);

            cout << "Sorted by model:" << endl << endl;

            for (size_t i = 0; i < temp.size(); i++) {
                cout << i << ". " << temp[i] << endl;
            }

            break;
        case SortingConstants::YEAR:
            this->sort_by_year(cars, this->first, this->last);
            break;
        case SortingConstants::PRICE:
            this->sort_by_price(cars, this->first, this->last);
            break;
        case SortingConstants::MAXSPEED:
            this->sort_by_max_speed(cars, this->first, this->last);
            break;
        case SortingConstants::RACETIME:
            this->sort_by_race_time(cars, this->first, this->last);
            break;
        case SortingConstants::ID:
            this->sort_by_id(cars, this->first, this->last);
            break;
    }

    if (this->type == SortingConstants::DESCENDING) {
        std::reverse(cars.begin(), cars.end());
    }
}


