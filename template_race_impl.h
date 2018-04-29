#include <iostream>
#include <cmath>

using namespace std;

template <class T>
Race<T>::Race() {
#ifndef NDEBUG
    cout << "Race object is created" << endl;
#endif
}

template <class T>
Race<T>::~Race() {
#ifndef NDEBUG
    cout << "Race object is deleted" << endl;
#endif
}

template <class T>
void Race<T>::setConstant1(T c1) {
    constant1 = c1;
}

template <class T>
void Race<T>::setConstant2(T c2) {
    constant2 = c2;
}

template <class T>
void Race<T>::setNotToSixty(T nts) {
    notToSixty = nts;
}

template <class T>
void Race<T>::setSixtyToMaxSpeed(T stms) {
    sixtyToMaxSpeed = stms;
}

template <class T>
void Race<T>::setMaxSpeed(T maxsp) {
    maxSpeed = maxsp;
}

template <class T>
void Race<T>::setDistance(T d) {
    distance = d;
}

template <class T>
void Race<T>::setRaceDistance(T rd) {
    raceDistance = rd;
}

template <class T>
T Race<T>::getConstant1() {
    return constant1;
}

template <class T>
T Race<T>::getConstant2() {
    return constant2;
}

template <class T>
T Race<T>::getNotToSixty() {
    return notToSixty;
}

template <class T>
T Race<T>::getSixtyToMaxSpeed() {
    return sixtyToMaxSpeed;
}

template <class T>
T Race<T>::getMaxSpeed() {
    return maxSpeed;
}

template <class T>
T Race<T>::getDistance() {
    return distance;
}

template <class T>
T Race<T>::getRaceDistance() {
    return raceDistance;
}

template <class T>
T Race<T>::f1(T x) {
    return pow(2 + constant1, x) - 1;
}

template <class T>
T Race<T>::f2(T x) {
    return constant2 * log(x + 1) + 27.8;
}

template <class T>
T Race<T>::f3(T x) {
    return maxSpeed / 3.6;
}

template <class T>
void Race<T>::integral(T(*f)(T x), T a, T b, int n) {
    T step = (b - a) / n;  // width of each small rectangle
    for (int i = 0; i < n; i ++) {
        distance += f(a + (i + 0.5) * step) * step; // sum up each small rectangle
    }
}

template <class T>
T Race<T>::race(int notToSixtySteps, int sixtyToMaxSpeedSteps, int maxSpeedSteps) {

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

template <class T>
T Race<T>::constant1 = 0;

template <class T>
T Race<T>::constant2 = 0;

template <class T>
T Race<T>::notToSixty = 0;

template <class T>
T Race<T>::sixtyToMaxSpeed = 0;

template <class T>
T Race<T>::maxSpeed = 0;

template <class T>
T Race<T>::distance = 0;

template <class T>
T Race<T>::raceDistance = 0;

