#ifndef __TABLE_H_
#define __TABLE_H_

class Table {
    const std::vector<std::string> params;
    std::vector<size_t> column_widths;

    public: 
        Table(std::vector<std::string> params, std::vector<size_t> column_widths);

        void setColumnWidths(std::vector<size_t>);

        // print the heading of the table
        void print_heading() const;

        void printEntry(std::vector<std::string> args) const;

}; 

#endif
