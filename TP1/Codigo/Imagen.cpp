#include "Imagen.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>

using namespace std;

Imagen::Imagen(){ //Constructor. Crea una imagen de 3x3 en negro.
	
    ancho = ANCHO_POR_DEFECTO;
    alto = ALTO_POR_DEFECTO;
    intensidad_max = INTENSIDAD_MAXIMA_POR_DEFECTO;
    
    //Pide memoria para la matriz de pixels.
    mapa = new Pixel *[alto];
    for(int i=0; i<alto; i++)
        mapa[i] = new Pixel[ancho];
    
    //Coloca el (0,0) en el medio
    for(int i=0, j=(alto/2); i<alto; i++, j--){
        for(int k=0, l=(-ancho)/2; k<ancho; k++, l++){
            Complejo c((double)l/(ancho/2), (double)j/(alto/2));
            mapa[i][k].setPosition(c);
        }
    }
}

Imagen::Imagen(int an, int al, int in){
	
	int alto_aux;
	int ancho_aux;
	
    ancho = an;
    alto = al;
    intensidad_max = in;
    
    //Calculamos y asignamos la precision con la que se formara la imagen de salida
    precision_ancho = 2/((double)ancho);
    precision_alto = 2/((double)alto);

    //Pide memoria para la matriz de Pixels validando que alto y ancho sean impares.
    if((alto%2) == 0)
        alto_aux = alto + 1;
    else
        alto_aux = alto;
    if((ancho%2) == 0)
        ancho_aux = ancho + 1;
    else
        ancho_aux = ancho;
    mapa = new Pixel *[alto_aux];
    for(int i=0; i<alto_aux; i++)
        mapa[i] = new Pixel[ancho_aux];
    
    //Coloca el (0,0) en el medio
    for(int i=0, j=(alto_aux/2); i<alto_aux; i++, j--){
        for(int k=0, l=(-ancho_aux)/2; k<ancho_aux; k++, l++){
            Complejo c((double)l/(ancho_aux/2), (double)j/(alto_aux/2));
            mapa[i][k].setPosition(c);
        }
    }
    
    //Actualizamos los valores de ancho y alto
    ancho = ancho_aux;
    alto = alto_aux;
}

Imagen::Imagen(istream& archivoEntrada)
{
	
	int pixel;
	int alto_aux;
	int ancho_aux;
	
	string lineaEntrada = "";
	stringstream ss;				// Variable Stream para almacenar en un bufer.

	if (!getline(archivoEntrada,lineaEntrada))  // Leo la primera línea
		Errores::noSePuedeLeerArchivo();								// En caso de que no se pudo leer correctamente.
	
    if(lineaEntrada.compare(FORMATO_IMAGEN) != 0){  //En caso de que el archivo de entradas sea distinto a .pgm
		Errores::archivoIncorrecto();				//retornamos un error y terminamos la ejecución del programa.
	}

    if(!getline(archivoEntrada,lineaEntrada))  // Lee la segunda línea
		Errores::noSePuedeLeerArchivo();	
		
    if(lineaEntrada[0] != CARACTER_COMENTARIO){
        size_t pos_espacio = lineaEntrada.find(DELIMITADOR); //Guardo la posicion donde esta el DELIMITADOR.
        string aux;
        aux = lineaEntrada.substr(0, pos_espacio); //En el string aux guardo lo que hay hasta el DELIMITADOR.
        
        if(!(stringstream(aux) >> ancho)) //En la variable width guardo el string aux convertido en int.
			Errores::noSePuedeObtenerAncho();
        aux = lineaEntrada.substr(pos_espacio+1); //En el string aux guardo lo que hay desde el caracter que 
													//le sigue al espacio hasta el final del string s.
        if(!(stringstream(aux) >> alto)) //En el atributo alto guardo el string aux convertido en int.
			Errores::noSePuedeObtenerLargo();
			
        if(!(ss << archivoEntrada.rdbuf())) //Almacenamos en un bufer los datos que quedan en el archivo.
			Errores::noSePuedeLeerArchivo();
	}
    else{

        if(!(ss << archivoEntrada.rdbuf()))   // Almacenamos en un bufer los datos que quedan en el archivo.
			Errores::noSePuedeLeerArchivo();
    //Inserto los datos de ancho y largo de la imagen
        if(!(ss >> ancho))
			Errores::noSePuedeObtenerAncho();
        if(!(ss >> alto))
			Errores::noSePuedeObtenerLargo();	
    }

    //Inserto la intensidad máxima de color
    
    if(!(ss >> intensidad_max))      
	{
		Errores::noSePuedeObtenerIntensidadMaxima();
	}
    
    //Calculamos y asignamos la precision con la que se formara la imagen de salida

	precision_ancho = 2/((double)ancho);
	precision_alto = 2/((double)alto);

    //Pide memoria para la matriz de Pixels validando que alto y ancho sean impares.
    if((alto%2) == 0)
        alto_aux = alto + 1;
    else
        alto_aux = alto;
    if((ancho%2) == 0)
        ancho_aux = ancho + 1;
    else
        ancho_aux = ancho;
    mapa = new Pixel *[alto_aux];
    for(int i=0; i<alto_aux; i++)
        mapa[i] = new Pixel[ancho_aux];
    
    //Coloca el (0,0) en el medio
    
    for(int i=0, j=(alto_aux/2); i<alto_aux; i++, j--){
        for(int k=0, l=(-ancho_aux)/2; k<ancho_aux; k++, l++){
            Complejo c((double)l/(ancho_aux/2), (double)j/(alto_aux/2));
            mapa[i][k].setPosition(c);
        }
    }

    for(int i=0; i<alto; i++){
        for(int j=0; j<ancho; j++){
            if(!(ss>>pixel))
				Errores::noSePuedeObtenerIntensidad();
            mapa[i][j].setColor(pixel);
        }
    }
    
    // Actualizamos los valores de ancho y alto
    ancho = ancho_aux;
    alto = alto_aux;
}


Imagen::~Imagen(){
    if(mapa){
        for(int i=0; i<alto; i++)
            delete[] mapa[i];
        delete[] mapa;
        mapa = NULL;
    }
}

void Imagen::setAncho(const int &an){
    ancho = an;
}

void Imagen::setAlto(const int &al){
    alto = al;
}

void Imagen::setIntensidadMax(const int &in){
    intensidad_max = in;
}

void Imagen::setPrecisionAncho(const double &prec){
    precision_ancho= prec;
}

void Imagen::setPrecisionAlto(const double &prec){
    precision_alto= prec;
}

int &Imagen::getAncho(){
    return ancho;
}

int &Imagen::getAlto(){
    return alto;
}

int &Imagen::getIntensidadMax(){
    return intensidad_max;
}

double &Imagen::getPrecisionAncho(){
	return precision_ancho;
}

double &Imagen::getPrecisionAlto(){
	return precision_alto;
}

Pixel &Imagen::getPixel(int i, int j){
    if(i<0 || i>alto || j<0 ||j>ancho){
        return mapa[0][0];
    }
    return mapa[i][j];
}

int Imagen::getPixelColor(Complejo &c){
	
	if(fabs(c.getReal()) > 1 || fabs(c.getImag()) > 1) // Si el complejo no pertenece al cuadro de 2*2 se retorna 
	{												// el color negro.
		
		return 0; 
	}
	
    for(int i=0; i<alto; i++){
        for(int j=0; j<ancho; j++){
			
            Complejo aux = c-(mapa[i][j].getPosition());
            
			if(fabs(aux.getReal()) < precision_ancho){// || fabs(aux.getReal()) == precision_ancho){
				for(int k=i; k<alto; k++){
					Complejo aux = c-(mapa[k][j].getPosition());
					if(fabs(aux.getImag())< precision_alto){// ||fabs(aux.getImag()) == precision_alto){
						return mapa[k][j].getColor();
					}
				}
			}
          }
    }
    return 0;
}

//Función que imprime la imagen
void Imagen::print(ostream& oss)
{
	if(!(oss<<FORMATO_IMAGEN)) //Imprime el formato de la imagen .pgm
		Errores::noSePuedeImprimirFormato();
	oss<<endl;
	
	if(!(oss<<ancho))
		Errores::noSePuedeImprimirAncho();
	if(!(oss<<DELIMITADOR))		// Imprime el delimitador
		Errores::noSePuedeImprimirLargo();
	if(!(oss<<alto))
		Errores::noSePuedeImprimirLargo();
	oss<<endl;
	
	if(!(oss<<intensidad_max))  //Imprime intensidad máxima
		Errores::noSePuedeImprimirIntensidadMaxima();
	oss<<endl;
	//Lo siguiente imprime las intensidades de color
	for(int i=0; i<alto; i++){
			
            for(int j=0; j<ancho; j++){
                if(!(oss<<mapa[i][j].getColor()))
					Errores::noSePuedeImprimirIntensidad();
				if(!(oss<<DELIMITADOR))
					Errores::noSePuedeImprimirDelimitador();
				if(!(oss<<DELIMITADOR))
					Errores::noSePuedeImprimirDelimitador();
			}
			oss<<endl;
     }
}

//Asigna pixel a pixel una imagen a otra siendo ambas del mismo alto, alto e intensidad maxima.
Imagen &Imagen::operator=(Imagen &im){ 
    
    if(alto != im.getAlto() || ancho != im.getAncho() || intensidad_max != im.getIntensidadMax()){
        Errores::imagenesDeDistintoTamanio();
    }
    
    //Copia pixel a pixel.    
    for(int i=0; i<im.getAlto(); i++){
        for(int j=0; j<im.getAncho(); j++){
            mapa[i][j] = im.getPixel(i, j);
           }
    }
    return *this;
}

/*Método operar*/
void Imagen::operar(Imagen& img, Queue<string> *cola)
{
	img = *this;
	
	Pila<string> pila;
	string simbolo;
	string aux1, aux2;
	
	while(!(*cola).empty())
	{
		
		simbolo = (*cola).front();
		(*cola).deQueue();
		if(isdigit(simbolo[0]))
		{
			pila.push(simbolo);
			
		}else if (isalpha(simbolo[0]))
		{
			if(simbolo == VARIABLE_PI)
			{
				pila.push(simbolo);
			}
			else if(simbolo == VARIABLE_INDEPENDIENTE )
			{	if((*cola).empty())
					break;
				else
					pila.push(simbolo);
						
			}else if(simbolo == FUNCION_EXPONENCIAL||simbolo == FUNCION_LOGARITMO||simbolo == FUNCION_REAL||simbolo == FUNCION_IMAGINARIA||simbolo == FUNCION_ABS
					||simbolo == FUNCION_PHASE || simbolo == FUNCION_SENO || simbolo == FUNCION_COSENO){
				aux1 = pila.tope();
				pila.pop();
				if(aux1 == VARIABLE_INDEPENDIENTE)
				{	
					for (int fila = 0; fila < alto; fila++){
						for (int col = 0; col < ancho; col++){
							img.getPixel(fila,col).getPosition() = img.getPixel(fila,col).getPosition().aplicarFuncion(simbolo);
						}
					}
							
					pila.push(VARIABLE_INDEPENDIENTE);
					
				}else{
					Complejo comp1(aux1);				// Generamos un complejo
					comp1 = comp1.aplicarFuncion(simbolo);
					aux1 = comp1.aString();	// Convertimos el el complejo en string
					pila.push(aux1);			// Calculamos y luego cargamos a la pila,FALTA IMPLEMENTAR EN LA CLASE COMPLEJO
				}
			}
		}else if ( (simbolo == OPERADOR_SUMA||simbolo ==OPERADOR_SUSTRACCION||simbolo ==OPERADOR_MULTIPLICACION||simbolo ==OPERADOR_DIVISION||simbolo ==OPERADOR_POTENCIA) && simbolo.size() == 1 ) {

				aux1 = pila.tope();
				pila.pop();
			
				aux2 = pila.tope();
				pila.pop();
				
				if(aux1 == VARIABLE_INDEPENDIENTE)				// Si encuentro una z, aplico una transformacion a la imagen.
				{
					Complejo comp2(aux2);
					
					for (int fila = 0; fila < alto; fila++){
						for (int col = 0; col < ancho; col++){
							
							img.getPixel(fila,col).getPosition() = img.getPixel(fila,col).getPosition().aplicarOperador(comp2,simbolo);
						}
					}
							
					pila.push(VARIABLE_INDEPENDIENTE);
					
				}else if(aux2 == VARIABLE_INDEPENDIENTE){
					
					Complejo comp1(aux1);
					
					for (int fila = 0; fila < alto; fila++){
						for (int col = 0; col < ancho; col++){
							
							img.getPixel(fila,col).getPosition() = img.getPixel(fila,col).getPosition().aplicarOperador(comp1,simbolo);
						}
					}
							
					pila.push(VARIABLE_INDEPENDIENTE);
				}else{
					Complejo comp1(aux1);
					Complejo comp2(aux2);
					
					comp2 = comp2.aplicarOperador(comp1,simbolo);
					pila.push(comp2.aString());
				}
				
		}else if ( (simbolo[0] ==OPERADOR_SUSTRACCION[0] && simbolo.size() != 1)){
			
			if(simbolo.back() == VARIABLE_INDEPENDIENTE[0]){
				for (int fila = 0; fila < alto; fila++){
						for (int col = 0; col < ancho; col++){
							
							img.getPixel(fila,col).getPosition() = -(img.getPixel(fila,col).getPosition());
						}
					}
							
					pila.push(VARIABLE_INDEPENDIENTE);
			}else{
				pila.push(simbolo);				// Cargamos el numero complejo a la pila.
			}
		}
	}//cierro while
	for (int fila = 0; fila < alto; fila++){
		for (int col = 0; col < ancho; col++){
					
				img.getPixel(fila,col).setColor(this->getPixelColor(img.getPixel(fila,col).getPosition()));
		}
	}
}
