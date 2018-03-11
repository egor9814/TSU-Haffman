//
// Created by egor9814 on 10.03.18.
//

#include <algorithm>
#include <vector>
#include <iostream>
#include "haffman.hpp"
#include "bool_vector.hpp"
#include "list"
#include "binary_io.hpp"

struct FrequencyNode {
    BoolVector chars;
    unsigned long frequency;
    FrequencyNode *left, *right;

    explicit FrequencyNode(char &c)
            : chars(c), frequency(1), left(nullptr), right(nullptr) {}

    explicit FrequencyNode()
            : chars(), frequency(1), left(nullptr), right(nullptr) {}

    FrequencyNode(FrequencyNode *a, FrequencyNode *b)
            : chars(a->chars), frequency(a->frequency), left(a), right(b) {
        chars.append(b->chars);
        frequency += b->frequency;
    }

    /*FrequencyNode(const FrequencyNode& fn)
            : chars(fn.chars), frequency(fn.frequency), left(fn.left), right(fn.right) {}*/

    FrequencyNode(const FrequencyNode &) = delete;

    bool isLeaf() const {
        return !left && !right;
    }

    bool operator<(const FrequencyNode &fn) const {
        return frequency < fn.frequency;
    }

    bool operator<=(const FrequencyNode &fn) const {
        return frequency <= fn.frequency;
    }

    bool operator>(const FrequencyNode &fn) const {
        return frequency > fn.frequency;
    }

    bool operator>=(const FrequencyNode &fn) const {
        return frequency >= fn.frequency;
    }

    bool operator==(const FrequencyNode &fn) const {
        return frequency == fn.frequency;
    }

    bool operator!=(const FrequencyNode &fn) const {
        return frequency != fn.frequency;
    }
};


/// Encoder

void findNode(std::vector<FrequencyNode *> &list, char &c) {
    for (auto &i : list) {
        if (i->chars.has(c)) {
            i->frequency++;
            return;
        }
    }
    list.push_back(new FrequencyNode(c));
}

struct FrequencyNodeComparator {
    bool operator()(const FrequencyNode *lhs, const FrequencyNode *rhs) {
        return *lhs < *rhs;
    }

    bool operator()(FrequencyNode *lhs, FrequencyNode *rhs) {
        return *lhs < *rhs;
    }
};

std::list<FrequencyNode *> frequencyList(std::ifstream &in) {
    std::vector<FrequencyNode *> l;
    char c;
    in >> c;
    while (!in.eof()) {
        findNode(l, c);
        in >> c;
    }
    std::sort(l.begin(), l.end(), FrequencyNodeComparator());
    std::list<FrequencyNode *> res;
    for (auto &i : l) {
        res.push_back(i);
    }
    return res;
}

FrequencyNode *buildTree(std::list<FrequencyNode *> &l) {
    FrequencyNodeComparator cmp;
    while (l.size() != 1) {
        auto a = l.front();
        l.pop_front();
        auto b = l.front();
        l.pop_front();

        auto node = new FrequencyNode(a, b);
        if (l.empty()) {
            l.push_back(node);
        } else {
            auto it = l.begin();
            auto end = l.end();
            while (it != end && cmp(*it, node))
                it++;
            it--;
            l.insert(it, node);
        }
    }
    return l.front();
}

void freeTree(FrequencyNode *tree) {
    if (tree) {
        freeTree(tree->left);
        freeTree(tree->right);
        delete tree;
    }
}


void writeChar(FrequencyNode &tree, char &c, BinaryOutput &out) {
    if (tree.left && tree.left->chars.has(c)) {
        out.write(false);
        writeChar(*tree.left, c, out);
        std::cout << '0';
    } else if (tree.right && tree.right->chars.has(c)) {
        out.write(true);
        writeChar(*tree.right, c, out);
        std::cout << '1';
    }
}


int getLength(FrequencyNode &tree, char c, int len = 1) {
    if (tree.isLeaf()) {
        return len;
    } else {
        if (tree.left && tree.left->chars.has(c)) {
            return getLength(*tree.left, c, len + 1);
        } else if (tree.right && tree.right->chars.has(c)) {
            return getLength(*tree.right, c, len + 1);
        } else {
            return 0;
        }
    }
}

void writeTree(FrequencyNode &node, BinaryOutput &out) {
    for (unsigned char c = '\0'; c < 256; c++) {
        int l = getLength(node, c);
        //std::cout << "debug: " << (int)c << "('" << (char)c << "'): " << l << std::endl;
        if (l != 0) {
            for (auto i = 0; i < l; i++) {
                out.write(true);
            }
        }
        out.write(false);
    }
}


int encode(std::ifstream &in, std::ofstream &out) {
    BinaryOutput bin_out(out);

    auto freq = frequencyList(in);
    in.clear();
    in.seekg(0, std::ios::beg);

    auto tree = buildTree(freq);

    writeTree(*tree, bin_out);

    char c;
    in >> c;
    while (!in.eof()) {
        bin_out.write(true);
        std::cout << "debug: next char " << (int) c << "('" << c << "'): 1";
        writeChar(*tree, c, bin_out);
        std::cout << std::endl;
        in >> c;
    }

    bin_out.close();
    freeTree(tree);

    return 0;
}



/// Decoder

FrequencyNode *recoverTree(BinaryInput &in) {
    int len[256]{0};
    for (int &i : len) {
        while (in.readBool())
            i++;
    }
    //TODO: implement recovering tree
    return nullptr;
}


int decode(std::ifstream &in, std::ofstream &out) {
    BinaryInput bin_in(in);
    //TODO: implement decoding
    return -1;
}


int huffman(char &type, std::ifstream &in, std::ofstream &out) {
    return type == 'e' ? encode(in, out) : decode(in, out);
}
