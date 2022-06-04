#ifndef PIXEL_H_INCLUDED
#define PIXEL_H_INCLUDED

#include "Complejo.h"

#define REAL_DEFECTO 0.0
#define IMAGINARIO_DEFECTO 0.0
#define COLOR_DEFECTO 0

class Pixel{
private:
    Complejo posicion; //Posicion del pixel en el mapa.
    int color; //Color del pixel (Escala de grises).

public:
    Pixel(); //Constructor por defecto.
    ~Pixel(); //Destructor.

    void setPosition(const Complejo &); //Setea la posicion del pixel en el mapa.
    void setColor(const int &); //Setea el color del pixel.
    Complejo &getPosition(); //Devuelve la posicion del Pixel.
    int &getColor(); //Devuelve el color del pixel (Escala de grises).

    Pixel &operator=(Pixel &);  // operador =.
};




#endif // PIXEL_H_INCLUDED
