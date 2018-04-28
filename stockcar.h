#ifndef STOCKCAR_H
#define STOCKCAR_H

#include <iostream>
#include "car.h"

class StockCar : public Car {
    public:
        StockCar();

        StockCar(
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
            float protectorDepth
        );

        ~StockCar() override;

        void getCar(int) override;

        float getNotToSixtyForRace(const std::string&) const override;
        float getSixtyToMaxSpeedForRace(const std::string&) const override;
        int getMaxSpeedForRace(const std::string&) const override; 


};

#endif
