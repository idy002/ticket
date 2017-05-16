#ifndef VECTOR_DYY_H
#define VECTOR_DYY_H

#include "lib/exceptions.hpp"

const int initLength = 5;

namespace tic {
template<typename T>
class vector_dyy {
    T **head, **rear, **finish;
    void doubleSpace() {
        T **_head, **_rear, **_finish;
        int curlen = (finish - head) * 2;
        _head = (T**)::operator new( curlen * sizeof(T*) );
        _finish = _head + curlen;
        _rear = _head + (rear - head);
        int len = int(rear - head);
        for( int i = 0; i < len; i++ )
            _head[i] = head[i];
        delete head;
        head = _head;
        rear = _rear;
        finish = _finish;
    }

public:
    vector_dyy() {
        head = (T**)::operator new( initLength * sizeof(T*) );
        finish = head + initLength;
        rear = head;
    }
    vector_dyy( const vector_dyy &other ) {
        int cap = ((((other.rear - other.head) + 1) >>1 ) << 1);
        int len = (int)(other.rear - other.head);
        if( cap < initLength ) cap = initLength;
        head = (T**)::operator new( cap * sizeof(T*));
        finish = head + cap;
        rear = head + len;
        for( int i = 0; i < len; i++ )
            head[i] = new T(*other.head[i]);
    }
    ~vector_dyy() {
        int len = int(rear - head);
        for( int i = 0; i < len; i++ )
            delete head[i];
        delete head;
    }
    vector_dyy & operator=( const vector_dyy &other ) {
        this->~vector_dyy();
        new(this) vector_dyy(other);
        return *this;
    }
    T &operator[]( int index ) {
        if( index < 0 || index >= (rear - head) ) {
            throw tic::index_out_of_bound();
        }
        return *head[index];
    }
    int size() const {
        return int(rear - head);
    }
    void clear() {
        int len = int(rear - head);
        for( int i = 0; i < len; i++ )
            delete head[i];
        rear = head;
    }

    T & back() {
        if( head == rear ) throw tic::container_is_empty();
        return **(rear - 1);
    }
    T & front() {
        if( head == rear ) throw tic::container_is_empty();
        return *head[0];
    }
    void push_back( const T & val ) {
        if( rear == finish )
            doubleSpace();
        *rear = new T(val);
        rear++;
    }
};
}

#endif // VECTOR_DYY_H
