#include "Errores.h"

Errores::Errores(){}

Errores::~Errores(){}

void Errores::archivoIncorrecto(void)
{
	cerr<<MSJ_ERROR_ARCHIVO_INCORRECTO<<endl;
	exit(1);
}

void Errores::imagenesDeDistintoTamanio(void)
{
	cerr<<MSJ_ERROR_IMAGENES_DE_DISTINTO_TAMANIO<<endl;
	exit(1);
}

void Errores::noSePuedeLeerArchivo(void)
{
	cerr<<MSJ_ERROR_IMAGENES_DE_DISTINTO_TAMANIO<<endl;
	exit(1);
}

void Errores::noSePuedeObtenerAncho(void)
{
	cerr<<MSJ_ERROR_NO_SE_PUEDE_OBTENER_ANCHO<<endl;
	exit(1);
}

void Errores::noSePuedeObtenerLargo(void)
{
	cerr<<MSJ_ERROR_NO_SE_PUEDE_OBTENER_LARGO<<endl;
	exit(1);
}

void Errores::noSePuedeObtenerIntensidadMaxima(void)
{
	cerr<<MSJ_ERROR_NO_SE_PUEDE_OBTENER_INTENSIDAD_MAXIMA<<endl;
	exit(1);
}

void Errores::noSePuedeObtenerIntensidad(void)
{
	cerr<<MSJ_ERROR_NO_SE_PUEDE_OBTENER_INTENSIDAD<<endl;
	exit(1);
}


void Errores::noSePuedeImprimirFormato(void)
{
	cerr<<MSJ_ERROR_NO_SE_PUEDE_IMPRIMIR_FORMATO<<endl;
	exit(1);
}


void Errores::noSePuedeImprimirAncho(void)
{
	cerr<<MSJ_ERROR_NO_SE_PUEDE_IMPRIMIR_ANCHO<<endl;
	exit(1);
}

void Errores::noSePuedeImprimirLargo(void)
{
	cerr<<MSJ_ERROR_NO_SE_PUEDE_IMPRIMIR_LARGO<<endl;
	exit(1);
}

void Errores::noSePuedeImprimirIntensidadMaxima(void)
{
	cerr<<MSJ_ERROR_NO_SE_PUEDE_IMPRIMIR_INTENSIDAD_MAXIMA<<endl;
	exit(1);
}

void Errores::noSePuedeImprimirIntensidad(void)
{
	cerr<<MSJ_ERROR_NO_SE_PUEDE_IMPRIMIR_INTENSIDAD<<endl;
	exit(1);
}

void Errores::noSePuedeImprimirDelimitador(void)
{
	cerr<<MSJ_ERROR_NO_SE_PUEDE_IMPRIMIR_DELIMITADOR<<endl;
	exit(1);
}

void Errores::noSePuedeOperar(void)
{
	cerr<<MSJ_ERROR_NO_SE_PUEDE_OPERAR<<endl;
	exit(1);
}

void Errores::operacionInvalida(void)
{
	cerr<<MSJ_ERROR_OPERACION_INVALIDA<<endl;
	exit(1);
}
