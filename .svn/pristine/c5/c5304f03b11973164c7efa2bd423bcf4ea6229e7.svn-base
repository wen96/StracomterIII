#ifndef __MY_VECTOR__
#define __MY_VECTOR__

#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

/*
 * O(1) insert and recovery, memory heavy, dynamic vector.
 * Not intended for use as hashmap.
 * Asking for outbounds data results into a new memory being reserved
 */


template <class T>

class myVector
{
    protected:
        T* vector;
        int _size;

    public:

        myVector <T> ()
        {
            vector = (T*)malloc(sizeof(T));
            _size = 1;
        }

        myVector <T> (const myVector<T>& v)
        {
            _size = v._size;
            vector = (T*)malloc(sizeof(T)*_size);
            memcpy(vector, v.vector, sizeof(T)*_size);
        }

        ~myVector ()
        {
            free(vector);
            _size = -1;
        }

        void clear()
        {
            free(vector);
            size = 1;
            vector = (T*)malloc(sizeof(T));
        }


        T &operator [](const int index)
        {
            if (index >= _size)
            {
                _size = index+1;
                vector = (T*)realloc(vector, sizeof(T)*_size);
            }

            return vector[index];
        }

        //Size of the vector
        int size()
        {
            return _size;
        }

        //Size of the vector
        int length()
        {
            return size();
        }   

        //Sets the size to a fixed value, reallocating memory as needed.
        //Useful in lots-of-insertions case.
        void setSize( int newSize )
        {
            if (newSize >= 0)
            {
                _size = newSize;
                vector = (T*) realloc (vector, sizeof(T)*_size);
            }
        }

        //Swaps two elements. 
        void swap (int a, int b)
        {
            T aux = vector[a];
            vector[a] = vector[b];
            vector[b] = aux;
        }

};


//Same as the above, but you can sort the vector if the stored class 
//has a public Double val() function
template <class T>
class mySortableVector : public myVector<T>
{
    public:
        mySortableVector <T> () : myVector<T>() {};
        ~mySortableVector () {};

        void sort()
        {
            sort(0, myVector<T>::_size-1);
        }

        void sort(int inicio, int fin)
        {
            if (inicio < fin)
            {
                int pivot = (inicio + fin) / 2;
                double pivotVal = myVector<T>::vector[pivot].val();
                int storeIndex = inicio;
                swap(pivot, fin);
                
                for (int i =  inicio; i < fin; i++)
                {
                    if (myVector<T>::vector[i].val() < pivotVal)
                    {
                        myVector<T>::swap(storeIndex, i);
                        storeIndex++;
                    }
                }
                swap(storeIndex, fin);

                sort(inicio, storeIndex-1);
                sort(storeIndex+1, fin);
            }
        }    

};




//Same as the above, but works with pointers rather than objects
template <class T>
class mySortablePointerVector : public myVector<T>
{
    public:
        mySortablePointerVector <T> () : myVector<T>() {};
        ~mySortablePointerVector () {};

        void sort()
        {
            sort(0, myVector<T>::_size-1);
        }

        void sort(int inicio, int fin)
        {
            if (inicio < fin)
            {
                int pivot = (inicio + fin) / 2;
                double pivotVal = myVector<T>::vector[pivot]->val();
                int storeIndex = inicio;
                swap(pivot, fin);
                
                for (int i =  inicio; i < fin; i++)
                {
                    if (myVector<T>::vector[i]->val() < pivotVal)
                    {
                        myVector<T>::swap(storeIndex, i);
                        storeIndex++;
                    }
                }
                swap(storeIndex, fin);

                sort(inicio, storeIndex-1);
                sort(storeIndex+1, fin);
            }
        }    
};

#endif
