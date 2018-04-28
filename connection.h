#ifndef __CONNECTION_H_
#define __CONNECTION_H_

#include <fstream>
#include <vector>

class Car;

class Connection {
    std::ofstream output;
    std::ifstream input;
    const std::string filename;

    public:
        explicit Connection(const std::string& filename);
        ~Connection();

        void load_from_file_stock_cars(std::vector<Car*> &cars);
        void load_from_file_race_cars(std::vector<Car*> &cars);
        void load_from_file_suv_cars(std::vector<Car*> &cars);

        void write_to_file_stock_cars(std::vector<Car*> &cars);
        void write_to_file_race_cars(std::vector<Car*> &cars);
        void write_to_file_suv_cars(std::vector<Car*> &cars);
};

#endif
