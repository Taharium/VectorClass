#include <algorithm>
#include <stdexcept>

template<typename T>
class Vector {
    public:
        using value_type = T;
        using pointer = T*;
        using reference = T&;

        Vector() : m_container(nullptr), m_length(0), m_capacity(0) {}
        Vector(size_t size) : m_capacity(size), m_length(0) {
            if(size > 0)
                resize(size);
        }

        Vector(const Vector& other){
            if(!other.m_container){
                return;
            }
            m_container = new T[other.m_capacity];
            m_length = other.m_length;
            m_capacity = other.m_capacity;
            std::copy(other.m_container, other.m_container + m_length, m_container);
            //memcpy(m_container, other.m_container, m_length * sizeof(T));
        }

        Vector(Vector&& other) noexcept {
            if(!other.m_container){
                return;
            }
            m_container = other.m_container;
            m_length = other.m_length;
            m_capacity = other.m_capacity;
            other.m_container = nullptr;
            other.m_capacity = 0;
            other.m_length = 0;
        }

        Vector& operator=(Vector&& other) noexcept {
            if(!other.m_container || this != &other){
                delete[] m_container;
                m_container = other.m_container;
                m_length = other.m_length;
                m_capacity = other.m_capacity;
                other.m_container = nullptr;
                other.m_capacity = 0;
                other.m_length = 0;
            }

            
            return *this;
        }

        Vector& operator=(const Vector& other){
            if(!other.m_container || this != &other){
                delete[] m_container;
                m_container = new T[other.m_capacity];
                m_length = other.m_length;
                m_capacity = other.m_capacity;
                std::copy(other.m_container, other.m_container + m_length, m_container);
            }
            
            //memcpy(m_container, other.m_container, m_length * sizeof(T));
            return *this;
        }

        ~Vector() {
            delete[] m_container;
        }
        
        reference operator[](size_t n) const {
            return m_container[n];
        }

        reference at(size_t n) const {
            if(n >= m_length){
                throw std::out_of_range("");
            }
            return m_container[n];
        }

        void reserve(size_t size) const {
            if(m_capacity < size){
                resize(size);
            }
        }

        void push_back(const value_type& elem){
            if(m_capacity <= m_length){
                resize(m_capacity * 2 + 1);
            }
            m_container[m_length] = elem;
            ++m_length;
        }

        void resize(size_t size) {
            
            T* newCon = new T[size];
            if (m_container) {
                for (size_t i = 0; i < m_length; ++i) {
                    newCon[i] = m_container[i];
                }
                delete[] m_container;
            }

            m_capacity = size;
            m_container = newCon;
            newCon = nullptr;
        }

        size_t size() const {
            return m_length;
        }


    private:
        void memcpy(pointer des, pointer src, size_t size) {
            for(size_t i = 0; i < size; ++i ){
                des[i] = src[i];
            }
        }

        pointer m_container;
        size_t m_length;
        size_t m_capacity;
};
