#ifndef TEMPLATE_RACE_H
#define TEMPLATE_RACE_H

template <class T>
class Race {
    static T constant1;
    static T constant2;
    static T notToSixty;
    static T sixtyToMaxSpeed;
    static T maxSpeed;
    static T distance;
    static T raceDistance;

    public:
        Race();
        ~Race();

        static void setConstant1(T);
        static void setConstant2(T);
        static void setNotToSixty(T);
        static void setSixtyToMaxSpeed(T);
        static void setMaxSpeed(T);
        static void setDistance(T);
        static void setRaceDistance(T);

        static T getConstant1();
        static T getConstant2();
        static T getNotToSixty();
        static T getSixtyToMaxSpeed();
        static T getMaxSpeed();
        static T getDistance();
        static T getRaceDistance();

        static T f1(T);
        static T f2(T);
        static T f3(T);

        static void integral(T(*f)(T), T, T, int);
        static T race(int, int, int);
};


#include "template_race_impl.h"

#endif
