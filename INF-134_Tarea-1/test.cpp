#include <string>
#include <iostream>
#include <cstring>
#include <fstream>

struct SaldoColaborador {
	char rut[11];
	int saldo_desayuno;
	int saldo_almuerzo;
	int saldo_once;
	int saldo_cena;
};


int main(int argc, char const *argv[])
{
    std::fstream file;
	file.open("consumos_dias.txt", std::ios::in | std::ios::app);

	SaldoColaborador Colaborador;
	strcpy(Colaborador.rut, "66666666-6");
	
	file << Colaborador.rut << " Almuerzo" << std::endl;

    return 0;
}
