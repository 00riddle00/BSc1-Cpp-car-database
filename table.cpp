#include <iostream>
#include <iomanip>
#include <vector>

#include "table.h"

using namespace std;

Table::Table(vector<string> params, vector<size_t> column_widths) : params(params) {
    setColumnWidths(column_widths);
}

void Table::setColumnWidths(vector<size_t> column_widths) {
    if (!this->params.size()) {
        throw std::invalid_argument("TABLE ERROR: The parameters are not set, hence the width values cannot be set");
    }

    if (column_widths.size() != this->params.size()) {
        throw std::invalid_argument("TABLE ERROR: Please make sure that the number of width values correspond to the number of parameters");
    }

    for (size_t i = 0; i < params.size(); i++) {
        if (params[i].length() > column_widths[i]) {
            string error = "TABLE ERROR: parameter's \"" + params[i] + "\" length(" + to_string(params[i].length()) + ") is bigger than its column width(" + to_string(column_widths[i]) + ")!";
            throw std::invalid_argument(error);
        }
    }

    this->column_widths = column_widths;
}


void Table::print_heading() const {
    int count = this->params.size();
    int length = 0;

    for (auto& n : this->column_widths)
        length += n;

    length += count + 1;

    cout << string(length, '_') << endl;
    cout << "|";

    for (int i = 0; i < count; i++) {

        int diff = this->column_widths[i] - this->params[i].length(); 
        int odd = diff % 2;
        int left_space = (diff / 2);
        int right_space = (diff / 2 + odd);

        //cout << "LS " << left_space << endl;
        //cout << "RS " << right_space << endl;;
        if (!left_space && !right_space) {
            cout << this->params[i] << "|";
        } else {
            cout << setw(left_space) << " " << this->params[i] << setw(right_space) << " " << "|";
        }
        //cout << setw(0) << " " << this->params[i] << setw(0) << " " << "|";
    }
    cout << endl;

    cout << "|";

    for (int i = 0; i < count; i++) {
        cout << string(this->column_widths[i], '_') << "|";
    }
    cout << endl;
}


void Table::printEntry(vector<string> args) const {
    int count = this->params.size();

    cout << "|";

    for (int i = 0; i < count; i++) {

        if (args[i].length() > this->column_widths[i]) {
            string error = "TABLE ERROR: argument's \"" + args[i] + "\" length(" + to_string(args[i].length()) + ") is bigger than its column width(" + to_string(this->column_widths[i]) + ")!";
            throw std::invalid_argument(error);
        }
        cout << setw(this->column_widths[i]) << args[i] << "|";
    }
    cout << endl;

    cout << "|";

    for (int i = 0; i < count; i++) {
        cout << string(this->column_widths[i], '_') << "|";
    }
    cout << endl;

}


