#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <map>
#include <memory>
#include <climits>
#include <cstdint>
#include <istream>
#include "binary.h"
#include <ostream>
#include <vector>

namespace HuffmanArchiver {

    const std::size_t CHAR_CNT = UCHAR_MAX + 1;

    class HuffmanTree {
    protected:
        class Node {
        private:
            uint32_t _weight;
            unsigned char _val;
            mutable std::unique_ptr<Node> _left;
            mutable std::unique_ptr<Node> _right;

        public:

            explicit Node(uint32_t weight, unsigned char val);

            Node(std::unique_ptr<Node> l, std::unique_ptr<Node> r);

            Node(const Node &other);

            Node &operator=(const Node &other);

            bool isLeaf() const;

            uint32_t getWeight() const;

            unsigned char getVal() const;

            const std::unique_ptr<Node> &getLeft() const;

            const std::unique_ptr<Node> &getRight() const;

        };

        std::unique_ptr<Node> _root;
        const std::vector<uint32_t> &cnt;

        std::map<unsigned char, std::vector<bool>> _code;

        void getCodes(const std::unique_ptr<Node> &v);

        std::size_t initSize;
        std::size_t newSize;
        std::size_t addSize = CHAR_CNT * sizeof(uint32_t) * CHAR_BIT;

    public:
        explicit HuffmanTree(const std::vector<uint32_t> &cnt);

        HuffmanTree(const HuffmanTree &) = delete;

        void operator=(const HuffmanTree &) = delete;

        void encode(std::istream &is, std::ostream &os) const;

        void decode(std::istream &is, std::ostream &os);

        std::size_t getInitSize() const;

        std::size_t getNewSize() const;

        std::size_t getAddSize() const;
    };

    class HuffmanException : public std::logic_error {
    public:
        HuffmanException(const std::string &msg);
    };

}


#endif //HUFFMAN_H