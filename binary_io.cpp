//
// Created by egor9814 on 11.03.18.
//

#include "binary_io.hpp"

BinaryOutput::BinaryOutput(std::ofstream &out)
        : output(out), buffer(0), buffer_len(0) {}

void BinaryOutput::flush() {
    buffer <<= (8 - buffer_len);
    output << (char) (buffer & 0xff);
    buffer_len = buffer = 0;
}

void BinaryOutput::close() {
    if (buffer_len != 0)
        flush();
    output.close();
}

void BinaryOutput::write(bool v) {
    check();
    buffer <<= 1;
    if (v)
        buffer++;
    buffer_len++;
}

void BinaryOutput::write(char v) {
    for (auto mask = static_cast<char>(1 << 7); mask; mask >>= 1) {
        write((v & mask) != 0);
    }
}

void BinaryOutput::check() {
    if (buffer_len == 8) {
        flush();
    }
}



BinaryInput::BinaryInput(std::ifstream &in)
        : input(in), buffer(0), buffer_len(0) {}

bool BinaryInput::eof() {
    return input.eof();
}

void BinaryInput::close() {
    input.close();
}

bool BinaryInput::readBool() {
    check();
    buffer_len--;
    return ((buffer >> buffer_len) & 0x1) != 0;
}

char BinaryInput::readChar() {
    char res = 0;
    for(int i = 0; i < 8; i++) {
        res <<= 1;
        if(readBool())
            res++;
    }
    return res;
}

void BinaryInput::check() {
    if(buffer_len == 0){
        char c;
        input >> c;
        buffer_len = 8;
        buffer = c;
    }
}