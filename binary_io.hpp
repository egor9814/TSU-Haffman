//
// Created by egor9814 on 11.03.18.
//

#ifndef TSU_HAFFMAN_BINARY_IO_HPP
#define TSU_HAFFMAN_BINARY_IO_HPP

#include <fstream>

class BinaryOutput {
    int buffer, buffer_len;
    std::ofstream &output;

    void check();

public:
    explicit BinaryOutput(std::ofstream &out);

    BinaryOutput(const BinaryOutput &) = delete;

    void flush();

    void close();

    void write(bool);

    void write(char);

};


class BinaryInput {
    int buffer, buffer_len;
    std::ifstream &input;

    void check();

public:
    explicit BinaryInput(std::ifstream &in);

    BinaryInput(const BinaryInput &) = delete;

    bool eof();

    void close();

    bool readBool();

    char readChar();

};

#endif //TSU_HAFFMAN_BINARY_IO_HPP
