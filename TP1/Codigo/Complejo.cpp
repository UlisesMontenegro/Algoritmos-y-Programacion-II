#include "Complejo.h"
#include <cmath>

Complejo::Complejo(){
    real = 0.0;
    imaginario = 0.0;
}

Complejo::Complejo(const Complejo &c){
    real = c.real;
    imaginario = c.imaginario;
}

Complejo::Complejo(double re, double im){
    real = re;
    imaginario = im;
}

Complejo::Complejo(double re){
    real = re;
    imaginario = 0.0;
}

Complejo::Complejo(string str){
	int i = 0;
	string aux="";
	string aux_imaginario;
	string aux_real;
	double num;

	if(str == VARIABLE_PI || str == VARIABLE_PI_NEGADO || str == "+pi")
	{
		if (str == VARIABLE_PI_NEGADO)
			real = -M_PI;
		else{
			real = M_PI;
		}
		imaginario = 0.0;
		
	}else if (str.back() == NUMERO_IMAGINARIO[0] && str[str.size()-2] != VARIABLE_PI[0]){
		if(str[0] == OPERADOR_SUSTRACCION[0]) // Entra sólo si str = -i
		{
			real = 0.0;
			imaginario = 0.1;
			
		}else{
			num = stod(str);		// Convertimos el número a un double.
			// Generamos el número complejo
			real = 0.0;
			imaginario = num;
		}
	}else{

		while ( str[i] != '\0')
		{
			aux = aux+str[i];
			if (str[i+1] == ' '|| str[i+1] == '\0')
			{
				aux_real = aux;
				aux.clear(); // Limpio la variable aux
				i++;
				while ( str[i] != '\0')
				{	
					if(str[i] ==' ')
						i++;
					aux = aux+str[i];
					i++;
				}
				aux_imaginario = aux;
				i--;
			}
			i++;
		}
		
		// una vez obtengo aux_real y aux_imaginario
		
		if(aux_real == VARIABLE_PI || aux_real == VARIABLE_PI_NEGADO||aux_imaginario == VARIABLE_PI || aux_imaginario ==VARIABLE_PI_NEGADO)
		{
			if (aux_real ==VARIABLE_PI_NEGADO)
				real = -M_PI;
			else if (aux_real ==VARIABLE_PI)
				real = M_PI;
			if (aux_imaginario ==VARIABLE_PI_NEGADO)
				imaginario = -M_PI;
			else if (aux_imaginario ==VARIABLE_PI)
				imaginario = M_PI;
		}
		else{
			num = stod(aux_real);		// Convertimos el número a un double.
			real = num;
			if(aux_imaginario[0] == '\0')
			{
				imaginario = 0.0;
			}else{
				num = stod(aux_imaginario);
				imaginario = num;
			}
		}
	}
}



Complejo::~Complejo(){
}

void Complejo::setReal(double r){
    real = r;
}

void Complejo::setImag(double i){
    imaginario = i;
}

double Complejo::getReal(){
    return real;
}

double Complejo::getImag(){
    return imaginario;
}



string Complejo::aString()
{
	string aux;
	string aux_real = "", aux_imaginario="";
	
	if( (fabs(real) == M_PI || fabs(imaginario) == M_PI))
	{
		if (real == M_PI)
			aux_real = VARIABLE_PI;
		else if (real == -M_PI)
			aux_real = VARIABLE_PI_NEGADO;
		else 
			aux_real = to_string(real);
		if (imaginario == M_PI)
			aux_imaginario = VARIABLE_PI;
		else if(imaginario == -M_PI)
			aux_imaginario = VARIABLE_PI_NEGADO;
		else
			aux_imaginario = to_string(imaginario);
		aux = aux_real+' '+aux_imaginario;
	}else
		aux= to_string(real)+' '+to_string(imaginario);
	return aux;
}

Complejo Complejo::aplicarFuncion(string fun){ //Aplica la funcion a this y devuelve otro Complejo (modulo y fase devuelven otro Complejo!=this). Si no es una funcion, devuelve this.
    Complejo aux;
    if(fun == FUNCION_EXPONENCIAL){
        aux = (this->expc());
        return aux;
    }
    else if(fun == FUNCION_SENO){
        aux = (this->sinc());
        return aux;
    }
    else if(fun == FUNCION_COSENO){
        aux = (this->cosc());
        return aux;
    }
    else if(fun == FUNCION_LOGARITMO){
        aux = (this->lnc());
        return aux;
    }else if(fun == FUNCION_REAL){
        aux = (Complejo)(this->getReal());
        return aux;
    }else if(fun == FUNCION_IMAGINARIA){
        aux = (Complejo)(this->getImag());
        return aux;
    }
    else if(fun == FUNCION_ABS){
        aux = (Complejo)(this->modulo());
        return aux;
    }
    else if(fun == FUNCION_PHASE){
        aux = (Complejo)(this->phase());
        return aux;
    }
    else
        return (*this);
}

Complejo Complejo::aplicarOperador(Complejo &c, string op){ //Aplica el operador entre this y c, devuelve this modificado. Si no es ningun operador, devuelve this.
    Complejo aux;
    if(op == OPERADOR_SUMA){
        aux = ((*this)+c);
        return aux;
    }
    else if(op == OPERADOR_SUSTRACCION){
        aux = ((*this)-c);
        return aux;
    }
    else if(op == OPERADOR_MULTIPLICACION){
        aux = ((*this)*c);
        return aux;
    }
    else if(op == OPERADOR_DIVISION){
        aux = ((*this)/c);
        return aux;
    }
    else if(op == OPERADOR_POTENCIA){
        aux = (*this)^(int)c;
        return aux;
    }
    else
        return (*this);
}



Complejo Complejo::conjugado(){
    Complejo aux;
    aux.real = this->real;
    aux.imaginario = (this->imaginario * (-1));
    return aux;
}

Complejo Complejo::expc()
{
	//cout<<" expc"<<endl;
	Complejo aux(0.0, 0.0);
    aux.real = exp(real)*cos(imaginario);
    aux.imaginario = exp(real)*sin(imaginario);
    //cout<<"espc: sin (imaginario) "<<sin(imaginario)<<endl;
    //cout<<"espc: cos (imaginario) "<<cos(imaginario)<<endl;
    return aux;
}

Complejo Complejo::identidad(){
	Complejo aux(0.0, 0.0);
	aux.real = real;
	aux.imaginario = imaginario;
	return aux;
}

Complejo Complejo::sinc(){
    Complejo aux;
    aux.real = (sin(this->real)*cosh(this->imaginario));
    aux.imaginario = (cos(this->real)*sinh(this->imaginario));
    return aux;
}

Complejo Complejo::cosc(){
    Complejo aux;
    aux.real = (cos(this->real)*cosh(this->imaginario));
    aux.imaginario = -(sin(this->real)*sinh(this->imaginario));
    return aux;
}

Complejo Complejo::lnc(){
    Complejo aux;
    aux.real = log(this->modulo());
    aux.imaginario = this->phase();
    return aux;
}


double Complejo::modulo(){
    double aux = real*real + imaginario*imaginario;
    return sqrt(aux);
}

double Complejo::phase(){
    if(real == 0 && imaginario == 0)
        return 0;
    if(real < 0){
        if(imaginario > 0)
            return (M_PI + (atan(imaginario/real)));
        if(imaginario < 0)
            return (-M_PI + (atan(imaginario/real)));
        return M_PI;
    }
    return atan(imaginario/real);
}


Complejo Complejo::operator+(Complejo c){
    Complejo aux;
    aux.real = (this->real + c.real);
    aux.imaginario = (this->imaginario + c.imaginario);
    return aux;
}

Complejo Complejo::operator-(Complejo c){
    Complejo aux;
    aux.real = (this->real - c.real);
    aux.imaginario = (this->imaginario - c.imaginario);
    return aux;
}

Complejo Complejo::operator-(){
    Complejo aux;
    aux.real = -(this->real);
    aux.imaginario = -(this->imaginario);
    return aux;
}

Complejo Complejo::operator*(Complejo c){
    Complejo aux;
    aux.real = ((this->real * c.real) - (this->imaginario * c.imaginario));
    aux.imaginario = ((this->real * c.imaginario) + (this->imaginario * c.real));
    return aux;
}

Complejo Complejo::operator/(Complejo c){
    Complejo aux, aux2;
    aux2 = (*this * (c.conjugado()));
    aux = (c * (c.conjugado()));
    aux.imaginario = (aux2.imaginario / aux.real);
    aux.real = (aux2.real / aux.real);
    return aux;
}

Complejo Complejo::operator^(int i){
    if(i<0)
        return ((Complejo)1/((*this)^(-i)));
    if(i == 0)
        return Complejo(1, 0);
    Complejo aux;
    if(i/2 < 1){
        aux = *this;
        return aux;
    }
    int aux2 = i/2;
    aux = (this->pow2());
    for(int j=1; j<aux2; j++)
        aux = aux * (this->pow2());
    if(i%2 == 1)
        return aux*(*this);
    return aux;
}

Complejo &Complejo::operator=(const Complejo &c){
    real = c.real;
    imaginario = c.imaginario;
    return *this;
}

bool Complejo::operator==(Complejo &c){
    if(real == c.getReal()){
        if(imaginario == c.getImag())
            return true;
    }
    return false;
}

Complejo::operator int(){
    return (int)real;
}



Complejo Complejo::pow2(){
	Complejo aux(0.0, 0.0);
	aux.real = real*real-imaginario*imaginario;
	aux.imaginario = 2*real*imaginario;
	return aux;
}
