#include <fstream>
#include <iostream>

struct SaldoColaborador {
	char rut[11];
	int saldo_desayuno;
	int saldo_almuerzo;
	int saldo_once;
	int saldo_cena;
};

int main(int argc, char const *argv[])
{
    std::fstream saldos_file;
    SaldoColaborador Colaborador;

    saldos_file.open("saldos.bin", std::ios::binary | std::ios::out);

    int n;
    std::cin >> n;

    saldos_file.write((char *) &n, sizeof(int));

    for (int i = 0; i < n; i++)
    {
        std::cout << "Ingrese Colaborador " << i << std::endl;
        std::cin >> Colaborador.rut;
        std::cin >> Colaborador.saldo_desayuno;
        std::cin >> Colaborador.saldo_almuerzo;
        std::cin >> Colaborador.saldo_once;
        std::cin >> Colaborador.saldo_cena;
        saldos_file.write((char*) &Colaborador, sizeof(SaldoColaborador));
    }
    
    saldos_file.close();

    return 0;
}
