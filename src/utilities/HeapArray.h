#pragma once

#include <iostream>


namespace m4w {
    template <typename T>
    class HeapArray {
        T* m_Pointer;
        unsigned int* m_Owners;
        unsigned int m_Size;
    public:
        HeapArray()
            : m_Pointer(nullptr), m_Owners(new unsigned int(1))
        { }

        HeapArray(unsigned int size)
            : m_Size(size), m_Pointer(new T[size]), m_Owners(new unsigned int(1))
        { }
        
        //HeapArray(T* pointer, unsigned int size)
        //    : m_Size(size), m_Pointer(pointer), m_Owners(new unsigned int(1))
        //{ }

        ~HeapArray() {
            *m_Owners -= 1;

            if ( *m_Owners == 0 ) {
                if ( m_Pointer ) delete[] m_Pointer;
                delete m_Owners;
            }
        }

        HeapArray(const HeapArray& array)
            : m_Pointer(array.m_Pointer), m_Owners(array.m_Owners), m_Size(array.m_Size)
        {
            *m_Owners += 1;
        }

        HeapArray& operator= (const HeapArray& array) {
            this->~HeapArray();

            m_Pointer = array.m_Pointer;
            m_Size = array.m_Size;
            m_Owners = array.m_Owners;
            *m_Owners += 1;
            return *this;
        }

        //void LateInit(unsigned int size) {
        //    m_Size = size;
        //    m_Pointer = new T[size];
        //}

        unsigned int GetSize() {
            return m_Size;
        }

        T* operator-> () const {
            return m_Pointer;
        }

        T& operator[] (unsigned int index) const {
            if ( index >= m_Size ) {
                std::cout << "[ERROR] Heaparray Index out of bounds!\n";
                return m_Pointer[0];
            }
            
            return m_Pointer[index];
        }
    };
}