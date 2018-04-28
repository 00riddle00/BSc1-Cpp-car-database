#include <iostream>
#include <fstream>
#include <string>

#include "write_to_binary_file.h"

using namespace std;

WriteToBinaryFile::WriteToBinaryFile(const string& filename) : filename(filename) {
    otf.open(filename, ios::out | ios::binary);
}

WriteToBinaryFile::~WriteToBinaryFile() {
    if (otf.is_open()) {
        this->close();
    }
}

void WriteToBinaryFile::write(const string& line, int size) {
    otf.write(line.c_str(), size);
}

void WriteToBinaryFile::write(float number) {
    otf.write((char*)&number, sizeof(float));
}

void WriteToBinaryFile::write(int number) {
    otf.write((char*)&number, sizeof(int));
}

void WriteToBinaryFile::close() {
   otf.close();
}

