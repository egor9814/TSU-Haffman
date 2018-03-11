//
// Created by egor9814 on 10.03.18.
//

#include "bool_vector.hpp"

BoolVector::BoolVector()
        : bytes(0), vector(nullptr) {}

BoolVector::BoolVector(char c)
        : bytes(1), vector(new byte[1]) {
    vector[0] = static_cast<byte>(c);
}

BoolVector::BoolVector(const BoolVector &bv)
        : bytes(bv.bytes) {
    vector = new byte[bytes];
    for (auto i = 0UL; i < bytes; i++) {
        vector[i] = bv.vector[i];
    }
}

BoolVector::~BoolVector() {
    delete[] vector;
}

BoolVector &BoolVector::operator=(const BoolVector &bv) {
    if (this != &bv) {
        delete[] vector;
        bytes = bv.bytes;
        vector = new byte[bytes];
        for (auto i = 0UL; i < bytes; i++) {
            vector[i] = bv.vector[i];
        }
    }
    return *this;
}


void BoolVector::append(char c) {
    if (has(c))
        return;
    auto v = new byte[bytes + 1];
    for (auto i = 0UL; i < bytes; i++) {
        v[i] = vector[i];
    }
    v[bytes] = static_cast<byte>(c);
    bytes++;
    delete[] vector;
    vector = v;
}

void BoolVector::append(BoolVector &bv) {
    /*auto v = new byte[bytes + bv.bytes];
    for (auto i = 0UL; i < bytes; i++) {
        v[i] = vector[i];
    }
    for (auto i = 0UL; i < bv.bytes; i++) {
        v[i + bytes] = bv.vector[i];
    }
    bytes += bv.bytes;
    delete[] vector;
    vector = v;*/
    for (auto i = 0UL; i < bv.count(); i++) {
        append(bv[i]);
    }
}

char &BoolVector::operator[](unsigned long i) {
    return reinterpret_cast<char &>(vector[bytes - i - 1]);
}

unsigned long BoolVector::count() const {
    return bytes;
}

bool BoolVector::has(char c) {
    for (auto i = 0UL; i < bytes; i++) {
        if (vector[i] == static_cast<byte>(c))
            return true;
    }
    return false;
}
