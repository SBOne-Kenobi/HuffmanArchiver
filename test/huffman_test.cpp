#include "huffman_test.h"
#include "archiver.h"
#include <fstream>
#include <huffman.h>

bool HuffmanTest::encode_decode(const std::string &fname) {
    std::ifstream in1(fname, std::ifstream::binary);
    std::ofstream out1("out.bin", std::ofstream::binary);
    HuffmanArchiver::encode(in1, out1);
    in1.close();
    out1.close();
    std::ifstream in2("out.bin", std::ifstream::binary);
    std::ofstream out2("out.txt", std::ofstream::binary);
    HuffmanArchiver::decode(in2, out2);
    in2.close();
    out2.close();
    bool result = equal_files(fname, "out.txt");
    remove("out.bin");
    remove("out.txt");
    return result;
}

bool HuffmanTest::equal_files(const std::string &file1, const std::string &file2) {
    std::ifstream in1(file1);
    std::ifstream in2(file2);
    while (1) {
        unsigned char a, b;
        if (!in1.read((char *) &a, sizeof(unsigned char))) {
            if (!in2.read((char *) &b, sizeof(unsigned char)))
                return 1;
            else
                return 0;
        } else {
            if (!in2.read((char *) &b, sizeof(unsigned char)))
                return 0;
        }
        if (a != b)
            return 0;
    }
    return 1;
}

void HuffmanTest::check_encode_empty_file() {
    std::ifstream file("empty.txt");
    file.close();
    DO_CHECK(encode_decode("empty.txt"));
    remove("empty.txt");
}

void HuffmanTest::check_encode_large_file() {
    std::ofstream file("large.txt");
    for (size_t i = 0; i < 5000000; i++) {
        file << (unsigned char)(rand() % CHAR_MAX);
    }
    file.close();
    DO_CHECK(encode_decode("large.txt"));
    remove("large.txt");
}

void HuffmanTest::check_encode_one_symbol() {
    std::ofstream file("one_symb.txt");
    file << (unsigned char)(rand() % CHAR_MAX);
    file.close();
    DO_CHECK(encode_decode("one_symb.txt"));
    remove("one_symb.txt");
}

void HuffmanTest::check_encode_equal_symbols() {
    std::ofstream file("eq_symbs.txt");
    unsigned char c = (unsigned char)(rand() % CHAR_MAX);
    for (size_t i = 0; i < (size_t)rand(); i++) {
        file << c;
    }
    file.close();
    DO_CHECK(encode_decode("eq_symbs.txt"));
    remove("eq_symbs.txt");
}

void HuffmanTest::check_encode_space_symbs() {
    std::ofstream file("space.txt");
    for (size_t i = 0; i < (size_t)rand(); i++) {
        file << (unsigned char)' ';
    }
    file.close();
    DO_CHECK(encode_decode("space.txt"));
    remove("space.txt");
}

void HuffmanTest::check_exceptions_decode() {
    std::ofstream file("exception.bin");
    for (size_t i = 0; i < (size_t)(rand() % (CHAR_MAX - 1)); i++) {
        file << (int32_t)rand();
    }
    file.close();
    std::ifstream in("exception.bin");
    std::ofstream out("out.txt");
    bool except = false;
    try {
        HuffmanArchiver::decode(in, out);
    }
    catch (HuffmanArchiver::HuffmanException &e) {
        except = true;
    }
    catch (...) {
        throw;
    }
    in.close();
    out.close();
    remove("exception.bin");
    remove("out.txt");
    DO_CHECK(except);
}

void HuffmanTest::checkAll() {
    try {
        check_encode_empty_file();
        check_encode_large_file();
        for (size_t i = 0; i < 4; i++)
            check_encode_one_symbol();
        for (size_t i = 0; i < 4; i++)
            check_encode_equal_symbols();
        check_encode_space_symbs();
        for (size_t i = 0; i < 4; i++)
            check_exceptions_decode();
    }
    catch (HuffmanArchiver::HuffmanException &e) {
        std::cout << e.what() << "\n";
        HuffmanTest::totalNum++;
        HuffmanTest::failedNum++;
    }
    catch (...) {
        std::cout << "Unknown error.\n";
        HuffmanTest::totalNum++;
        HuffmanTest::failedNum++;
    }
}
