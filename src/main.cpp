#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include "archiver.h"
#include "huffman.h"

int main(int argc, char **argv) {

    try {
        if (argc == 6) {
            bool encode = false;
            bool decode = false;
            std::string file;
            std::string output;

            for (int i = 1; i < argc; i++) {
                if (strcmp("-c", argv[i]) == 0)
                    encode = true;
                else if (strcmp("-u", argv[i]) == 0)
                    decode = true;
                else if (strcmp("-f", argv[i]) == 0 || strcmp("--file", argv[i]) == 0) {
                    if (++i < argc && file.empty())
                        file = argv[i];
                    else
                        throw HuffmanArchiver::HuffmanException("ERROR: invalid parameters format.");
                } else if (strcmp("-o", argv[i]) == 0 || strcmp("--output", argv[i]) == 0) {
                    if (++i < argc && output.empty())
                        output = argv[i];
                    else
                        throw HuffmanArchiver::HuffmanException("ERROR: invalid parameters format.");
                }
            }

            if (encode == decode)
                throw HuffmanArchiver::HuffmanException("ERROR: invalid parameters format.");

            std::ifstream in(file, std::ifstream::binary);
            std::ofstream out(output, std::ofstream::binary);
            if (!in.is_open() || !out.is_open())
                throw HuffmanArchiver::HuffmanException("ERROR: unable to open the file.");

            try {
                if (encode) {
                    HuffmanArchiver::encode(in, out);
                } else {
                    HuffmanArchiver::decode(in, out);
                }
            } catch (...) {
                in.close();
                out.close();
                throw;
            }
        } else
            throw HuffmanArchiver::HuffmanException("ERROR: invalid parameters format.");

    } catch (const HuffmanArchiver::HuffmanException &e) {
        std::cout << e.what() << "\n";
    } catch (...) {
        std::cout << "Unknown error.\n";
    }

    return 0;
}