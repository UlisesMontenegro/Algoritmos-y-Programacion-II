#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

//Clase Queue implementado con una lista circular
//ejemplo sencillo de listas circulares
//este programa solo intenta mostrar el comportamiento de los punteros en las listas circulares

#include <iostream>

#include "Template_clase_nodo.h"

using namespace std;

template <class T> class Queue ;


template <typename T>
class Queue
{
	
	private:
		Nodo <T> * first;
		Nodo <T> * last;
	public:
		Queue( ); //constructor
					// Escribir el constructor copia como ej
		~Queue( ); //destructor
		
		void enQueue(const T &); // Da alta en la cola a un elemento.
		void deQueue( ); 	// Elimina el elemento del frente de la misma
		bool empty( ) const; 	//retorna true si lista vacia.
		void Emitir ( ) const; //emite la lista.
		T front() const;  // Retorna el valor del primer elemento de la cola.
};
template <typename T>
Queue <T>::Queue(){
	first = last = 0;
}

template <typename T>
Queue<T>::~Queue()
{
	if(first)
	{
		if (first->getSig() == first)delete first;
		else
		{
			Nodo <T> *_aux1, *_aux2;
			_aux1=first->getSig();
			first->setSig(0);
			while(_aux1!=0)
			{
				_aux2=_aux1;
				_aux1=_aux1->getSig();
				delete _aux2;
			}
		}
	}
}

template <typename T>
void Queue <T> :: enQueue (const T & _v)
{
	Nodo<T> *_nuevo = new Nodo <T>(_v);
	if(empty())
	{
		first =_nuevo;
		last = _nuevo;
		_nuevo->setSig(_nuevo);
	}
	else
	{
		last->setSig(_nuevo);
		_nuevo->setSig(first);
		last = _nuevo;
	}
}

template <typename T>
void Queue <T> :: deQueue()
{
	Nodo<T> *_aux1;
	if (!empty())
	{
		if (first->getSig() == first)
		{
			delete first;
			first = 0;
			last = 0;
		}
		else
		{
			_aux1=first;
			first = first->getSig();
			//last->getSig() = first; 
			last->setSig(first);
			delete _aux1;
		}
	}
}

template <typename T>
void Queue <T> :: Emitir () const
{
	Nodo<T> *_aux=first;
	if(!empty())
	{ 	do
		{ 	cout<<_aux->getInfo()<<"      ";
			_aux=_aux->getSig();
		}
		while(_aux!=first);
	}
}

template <typename T>
bool Queue <T> :: empty () const
{
	return (first==0);
}

template <typename T>
T Queue <T> :: front() const
{
	return first->getInfo(); //ojo lo cambie de front a first
}

#endif
