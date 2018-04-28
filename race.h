#ifndef RACE_H
#define RACE_H

class Race {
    static float constant1;
    static float constant2;
    static float notToSixty;
    static float sixtyToMaxSpeed;
    static int maxSpeed;
    static double distance;
    static double raceDistance;

    public:
        Race();
        ~Race();

        static void setConstant1(float);
        static void setConstant2(float);
        static void setNotToSixty(float);
        static void setSixtyToMaxSpeed(float);
        static void setMaxSpeed(int);
        static void setDistance(double);
        static void setRaceDistance(double);

        static float getConstant1();
        static float getConstant2();
        static float getNotToSixty();
        static float getSixtyToMaxSpeed();
        static int getMaxSpeed();
        static double getDistance();
        static double getRaceDistance();

        static double f1(double);
        static double f2(double);
        static double f3(double);

        static void integral(double(*f)(double), double, double, int);
        static float race(int, int, int);
};
#endif
