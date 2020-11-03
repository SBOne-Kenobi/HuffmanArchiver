#ifndef HUFFMAN_TEST_H
#define HUFFMAN_TEST_H

#include "auto_test.h"
#include <string>

class HuffmanTest : public Test {
private:
    static bool encode_decode(const std::string &fname);
    static bool equal_files(const std::string &file1, const std::string &file2);

    void check_encode_empty_file();
    void check_encode_large_file();
    void check_encode_one_symbol();
    void check_encode_equal_symbols();
    void check_encode_space_symbs();
    void check_exceptions_decode();

public:
    HuffmanTest() = default;
    virtual void checkAll() override;
};

#endif //HUFFMAN_TEST_H