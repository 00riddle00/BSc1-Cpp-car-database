#include "race.h"
#include <iostream>
#include <cmath>

using namespace std;

Race::Race() {
#ifndef NDEBUG
    cout << "Race object is created" << endl;
#endif
}

Race::~Race() {
#ifndef NDEBUG
    cout << "Race object is deleted" << endl;
#endif
}

void Race::setConstant1(float c1) {
    constant1 = c1;
}

void Race::setConstant2(float c2) {
    constant2 = c2;
}

void Race::setNotToSixty(float nts) {
    notToSixty = nts;
}

void Race::setSixtyToMaxSpeed(float stms) {
    sixtyToMaxSpeed = stms;
}

void Race::setMaxSpeed(int maxsp) {
    maxSpeed = maxsp;
}

void Race::setDistance(double d) {
    distance = d;
}

void Race::setRaceDistance(double rd) {
    raceDistance = rd;
}

float Race::getConstant1() {
    return constant1;
}

float Race::getConstant2() {
    return constant2;
}

float Race::getNotToSixty() {
    return notToSixty;
}

float Race::getSixtyToMaxSpeed() {
    return sixtyToMaxSpeed;
}

int Race::getMaxSpeed() {
    return maxSpeed;
}

double Race::getDistance() {
    return distance;
}

double Race::getRaceDistance() {
    return raceDistance;
}

double Race::f1(double x) {
    return pow(2 + constant1, x) - 1;
}

double Race::f2(double x) {
    return constant2 * log(x + 1) + 27.8;
}

double Race::f3(double x) {
    return maxSpeed / 3.6;
}

void Race::integral(double(*f)(double x), double a, double b, int n) {
    double step = (b - a) / n;  // width of each small rectangle
    for (int i = 0; i < n; i ++) {
        distance += f(a + (i + 0.5) * step) * step; // sum up each small rectangle
    }
}

float Race::race(int notToSixtySteps, int sixtyToMaxSpeedSteps, int maxSpeedSteps) {

    for (size_t j = 0; j < 100; j++) {
        integral(&f1, j * notToSixty / notToSixtySteps, (j+1) * notToSixty / notToSixtySteps, 1);
        if (distance > raceDistance) {
            // return total time
            return (j+1) * notToSixty / notToSixtySteps;
        }
    }

    for (size_t j = 0; j < sixtyToMaxSpeedSteps; j++) {
        integral(&f2, j * sixtyToMaxSpeed / sixtyToMaxSpeedSteps, (j+1) * sixtyToMaxSpeed / sixtyToMaxSpeedSteps, 1);
        if (distance > raceDistance) {
            // return total time
            return notToSixty + (j+1) * sixtyToMaxSpeed / sixtyToMaxSpeedSteps;
        }
    }

    for (size_t j = 0; j < maxSpeedSteps; j++) {
        integral(&f3, j, j+1, 1);
        if (distance > raceDistance) {
            // return total time
            return notToSixty + sixtyToMaxSpeed + j+1;
        }
    }
}

float Race::constant1 = 0;
float Race::constant2 = 0;
float Race::notToSixty = 0;
float Race::sixtyToMaxSpeed = 0;
int Race::maxSpeed = 0;
double Race::distance = 0;
double Race::raceDistance = 0;


