#include "Base64.h"

#include <iostream>

    void brint(void* start, int bytes, bool b64) {
        //uint64_t beg = (uint64_t) start + bytes;
        char* beg = (char*) start;

        for ( int i = 0; i < bytes; i++) {
            
            char current = *((char*)beg);

            for ( char b = (b64 ? 5 : 7); b>=0; b--) {
                std::cout << ( (current >> b) & 1 );
            }
            
            std::cout << " ";
            beg++;
        }

        std::cout << "\n";
    }

    uint32_t getPos(char c) {
        uint32_t temp;
        if ( c == '+' ) temp = 62;
        else if ( c == '/' ) temp = 63;
        else if ( c <= '9' ) temp = c - '0' + 52;
        else if ( c <= 'Z' ) temp = c - 'A';
        else temp = c - 'a' + 26;

        //std::cout << c << " "; brint(&temp, 1, true);
        return temp;
    }

namespace m4w {
    BinaryData DecodeB64 (std::string input, bool addNullCharacter) {

        int len = input.length();

        m4w::BinaryData data;

        data.Size = len*3/4;
        int equals = 0;
        while ( input[len - equals - 1] == '=' ) {
            --data.Size;
            ++equals;
        }

        data.DataPointer = new char[data.Size + addNullCharacter];

        for ( int i = 0; i < data.Size + addNullCharacter ; i++ ) data.DataPointer[i] = 0;

        int j = 0, i = 0;
        for ( ; i < data.Size - 2; i += 3 ) {
            (uint32_t&) data.DataPointer[i] |= getPos(input[j++]) << 18
                            |  getPos(input[j++]) << 12
                            |  getPos(input[j++]) << 6
                            |  getPos(input[j++]) << 0;
            
            char temp = data.DataPointer[i];
            data.DataPointer[i] = data.DataPointer[i + 2];
            data.DataPointer[i + 2] = temp;
            //brint(&out[i], 3);
        }

        if (equals == 1) {
            char a = getPos(input[j++]);
            char b = getPos(input[j++]);
            char c = getPos(input[j]);

            data.DataPointer[i] = a << 2 | b >> 4;
            data.DataPointer[i+1] = b << 4 | c >> 2;
        }

        if (equals == 2) {
            char a = getPos(input[j++]);
            char b = getPos(input[j]);

            data.DataPointer[i] = a << 2 | b >> 4;
        }

        //std::cout << " >> " << out << std::endl;

        //for (int i = 0; i < elen; i += 4) {
        //    std::cout << *((float*) &out[i]) << " ";
        //    brint(&out[i], 4);
        //}

        return data;
    }
}