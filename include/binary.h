#ifndef BINARY_H
#define BINARY_H

#include <istream>
#include <ostream>
#include <cstdint>
#include <climits>
#include <queue>

namespace HuffmanArchiver {
    template<typename T>
    class binary {
    private:
        const T &_data;
    public:
        explicit binary(const T &data) : _data(data) {}

        template<typename H>
        friend std::istream &operator>>(std::istream &is, const binary<H> &x);

        template<typename H>
        friend std::ostream &operator<<(std::ostream &os, const binary<H> &x);
    };

    template<typename T>
    inline std::istream &operator>>(std::istream &in, const binary<T> &x) {
        in.read(const_cast<char *>(reinterpret_cast<const char *>(&x._data)), sizeof(T));
        return in;
    }

    template<typename T>
    inline std::ostream &operator<<(std::ostream &out, const binary<T> &x) {
        out.write(reinterpret_cast<const char *>(&x._data), sizeof(T));
        return out;
    }

    bool readBool(std::istream &in, bool &data);

    bool writeBool(std::ostream &out, bool &data);
}

#endif //BINARY_H