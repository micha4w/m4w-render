#pragma once

#include <string>

namespace m4w {
    struct BinaryData {
        char* DataPointer;
        unsigned int Size;

        void Delete () { delete[] DataPointer; }
    };

    void brint(void* start, int bytes, bool b64 = false);

    BinaryData DecodeB64 (std::string input, bool addNullCharacter = false);
}