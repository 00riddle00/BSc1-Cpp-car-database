#ifndef RACECAR_H
#define RACECAR_H

#include <iostream>
#include "car.h"

class RaceCar : public Car {
    float heightFromGround;
    float aerodynamicsCoefficient;

    public:
        RaceCar();

        RaceCar(
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
            float heightFromGround,
            float aerodynamicsCoefficient
        );

        ~RaceCar() override;

        void setHeightFromGround(float);
        void setAerodynamicsCoefficient(float);

        float getHeightFromGround() const;
        float getAerodynamicsCoefficient() const;

        void getCar(int) override;

        float getNotToSixtyForRace(const std::string&) const override;
        float getSixtyToMaxSpeedForRace(const std::string&) const override;
        int getMaxSpeedForRace(const std::string&) const override; 
};

#endif
