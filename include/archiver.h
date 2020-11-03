#ifndef ARCHIVER_H
#define ARCHIVER_H

#include <iostream>

namespace HuffmanArchiver {

    void encode(std::istream &in, std::ostream &out);

    void decode(std::istream &in, std::ostream &out);

}

#endif //ARCHIVER_H
