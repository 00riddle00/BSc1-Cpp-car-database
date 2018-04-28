#ifndef __WRITE_TO_BINARY_FILE_H_
#define __WRITE_TO_BINARY_FILE_H_

class WriteToBinaryFile {
    std::ofstream otf;
    const std::string filename;

    public:
        explicit WriteToBinaryFile(const std::string&);
        ~WriteToBinaryFile();

       void write(const std::string&, int);

       void write(float);

       void write(int);

       void close();
};

#endif
