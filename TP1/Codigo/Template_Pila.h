#ifndef CLASE_PILA_H_INCLUDED
#define CLASE_PILA_H_INCLUDED

#include "Template_clase_lista.h"

template <typename T>
class Pila{
private:
    Lista<T> *p_entrada;

public:
    Pila(); //Constructor por defecto.
    ~Pila(); //Destructor por defecto.

    Pila<T>& push(T); //Hace un alta al principio de la lista.
    Pila<T>& pop(); //Hace una baja al principio de la lista.
    T tope(); //Retorna el valor del tope de la pila (primer elemento de la lista).
    bool vacia(); //Verifica si la pila esta vacia.
};


template <typename T>
Pila<T>::Pila(){
    p_entrada = new Lista<T>;
}

template <typename T>
Pila<T>::~Pila(){
    if(p_entrada){
        p_entrada->~Lista();
        delete p_entrada;
        p_entrada = NULL;
    }
}

template <typename T>
Pila<T>& Pila<T>::push(T dato){
    if(p_entrada)
        p_entrada->altaprin(dato);
    return *this;
}

template <typename T>
Pila<T>& Pila<T>::pop(){
    if(p_entrada)
        p_entrada->bajaprin();
    return *this;
}

template <typename T>
T Pila<T>::tope(){
    return p_entrada->primerElemento();
}

template <typename T>
bool Pila<T>::vacia(){
    if((!p_entrada) || p_entrada->conteoNodos() == 0)
        return true;
    return false;
}


#endif // CLASE_PILA_H_INCLUDED
