#ifndef __SORTING_H_
#define __SORTING_H_

#include <string>
#include <vector>

namespace SortingConstants {
    enum Fields { MAKE = 1, MODEL, YEAR, PRICE, MAXSPEED, RACETIME, ID };
    enum Types { ASCENDING = 1, DESCENDING };
};

class Sorting {

    SortingConstants::Fields field;
    SortingConstants::Types type;

    int first;
    int last;

    void sort_by_year(std::vector<Car*> &cars, int first, int last) const;
    void sort_by_price(std::vector<Car*> &cars, int first, int last) const;
    void sort_by_max_speed(std::vector<Car*> &cars, int first, int last) const;
    void sort_by_race_time(std::vector<Car*> &cars, int first, int last) const;
    void sort_by_id(std::vector<Car*> &cars, int first, int last) const;

    public:
        Sorting();
        Sorting(int field, int type);
        ~Sorting();
		void setField(int field);
		void setType(int type);
        void sort (std::vector<Car*> &cars);
};

#endif


