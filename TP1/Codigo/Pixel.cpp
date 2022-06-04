#include "Pixel.h"

//Constructor por defecto. Crea un pixel negro en el origen.
Pixel::Pixel(){ 
    posicion.setReal(REAL_DEFECTO);
    posicion.setImag(IMAGINARIO_DEFECTO);
    color = COLOR_DEFECTO;
}

Pixel::~Pixel(){
}

void Pixel::setPosition(const Complejo &c){
    posicion = c;
}

void Pixel::setColor(const int &colour){
    color = colour;
}

Complejo &Pixel::getPosition(){
    return posicion;
}

int &Pixel::getColor(){
    return color;
}

Pixel &::Pixel::operator=(Pixel &p){
    posicion = p.getPosition();
    color = p.getColor();
    return *this;
}
