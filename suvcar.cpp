#include <iostream>
#include <cmath>
#include "suvcar.h"

using namespace std;

SUVCar::SUVCar() 
    : Car(
        0,
        false,
        "",
        "",
        0,
        0,
        0,
        0.0,
        0.0,
        0.0,
        0.0,
        0,
        "",
        0.0
    ),
    heightFromGround(0.0)
    {}


SUVCar::SUVCar(
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
        float protectorDepth,
        float heightFromGround
    ) : 
        Car(
            id,
            filter,
            car_make,
            car_model,
            car_year,
            car_price,
            max_speed,
            not_to_sixty,
            sixty_to_max_speed,
            offroad_hindrance,
            maneuverability,
            tireSize,
            tireType,
            protectorDepth
        ), 
        heightFromGround(heightFromGround)
        {}

SUVCar::~SUVCar() { 
    decrementNumberOfCars();
#ifndef NDEBUG
    cout << "SUVCar is deleted" << endl;
#endif
}


void SUVCar::setHeightFromGround(float heightFromGround) {
    if (heightFromGround <= 0) {
        throw std::invalid_argument("Height from ground cannot be zero or negative!");
    }
    if (heightFromGround > MAX_HEIGHT_FROM_GROUND) {
        throw std::invalid_argument("Height from ground has outgone its upper limit!");
    }

    this->heightFromGround = heightFromGround;
};

float SUVCar::getHeightFromGround() const {
    return this->heightFromGround;
}

void SUVCar::getCar(int id) {
    Car::getCar(id);

    while(1) {
        cout << "Enter car body height from the ground (in centimeters) > ";
        float heightFromGround;
        cin >> heightFromGround;

        try {
            this->setHeightFromGround(heightFromGround);
        } catch (const std::invalid_argument& e) {
            cout << e.what() << endl;
            continue;
        }
        break;
    }
}

float SUVCar::getNotToSixtyForRace(const string& raceType) const {
    float notToSixty;

    if (raceType == "drag") {
        notToSixty = getNotToSixty() * (1 + (fabs(wheels.getTireSize() - 15) / 1000)) * (1 + (fabs(wheels.getProtectorDepth() - 3) / 100));
        if (wheels.getTireType() == "drag") {
            notToSixty *= 0.98;
        } else if (wheels.getTireType() == "track") {
            notToSixty *= 1.02;
        } else if (wheels.getTireType() == "offroad") {
            notToSixty *= 1.04;
        }
    } else if (raceType == "track") {
        notToSixty = getNotToSixty() * (1 + (fabs(wheels.getTireSize() - 14) / 1000)) * (1 + (fabs(wheels.getProtectorDepth() - 5) / 100));
        if (wheels.getTireType() == "drag") {
            notToSixty *= 1.03;
        } else if (wheels.getTireType() == "track") {
            notToSixty *= 0.95;
        } else if (wheels.getTireType() == "offroad") {
            notToSixty *= 1.08;
        }
    } else if (raceType == "offroad") {
        notToSixty = getNotToSixty() * (1 + (fabs(wheels.getTireSize() - 23) / 1000)) * (1 + (fabs(wheels.getProtectorDepth() - 18) / 100));
        if (wheels.getTireType() == "drag") {
            notToSixty *= 1.07;
        } else if (wheels.getTireType() == "track") {
            notToSixty *= 1.02;
        } else if (wheels.getTireType() == "offroad") {
            notToSixty *= 0.95;
        }
    }
    return notToSixty;
}

float SUVCar::getSixtyToMaxSpeedForRace(const string& raceType) const {
    float sixtyToMaxSpeed;

    if (raceType == "drag") {
        sixtyToMaxSpeed = getSixtyToMaxSpeed() * (1 + (fabs(wheels.getTireSize() - 15) / 1000)) * (1 + (fabs(wheels.getProtectorDepth() - 3) / 100));
        if (wheels.getTireType() == "drag") {
            sixtyToMaxSpeed *= 0.96;
        } else if (wheels.getTireType() == "track") {
            sixtyToMaxSpeed *= 1.03;
        } else if (wheels.getTireType() == "offroad") {
            sixtyToMaxSpeed *= 1.07;
        }
    } else if (raceType == "track") {
        sixtyToMaxSpeed = getSixtyToMaxSpeed() * (1 + (fabs(wheels.getTireSize() - 14) / 1000)) * (1 + (fabs(wheels.getProtectorDepth() - 5) / 100));
        if (wheels.getTireType() == "drag") {
            sixtyToMaxSpeed *= 1.04;
        } else if (wheels.getTireType() == "track") {
            sixtyToMaxSpeed *= 0.92;
        } else if (wheels.getTireType() == "offroad") {
            sixtyToMaxSpeed *= 1.09;
        }
    } else if (raceType == "offroad") {
        sixtyToMaxSpeed = getSixtyToMaxSpeed() * (1 + (fabs(wheels.getTireSize() - 25) / 1000)) * (1 + (fabs(wheels.getProtectorDepth() - 19) / 100));
        if (wheels.getTireType() == "drag") {
            sixtyToMaxSpeed *= 1.17;
        } else if (wheels.getTireType() == "track") {
            sixtyToMaxSpeed *= 1.07;
        } else if (wheels.getTireType() == "offroad") {
            sixtyToMaxSpeed *= 0.93;
        }
    }
    return sixtyToMaxSpeed;
}

int SUVCar::getMaxSpeedForRace(const string& raceType) const {
    float maxSpeed = getMaxSpeed();

    // if (raceType == "drag") -> nothing changes
    if (raceType == "track") {
        maxSpeed = (maxSpeed - 100) * (1 + getManeuverability());
    } else if (raceType == "offroad") {
        maxSpeed = (maxSpeed - 150) * (2 - getOffroadHindrance());
    }

    return floor(maxSpeed + 0.5);
}


