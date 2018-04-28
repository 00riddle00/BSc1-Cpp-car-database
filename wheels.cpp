#include <iostream>
#include "wheels.h"

using namespace std;

Wheels::Wheels() {
    this->tireSize = 0;
    this->tireType = "";
    this->protectorDepth = 0;
}

Wheels::Wheels(int tireSize, const string& tireType, float protectorDepth) {
    this->tireSize = tireSize;
    this->tireType = tireType;
    this->protectorDepth = protectorDepth;
}

Wheels::~Wheels() {
#ifndef NDEBUG
    cout << "Wheels object is deleted" << endl;
#endif
}

void Wheels::setTireSize(int tireSize) {
    if (tireSize <= 0) {
        throw std::invalid_argument("Please make sure that tire size is a positive integer");
    }
    if (tireSize > MAX_TIRE_SIZE) {
        throw std::invalid_argument("Tire size has outgone its upper limit!");
    }

    this->tireSize = tireSize;
}

void Wheels::setTireType(const string& tireType) {
    // TODO add validation
    this->tireType = tireType;
}

void Wheels::setProtectorDepth(float protectorDepth) {
    if (protectorDepth <= 0) {
        throw std::invalid_argument("Please make sure that protector depth is not negative or zero");
    }
    if (protectorDepth > MAX_PROTECTOR_DEPTH) {
        throw std::invalid_argument("Protector depth has outgone its upper limit!");
    }

    this->protectorDepth = protectorDepth;
}

int Wheels::getTireSize() const {
    return this->tireSize;
}

const string& Wheels::getTireType() const {
    return this->tireType;
}

float Wheels::getProtectorDepth() const {
    return this->protectorDepth;
}
