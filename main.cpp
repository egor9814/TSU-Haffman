//
// Created by egor9814 on 10.03.18.
//

#include <iostream>
#include "haffman.hpp"

int haff(int argc, const char **argv) {
    using namespace std;
    if (argc < 3) {
        cerr << "using: haff <type> <input file> [<output file>]" << endl;
        cerr << "\t<type>:" << endl << "\t\td - decode" << endl << "\t\te - encode" << endl;
        cerr << "\t<input file> - path to input file" << endl;
        cerr << "\t<output file> - path to output file (optional: by default '<input file>.out'" << endl;
        return -1;
    } else {
        string type = argv[1];
        if (type != "e" || type != "d") {
            cerr << "invalid type: " << type << endl;
            return -2;
        }
        string input = argv[2];
        string output = argc > 3 ? argv[3] : (input + ".out");

        ifstream in(input);
        in.unsetf(ios::skipws);
        if (!in.is_open()) {
            cerr << "cannot open input file" << endl;
            return -3;
        }
        ofstream out(output);
        if (!out.is_open()) {
            cerr << "cannot open output file" << endl;
            return -3;
        }

        return haffman(type[0], in, out);
    }
}


int main(int argc, char *argv[]) {
    const char *encode[3]{
            "e",
            "e.test.txt",
            "e.test.out.txt"
    };
    const char *decode[3]{
            "d",
            "d.test.txt",
            "d.test.out.txt"
    };
    return haff(3, encode);
}