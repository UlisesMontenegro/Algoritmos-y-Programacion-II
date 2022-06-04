#ifndef CLASE_LISTA_H_INCLUDED
#define CLASE_LISTA_H_INCLUDED

#include "Template_clase_nodo.h"


template<typename T>
class Lista{
private:
    Nodo<T> *primero;

public:
    Lista(); //Constructor
    ~Lista(); //Destructor

    void altafin(T);
    void altaprin(T);
    void altapos(T, int);
    void baja(T);
    void bajaprin();
    bool busca(T);
    T primerElemento();
    void emite() const;
    int conteoNodos() const; //Cuenta los nodos que tiene la lista.
    int valoresPositivos() const; //Devuelve 1 si todos los valores de la lista son positivos, de lo contrario devuelve 0.
    Lista<T> *inversion(); //Devuelve una lista con los nodos en el orden inverso. REVISAR!
    void pertenece(Lista<T>); //HACER!!!
    Lista<T> interseccionListas(Lista<T>); //VERIFICAR CUANDO SE REPITEN LAS INTERSECCIONES, VER POR QUE NO ANDA!
    Lista<T> unionListas(Lista<T>); //HACER!!!
};


template<typename T>
Lista<T>::Lista(){
    primero = NULL;
}

template<typename T>
Lista<T>::~Lista(){
    if(primero){  //Si primero no es NULL
        Nodo<T> *aux = primero;
        while(aux){ //Mientras aux no sea NULL
            primero = primero->getSig();
            delete aux;
            aux = primero;
        }
    }
}

template<typename T>
void Lista<T>::altafin(T x){
    Nodo<T> *aux = primero;

    while((aux) && (aux->getSig())) //Mientras aux y aux->sig sean distintos de NULL
        aux = aux->getSig();
    if(aux){ //Si aux es distinto de NULL (aux->sig es NULL)
        aux->setSig(new Nodo<T>(x, aux->getSig()));
    }
    else
        primero = new Nodo<T>(x, primero);
}

template<typename T>
void Lista<T>::altaprin(T x){
    primero = new Nodo<T>(x, primero); //Llama al constructor apuntando a primero y asigna x a info.
}

template<typename T>
void Lista<T>::altapos(T x, int pos){
    if(pos == 0)
        altaprin(x);
    else{
        Nodo<T> *aux1 = primero;
        Nodo<T> *aux2;
        int contador = 0;
        while(((aux1) && (aux1->getSig())) && (contador < pos-1)){
            aux1 = aux1->getSig();
            contador++;
        }
        if(aux1){
            aux2 = new Nodo<T>(x);
            aux2->setSig(aux1->getSig());
            aux1->setSig(aux2);
        }
        else
            altafin(x);
    }
}

template<typename T>
void Lista<T>::baja(T x){ //Da de baja al primer nodo que contenga x.
    if(primero){
        if((primero->getInfo() != x) && (primero->getSig())){
            Nodo<T> *aux1 = primero, *aux2 = primero->getSig();
            while((aux2->getInfo() != x) && (aux2->getSig())){
                aux1 = aux2;
                aux2 = aux2->getSig();
            }
            if(aux2->getInfo() == x){
                aux1->setSig(aux2->getSig());
                delete aux2;
            }
        }
        else if(primero->getInfo() == x){
            Nodo<T> *aux = primero;
            primero = primero->getSig();
            delete aux;
        }
    }
}

template <typename T>
void Lista<T>::bajaprin(){
    if(primero){
        Nodo<T> *aux = primero;
        primero = primero->getSig();
        delete aux;
    }
}

template<typename T>
bool Lista<T>::busca(T x){
    Nodo<T> *aux = primero;

    while(aux){
        if(aux->getInfo() == x)
            return true;
        aux = aux->getSig();
    }
    return false;
}

template <typename T>
T Lista<T>::primerElemento(){
    return primero->getInfo();
}


template<typename T>
void Lista<T>::emite() const{
    Nodo<T> *aux = primero;

    while(aux){
        std::cout<<aux->getInfo();
        aux = aux->getSig();
    }
}

template<typename T>
int Lista<T>::conteoNodos()const{
    Nodo<T> *aux = primero;
    int cont = 0;

    while(aux){
        cont++;
        aux = aux->getSig();
    }
    return cont;
}

template<typename T>
int Lista<T>::valoresPositivos() const{
    Nodo<T> *aux = primero;

    if(!aux)
        return 0;

    while((aux) && (aux->getInfo() > 0))
        aux = aux->getSig();

    if(aux)
        return 0;

    return 1;
}

template<typename T>
Lista<T> *Lista<T>::inversion(){
    Nodo<T> *nodo_aux = primero;

    if((!nodo_aux) || (!nodo_aux->getSig()))
        return this;

    Lista<T> *lista_aux;

    while(nodo_aux){
        lista_aux->altaprin(nodo_aux->getInfo());
        nodo_aux = nodo_aux->getSig();
    }

    return lista_aux;
}

template<typename T>
Lista<T> Lista<T>::interseccionListas(Lista<T> l){
    Nodo<T> *nodo_aux1 = primero, *nodo_aux2 = l.primero;

    if(!nodo_aux2)
        return l;
    if(!nodo_aux1)
        return *this;

    Lista<T> lista_aux;

    while(nodo_aux2){
        nodo_aux1 = primero;
        while(((nodo_aux1->getInfo()) != (nodo_aux2->getInfo())) && nodo_aux1)
            nodo_aux1 = nodo_aux1->getSig();

        if(nodo_aux1)
            lista_aux.altafin(nodo_aux1->getInfo());

        nodo_aux2 = nodo_aux2->getSig();
    }

    return lista_aux;
}

#endif // CLASE_LISTA_H_INCLUDED
