#include "archiver.h"
#include "binary.h"
#include "huffman.h"

using HuffmanArchiver::binary;

namespace HuffmanArchiver {

    void encode(std::istream &in, std::ostream &out) {
        std::vector<uint32_t> cnt(CHAR_CNT, 0);
        unsigned char c;
        while (in >> binary<unsigned char>(c)) {
            cnt[c]++;
        }
        for (auto it : cnt) {
            out << binary<uint32_t>(it);
        }
        in.clear();
        in.seekg(0);
        HuffmanTree tree(cnt);
        tree.encode(in, out);

        std::cout << tree.getInitSize() << "\n" << tree.getNewSize() << "\n" << tree.getAddSize() << "\n";
    }

    void decode(std::istream &in, std::ostream &out) {
        std::vector<uint32_t> cnt(CHAR_CNT);
        for (std::size_t i = 0; i < CHAR_CNT; i++) {
            in >> binary<uint32_t>(cnt[i]);
            if (!in)
                throw HuffmanException("ERROR: invalid text format.");
        }
        HuffmanTree tree(cnt);
        tree.decode(in, out);

        std::cout << tree.getNewSize() << "\n" << tree.getInitSize() << "\n" << tree.getAddSize() << "\n";
    }

}