#include <iostream>
#include <sstream>
#include "input.h"

using namespace std;

Input::Input() {
    this->count = 0;
    this->cmd = false;
}

Input::~Input() { }

void Input::add(const string& param) {
    if (this->count == MAX_PARAMS) {
        throw std::invalid_argument("Too many arguments");
    }

    this->params[this->count] = param;
    this->count++;

}

void Input::setCMD() {
    this->cmd = true;
}

void Input::unsetCMD() {
    this->cmd = false;
}

bool Input::isCMD() const {
    return this->cmd;
}

char Input::getAction() const {
    return this->params[0][0];
}

int Input::getID() const {
    return stoi(this->params[1]);
}

void Input::get_input() {

    string line;

    cout << "[enter \"i\" for info] main shell > ";

    getline(cin, line);

    string buf; // Have a buffer string
    stringstream ss(line); // Insert the string into a stream

    while (ss >> buf) {
        try {
            this->add(buf);
        } catch (const std::invalid_argument& e) {
            cout << e.what() << endl;
            break;
        }
    }
}

bool Input::isValid() const {

    // Validate argument count
   
    if (this->count == 0) {
        cout << "The input is empty." << endl;
        return false;
    }

    // Validate action
    
    string all_actions = "a,g,s,d,l,c,i,q,action,get,set,delete,list,clear,info,quit";
    
    if (all_actions.find(this->params[0]) == std::string::npos) {
        cout << "Such action does not exist" << endl;
        return false;
    }

    char action = this->params[0][0];

    if (this->count == 1) {
        string actions = "gsd";
        if (actions.find(action) != std::string::npos) {
            cout << "ID is not submitted" << endl;
            return false;
        }
    }

    // Validate id
    
    if (this->count > 1) {

        string one_args = "alicq";

        if (one_args.find(action) != std::string::npos) {
            cout << "Too much arguments for this action" << endl;
            return false;
        }

        int id = stoi(this->params[1]);

        // id being equal to 0 in condition
        // below also validates from char input
        if (id <= 0) {
            cout << "ID should be a positive integer." << endl;
            return false;
        }
    }

    return true;
}


void Input::clear_input() {
    for (int i = 0; i < MAX_PARAMS; ++i) {
        this->params[i] = "";
    }
    this->count = 0;
    this->cmd = false;
}

