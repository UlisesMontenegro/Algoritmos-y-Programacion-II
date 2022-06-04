#ifndef IMAGEN_H_INCLUDED
#define IMAGEN_H_INCLUDED

#include <iostream>
#include <fstream>
#include <cmath>
#include <string.h>
#include "Pixel.h"
#include "Errores.h"
#include "Complejo.h"
#include "constantes.h"

#include "Queue.h"
#include "Template_Pila.h"

#define ANCHO_POR_DEFECTO 3
#define ALTO_POR_DEFECTO 3
#define INTENSIDAD_MAXIMA_POR_DEFECTO 0

using namespace std;


/* Se define la clase Imagen que se encarga de guardar los datos de una imagen
 *  
 */
class Imagen{
private:
    int ancho; //Ancho de la imagen (Cantidad de pixeles).
    int alto; //Alto de la imagen (Cantidad de pixeles).
    int intensidad_max; //Intensidad maxima de la escala de grises.
    double precision_ancho;  // Precisión para obtener la imagen trasformada.
    double precision_alto;
    
    Pixel **mapa; //Puntero al primer elemento de la matriz de pixels.

public:
    Imagen(); //Constructor por defecto.
    Imagen(int, int, int); //Constructor por parametros.
    Imagen(istream&); //Constructor por archivo.
    ~Imagen(); //Destructor.

    void setAncho(const int&); //Carga en el atributo ancho.
    void setAlto(const int&); //Carga en el atributo alto.
    void setIntensidadMax(const int&); //Carga en el atributo intensidad_max.
    void setPrecisionAncho(const double&);  //Carga en el atributo precision_ancho.
    void setPrecisionAlto(const double&);  //Carga en el atributo precision_alto.
    int &getAncho();	//Retorna el atributo ancho.
    int &getAlto();		//Retorna el atributo alto.
    int &getIntensidadMax();  //Retorna el atributo intensidad_max.
    double &getPrecisionAncho();		//Retorna el atributo precision_ancho.
    double &getPrecisionAlto();		//Retorna el atributo precision_alto.
    Pixel &getPixel(int, int); //Recibe como argumento la posicion (i,j) de la matriz y retorna el objeto pixel que se encuentra ahi.
    int getPixelColor(Complejo &);  //Recibe un complejo y retorna la intensidad máxima.
    int getPixelColor(double&);
   
    void operar(Imagen&, Queue<string>*);
    
    void print(ostream&);   // Método que imprime la imagen por el flujo de salida.

    Imagen &operator=(Imagen &);  //operador =.
};

#endif // IMAGEN_H_INCLUDED
