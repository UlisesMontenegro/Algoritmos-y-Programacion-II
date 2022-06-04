// cmdline - procesamiento de opciones en la línea de comando.

#include <string>
#include <cstdlib>
#include <iostream>
#include "cmdline.h"

using namespace std;

cmdline::cmdline()
{
}

cmdline::cmdline(option_t *table) : option_table(table)
{
}

void cmdline::parse(int argc, char * const argv[])
{
	
#define END_OF_OPTIONS(p)       \
	((p)->short_name == 0   \
	 && (p)->long_name == 0 \
	 && (p)->parse == 0)

	// Primer pasada por la secuencia de opciones: marcamos 
	// todas las opciones, como no procesadas. Ver código de
	// abajo.
	//
	for (option_t *op = option_table; !END_OF_OPTIONS(op); ++op)
		op->flags &= ~OPT_SEEN;

	// Recorremos el arreglo argv. En cada paso, vemos
	// si se trata de una opción corta, o larga. Luego,
	// llamamos a la función de parseo correspondiente.
	//
	for (int i = 1; i < argc; ++i) {
		// Todos los parámetros de este programa deben
		// pasarse en forma de opciones. Encontrar un
		// parámetro no-opción es un error.
		//
		if (argv[i][0] != '-') {
			cerr << "Invalid non-option argument: "
			     << argv[i]
			     << endl;
			exit(1);
		}

		// Usamos "--" para marcar el fin de las
		// opciones; todo los argumentos que puedan
		// estar a continuación no son interpretados
		// como opciones.
		//
		if (argv[i][1] == '-'
		    && argv[i][2] == 0)
			break;

		// Finalmente, vemos si se trata o no de una
		// opción larga; y llamamos al método que se
		// encarga de cada caso.
		//
		if (argv[i][1] == '-')
			i += do_long_opt(&argv[i][2], argv[i + 1]);
		else
			i += do_short_opt(&argv[i][1], argv[i + 1]);
	}

	// Segunda pasada: procesamos aquellas opciones que,
	// (1) no hayan figurado explícitamente en la línea 
	// de comandos, y (2) tengan valor por defecto.
	//
	for (option_t *op = option_table; !END_OF_OPTIONS(op); ++op) {
#define OPTION_NAME(op) \
	(op->short_name ? op->short_name : op->long_name)
		if (op->flags & OPT_SEEN)
			continue;
		if (op->flags & OPT_MANDATORY) {
			cerr << "Option "
			     << "-"
			     << OPTION_NAME(op)
			     << " is mandatory."
			     << "\n";
			exit(1);
		}
		if (op->def_value == 0)
			continue;
		op->parse(string(op->def_value));
	}
}

int
cmdline::do_long_opt(const char *opt, const char *arg)
{
	// Recorremos la tabla de opciones, y buscamos la
	// entrada larga que se corresponda con la opción de 
	// línea de comandos. De no encontrarse, indicamos el
	// error.
	//
	for (option_t *op = option_table; op->long_name != 0; ++op) {
		if (string(opt) == string(op->long_name)) {
			// Marcamos esta opción como usada en
			// forma explícita, para evitar tener
			// que inicializarla con el valor por
			// defecto.
			//
			op->flags |= OPT_SEEN;

			if (op->has_arg) {
				// Como se trada de una opción
				// con argumento, verificamos que
				// el mismo haya sido provisto.
				//
				if (arg == 0) {
					cerr << "Option requires argument: "
					     << "--"
					     << opt
					     << "\n";
					exit(1);
				}
				op->parse(string(arg));
				return 1;
			} else {
				// Opción sin argumento.
				//
				op->parse(string(""));
				return 0;
			}
		}
	}

	// Error: opción no reconocida. Imprimimos un mensaje
	// de error, y finalizamos la ejecución del programa.
	//
	cerr << "Unknown option: "
	     << "--"
	     << opt
	     << "."
	     << endl;
	exit(1);

	// Algunos compiladores se quejan con funciones que 
	// lógicamente no pueden terminar, y que no devuelven
	// un valor en esta última parte.
	//
	return -1;
}

int
cmdline::do_short_opt(const char *opt, const char *arg)
{
	option_t *op;

	// Recorremos la tabla de opciones, y buscamos la
	// entrada corta que se corresponda con la opción de 
	// línea de comandos. De no encontrarse, indicamos el
	// error.
	//
	for (op = option_table; op->short_name != 0; ++op) {
		if (string(opt) == string(op->short_name)) {
			// Marcamos esta opción como usada en
			// forma explícita, para evitar tener
			// que inicializarla con el valor por
			// defecto.
			//
			op->flags |= OPT_SEEN;

			if (op->has_arg) {
				// Como se trata de una opción
				// con argumento, verificamos que
				// el mismo haya sido provisto.
				//
				if (arg == 0) {
					cerr << "Option requires argument: "
					     << "-"
					     << opt
					     << "\n";
					exit(1);
				}
				op->parse(string(arg));
				return 1;
			} else {
				// Opción sin argumento.
				//
				op->parse(string(""));
				return 0;
			}
		}
	}

	// Error: opción no reconocida. Imprimimos un mensaje
	// de error, y finalizamos la ejecución del programa.
	//
	cerr << "Unknown option: "
	     << "-"
	     << opt
	     << "."
	     << endl;
	exit(1);

	// Algunos compiladores se quejan con funciones que 
	// lógicamente no pueden terminar, y que no devuelven
	// un valor en esta última parte.
	//
	return -1;
}


//Esta función está implementada ...
void
cmdline::parseOperacion(string str, Queue<string> *cola)
{
	Pila<string> pila;
	string aux, simbolo;
	string aux2="";
	
	if(!preParse(str))
		Errores::operacionInvalida();
             	
	unsigned int leng = str.size();
	
	unsigned int i=0;
	while (i < leng)
	{
		simbolo = str[i];
		
		if(isdigit(simbolo[0] )) //Si símbolo es un número ingreso al if
		{	
			int j=0;
			while( isdigit(simbolo[0]) || simbolo == "." || simbolo == NUMERO_IMAGINARIO ){
				aux2.insert(j,simbolo);
				j++;
				i++;
				simbolo = str[i];	
			}
			if(simbolo == NUMERO_IMAGINARIO)
			{
				aux2.insert(j,simbolo);
			}else{
				i--;
			}
			(*cola).enQueue(aux2);			// Agrego a la cola.
			aux2.clear();
			
		}else if(isalpha(simbolo[0])){
			
			if(simbolo == "p" && str[i+1] == NUMERO_IMAGINARIO[0])
			{
				simbolo.insert(1,"i");			//cargamos el valor pi
				(*cola).enQueue(simbolo);
				i++;
			}else if(simbolo == NUMERO_IMAGINARIO && !isalpha(str[i+1])){
				
				simbolo.insert(0,"1");					// Para cargar el valor "1i"			
				(*cola).enQueue(simbolo);				// Agregamos a la cola
			}else if(simbolo == VARIABLE_INDEPENDIENTE){ // Si simbolo es "z"
				(*cola).enQueue(simbolo);			// Agregamos a la cola
			}else{
				int j = 0;
				while(isalpha(simbolo[0]))
				{
					aux2.insert(j,simbolo);
					j++;
					i++;
					simbolo = str[i];	
				}
				i--;
				pila.push(aux2);			// Se agrega a la pila.	
				aux2.clear();				// Se limpia la variable aux2;				
			}
		}else if(simbolo == PARENTESIS_IZQUIERDO){
			pila.push(simbolo);			// Se agrega a la pila
		}
		else if(simbolo == PARENTESIS_DERECHO){
			while(pila.tope() != PARENTESIS_IZQUIERDO){
				aux = pila.tope();		
				pila.pop();				// Se quita a la pila
				(*cola).enQueue(aux);		// Se agrega a la cola
			}
			if(pila.tope() == PARENTESIS_IZQUIERDO)
			{
				pila.pop();			// eliminar el token y el "("			
			}
		}
		else if(simbolo ==OPERADOR_SUMA||simbolo ==OPERADOR_SUSTRACCION||simbolo ==OPERADOR_MULTIPLICACION||simbolo ==OPERADOR_DIVISION||simbolo ==OPERADOR_POTENCIA){
			if( (simbolo ==OPERADOR_SUMA||simbolo ==OPERADOR_SUSTRACCION) &&  i == 0)
			{				
				
				int j=0;
				aux2.insert(j,simbolo);
				j++;
				i++;
				simbolo = str[i];
				
				while( isdigit(simbolo[0]) || simbolo == "." || simbolo == NUMERO_IMAGINARIO ){
					aux2.insert(j,simbolo);
					j++;
					i++;
					simbolo = str[i];
				}
				if(simbolo == NUMERO_IMAGINARIO)
				{
					aux2.insert(j,"1");
					j++;
					aux2.insert(j,simbolo);
					i++;
					simbolo = str[i];
					
					if(simbolo == PARENTESIS_IZQUIERDO|| simbolo== PARENTESIS_DERECHO|| simbolo == "," ){
						(*cola).enQueue(aux2);			// Agrego a la cola.
						aux2.clear();
						continue;
					}
				}
				if(simbolo == VARIABLE_INDEPENDIENTE)
				{
					aux2.insert(j,simbolo);
					i++;
					simbolo = str[i];
					
					if(simbolo == PARENTESIS_IZQUIERDO|| simbolo== PARENTESIS_DERECHO|| simbolo == "," ){
						(*cola).enQueue(aux2);			// Agrego a la cola.
						aux2.clear();
						continue;
					}
				}
				if(simbolo == "p" && str[i+1] == NUMERO_IMAGINARIO[0])
				{
					aux2.insert(j,VARIABLE_PI);
					i=i+2;
					simbolo = str[i];
					if(simbolo == PARENTESIS_IZQUIERDO|| simbolo== PARENTESIS_DERECHO|| simbolo == "," ){
						(*cola).enQueue(aux2);			// Agrego a la cola.
						aux2.clear();
						continue;
					}
				}
				(*cola).enQueue(aux2);			// Agrego a la cola.
				aux2.clear();
			}else if( (simbolo == OPERADOR_SUMA||simbolo == OPERADOR_SUSTRACCION) && ( !isdigit(str[i-1]) && str[i-1] != NUMERO_IMAGINARIO[0]
						&& str[i-1] != VARIABLE_INDEPENDIENTE[0] && str[i-1] != PARENTESIS_DERECHO[0]) ){
				int j=0;
				aux2.insert(j,simbolo);
				j++;
				i++;
				simbolo = str[i];
			
				while( isdigit(simbolo[0]) || simbolo == "." || simbolo == NUMERO_IMAGINARIO ){
					aux2.insert(j,simbolo);
					j++;
					i++;
					simbolo = str[i];
				}
				if(simbolo == NUMERO_IMAGINARIO)
				{
					aux2.insert(j,"1");
					j++;
					aux2.insert(j,simbolo);
					i++;
					simbolo = str[i];
					if(simbolo == PARENTESIS_IZQUIERDO|| simbolo== PARENTESIS_DERECHO|| simbolo == "," ){
						(*cola).enQueue(aux2);			// Agrego a la cola.
						aux2.clear();
						continue;
					}
				}
				if(simbolo == VARIABLE_INDEPENDIENTE)
				{
					aux2.insert(j,simbolo);
					i++;
					simbolo = str[i];
					if(simbolo == PARENTESIS_IZQUIERDO|| simbolo== PARENTESIS_DERECHO|| simbolo == "," ){
						(*cola).enQueue(aux2);			// Agrego a la cola.
						aux2.clear();
						continue;
					}
				}
				if(simbolo == "p" && str[i+1] == NUMERO_IMAGINARIO[0])
				{
					aux2.insert(j,VARIABLE_PI);
					i=i+2;
					simbolo = str[i];
					if(simbolo == PARENTESIS_IZQUIERDO|| simbolo== PARENTESIS_DERECHO|| simbolo == "," ){
						(*cola).enQueue(aux2);			// Agrego a la cola.
						aux2.clear();
						continue;
					}
				}
				(*cola).enQueue(aux2);			// Agrego a la cola.
				aux2.clear();
			}
			if(simbolo == PARENTESIS_IZQUIERDO|| simbolo== PARENTESIS_DERECHO || simbolo == "," ){
				continue;
			}
			while ((!pila.vacia()) && (precedencia(pila.tope(),simbolo) <= 0)  && (pila.tope() != PARENTESIS_IZQUIERDO))
			{
				aux = pila.tope();		// Se lee el tope
				pila.pop();		// Se quita a la pila
				(*cola).enQueue(aux);		// Se agrega a la cola
			}
			pila.push(simbolo);			// Se agrega a la pila
		}
		i++;
	}
	if (i == leng)
	{		
			while(!pila.vacia())
			{	
				
				aux = pila.tope();
				if(aux == PARENTESIS_IZQUIERDO || aux == PARENTESIS_DERECHO)
				{
					Errores::operacionInvalida();
				}
				pila.pop();			// Se quita a la pila
				(*cola).enQueue(aux);		// Se agrega a la cola
			}
	}
}

/* Función que:
 * retorna -1 si el operador1 tiene mayor precedencia que el operador2
 * retorna 0 si el operador1 tiene la misma precedenica que el operador2
 * retorna 1 si el operador1 tiene menor precedencia que el operador 2
*/
 
int	cmdline::precedencia(string operador1, string operador2)
{
	if( (operador1==OPERADOR_SUMA||operador1==OPERADOR_SUSTRACCION) && (operador2==OPERADOR_MULTIPLICACION||operador2==OPERADOR_DIVISION||operador2==OPERADOR_POTENCIA) )
	{
		return 1;
	}else if( (operador1==OPERADOR_MULTIPLICACION||operador1==OPERADOR_DIVISION||operador1==OPERADOR_POTENCIA) && (operador2==OPERADOR_SUMA||operador2==OPERADOR_SUSTRACCION) ){
	
		return -1;
	}else if( (operador1==OPERADOR_MULTIPLICACION||operador1==OPERADOR_DIVISION) && (operador2==OPERADOR_POTENCIA) ){
		return 1;
	}else if( (operador1==OPERADOR_POTENCIA) && (operador2==OPERADOR_MULTIPLICACION||operador2==OPERADOR_DIVISION) ){
		return -1;
	}else return 0;							// Encaso de que los operadores tengan igual precedencia.
}



bool cmdline::preParse(string st){

    if(st.length() == 0) //Si la cadena esta vacia
        return false;

    int i=0, open=0;
    string aux="";

    while(st[i] != '\0'){
        if(isdigit(st[i]) == 0){ //Si no es un numero.
            if((isalpha(st[i]) != 0) && (st[i] != VARIABLE_INDEPENDIENTE[0])){ //Si es una letra distinta de z
                if(st[i] == NUMERO_IMAGINARIO[0])
                    i++;
                else{ //Si no es una i
                    while(isalpha(st[i]) != 0){ //Mientras sea una letra guarda en aux lo que hay en st caracter a caracter
                        aux.push_back(st[i]);
                        i++;
                    }
                    if(aux != FUNCION_SENO && aux != FUNCION_COSENO && aux != FUNCION_EXPONENCIAL && aux != FUNCION_LOGARITMO &&
                       aux != FUNCION_REAL && aux != FUNCION_IMAGINARIA && aux != FUNCION_ABS && aux != FUNCION_PHASE &&
                       aux != FUNCION_MAX && aux != VARIABLE_PI && st[i] != PARENTESIS_IZQUIERDO[0])
                        return false;

                    if(aux != VARIABLE_PI){

                        i++;

                        aux.clear();

                        while(st[i] != PARENTESIS_DERECHO[0] || open != 0){ //Mientras no sea ')' ni fin de la cadena --> guarda el caracter actual en aux y avanza.
                            if(st[i] == '\0')
                                return false;
                            aux.push_back(st[i]);
                            if(st[i] == PARENTESIS_IZQUIERDO[0])
                                open++;
                            else if(st[i] == PARENTESIS_DERECHO[0])
                                open--;
                            i++;
                        }
                        if(!preParse(aux))
                            return false;
                        i++;
                    }
                }
            }else{

                if(st[i] != OPERADOR_SUMA[0] && st[i] != OPERADOR_SUSTRACCION[0] && st[i] != OPERADOR_MULTIPLICACION[0] && st[i] != OPERADOR_DIVISION[0]
                   && st[i] != OPERADOR_POTENCIA[0] && st[i] != VARIABLE_INDEPENDIENTE[0] && st[i] != PARENTESIS_IZQUIERDO[0] && st[i] != '.')
                    return false;

                aux.clear();

                if(st[i] == PARENTESIS_IZQUIERDO[0]){ //Si es un '(' va guardando hasta que encuentre ')' o llegue al final de la cadena
                    i++;
                    while(st[i] != PARENTESIS_DERECHO[0] && st[i] != '\0'){
                        aux.push_back(st[i]);
                        i++;
                    }
                    if(st[i] != PARENTESIS_DERECHO[0]) //Si llego al final sin encontrar el ')' --> Devuelve falso
                        return false;
                    else{ //Si encontro el ')' --> Llama recursivamente a la funcion y le pasa lo guardado en aux.
                        if(!preParse(aux))
                            return false;
                        i++;
                    }
                }

                else if(st[i] == '.'){
                    if(isdigit(st[i+1]) == 0)
                        return false;
                    i++;
                }

                else if(st[i] == OPERADOR_SUSTRACCION[0]){
                    i++;
                }
                else{ //Si es un operador válido distinto del - y no es una z o un '(' o un '.'
                    if(i == 0 && st[i] != VARIABLE_INDEPENDIENTE[0])
                        return false;

                    if(st[i] != VARIABLE_INDEPENDIENTE[0] && isdigit(st[i+1]) == 0 && st[i+1] != VARIABLE_INDEPENDIENTE[0] && st[i+1] != '.' && st[i] != '\0'){ //Si es distinto de z y el que le sigue no es un numero ni la variable z ni el numero i, ni \0
                        if(isalpha(st[i+1]) == 0 && st[i+1] != '(')
                            return false;
                    }
                    i++;
                }
            }
        }else if(st[i] != '\0') //Si es un numero --> avanza
            i++;
    }
    return true;
}
