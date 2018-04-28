#ifndef SUVCAR_H
#define SUVCAR_H

#include <iostream>
#include "car.h"


class SUVCar : public Car {
    float heightFromGround;

    public: 
        SUVCar();

        SUVCar(
            int id,
            bool filter,
            const std::string& car_make, 
            const std::string& car_model,
            int car_year,
            int car_price,
            int max_speed,
            float not_to_sixty,
            float sixty_to_max_speed,
            float offroad_hindrance,
            float maneuverability,
            int tireSize,
            const std::string& tireType,
            float protectorDepth,
            float heightFromGround
        );

        ~SUVCar();

        void setHeightFromGround(float);

        float getHeightFromGround() const;

        void getCar(int) override;

        float getNotToSixtyForRace(const std::string&) const override;
        float getSixtyToMaxSpeedForRace(const std::string&) const override;
        int getMaxSpeedForRace(const std::string&) const override; 
};




#endif
