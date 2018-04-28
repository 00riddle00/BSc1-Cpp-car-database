#include <iostream>
#include <fstream>
#include <vector>

#include "load_from_binary_file.h"
#include "write_to_binary_file.h"
#include "car.h"
#include "stockcar.h"
#include "racecar.h"
#include "suvcar.h"
#include "connection.h"

using namespace std;

Connection::Connection(const string& filename) : filename(filename) {}

Connection::~Connection() {
    if (this->input.is_open()) {
        this->input.close();
    }

    if (this->output.is_open()) {
        this->output.close();
    }
}

void Connection::load_from_file_stock_cars(vector<Car*> &cars) {

    this->input.open(this->filename, ios::in | ios::binary);

    this->input.seekg(0, std::ios::end);
    if (this->input.tellg() == 0)
    {
        std::cout << "File is empty" << std::endl;
        return;
    }

    LoadFromBinaryFile lb(this->filename);

    if(this->input.good()) {

        int size = lb.readInt();

        for (int i = 0; i < size; i++) {

            cars.push_back(
                new StockCar(
                    lb.readInt(),
                    lb.readInt(), 
                    lb.readString(MAX_ENTRY_SIZE), 
                    lb.readString(MAX_ENTRY_SIZE),
                    lb.readInt(),
                    lb.readInt(),
                    lb.readInt(),
                    lb.readFloat(),
                    lb.readFloat(),
                    lb.readFloat(),
                    lb.readFloat(),
                    lb.readInt(),
                    lb.readString(MAX_ENTRY_SIZE), 
                    lb.readFloat()
                )
            );

        }

        lb.close();
    } 
}


void Connection::load_from_file_race_cars(vector<Car*> &cars) {

    this->input.open(this->filename, ios::in | ios::binary);

    this->input.seekg(0, std::ios::end);
    if (this->input.tellg() == 0)
    {
        std::cout << "File is empty" << std::endl;
        return;
    }

    LoadFromBinaryFile lb(this->filename);

    if(this->input.good()) {

        int size = lb.readInt();

        for (int i = 0; i < size; i++) {

            cars.push_back(
                new RaceCar(
                    lb.readInt(),
                    lb.readInt(), 
                    lb.readString(MAX_ENTRY_SIZE), 
                    lb.readString(MAX_ENTRY_SIZE),
                    lb.readInt(),
                    lb.readInt(),
                    lb.readInt(),
                    lb.readFloat(),
                    lb.readFloat(),
                    lb.readFloat(),
                    lb.readFloat(),
                    lb.readInt(),
                    lb.readString(MAX_ENTRY_SIZE), 
                    lb.readFloat(),
                    // heightFromGround
                    lb.readFloat(),
                    // aerodynamicsCoefficient
                    lb.readFloat()
                )
            );

        }

        lb.close();
    } 
}


void Connection::load_from_file_suv_cars(vector<Car*> &cars) {

    this->input.open(this->filename, ios::in | ios::binary);

    this->input.seekg(0, std::ios::end);
    if (this->input.tellg() == 0)
    {
        std::cout << "File is empty" << std::endl;
        return;
    }

    LoadFromBinaryFile lb(this->filename);

    if(this->input.good()) {

        int size = lb.readInt();

        for (int i = 0; i < size; i++) {

            cars.push_back(
                new SUVCar(
                    lb.readInt(),
                    lb.readInt(), 
                    lb.readString(MAX_ENTRY_SIZE), 
                    lb.readString(MAX_ENTRY_SIZE),
                    lb.readInt(),
                    lb.readInt(),
                    lb.readInt(),
                    lb.readFloat(),
                    lb.readFloat(),
                    lb.readFloat(),
                    lb.readFloat(),
                    lb.readInt(),
                    lb.readString(MAX_ENTRY_SIZE), 
                    lb.readFloat(),
                    // heightFromGround
                    lb.readFloat()
                )
            );

        }

        lb.close();
    } 
}

void Connection::write_to_file_stock_cars(vector<Car*> &cars) {

    WriteToBinaryFile wb(this->filename);
    int size = cars.size();
    wb.write(size);

    for (size_t i = 0; i < cars.size(); i++) {

        StockCar *stockCar = dynamic_cast<StockCar*>(cars[i]);
        if (stockCar != nullptr) {
            wb.write(stockCar->getID());
            wb.write(stockCar->getFilter());
            wb.write(stockCar->getCarMake(), MAX_ENTRY_SIZE);
            wb.write(stockCar->getCarModel(), MAX_ENTRY_SIZE);
            wb.write(stockCar->getCarYear());
            wb.write(stockCar->getCarPrice());
            wb.write(stockCar->getMaxSpeed());
            wb.write(stockCar->getNotToSixty());
            wb.write(stockCar->getSixtyToMaxSpeed());
            wb.write(stockCar->getOffroadHindrance());
            wb.write(stockCar->getManeuverability());
            wb.write(stockCar->wheels.getTireSize());
            wb.write(stockCar->wheels.getTireType(), MAX_ENTRY_SIZE);
            wb.write(stockCar->wheels.getProtectorDepth());
        }
    }

    wb.close();
}

void Connection::write_to_file_race_cars(vector<Car*> &cars) {

    WriteToBinaryFile wb(this->filename);
    int size = cars.size();
    wb.write(size);

    for (size_t i = 0; i < cars.size(); i++) {

        RaceCar *raceCar = dynamic_cast<RaceCar*>(cars[i]);
        if (raceCar != nullptr) {

            wb.write(raceCar->getID());
            wb.write(raceCar->getFilter());
            wb.write(raceCar->getCarMake(), MAX_ENTRY_SIZE);
            wb.write(raceCar->getCarModel(), MAX_ENTRY_SIZE);
            wb.write(raceCar->getCarYear());
            wb.write(raceCar->getCarPrice());
            wb.write(raceCar->getMaxSpeed());
            wb.write(raceCar->getNotToSixty());
            wb.write(raceCar->getSixtyToMaxSpeed());
            wb.write(raceCar->getOffroadHindrance());
            wb.write(raceCar->getManeuverability());
            wb.write(raceCar->wheels.getTireSize());
            wb.write(raceCar->wheels.getTireType(), MAX_ENTRY_SIZE);
            wb.write(raceCar->wheels.getProtectorDepth());
            // heightFromGround
            wb.write(raceCar->getHeightFromGround());
            // aerodynamicsCoeffiecient
            wb.write(raceCar->getAerodynamicsCoefficient());
        }
    }

    wb.close();
}

void Connection::write_to_file_suv_cars(vector<Car*> &cars) {

    WriteToBinaryFile wb(this->filename);
    int size = cars.size();
    wb.write(size);

    for (size_t i = 0; i < cars.size(); i++) {

        SUVCar *suvCar = dynamic_cast<SUVCar*>(cars[i]);
        if (suvCar != nullptr) {
            wb.write(suvCar->getID());
            wb.write(suvCar->getFilter());
            wb.write(suvCar->getCarMake(), MAX_ENTRY_SIZE);
            wb.write(suvCar->getCarModel(), MAX_ENTRY_SIZE);
            wb.write(suvCar->getCarYear());
            wb.write(suvCar->getCarPrice());
            wb.write(suvCar->getMaxSpeed());
            wb.write(suvCar->getNotToSixty());
            wb.write(suvCar->getSixtyToMaxSpeed());
            wb.write(suvCar->getOffroadHindrance());
            wb.write(suvCar->getManeuverability());
            wb.write(suvCar->wheels.getTireSize());
            wb.write(suvCar->wheels.getTireType(), MAX_ENTRY_SIZE);
            wb.write(suvCar->wheels.getProtectorDepth());
            // heightFromGround
            wb.write(suvCar->getHeightFromGround());
        }
    }
    wb.close();
}


