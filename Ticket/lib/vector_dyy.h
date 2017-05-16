#ifndef VECTOR_DYY_H
#define VECTOR_DYY_H

#include "lib/exceptions.hpp"

namespace tic_ {
template<typename T>
class vector {
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
    vector() {
        const int initLength = 5;
        head = (T**)::operator new( initLength * sizeof(T*) );
        finish = head + initLength;
        rear = head;
    }
    vector( const vector &other ) {
        int length = ((((other.rear - other.head) + 1) >>1 ) << 1);
        head = (T**)::operator new( length * sizeof(T*));
        finish = head + length;
        rear = head + (other.rear - other.head);
        for( int i = 0; i < length; i++ )
            head[i] = new T(*other.head[i]);
    }
    ~vector() {
        int len = int(rear - head);
        for( int i = 0; i < len; i++ )
            delete head[i];
        delete head;
    }
    vector & operator=( const vector &other ) {
        this->~vector();
        new(this) vector(other);
    }
    T &operator[]( int index ) {
        if( index < 0 || index >= (rear - head) )
            throw tic::index_out_of_bound();
        return *head[index];
    }
    int size() {
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
        return *(rear - 1);
    }
    T & front() {
        if( head == rear ) throw tic::container_is_empty();
        return *head;
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
