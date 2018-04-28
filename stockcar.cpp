#include <iostream>
#include <cmath>
#include "stockcar.h"

using namespace std;


StockCar::StockCar() 
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
    )
    {}


StockCar::StockCar(
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
        )
        {}

StockCar::~StockCar() {
#ifndef NDEBUG
    cout << "StockCar is deleted" << endl;
#endif
}

// TODO is it even needed here?
void StockCar::getCar(int id) {
    Car::getCar(id);
}

float StockCar::getNotToSixtyForRace(const string& raceType) const {
    float notToSixty;

    if (raceType == "drag") {
        notToSixty = getNotToSixty() * (1 + (fabs(wheels.getTireSize() - 15) / 1000)) * (1 + (fabs(wheels.getProtectorDepth() - 3) / 100));
        if (wheels.getTireType() == "drag") {
            notToSixty *= 0.96;
        } else if (wheels.getTireType() == "track") {
            notToSixty *= 1.04;
        } else if (wheels.getTireType() == "offroad") {
            notToSixty *= 1.08;
        }
    } else if (raceType == "track") {
        notToSixty = getNotToSixty() * (1 + (fabs(wheels.getTireSize() - 14) / 1000)) * (1 + (fabs(wheels.getProtectorDepth() - 6) / 100));
        if (wheels.getTireType() == "drag") {
            notToSixty *= 1.04;
        } else if (wheels.getTireType() == "track") {
            notToSixty *= 0.97;
        } else if (wheels.getTireType() == "offroad") {
            notToSixty *= 1.10;
        }
    } else if (raceType == "offroad") {
        notToSixty = getNotToSixty() * (1 + (fabs(wheels.getTireSize() - 25) / 1000)) * (1 + (fabs(wheels.getProtectorDepth() - 20) / 100));
        if (wheels.getTireType() == "drag") {
            notToSixty *= 1.08;
        } else if (wheels.getTireType() == "track") {
            notToSixty *= 1.04;
        } else if (wheels.getTireType() == "offroad") {
            notToSixty *= 0.98;
        }
    }
    return notToSixty;
}

float StockCar::getSixtyToMaxSpeedForRace(const string& raceType) const {
    float sixtyToMaxSpeed;

    if (raceType == "drag") {
        sixtyToMaxSpeed = getSixtyToMaxSpeed() * (1 + (fabs(wheels.getTireSize() - 15) / 1000)) * (1 + (fabs(wheels.getProtectorDepth() - 2) / 100));
        if (wheels.getTireType() == "drag") {
            sixtyToMaxSpeed *= 0.94;
        } else if (wheels.getTireType() == "track") {
            sixtyToMaxSpeed *= 1.04;
        } else if (wheels.getTireType() == "offroad") {
            sixtyToMaxSpeed *= 1.10;
        }
    } else if (raceType == "track") {
        sixtyToMaxSpeed = getSixtyToMaxSpeed() * (1 + (fabs(wheels.getTireSize() - 14) / 1000)) * (1 + (fabs(wheels.getProtectorDepth() - 5) / 100));
        if (wheels.getTireType() == "drag") {
            sixtyToMaxSpeed *= 1.06;
        } else if (wheels.getTireType() == "track") {
            sixtyToMaxSpeed *= 0.97;
        } else if (wheels.getTireType() == "offroad") {
            sixtyToMaxSpeed *= 1.14;
        }
    } else if (raceType == "offroad") {
        sixtyToMaxSpeed = getSixtyToMaxSpeed() * (1 + (fabs(wheels.getTireSize() - 25) / 1000)) * (1 + (fabs(wheels.getProtectorDepth() - 18) / 100));
        if (wheels.getTireType() == "drag") {
            sixtyToMaxSpeed *= 1.20;
        } else if (wheels.getTireType() == "track") {
            sixtyToMaxSpeed *= 1.10;
        } else if (wheels.getTireType() == "offroad") {
            sixtyToMaxSpeed *= 0.95;
        }
    }
    return sixtyToMaxSpeed;
}

int StockCar::getMaxSpeedForRace(const string& raceType) const {
    float maxSpeed = getMaxSpeed();

    // if (raceType == "drag") <- nothing changes
    if (raceType == "track") {
        maxSpeed = (maxSpeed - 100) * (1 + getManeuverability());
    } else if (raceType == "offroad") {
        maxSpeed = (maxSpeed - 150) * (2 - getOffroadHindrance());
    }

    return floor(maxSpeed + 0.5);
}


