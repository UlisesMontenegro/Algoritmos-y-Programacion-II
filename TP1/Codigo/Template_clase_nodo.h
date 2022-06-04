#ifndef CLASE_NODO_H_INCLUDED
#define CLASE_NODO_H_INCLUDED
//#ifndef NULL
//#define NULL 0

#include <iostream>

template<typename T>
class Nodo{
	
private:
    T info;
    Nodo<T> *sig;

public:
    Nodo(T, Nodo<T> *); //Constructor
    Nodo(const T& _v):info(_v),sig(0){} //Constructor

    T getInfo();
    Nodo<T> * getSig();
    void setInfo(T);
    void setSig(Nodo<T> *);
};


/*template<typename T>
Nodo<T>::Nodo(T x, Nodo<T> *p=0):info(x),sig(p){ //Asigna x al atributo info. Asigna p al atributo sig. Si no pasan el segundo argumento lo toma como un 0.
}*/

template<typename T>
Nodo<T>::Nodo(T x, Nodo<T> *p){
    info = x;
    sig = p;
}

template<typename T>
T Nodo<T>::getInfo(){
    return info;
}

template<typename T>
Nodo<T> *Nodo<T>::getSig(){
    return sig;
}

template<typename T>
void Nodo<T>::setInfo(T x){
    info = x;
}

template<typename T>
void Nodo<T>::setSig(Nodo<T> *p){
    sig = p;
}


#endif // CLASE_NODO_H_INCLUDED
