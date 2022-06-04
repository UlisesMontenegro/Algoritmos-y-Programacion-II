#include "main.h"

using namespace std;


static option_t options[] = {
	{1, "i", "input", "-", opt_input, OPT_DEFAULT},
	{1, "o", "output", "-", opt_output, OPT_DEFAULT},
	{1, "f", "function", "-", opt_function, OPT_DEFAULT},
	{0, "h", "help", NULL, opt_help, OPT_DEFAULT},
	{0, },
};


static istream *iss = 0;	// Input stream objects (clase para manejo de los flujos de entrada)
static ostream *oss = 0;	// Output Stream objects(clase para manejo de los flujos de salida)
static fstream ifs; 		// File Stream (para el manejo de archivos)
static fstream ofs;			// File Stream (para el manejo de archivos)
static string fun;			//String para manejo de la función de entrada

static void
opt_input(string const &arg)
{
	// Si el nombre del archivos es "-", usaremos la entrada
	// estándar. De lo contrario, abrimos un archivo en modo
	// de lectura.
	//
	if (arg == "-") {
		iss = &cin;		// Asignamos la entrada estandar cin como flujo de entrada.
	}
	else {
		ifs.open(arg.c_str(), ios::in);  // Abrimos el archivo de entrada.
		iss = &ifs;						// Asignamos el archivo leido al flujo de entrada.
	}

	// Verificamos que el stream este OK.
	//
	if (!iss->good()) {
		cerr << "cannot open "
		     << arg
		     << "."
		     << endl;
		exit(1);
	}
}

static void
opt_output(string const &arg)
{
	// Si el nombre del archivos es "-", usaremos la salida
	// estándar. De lo contrario, abrimos un archivo en modo
	// de escritura.
	//
	if (arg == "-") {
		oss = &cout;	// Asignamos la salida estandar cout como flujo de salida.
	} else {
		ofs.open(arg.c_str(), ios::out); //Abrimos y/o creamos el archivo de salida
		oss = &ofs;		// Asignamos el archivo como flujo de salida.
	}

	// Verificamos que el stream este OK.
	//
	if (!oss->good()) {
		cerr << "cannot open "
		     << arg
		     << "."
		     << endl;
		exit(1);		
	}
}

static void
opt_function(string const &arg)
{
	// Si el nombre del archivos es "-", usaremos la función por defecto
	//de lo contrario, guardamos en un string la función que se va a evaluar.
	//
	
	if (arg == "-") {
		fun = "z";		// Asignam la función por default "En este caso f(z)=z"
	}
	else {
		fun = arg; // Asignamos la función pasada por línea de comandos.
	}
}

static void
opt_help(string const &arg)
{
	cout << "cmdline [-i file] [-o file] [-f fuction]"
	     << endl;
	exit(0);
}

int main(int argc, char * const argv[])
{
    cmdline cmdl(options);	// Inicializamos el objeto con parametro tipo option_t.
	cmdl.parse(argc, argv); // Parseamos argv.
	Imagen imgEntrada(*iss); // Inicializamos los datos de la imagen recibida por el flujo de entrada.
	
	// Construimos la imagen de salida con las mismas dimensiones que la imagen de entrada.
	Imagen imgSalida(imgEntrada.getAncho(),imgEntrada.getAlto(),imgEntrada.getIntensidadMax());
	
	Queue<string> cola;
	
	cmdl.parseOperacion(fun, &cola);	// Parseamos la operación pasada por línea de comandos.	
	
	imgEntrada.operar(imgSalida,&cola);  // Realiazamos la operación.
	
	imgSalida.print(*oss);				// Imprimimos la imagen por el flujo de salida.
		
	return 0;
}
