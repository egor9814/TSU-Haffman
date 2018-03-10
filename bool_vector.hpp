//
// Created by egor9814 on 10.03.18.
//

#ifndef TSU_HAFFMAN_BOOL_VECTOR_HPP
#define TSU_HAFFMAN_BOOL_VECTOR_HPP

class BoolVector {
public:
    typedef unsigned char byte;

private:
    unsigned long bytes;
    byte *vector;

public:
    BoolVector();

    BoolVector(char);

    BoolVector(const BoolVector &);

    ~BoolVector();

    BoolVector &operator=(const BoolVector &);

    void append(char);

    void append(BoolVector &);

    char &operator[](unsigned long i);

    unsigned long count() const;

    bool has(char);
};


#endif //TSU_HAFFMAN_BOOL_VECTOR_HPP
