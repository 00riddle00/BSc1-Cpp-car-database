#include <iostream>
#include <fstream>
#include <string>

#include "load_from_binary_file.h"
using namespace std;

LoadFromBinaryFile::LoadFromBinaryFile(const string& filename) : filename(filename) {
    itf.open(filename, ios::in | ios::binary);
}

LoadFromBinaryFile::~LoadFromBinaryFile() {
    if (itf.is_open()) {
        close();
    }
}

string LoadFromBinaryFile::readString(int len) {
    string my_string;
    char* temp = new char[len+1];
    itf.read(temp, len);
    temp[len] = '\0';
    my_string = temp;
    delete [] temp;
    return my_string;
}

int LoadFromBinaryFile::readInt() {
    int my_int;
    itf.read((char*)&my_int, sizeof(int));
    return my_int;
}

float LoadFromBinaryFile::readFloat() {
    float my_float;
    itf.read((char*)&my_float, sizeof(float));
    return my_float;
}

void LoadFromBinaryFile::close() {
    itf.close();
}
