#pragma once

#include <iostream>


namespace m4w {
    template <typename T>
    class Pointer {
    private:
        T* m_Pointer;
        unsigned int* m_Owners;

        template<typename> friend class Pointer;

        Pointer(T* pointer, unsigned int* owners)
            : m_Pointer(pointer), m_Owners(owners)
        {
            *m_Owners += 1;
        }
    public:
        Pointer()
            : m_Pointer(nullptr), m_Owners( new unsigned int(1) )
        { }

        Pointer(T* pointer)
            : m_Pointer(pointer), m_Owners( new unsigned int(1) )
        { }

        //template <typename... Args>
        //Pointer(Args&&... args)
        //    : m_Pointer( new T( args... ) ), m_Owners( new unsigned int(1) ) 
        //{ }

        T* GetCPointer() {
            return m_Pointer;
        }

        ~Pointer() {
            *m_Owners -= 1;

            if ( *m_Owners == 0 ) {
                if ( m_Pointer ) {
                    //std::cout << "del " << typeid(T).name() << "\n";
                    delete m_Pointer;
                }
                delete m_Owners;
            }
        }

        Pointer(const Pointer& pointer)
            : m_Pointer(pointer.m_Pointer), m_Owners(pointer.m_Owners)
        {
            *m_Owners += 1;
        }

        void Defuse() {
            m_Pointer = nullptr;
        }
        
        void Delete() {
            delete m_Pointer;
            m_Pointer = nullptr;
        }

        Pointer& operator= (const Pointer& pointer) {
            this->~Pointer();

            m_Pointer = pointer.m_Pointer;
            m_Owners = pointer.m_Owners;
            *m_Owners += 1;
            return *this;
        }

        Pointer& operator= (T* pointer) {
            this->~Pointer();

            m_Pointer = pointer;
            m_Owners = new unsigned int(1);
            return *this;
        }

        T& operator* () const {
            return *m_Pointer;
        }

        T* operator-> () const {
            return m_Pointer;
        }

        T& operator[] (unsigned int index) const {
            return m_Pointer[index];
        }

        template <typename... Args>
        void Create(Args&&... args) {
            if ( m_Pointer ) delete m_Pointer;

            new (m_Pointer) T(std::forward<Args>(args)...);
        }

        // Different casts, yay
        operator T*() const {
            return m_Pointer;
        }

        template <typename S>
        operator Pointer<S>() const {
            Pointer<S> cast = Pointer<S>((S*) m_Pointer, m_Owners);
            return cast;
        }

        operator bool() const {
            return m_Pointer;
        }
    };
}