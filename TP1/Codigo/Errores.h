#ifndef _ERRORS_H_INCLUDED_
#define _ERRORS_H_INCLUDED_

#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

/* Se definen las macros de los mensajes de error
 */

#define MSJ_ERROR_ARCHIVO_INCORRECTO							"Ingresar una imagen con identificador P2"
#define MSJ_ERROR_IMAGENES_DE_DISTINTO_TAMANIO 				 	"Imagenes de distinto tamaño"
#define MSJ_ERROR_NO_SE_PUEDE_LEER_ARCHIVO						"No se puede leer el archivo"
#define MSJ_ERROR_NO_SE_PUEDE_OBTENER_ANCHO						"No se puede obtener el ancho de la imagen"
#define MSJ_ERROR_NO_SE_PUEDE_OBTENER_LARGO						"No se puede obtener el largo de la imagen"
#define MSJ_ERROR_NO_SE_PUEDE_OBTENER_INTENSIDAD_MAXIMA			"No se puede obtener la intensidad máxima de color"
#define MSJ_ERROR_NO_SE_PUEDE_OBTENER_INTENSIDAD				"No se puede obtener la intensidad de color"

#define MSJ_ERROR_NO_SE_PUEDE_IMPRIMIR_FORMATO					"No se pude imprimir formato (P2)"
#define MSJ_ERROR_NO_SE_PUEDE_IMPRIMIR_ANCHO					"No se puede imprimir el ancho de la imagen"
#define MSJ_ERROR_NO_SE_PUEDE_IMPRIMIR_LARGO					"No se puede imprimir el largo de la imagen"
#define MSJ_ERROR_NO_SE_PUEDE_IMPRIMIR_INTENSIDAD_MAXIMA		"No se puede imprimir la intensidad máxima de color"
#define MSJ_ERROR_NO_SE_PUEDE_IMPRIMIR_INTENSIDAD				"No se puede imprimir la intensidad de color"
#define MSJ_ERROR_NO_SE_PUEDE_IMPRIMIR_DELIMITADOR				"No se puede imprimir el delimitador"
#define MSJ_ERROR_NO_SE_PUEDE_OPERAR							"No se puede operar"
#define MSJ_ERROR_OPERACION_INVALIDA							"Operación inválida"


/* Se define una clase Errors que tienen métodos  que se encargan de 
 * imprimir por std::cerr los mensajes de error. Los métodos se definen
 * con static para que cuando sean convocadas de la siguiente manera:
 * Errors::método(); 
 */

class Errores
{
	public:
		Errores();
		~Errores();
		static void archivoIncorrecto();
		static void imagenesDeDistintoTamanio();
		static void noSePuedeLeerArchivo();
		static void noSePuedeObtenerAncho();
		static void noSePuedeObtenerLargo();
		static void noSePuedeObtenerIntensidadMaxima();
		static void noSePuedeObtenerIntensidad();
		
		static void noSePuedeImprimirFormato();
		static void noSePuedeImprimirAncho();
		static void noSePuedeImprimirLargo();
		static void noSePuedeImprimirIntensidadMaxima();
		static void noSePuedeImprimirIntensidad();
		static void noSePuedeImprimirDelimitador();
		
		static void noSePuedeOperar();
		static void operacionInvalida();
};
#endif
