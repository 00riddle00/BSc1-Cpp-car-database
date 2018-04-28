#include <iostream>
#include <iomanip>
#include "car.h"
#include "filter.h"

#include <vector>

using namespace std;

Filter::Filter() {
#ifndef NDEBUG
    cout << "[CONSTRUCTOR] Filter object is created" << endl;
#endif
}

Filter::Filter(int field, int type, const string& value) {
    this->setField(field);
    this->setType(type);
    this->setValue(value);
#ifndef NDEBUG
    cout << "[CONSTRUCTOR] Filter object is created with parameters" << endl;
#endif
}

Filter::~Filter() {
#ifndef NDEBUG
    cout << "[DESTRUCTOR] Filter object is destroyed" << endl;
#endif
}

void Filter::filter_by_make(vector<Car*> &cars) const {

    switch(this->type) {
        case FilterConstants::EQUAL:
            for (size_t i = 0; i < cars.size(); i++) {
                if (cars[i]->getCarMake() != this->value) {
                    cars[i]->setFilter(false);
                } 
            }
            break;
        case FilterConstants::CONTAINS:
            for (size_t i = 0; i < cars.size(); i++) {
                if (cars[i]->getCarMake().find(this->value) == std::string::npos) {
                    cars[i]->setFilter(false);
                }
            }
            break;
        case FilterConstants::NOT_EQUAL:
            for (size_t i = 0; i < cars.size(); i++) {
                if (cars[i]->getCarMake() == this->value) {
                    cars[i]->setFilter(false);
                } 
            }
            break;
        case FilterConstants::DOES_NOT_CONTAIN:
            for (size_t i = 0; i < cars.size(); i++) {
                if (cars[i]->getCarMake().find(this->value) != std::string::npos) {
                    cars[i]->setFilter(false);
                } 
            }
            break;
    }
}

void Filter::filter_by_model(vector<Car*> &cars) const {

    switch(this->type) {
        case 1:
            for (size_t i = 0; i < cars.size(); i++) {
                if (cars[i]->getCarModel() != this->value) {
                    cars[i]->setFilter(false);
                } 
            }
            break;
        case 2:
            for (size_t i = 0; i < cars.size(); i++) {
                if (cars[i]->getCarModel().find(this->value) == std::string::npos) {
                    cars[i]->setFilter(false);
                } 
            }
            break;
        case 3:
            for (size_t i = 0; i < cars.size(); i++) {
                if (cars[i]->getCarModel() == this->value) {
                    cars[i]->setFilter(false);
                } 
            }
            break;
        case 4:
            for (size_t i = 0; i < cars.size(); i++) {
                if (cars[i]->getCarModel().find(this->value) != std::string::npos) {
                    cars[i]->setFilter(false);
                } 
            }
            break;
    }
}


void Filter::filter_by_year(vector<Car*> &cars) const {

    switch(this->type) {
        case 1:
            for (size_t i = 0; i < cars.size(); i++) {
                string car_year = to_string(cars[i]->getCarYear());
                if (car_year != this->value) {
                    cars[i]->setFilter(false);
                } 
            }
            break;
        case 2:
            for (size_t i = 0; i < cars.size(); i++) {
                string car_year = to_string(cars[i]->getCarYear());
                if (car_year.find(this->value) == std::string::npos) {
                    cars[i]->setFilter(false);
                } 
            }
            break;
        case 3:
            for (size_t i = 0; i < cars.size(); i++) {
                string car_year = to_string(cars[i]->getCarYear());
                if (car_year == this->value) {
                    cars[i]->setFilter(false);
                } 
            }
            break;
        case 4:
            for (size_t i = 0; i < cars.size(); i++) {
                string car_year = to_string(cars[i]->getCarYear());
                if (car_year.find(this->value) != std::string::npos) {
                    cars[i]->setFilter(false);
                } 
            }
            break;
    }
}


void Filter::filter_by_price(vector<Car*> &cars) const {

    switch(this->type) {
        case 1:
            for (size_t i = 0; i < cars.size(); i++) {
                string car_price = to_string(cars[i]->getCarPrice());
                if (car_price != this->value) {
                    cars[i]->setFilter(false);
                } 
            }
            break;
        case 2:
            for (size_t i = 0; i < cars.size(); i++) {
                string car_price = to_string(cars[i]->getCarPrice());
                if (car_price.find(this->value) == std::string::npos) {
                    cars[i]->setFilter(false);
                } 
            }
            break;
        case 3:
            for (size_t i = 0; i < cars.size(); i++) {
                string car_price = to_string(cars[i]->getCarPrice());
                if (car_price == this->value) {
                    cars[i]->setFilter(false);
                } 
            }
            break;
        case 4:
            for (size_t i = 0; i < cars.size(); i++) {
                string car_price = to_string(cars[i]->getCarPrice());
                if (car_price.find(this->value) != std::string::npos) {
                    cars[i]->setFilter(false);
                } 
            }
            break;
    }
}


void Filter::filter_by_max_speed(vector<Car*> &cars) const {

    switch(this->type) {
        case 1:
            for (size_t i = 0; i < cars.size(); i++) {
                string max_speed = to_string(cars[i]->getMaxSpeed());
                if (max_speed != this->value) {
                    cars[i]->setFilter(false);
                } 
            }
            break;
        case 2:
            for (size_t i = 0; i < cars.size(); i++) {
                string max_speed = to_string(cars[i]->getMaxSpeed());
                if (max_speed.find(this->value) == std::string::npos) {
                    cars[i]->setFilter(false);
                } 
            }
            break;
        case 3:
            for (size_t i = 0; i < cars.size(); i++) {
                string max_speed = to_string(cars[i]->getMaxSpeed());
                if (max_speed == this->value) {
                    cars[i]->setFilter(false);
                } 
            }
            break;
        case 4:
            for (size_t i = 0; i < cars.size(); i++) {
                string max_speed = to_string(cars[i]->getMaxSpeed());
                if (max_speed.find(this->value) != std::string::npos) {
                    cars[i]->setFilter(false);
                } 
            }
            break;
    }
}




void Filter::setField(int field) {
    switch(field) {
        case FilterConstants::MAKE:
        case FilterConstants::MODEL:
        case FilterConstants::YEAR:
        case FilterConstants::PRICE: 
        case FilterConstants::MAXSPEED: 
            this->field = static_cast<FilterConstants::Fields>(field);
            break;
        default:
            throw std::invalid_argument("Please make sure that field value is within bounds");
    }
}

void Filter::setType(int type) {
    switch(type) {
        case FilterConstants::EQUAL: case FilterConstants::CONTAINS: case FilterConstants::NOT_EQUAL: case FilterConstants::DOES_NOT_CONTAIN: 
            this->type = static_cast<FilterConstants::Types>(type);
            break;
        default:
            throw std::invalid_argument("Please make sure that type value is within bounds");
    }
}

void Filter::setValue(const string& value) {
    this->value = value;
}

void Filter::filter(vector<Car*> &cars) const {

    switch(this->field) {
        case FilterConstants::MAKE:
            this->filter_by_make(cars);
            break;
        case FilterConstants::MODEL:
            this->filter_by_model(cars);
            break;
        case FilterConstants::YEAR:
            this->filter_by_year(cars);
            break;
        case FilterConstants::PRICE:
            this->filter_by_price(cars);
            break;
        case FilterConstants::MAXSPEED:
            this->filter_by_max_speed(cars);
            break;
    }
}

void Filter::reset_filter(vector<Car*> &cars) {

    for (size_t i = 0; i < cars.size(); i++) {
        cars[i]->setFilter(true);
    }
}


