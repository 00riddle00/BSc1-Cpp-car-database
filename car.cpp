#define _USE_MATH_DEFINES

#include <iostream>
#include <iomanip>
#include <cmath>
#include "wheels.h"
#include "car.h"

using namespace std;

// TODO remove "this"
// TODO move to init list
Car::Car() {
    this->id = 0;
    this->filter = false;
    this->car_make = "";
    this->car_model = "";
    this->car_year = 0;
    this->car_price = 0;
    this->max_speed = 0;
    this->not_to_sixty = 0.0;
    this->sixty_to_max_speed = 0.0;
    this->offroad_hindrance = 0.0;
    this->maneuverability = 0.0;
}

Car::Car(
        int id,
        bool filter,
        const string& car_make, 
        const string& car_model,
        int car_year,
        int car_price,
        int max_speed,
        float not_to_sixty,
        float sixty_to_max_speed,
        float offroad_hindrance,
        float maneuverability,
        int tireSize,
        const string& tireType,
        float protectorDepth
    ) : 
        id(id),
        filter(filter),
        car_make(car_make),
        car_model(car_model),
        car_year(car_year),
        car_price(car_price),
        max_speed(max_speed),
        not_to_sixty(not_to_sixty),
        sixty_to_max_speed(sixty_to_max_speed),
        offroad_hindrance(offroad_hindrance),
        maneuverability(maneuverability),
        wheels(tireSize, tireType, protectorDepth)
    {}


Car::~Car() {
#ifndef NDEBUG
    cout << "Car is deleted" << endl;
#endif
}

void Car::setID(int id) {
    if (id <= 0) {
        throw std::invalid_argument("Please make sure that id is a positive integer");
    }
    this->id = id;
}

void Car::setFilter(bool filter) {
    this->filter = filter;
}

void Car::setCarMake(const string& car_make) {

    if (std::string::npos != car_make.find_first_of("0123456789")) {
        throw std::invalid_argument("Car make cannot contain numbers!");
    }
    if (car_make.length() > MAX_ENTRY_SIZE) {
        throw std::invalid_argument("Database entry cannot contain more than 30 characters!");
    }
    this->car_make = car_make;
};

void Car::setCarModel(const string& car_model) {
    if (car_model.length() > MAX_ENTRY_SIZE) {
        throw std::invalid_argument("Database entry cannot contain more than 30 characters!");
    }
    this->car_model = car_model;
};


void Car::setCarYear(int car_year) {
    if (car_year < EARLIEST_YEAR || car_year > LATEST_YEAR) {
        throw std::invalid_argument("Please make sure that year is in normal format");
    }

    this->car_year = car_year;
};

void Car::setCarPrice(int car_price) {
    if (car_price <= 0) {
        throw std::invalid_argument("Price cannot be zero or negative!");
    }
    if (car_price > MAX_PRICE) {
        throw std::invalid_argument("Price has outgone its upper limit!");
    }

    this->car_price = car_price;
};

void Car::setMaxSpeed(int max_speed) {
    if (max_speed <= 0) {
        throw std::invalid_argument("Max speed cannot be zero or negative!");
    }
    if (max_speed > MAX_MAX_SPEED) {
        throw std::invalid_argument("Max speed has outgone its upper limit!");
    }

    this->max_speed = max_speed;
};

void Car::setNotToSixty(float not_to_sixty) {
    if (not_to_sixty <= 0) {
        throw std::invalid_argument("Not to sixty cannot be zero or negative!");
    }
    if (not_to_sixty > MAX_NOT_TO_SIXTY) {
        throw std::invalid_argument("Not to sixty has outgone its upper limit!");
    }

    this->not_to_sixty = not_to_sixty;
};

void Car::setSixtyToMaxSpeed(float sixty_to_max_speed) {
    if (sixty_to_max_speed <= 0) {
        throw std::invalid_argument("Sixty to max speed cannot be zero or negative!");
    }
    if (sixty_to_max_speed > MAX_SIXTY_TO_MAX_SPEED) {
        throw std::invalid_argument("Sixty to max speed has outgone its upper limit!");
    }

    this->sixty_to_max_speed = sixty_to_max_speed;
};

void Car::setOffroadHindrance(float offroad_hindrance) {
    if (offroad_hindrance <= 0 || offroad_hindrance > 1) {
        throw std::invalid_argument("Offroad hindrance cannot be zero, negative, or above 1 (one)!");
    }

    this->offroad_hindrance = offroad_hindrance;
};

void Car::setManeuverability(float maneuverability) {
    if (maneuverability <= 0 || maneuverability > 1) {
        throw std::invalid_argument("Maneuverability cannot be zero, negative, or above 1 (one)!");
    }

    this->maneuverability = maneuverability;
};

void Car::setConstant1(float not_to_sixty) {
    if (not_to_sixty <= 0) {
        throw std::invalid_argument("Not to sixty cannot be zero or negative!");
    }
    if (not_to_sixty > MAX_NOT_TO_SIXTY) {
        throw std::invalid_argument("Not to sixty has outgone its upper limit!");
    }

    this->constant1 = pow(M_E, log(27.8 + 1) / not_to_sixty) - 2;
};

void Car::setConstant2(float sixty_to_max_speed, int max_speed) {
    if (sixty_to_max_speed <= 0) {
        throw std::invalid_argument("Sixty to max speed cannot be zero or negative!");
    }
    if (sixty_to_max_speed > MAX_SIXTY_TO_MAX_SPEED) {
        throw std::invalid_argument("Sixty to max speed has outgone its upper limit!");
    }

    // TODO add static cast to float
    this->constant2 = (max_speed - 27.8) / log(sixty_to_max_speed + 1);
};

void Car::setRaceTime(float race_time) {
    if (race_time <= 0) {
        throw std::invalid_argument("Race time cannot be zero or negative!");
    }
    this->race_time = race_time;
};



int Car::getID() const {
    return this->id;
}

bool Car::getFilter() const {
    return this->filter;
}

const string& Car::getCarMake() const {
    return this->car_make;
}

const string& Car::getCarModel() const {
    return this->car_model;
};


int Car::getCarYear() const {
    return this->car_year;
};

int Car::getCarPrice() const {
    return this->car_price;
};

int Car::getMaxSpeed() const {
    return this->max_speed;
};

float Car::getNotToSixty() const {
    return this->not_to_sixty;
}

float Car::getSixtyToMaxSpeed() const {
    return this->sixty_to_max_speed;
}

float Car::getOffroadHindrance() const {
    return this->offroad_hindrance;
}

float Car::getManeuverability() const {
    return this->maneuverability;
}

float Car::getConstant1() const {
    return this->constant1;
}

float Car::getConstant2() const {
    return this->constant2;
}

float Car::getRaceTime() const {
    return this->race_time;
}

void Car::getCar(int id) {

    this->setID(id);
    this->setFilter(true);

    while (1) {

        cout << "Enter make > ";
        string car_make;
        cin >> car_make;
        try {
            this->setCarMake(car_make);
        } catch (const std::invalid_argument& e) {
            cout << e.what() << endl;
            continue;
        }
        // FIXME is this the way
        cin.get();
        break;
    }

    while (1) {

        cout << "Enter model > ";
        string car_model;
        getline(cin, car_model);
        try {
            this->setCarModel(car_model);
        } catch (const std::invalid_argument& e) {
            cout << e.what() << endl;
            continue;
        }
        break;
    }

    while(1) {
        cout << "Enter year > ";
        int car_year;
        cin >> car_year;

        try {
            this->setCarYear(car_year);
        } catch (const std::invalid_argument& e) {
            cout << e.what() << endl;
            continue;
        }
        break;
    }

    while(1) {
        cout << "Enter price > ";
        int car_price;
        cin >> car_price;

        try {
            this->setCarPrice(car_price);
        } catch (const std::invalid_argument& e) {
            cout << e.what() << endl;
            continue;
        }
        break;
    }


    while(1) {
        cout << "Enter max speed (km/h) > ";
        int max_speed;
        cin >> max_speed;

        try {
            this->setMaxSpeed(max_speed);
        } catch (const std::invalid_argument& e) {
            cout << e.what() << endl;
            continue;
        }
        break;
    }


    while(1) {
        cout << "Enter not to sixty (time, in seconds) > ";
        float not_to_sixty;
        cin >> not_to_sixty;

        try {
            this->setNotToSixty(not_to_sixty);
        } catch (const std::invalid_argument& e) {
            cout << e.what() << endl;
            continue;
        }
        break;
    }

    while(1) {
        cout << "Enter sixty to max speed (time, in seconds) > ";
        float sixty_to_max_speed;
        cin >> sixty_to_max_speed;

        try {
            this->setSixtyToMaxSpeed(sixty_to_max_speed);
        } catch (const std::invalid_argument& e) {
            cout << e.what() << endl;
            continue;
        }
        break;
    }

    while(1) {
        cout << "Enter offroad hindrance coefficient (how much the offroad slows the car), from 0 to 1 > ";
        float offroad_hindrance;
        cin >> offroad_hindrance;

        try {
            this->setOffroadHindrance(offroad_hindrance);
        } catch (const std::invalid_argument& e) {
            cout << e.what() << endl;
            continue;
        }
        break;
    }

    while(1) {
        cout << "Enter maneuverability coeffiecient (how well the car is suited to maneuvre in a race track) from 0 to 1 > ";
        float maneuverability;
        cin >> maneuverability;

        try {
            this->setManeuverability(maneuverability);
        } catch (const std::invalid_argument& e) {
            cout << e.what() << endl;
            continue;
        }
        break;
    }
    cin.get();

    // creating Wheels subobject
    Wheels wheels;

     while(1) {
        cout << "Enter wheels tire size (whole number (inches)) > ";
        int tireSize;;
        cin >> tireSize;

        try {
            wheels.setTireSize(tireSize);
        } catch (const std::invalid_argument& e) {
            cout << e.what() << endl;
            continue;
        }
        break;
    }

     while(1) {
        cout << "Enter wheels tire type > ";
        string tireType;
        cin >> tireType;
        try {
            wheels.setTireType(tireType);
        } catch (const std::invalid_argument& e) {
            cout << e.what() << endl;
            continue;
        }
        cin.get();
        break;
    }

     while(1) {
        cout << "Enter wheels tires' protector depth (in milimetres) > ";
        int protectorDepth;;
        cin >> protectorDepth;

        try {
            wheels.setProtectorDepth(protectorDepth);
        } catch (const std::invalid_argument& e) {
            cout << e.what() << endl;
            continue;
        }
        break;
    }

     this->wheels = wheels;
};

