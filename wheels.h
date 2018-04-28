#ifndef WHEELS_H
#define WHEELS_H

#include <iostream>

const int MAX_TIRE_SIZE = 30;
const float MAX_PROTECTOR_DEPTH = 100.0;

class Wheels {
    int tireSize;
    // TODO convert to ENUM
    std::string tireType;
    float protectorDepth;

    public:
        Wheels();
        Wheels(int, const std::string&, float);
        ~Wheels();

        void setTireSize(int);
        void setTireType(const std::string&);
        void setProtectorDepth(float);

        int getTireSize() const;
        const std::string& getTireType() const;
        float getProtectorDepth() const;
};

#endif
