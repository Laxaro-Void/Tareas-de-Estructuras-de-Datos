#include <iostream>
#include <fstream>
#include <cstring>

const int SERV_DESAYUNO = 0;
const int SERV_ALMUERZO = 1;
const int SERV_ONCE = 2;
const int SERV_CENA = 3;

struct SaldoColaborador {
	char rut[11];
	int saldo_desayuno;
	int saldo_almuerzo;
	int saldo_once;
	int saldo_cena;
};

bool puedeConsumir(char * rut, int servicio, std::string consumos_dia)
{
	/*******************************************************************************************************************
	 * bool puedeConsumir
	 * *****************************************************************************************************************
	 * Extrae informacion de los archivos "saldos.bin" y "consumos_dia" sobre un rut dado,
	 * verifica si el rut posee tickets disponibles del servicio solicitado
	 * escribe en "consumos_dias" si y solo si el rut posee tickets del servicio solicitado
	 * y retornara un bool true si lo anterior se cumple o false de lo contrario
	 * 
	 * Importante: Retorna false si no se pudo abrir el archivo, e imprime por pantalla cual fue.
	 * *****************************************************************************************************************
	 * 	Imput:
	 * 		char * rut	:	Cadena de forma NNNNNNNN-D tal que N es un numero y D un numero o la letra k, es el rut cual se buscara en los archivos
	 * 		int servicio	:	Numero entre 0 y 3 cual representa el servicio solicitado por el rut
	 * 		std::string consumos_dias	:	Un string dado cual es el archivo correspondiente al dia, es donde se consigue el registro del dia dado por la maquina
	 * *****************************************************************************************************************
	 * 	Returns:
	 * 		bool	:	Es True si y solo si el saldo de Rut es disponible para el servicio, False de lo contrario o si algun archivo no pudo abrir correctamente
	 * 		std::fstream <<	:	Cuando el retorno es True, se escribe en el archivo "consumos_dia" el Rut y el tipo de servicio solicitado.
	*******************************************************************************************************************/

	//Definir dos archivos.
	std::fstream file_consumos;
	std::fstream file_saldos;
	file_consumos.open(consumos_dia, std::ios::in);
	file_saldos.open("saldos.bin", std::ios::out | std::ios::app | std::ios::in | std::ios::binary);

	//Siempre verificar si se abrieron correctamente, retornar falso.
	if (!file_consumos.is_open())
	{
		std::cout << "Could not open File: " << consumos_dia << std::endl;
		return false;
	}
	if (!file_saldos.is_open())
	{
		std::cout << "Could not open File: " << "saldos.bin" << std::endl;
		return false;
	}

	//Extraer datos del archivo binario
	int n;
	bool si_existe = false;
	SaldoColaborador Colaborador;

	file_saldos.read((char *) &n, sizeof(int));	//extraer n
	
	//Recorrer los Structs binarios para encontrar el RUT ingresado
	for (int i = 0; i < n; i++)
	{
		file_saldos.read((char *) &Colaborador, sizeof(SaldoColaborador));	//Extraer Struct de SaldoColaborador
		if (strcmp(Colaborador.rut, rut) == 0)	//Compara el Rut extraido con el ingresado, "strncmp" retorna 0 si son iguales
		{	
			si_existe = true;	//Recordar si exite Rut
			break;
		}
	}

	if (!si_existe)	//Si no existe, establece Colaborador a 0 con su RUT
	{
		strcpy(Colaborador.rut, rut);	//Copia el parametro rut en el Colaborador
		Colaborador.saldo_almuerzo = 0;
		Colaborador.saldo_cena = 0;
		Colaborador.saldo_desayuno = 0;
		Colaborador.saldo_once = 0;

	} else { //Si existe, buscar los consumos diarios en caso de no estar los datos
		//Lectura de los Consumos del Dia
		std::string dataLine;	//Extraccion de la linea
		int longitud;
		char dataRut[11];		//Almacenar Rut extraido
		char * dataServicio;	//Almacenar Servicio extraido, tamanio variable para el uso de memoria

		while(!file_consumos.eof())	//Recorrer el Archivo hasta el final
		{
			std::getline(file_consumos, dataLine); //12345678-9 __SERVICIO__
			longitud = dataLine.length();

			if (longitud == 0) //Caso de dataLine vacia
				continue;
			
			dataServicio = new char[longitud -9];	//Localiza segun el tamanio del servicio contenido en dataLine

			strcpy(dataRut, dataLine.substr(0, 10).c_str());	//Copia contenido de RUT, tamanio fijo, c_str() retorna puntero de version cString
			strcpy(dataServicio, dataLine.substr(11, longitud-1).c_str());	//Copia contenido de __SERVICIO__, tamanio variable

			if(strcmp(Colaborador.rut, dataRut) == 0)	//Compara el Rut del Colaborador con lo extraido
			{
				//Solo es necesario comparar unicamente la Primera Letra, todas diferentes
				if (dataServicio[0] == 'D')		//Desayuno
				{
					Colaborador.saldo_desayuno--;
				}
				else if (dataServicio[0] == 'A')	//Almuerzo
				{
					Colaborador.saldo_almuerzo--;
				}
				else if (dataServicio[0] == 'O')	//Once
				{
					Colaborador.saldo_once--;
				}
				else if(dataServicio[0] == 'C')		//Cena
				{
					Colaborador.saldo_cena--;
				}
			}

			delete[] dataServicio;		//Siempre desalocar memoria dinamica
			dataServicio = NULL;		//Recomendable cambiar puntero a NULL
		}
	}

	//Reinicia el fstream para la escritura
	file_consumos.close();
	file_consumos.open(consumos_dia, std::ios::app);	//Establecer modo de agregar al final
	//Siempre verificar si se abrieron correctamente, retornar falso.
	if (!file_consumos.is_open())
	{
		std::cout << "Could not open File: " << consumos_dia << std::endl;
		return false;
	}

	bool si_disponible = true;	//Variable de retorno

	switch(servicio)	//Seleccion de Caso unico dependiendo de Servicio de entrada, igual logica
	{
	case SERV_DESAYUNO:
		if(Colaborador.saldo_desayuno <= 0)		//Si no posee tickets disponible
		{
			si_disponible = false;
			break;
		}

		file_consumos << Colaborador.rut << " DESAYUNO" << std::endl;	//Escritura en Consumos del Dia
		break;

	case SERV_ALMUERZO:
		if(Colaborador.saldo_almuerzo <= 0)
		{
			si_disponible = false;
			break;
		}
	
		file_consumos << Colaborador.rut << " ALMUERZO" << std::endl;
		break;

	case SERV_ONCE:
		if (Colaborador.saldo_once <= 0)
		{
			si_disponible = false;
			break;
		}

		file_consumos << Colaborador.rut << " ONCE" << std::endl;
		break;

	case SERV_CENA:
		if (Colaborador.saldo_cena <= 0)
		{
			si_disponible = false;
			break;
		}
		
		file_consumos << Colaborador.rut << " CENA" << std::endl;
		break;
	}

	//Siempre cerrar archivos
	file_consumos.close();
	file_saldos.close();
	
	return si_disponible;
}

int main(int argc, char const *argv[])
{
	//Contenido de saldos.bin
	char rut_0[] = "00000000-0"; //0 0 0 0
	char rut_1[] = "11111111-1"; //1 1 1 1
	char rut_2[] = "22222222-2"; //2 2 2 2
	// char rut_3[] = "33333333-3"; //3 3 3 3
	char rut_4[] = "44444444-4"; //2 2 2 0
	char rut_5[] = "55555555-5"; //No existe

	std::string file = "consumos_dias.txt";
	/* Contenido de consumos_dias.txt
	22222222-2 DESAYUNO
	22222222-2 DESAYUNO
	22222222-2 ONCE
	22222222-2 ONCE
	33333333-3 ALMUERZO
	44444444-4 DESAYUNO
	44444444-4 ALMUERZO
	44444444-4 ONCE
	44444444-4 ALMUERZO

	*/

	std::cout << "00000000-0" << std::endl;
	std::cout << puedeConsumir(rut_0, 0, file) << std::endl; //false
	std::cout << puedeConsumir(rut_0, 1, file) << std::endl; //false
	std::cout << puedeConsumir(rut_0, 2, file) << std::endl; //false
	std::cout << puedeConsumir(rut_0, 3, file) << std::endl; //false

	std::cout << "11111111-1" << std::endl;
	std::cout << puedeConsumir(rut_1, 0, file) << std::endl; //true
	std::cout << puedeConsumir(rut_1, 1, file) << std::endl; //true
	std::cout << puedeConsumir(rut_1, 2, file) << std::endl; //true
	std::cout << puedeConsumir(rut_1, 3, file) << std::endl; //true

	std::cout << "2222222-2" << std::endl;
	std::cout << puedeConsumir(rut_2, 0, file) << std::endl; //false 2 desayuno en txt
	std::cout << puedeConsumir(rut_2, 1, file) << std::endl; //true
	std::cout << puedeConsumir(rut_2, 2, file) << std::endl; //false 2 once en txt
	std::cout << puedeConsumir(rut_2, 3, file) << std::endl; //true

	std::cout << "44444444-4" << std::endl;
	std::cout << puedeConsumir(rut_4, 0, file) << std::endl; // true 1 desayuno en txt
	std::cout << puedeConsumir(rut_4, 1, file) << std::endl; // false 2 almuerzo en txt
	std::cout << puedeConsumir(rut_4, 2, file) << std::endl; // true 1 once en txt
	std::cout << puedeConsumir(rut_4, 3, file) << std::endl; // false

	std::cout << "5555555-5" << std::endl;
	std::cout << puedeConsumir(rut_5, 0, file) << std::endl; //false no existe en bin
	std::cout << puedeConsumir(rut_5, 1, file) << std::endl; //false no existe en bin
	std::cout << puedeConsumir(rut_5, 2, file) << std::endl; //false no existe en bin
	std::cout << puedeConsumir(rut_5, 3, file) << std::endl; //false no existe en bin

	return 0;
}
