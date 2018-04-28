/*==============================================================================
 |
 |  Assignment:  Homework #2
 |
 |       Author:  Tomas Giedraitis
 |  Study group:  VU MIF INFO1, 1st group
 |     Contacts:  tomasgiedraitis@gmail.com
 |        Class:  Programming Basics
 |         Date:  March 8th, 2018
 |
 |     Language:  C++ (using gcc on Lenovo Y50-70, OS: Arch Linux x86_64)
 |
 +-----------------------------------------------------------------------------
 |
 |  Description:  A car database program, where one can perform get, list, 
 |                create, edit, delete and clear operations. There are four fields
 | 				  for each car entry: (1) Make (2) Model (3) Year (4) Price. The 
 | 			      database is loaded from and saved to the binary file. The user
 | 				  can also perform sorting (ascending, descending) actions by each
 | 			      of the four fields, and also filtering by each field. There are 
 | 			      four filtering options: (1) Value is equal (2) Value contains 
 | 				  (3) Value is not equal (4) Value does not contain. After sorting
 | 			      or filtering, the changed database output is displayed to the 
 | 			      screen. Each time the program runs, the log entry is created in 
 |                ./log.txt file, with the info about the beginning of the program 
 |                 and how much time did it run.
 |
 |  Constraints:  
 |                
 |	    Input:    Command line input by user
 |
 |	    Output:   Prompt messages, validation errors and final results
 |                are displayed one per line to the standard output.
 |
 |  Known bugs:   
 |                
 |       TODOS:   (1) Add unit tests
 |
 | Version
 | updates:       Version 1.8
 |
 +===========================================================================*/

#include <iterator>
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <ctime>
#include <cmath>

#include "Helpers.h"
#include "input.h"
#include "car.h"
#include "stockcar.h"
#include "racecar.h"
#include "suvcar.h"
#include "table.h"
#include "connection.h"
#include "filter.h"
#include "sorting.h"
#include "race.h"

#define LOGFILE "log.txt"

using namespace std;


void list_data(Table &table, vector<Car*> &cars, bool sortedByID = true, bool filtered = false);

void perform_action(Table &table, vector<Car*> &cars);


// TODO add description
void race(Table &table, vector<Car*> &cars);

// this function gets called with atexit()
// writes logging info to a log file and 
// displays goodbye message
void exiting();


static clock_t start;
static clock_t finish;

static double clocks;
static double time_spent;

// TODO ir be static globalus
// static paslepia rysiu redagavima i vidini (jei dar globalus
// butu logfile, nesipjautu jie) (matomas tik to failo failo ribose)
static ofstream logfile;


int main(int argc, char *argv[]) {

    Table table({"ID", "Make", "Model", "Year", "Price", "Max Speed"}, {4, 30, 30, 10, 10, 11});

    std::vector<Car*> cars;

    if (argc < 4) {
        cout << "USAGE: test <dbfile_stockCars> <dbfile_raceCars> <dbfile_suvCars> <action> [action params]" << endl;
        exit(1);
    }

    logfile.open(LOGFILE, std::ofstream::out | std::ofstream::app);

    // current date/time based on current system
    const time_t now = time(0);

    // convert now to string form
    const char* current_time = ctime(&now);

    logfile << "Starting program @" << current_time;

    start = clock();

    /* register the termination function */
    atexit(exiting);

    Connection* conn_stock_cars = new Connection(argv[1]);
    conn_stock_cars->load_from_file_stock_cars(cars);

    Connection* conn_race_cars = new Connection(argv[2]);
    conn_race_cars->load_from_file_race_cars(cars);

    Connection* conn_suv_cars = new Connection(argv[3]);
    conn_suv_cars->load_from_file_suv_cars(cars);

    const string about = "This is a car database program, where one can perform get, list, create, edit and delete "
            "operations. The database is loaded from and saved to the binary file. Version: v.0";

    const string info = "Usage: in the main shell, input the Action[1] and ID[2].\n\n[1] Action - g=get, l=list, "
        "s=set, d=delete, c=clear database, q=quit, i=info.\n[2] ID - a positive integer. Only get, "
        "set and delete operations require ID parameter.\nExamples: (1) get 1 (get 1st element) (2) l (list elements) "
        "(3) set 2 (set 2nd element)";

    const string separator = "---------------------------------------------------";

    /* initialize input variable*/
    Input* input = new Input;

    cout << about << "\n\n";
    cout << separator << endl;
    cout << info << "\n\n";

    // process input from argv
    if (argc > 2) {
        input->setCMD();
        input->add(argv[2]);

        if (argc > 3) {
            input->add(argv[3]);
        }
        
        if (argc > 4) {
            cout << "Too many arguments" << endl;
            input->clear_input();
        }
    }

    // main control loop
    while (1) {
        cout << separator << endl;
        
        // FIXME what if input is valid?
        // in case of argv input
        if (input->isCMD()) {
            input->unsetCMD();
            if (!input->isValid()) {
                input->clear_input();
                continue;
            }
        // else get input from user
        } else {
            input->clear_input();
            input->get_input();
            if (!input->isValid()) {
                input->clear_input();
                continue;
            }
        }

        switch (input->getAction()) {
            case 'a': {
                perform_action(table, cars);
                break;
            }
            case 'r': {
                race(table, cars);
                break;
            }
            case 'g':; { // An empty statement before a label
                bool id_set = false;

                for (size_t i = 0; i < cars.size(); i++) {
                    if (cars[i]->getID() == input->getID()) {
                        vector<Car*> car = {cars[i]};
                        list_data(table, car);
                        id_set = true;
                        break;
                    }
                }
                if (!id_set) {
                    cout << "ID is not set" << endl;
                }
                break;
            }
            case 's':; { // An empty statement before a label
                int id = input->getID();
				int index = -1;

                for (size_t i = 0; i < cars.size(); i++) {
                    if (cars[i]->getID() == id) {
                        cout << "Such entry already exists:" << endl;
                        vector<Car*> car = {cars[i]};
                        list_data(table, car);
                        index = i;
                    }
                }

                if (index < 0 || (index >= 0 && Helpers::choice("Would you like to change it?"))) {
                    cout << "What type of car would you like to enter? (enter a number)" << endl
                         << "(1) Stock car" << endl
                         << "(2) Race car" << endl
                         << "(3) SUV car" << endl;

                     int car_choice;

                    while(1) {
                        cout << "(Enter a number) > ";
                        cin >> car_choice;

                        if (car_choice < 1 || car_choice > 3) {
                            cout << "Such option does not exist" << endl;
                            continue;
                        }
                        break;
                    }
                    cout << "Please enter the details about the car:" << endl;

                    // TODO remove code repetition
                    switch(car_choice) {
                        case 1: {
                            StockCar* car = new StockCar;

                            car->getCar(id);

                            if (Helpers::choice("Would you like to save?")) {
                                if (index >= 0) {
                                    cars[index] = car;
                                } else {
                                    cars.push_back(car);
                                }
                                conn_stock_cars->write_to_file_stock_cars(cars);
                                cout << "Successfully saved, ID = " << id << endl;
                            }

                            break;
                        }
                        case 2: {
                            RaceCar* car = new RaceCar;

                            car->getCar(id);

                            if (Helpers::choice("Would you like to save?")) {
                                if (index >= 0) {
                                    cars[index] = car;
                                } else {
                                    cars.push_back(car);
                                }
                                conn_race_cars->write_to_file_race_cars(cars);
                                cout << "Successfully saved, ID = " << id << endl;
                            }

                            break;
                        }
                        case 3: {
                            SUVCar* car = new SUVCar;

                            car->getCar(id);

                            if (Helpers::choice("Would you like to save?")) {
                                if (index >= 0) {
                                    cars[index] = car;
                                } else {
                                    cars.push_back(car);
                                }
                                conn_suv_cars->write_to_file_suv_cars(cars);
                                cout << "Successfully saved, ID = " << id << endl;
                            }

                            break;
                        }
                    }

               }
                break;
            }
            case 'd': {
                bool id_set = false;
                for (size_t i = 0; i < cars.size(); i++) {
                    if (cars[i]->getID() == input->getID()) {
                        if (Helpers::choice("Do you really want to delete this entry?")) {
                            StockCar *stockCar = dynamic_cast<StockCar*>(cars[i]);
                            if (stockCar != nullptr) {
                                cars.erase(cars.begin()+i);
                                conn_stock_cars->write_to_file_stock_cars(cars);
                            } else {
                                RaceCar *raceCar = dynamic_cast<RaceCar*>(cars[i]);
                                if (raceCar != nullptr) {
                                    cars.erase(cars.begin()+i);
                                    conn_race_cars->write_to_file_race_cars(cars);
                                } else {
                                    SUVCar *suvCar = dynamic_cast<SUVCar*>(cars[i]);
                                    if (suvCar != nullptr) {
                                        cars.erase(cars.begin()+i);
                                        conn_suv_cars->write_to_file_suv_cars(cars);
                                    } else {
                                        cout << "ERROR: Car is not of the right class" << endl;
                                        break;
                                    }
                                }
                            }
                            id_set = true;
                            break;
                        }
                    }
                }
                if (!id_set) {
                    cout << "There is no such entry with this ID" << endl;
                }
                break;
            }
            case 'l': {
                list_data(table, cars);
                break;
            }
            case 'c': {
                if (!cars.size()) {
                    cout << "Database has no entries. Nothing to clear." << endl;
                    break;
                }
                if (Helpers::choice("Do you really want to clear the entire database?")) {
                    cars.clear();
                } else {
                    break;
                }
                // empty the files
                conn_stock_cars->write_to_file_stock_cars(cars);
                conn_race_cars->write_to_file_race_cars(cars);
                conn_suv_cars->write_to_file_suv_cars(cars);
                break;
            }
            case 'i': {
                cout << separator << endl;
                cout << info << "\n\n";
                break;
            } 
            case 'q': {
                delete input;
                delete conn_stock_cars;
                delete conn_race_cars;
                delete conn_suv_cars;
                return 0;
            }
            default: {
                cout << "Invalid action, only: g=get, s=set, d=delete, l=list, q=quit, i=info" << endl;
            }
        }

    }
}




void list_data(Table &table, vector<Car*> &cars, bool sortedByID /*=true*/, bool filtered /*= false*/) {

    if (sortedByID) {
        Sorting sorting;
        sorting.setField(SortingConstants::ID);
        sorting.setType(SortingConstants::ASCENDING);
        sorting.sort(cars);
    }

    table.print_heading();

    if (cars.size() == 0) {
        cout << "No entries." << endl;
        return;
    }

    if (!filtered) {
        for (size_t i = 0; i < cars.size(); i++) {
            table.printEntry({
                    to_string(cars[i]->getID()),
                    cars[i]->getCarMake(),
                    cars[i]->getCarModel(),
                    to_string(cars[i]->getCarYear()),
                    to_string(cars[i]->getCarPrice()),
                    to_string(cars[i]->getMaxSpeed())
                    });
        }
    } else {
        for (size_t i = 0; i < cars.size(); i++) {
            if (cars[i]->getFilter()) {
                table.printEntry({
                        to_string(cars[i]->getID()),
                        cars[i]->getCarMake(),
                        cars[i]->getCarModel(),
                        to_string(cars[i]->getCarYear()),
                        to_string(cars[i]->getCarPrice()),
                        to_string(cars[i]->getMaxSpeed())
                        });
            }
        }
    }
}



void perform_action(Table &table, vector<Car*> &cars) {

    cout << "What action would you like to perform? (enter a number)" << endl 
         << "(1) Filter" << endl
         << "(2) Sort" << endl
         << "(3) Duplicate" << endl;

    int action;

    while(1) {
        cout << "(Enter a number) > ";
        cin >> action;

        if (action < 1 || action > 3) {
            cout << "Such option does not exist" << endl;
            continue;
        }
        break;
    }

    int field; 
    int type;

    switch(action) {
        case 1: {
            Filter filter;

            cout << "By which field would you like to filter? (enter a number)" << endl
                 << "(1) Make" << endl
                 << "(2) Model" << endl
                 << "(3) Year" << endl
                 << "(4) Price" << endl
                 << "(5) Max Speed" << endl;

            while(1) {
                cout << "(Enter a number) > ";
                cin >> field;

                try {
                    filter.setField(field);
                } catch (const std::invalid_argument& e) {
                    cout << e.what() << endl;
                    continue;
                }
                cin.get();
                break;
            }

            cout << "How would you like to filter?" << endl
                 << "(1) Entry is equal to the given value" << endl
                 << "(2) Entry contains the given value" << endl
                 << "(3) Entry is not equal to the given value" << endl
                 << "(4) Entry does not contain the given value" << endl;

            while(1) {
                cout << "(Enter a number) > ";
                cin >> type;

                try {
                    filter.setType(type);
                } catch (const std::invalid_argument& e) {
                    cout << e.what() << endl;
                    continue;
                }
                cin.get();
                break;
            }

            cout << "Please enter a value to be filtered by" << endl;

            string value;
            cout << "(Enter a value) > ";
            cin >> value;
            cin.get();

            filter.setValue(value);
            
            filter.filter(cars);

            list_data(table, cars, true, true);
            filter.reset_filter(cars);
            break;
        }

        case 2: {
            Sorting sorting;

            cout << "By which field would you like to sort? (enter a number)" << endl
                 << "(1) Make" << endl
                 << "(2) Model" << endl
                 << "(3) Year" << endl
                 << "(4) Price" << endl
                 << "(5) Max speed" << endl
                 << "(6) Race time" << endl
                 << "(7) ID" << endl;

            while(1) {
                cout << "(Enter a number) > ";
                cin >> field;

                try {
                    sorting.setField(field);
                } catch (const std::invalid_argument& e) {
                    cout << e.what() << endl;
                    continue;
                }
                cin.get();
                break;
            }

            cout << "How would you like to sort?" << endl
                 << "(1) Ascending order" << endl
                 << "(2) Descending order" << endl;

            while(1) {
                cout << "(Enter a number) > ";
                cin >> type;

                try {
                    sorting.setType(type);
                } catch (const std::invalid_argument& e) {
                    cout << e.what() << endl;
                    continue;
                }
                cin.get();
                break;
            }

            sorting.sort(cars);
            list_data(table, cars, false);
            break;
        }

        case 3: {
            cout << "Select the ID of the entry you would like to duplicate:" << endl;

            const int size = cars.size();

            // FIXME VLA
            int ids[size];
            //int ids[cars.size()];

            for (size_t i = 0; i < cars.size(); i++) {
                cout << "(" << cars[i]->getID() << ")" << endl;
                ids[i] = cars[i]->getID();
            }

            int id;
            bool exists;

            while(1) {
                cout << "(Enter a number) > ";
                cin >> id;

                for (size_t i = 0; i < size; i++) {
                    if (ids[i] == id) {
                        exists = true;
                    }
                }

                if (!exists) {
                    cout << "Such id does not exist" << endl;
                    continue;
                }
                break;
            }

            int new_id;

            cout << "Select the new ID of the duplicated entry:" << endl;

            while(1) {
                cout << "(Enter a number) > ";
                cin >> new_id;

                exists = false;
                for (size_t i = 0; i < size; i++) {
                    if (ids[i] == new_id) {
                        exists = true;
                    }
                }

                if (exists) {
                    cout << "Such id already exists" << endl;
                    continue;
                }
                break;
            }

            StockCar *stockCar = dynamic_cast<StockCar*>(cars[id]);
            if (stockCar != nullptr) {
                StockCar *newStockCar = new StockCar(*stockCar);
                //StockCar newStockCar = *stockCar;
                newStockCar->setID(new_id);
                cars.push_back(newStockCar);
            }
        }
    }
}


void race(Table &table, vector<Car*> &cars) {

    size_t type;
    string raceType;
    float distance;

    cout << "What kind of race would you like to perform? (enter a number)" << endl 
         << "(1) Drag race" << endl
         << "(2) Racetrack" << endl
         << "(3) Offroad" << endl;

    while(1) {
        cout << "(Enter a number) > ";
        cin >> type;

        if (type < 1 || type > 3) {
            cout << "Such option does not exist" << endl;
            continue;
        }
        break;
    }

    switch(type) {
        case 1:
            raceType = "drag";
            break;
        case 2:
            raceType = "track";
            break;
        case 3:
            raceType = "offroad";
            break;
    }

    cout << "What is the distance of the race? (in meters)" << endl;

    while(1) {
        cout << "(Enter a number) > ";
        cin >> distance;

        if (distance <= 0 || distance > 1000000) {
            cout << "Chosen distance is invalid." << endl;
            continue;
        }
        break;
    }

    cout << endl << "The " << distance << "m race begins" << endl << endl;

    static Race raceObject;
    raceObject.setRaceDistance(distance);

    cout << "The results of the race:" << endl;

    for (size_t i = 0; i < cars.size(); i++) {

        cars[i]->setConstant1(cars[i]->getNotToSixtyForRace(raceType));
        // converting km/h to m/s (dividing speed by 3.6) 
        cars[i]->setConstant2(cars[i]->getSixtyToMaxSpeedForRace(raceType), cars[i]->getMaxSpeedForRace(raceType) / 3.6);

        raceObject.setConstant1(cars[i]->getConstant1());
        raceObject.setConstant2(cars[i]->getConstant2());
        
        raceObject.setNotToSixty(cars[i]->getNotToSixtyForRace(raceType));
        raceObject.setSixtyToMaxSpeed(cars[i]->getSixtyToMaxSpeedForRace(raceType));
        raceObject.setMaxSpeed(cars[i]->getMaxSpeedForRace(raceType));

        raceObject.setDistance(0);

        cars[i]->setRaceTime(raceObject.race(100, 400, 3600));

        cout.precision(7);
        cout << setw(5) << "ID: " << cars[i]->getID();
        cout << setw(10) << "Make: " << cars[i]->getCarMake();
        cout << setw(20) << "Race time: " << cars[i]->getRaceTime() << " s" << endl;

    }

    Sorting sorting;
    sorting.setField(SortingConstants::RACETIME);
    sorting.setType(SortingConstants::ASCENDING);
    sorting.sort(cars);
    cout << endl << "The results table:" << endl;
    list_data(table, cars, false);
    cin.get();
}

void exiting() {
    finish = clock();

    clocks = (double)(finish - start);
    time_spent = clocks / CLOCKS_PER_SEC;
    logfile << "Time spent: " << time_spent << " seconds" << endl
            << string(20, '-') << endl;
    logfile.close();
    cout << "Goodbye!" << endl;
}


