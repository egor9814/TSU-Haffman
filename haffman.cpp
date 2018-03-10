//
// Created by egor9814 on 10.03.18.
//

#include "haffman.hpp"
#include "bool_vector.hpp"
#include "list"

struct FrequencyNode {
    BoolVector chars;
    unsigned long frequency;
    FrequencyNode *left, *right;

    explicit FrequencyNode(char &c)
            : chars(c), frequency(1), left(nullptr), right(nullptr) {}

    explicit FrequencyNode()
            : chars(), frequency(1), left(nullptr), right(nullptr) {}

    FrequencyNode(FrequencyNode &a, FrequencyNode &b)
            : chars(a.chars), frequency(a.frequency), left(&a), right(&b) {
        chars.append(b.chars);
        frequency += b.frequency;
    }

    bool operator<(FrequencyNode &fn) {
        return frequency < fn.frequency;
    }

    bool operator<=(FrequencyNode &fn) {
        return frequency <= fn.frequency;
    }

    bool operator>(FrequencyNode &fn) {
        return frequency > fn.frequency;
    }

    bool operator>=(FrequencyNode &fn) {
        return frequency >= fn.frequency;
    }

    bool operator==(FrequencyNode &fn) {
        return frequency == fn.frequency;
    }

    bool operator!=(FrequencyNode &fn) {
        return frequency != fn.frequency;
    }
};

void findNode(std::list<FrequencyNode> &list, char &c) {
    for (auto &i : list) {
        if (i.chars.has(c)) {
            i.frequency++;
            return;
        }
    }
    list.emplace_back(c);
}

std::list<FrequencyNode> frequencyList(std::ifstream in) {
    std::list<FrequencyNode> l;
    char c;
    in >> c;
    while (!in.eof()) {
        findNode(l, c);
        in >> c;
    }
    l.sort();
    return l;
}

FrequencyNode &buildTree(std::list<FrequencyNode> l) {
    while (l.size() != 1) {
        auto &a = l.front();
        l.pop_front();
        auto &b = l.front();
        l.pop_front();

        FrequencyNode node(a, b);
        for (auto it = l.begin(); it != l.end(); it++) {
            if (node >= *it) {
                it--;
                l.insert(it, node);
                break;
            }
        }
    }
    return l.front();
}


void push(unsigned char &vector, char &currentVectorLen,
          std::ofstream &out) {
    vector <<= (8 - currentVectorLen);
    out.write(reinterpret_cast<const char *>(&vector), 1);
    currentVectorLen = 0;
    vector = 0;
}

void writeChar(FrequencyNode &tree, char &c, unsigned char &vector, char &currentVectorLen,
               std::ofstream &out) {
    if (currentVectorLen == 8) {
        push(vector, currentVectorLen, out);
    }
    if (tree.left && tree.left->chars.has(c)) {
        vector = (vector << 1);
        currentVectorLen++;
        writeChar(*tree.left, c, vector, currentVectorLen, out);
    } else if (tree.right && tree.right->chars.has(c)) {
        vector = (vector << 1) | 1UC;
        currentVectorLen++;
        writeChar(*tree.right, c, vector, currentVectorLen, out);
    }
}


int encode(std::ifstream &in, std::ofstream &out) {
    auto freq = frequencyList(in);
    in.clear();
    in.seekg(0, std::ios::beg);

    auto tree = buildTree(freq);

    //TODO: implement frequency table write

    char len = 0;
    unsigned char vector = 0;

    char c;
    in >> c;
    while (!in.eof()) {
        if (len == 8)
            push(vector, len, out);
        vector = (vector << 1) | 1UC;
        len++;
        writeChar(tree, c, vector, len, out);
        in >> c;
    }
}

int decode(std::ifstream &in, std::ofstream &out);


int haffman(char &type, std::ifstream &in, std::ofstream &out) {
    return type == 'e' ? encode(in, out) : decode(in, out);
}
