#pragma once

#include <iostream>
#include <unordered_map>

namespace m4w {
    template <typename T>
    class UUIDMap {
    private:
        std::unordered_map<unsigned int, T> m_Items;
        unsigned int m_Position = 0;
    public:
        unsigned int Add(T&& t) {
            m_Items.emplace(m_Position, t);
            return m_Position++;
        }

        template <typename tuple>
        unsigned int Create(tuple&& args) {
            m_Items.emplace(
                std::piecewise_construct,
                std::forward_as_tuple(m_Position),
                std::forward<tuple>(args)
            );
            return m_Position++;
        }

        T* Get(unsigned int id) {
            auto item = m_Items.find(id);

            if ( item != m_Items.end() ) {
                return &item->second;

            } else {
                std::cout << "[Warning] Index " << id << " not found in UUIDMap!\n";
                return nullptr;
            }
        }

        void Remove(unsigned int id) {
            m_Items.erase(id);
        }

        unsigned int GetID(T t) {
            auto item = m_Items.find(t);

            if ( item == m_Items.end() ) {
                std::cout << "[Warning] Object not found in UUIDMap!\n";
                return -1;
            } else {
                return item->first;
            }
        }

        unsigned int GetSize() {
            return m_Items.size();
        }
 
        T* operator[] (unsigned int id) {
            return this->Get(id);
        }

        typedef std::unordered_map<unsigned int, T>::iterator iterator;
        typedef std::unordered_map<unsigned int, T>::const_iterator const_iterator;

        iterator begin() { return m_Items.begin(); }

        const_iterator begin() const { return m_Items.begin(); }

        iterator end() { return m_Items.end(); }

        const_iterator end() const { return m_Items.end(); }
    };
};
