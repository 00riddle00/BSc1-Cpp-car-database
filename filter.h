#ifndef __FILTER_H_
#define __FILTER_H_

#include <string>
#include <vector>

namespace FilterConstants {
	enum Fields { MAKE = 1, MODEL, YEAR, PRICE, MAXSPEED };
	enum Types { EQUAL = 1, CONTAINS, NOT_EQUAL, DOES_NOT_CONTAIN };
}


class Filter {

    FilterConstants::Fields field;
    FilterConstants::Types type;
    std::string value;

    void filter_by_make(std::vector<Car*> &cars) const;
    void filter_by_model(std::vector<Car*> &cars) const;
    void filter_by_year(std::vector<Car*> &cars) const;
    void filter_by_price(std::vector<Car*> &cars) const;
    void filter_by_max_speed(std::vector<Car*> &cars) const;

    public:
        Filter();
        Filter(int field, int type, const std::string& value);
        ~Filter();
		void setField(int field);
		void setType(int type);
        void setValue(const std::string& value);
        void filter(std::vector<Car*> &cars) const;
        void reset_filter(std::vector<Car*> &cars);

};

#endif


