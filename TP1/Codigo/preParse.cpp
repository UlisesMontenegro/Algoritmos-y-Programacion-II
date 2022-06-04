#include <iostream>
#include <string>
#include <string.h>
#include <cctype>
#include "constantes.h"

using namespace std;

bool preParse(string);

int main(){
    string fun;
    cin>>fun;

    if(preParse(fun))
        cout<<"La sentencia es correcta"<<endl;
    else
        cout<<"La sentencia es incorrecta"<<endl;

   //system("pause");

    return 0;
}

bool preParse(string st){

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
                       aux != FUNCION_MAX && aux != STR_PI && st[i] != PARENTESIS_IZQUIERDO[0])
                        return false;

                    if(aux != STR_PI[0]){

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
