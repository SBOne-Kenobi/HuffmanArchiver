#include "binary.h"

namespace HuffmanArchiver {

    bool readBool(std::istream &in, bool &data) {
        static std::queue<bool> q;
        if (q.empty()) {
            unsigned char c;
            in >> binary<unsigned char>(c);
            for (size_t i = 0; i < CHAR_BIT; i++) {
                q.push(c & 1);
                c >>= 1;
            }
        }
        data = q.front();
        q.pop();
        return q.empty();
    }

    bool writeBool(std::ostream &out, bool &data) {
        static std::queue<bool> q;
        q.push(data);
        if (q.size() == CHAR_BIT) {
            unsigned char c = 0;
            for (size_t i = 0; i < CHAR_BIT; i++) {
                if (q.front())
                    c |= (1 << i);
                q.pop();
            }
            out << binary<unsigned char>(c);
        }
        return q.empty();
    }
}