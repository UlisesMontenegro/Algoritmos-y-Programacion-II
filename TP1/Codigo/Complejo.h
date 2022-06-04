#ifndef COMPLEJO_H_INCLUDED
#define COMPLEJO_H_INCLUDED

#include "constantes.h"
#include "Errores.h"
#include <string>

using namespace std;

class Complejo{
private:
    double real;
    double imaginario;
    Complejo pow2();
public:
    Complejo(); //Constructor por defecto.
    Complejo(const Complejo &); //Constructor por copia.
    Complejo(double, double); //Constructor por valores.
    Complejo(double); //Constructor por un valor (real). Se usa para castear.
    Complejo(string); //Constructor por cadena.
    ~Complejo(); //Destructor

    void setReal(double);
    void setImag(double);
    double getReal();
    double getImag();

    string aString(); //Convierte un complejo a un string.
    Complejo aplicarFuncion(string);
    Complejo aplicarOperador(Complejo &, string);

    Complejo conjugado();
    Complejo identidad();   // Aplica la identidad y retorna el resultado.
    Complejo expc();	// Aplica la exponecial y retorna el resultado.
    Complejo sinc(); //Aplica el seno y retorna el resultado.
    Complejo cosc(); //Aplica el coseno y retorna el resultado.
    Complejo lnc(); //Aplica el logaritmo natural y retorna el resultado.
    double modulo();
    double phase();

    Complejo operator+(Complejo);
    Complejo operator-(Complejo);
    Complejo operator-();
    Complejo operator*(Complejo);
    Complejo operator/(Complejo);
    Complejo operator^(int);
    Complejo &operator=(const Complejo &);
    bool operator==(Complejo &);
    operator int(); //Castea a int un objeto de la clase Complejo.
};

#endif // COMPLEJO_H_INCLUDED
