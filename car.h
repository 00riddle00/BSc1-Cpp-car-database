#ifndef __CAR_H_
#define __CAR_H_

#include "wheels.h"

const int MAX_ENTRY_SIZE = 30;
const int LATEST_YEAR = 2018;
const int EARLIEST_YEAR = 1920;
const int MAX_PRICE = 1e9;
const int MAX_MAX_SPEED = 420;
const float MAX_NOT_TO_SIXTY = 100.0;
const float MAX_SIXTY_TO_MAX_SPEED = 1000.0;

const float MAX_HEIGHT_FROM_GROUND = 150.0;


class Car {
    int id;
    bool filter;
    std::string car_make;
    std::string car_model;
    int car_year;
    int car_price;
    int max_speed;
    float not_to_sixty;
    float sixty_to_max_speed;
    float offroad_hindrance;
    float maneuverability;
    // FIXME use the pointer or not?
    float constant1;
    float constant2;
    float race_time;
    static size_t numberOfCars;

    public:
        Wheels wheels;

        Car();
        Car(
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

        Car(const Car& orig);

        virtual ~Car() = 0;

        void setID(int);
        void setFilter(bool);
        void setCarMake(const std::string&);
        void setCarModel(const std::string&);
        void setCarYear(int);
        void setCarPrice(int);
        void setMaxSpeed(int);
        void setNotToSixty(float);
        void setSixtyToMaxSpeed(float);
        void setOffroadHindrance(float);
        void setManeuverability(float);
        void setConstant1(float);
        void setConstant2(float, int);
        void setRaceTime(float);

        int getID() const;
        bool getFilter() const;
        const std::string& getCarMake() const;
        const std::string& getCarModel() const;
        int getCarYear() const;
        int getCarPrice() const;
        int getMaxSpeed() const;
        float getNotToSixty() const;
        float getSixtyToMaxSpeed() const;
        float getOffroadHindrance() const;
        float getManeuverability() const;
        float getConstant1() const;
        float getConstant2() const;
        float getRaceTime() const;

        virtual void getCar(int id);

        virtual float getNotToSixtyForRace(const std::string&) const = 0;
        virtual float getSixtyToMaxSpeedForRace(const std::string&) const = 0;
        virtual int getMaxSpeedForRace(const std::string&) const = 0;

        static size_t getNumberOfCars();
        static void decrementNumberOfCars();
};

#endif
