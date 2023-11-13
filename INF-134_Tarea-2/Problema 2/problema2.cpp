#include <iostream>
#include <string>

#include "ABB.cpp"

#define EXIT -1
#define ENCENDER 1
#define CUANTOS_ENCENDER 2

using namespace std;

/**
 * void encender(tElem i, ABB &postersOn)
 * ***
 * Registra un poster i como ecendido insertandolo en un ABB
 * O(1)
 * ***
 * Inputs:
 *      tElem x    :    Poster a ecender
 *      ABB &postersOn    :     Referencia del registro de los posters
**/
void encender(tElem i, ABB &postersOn){
    postersOn.insert(i);
}

/**
 * void cuantos_encender(tElem i, ABB &posterON)
 * ***
 * Muetra por pantalla cuantos poster estan apagado entre un poster i y
 * el ecendido mas cercano menor o igual a i.
 * O(log n)
 * ***
 * Inputs:
 *      tElem i    :    poster a consultar
 *      ABB &postersOn    :     Referencia del registro de los posters
 * ***
 * Return:
 *      Salida por pantalla del numero de poster apagados
**/
void cuantos_encender(tElem i, ABB &posterON){
    if (posterON.lower_boud(i) == -1) { //Si no existe un menor o igual
        cout << i + 1 << endl;

    } else {
        cout << i - posterON.lower_boud(i) << endl;
    }
}

/**
 * void parar_programa(ABB &posterON)
 * ***
 * Muestra por pantalla cuantos poster estan encendido
 * O(1)
 * ***
 * Inputs:
 *      ABB &postersOn    :     Referencia del registro de los posters
 * ***
 * Return:
 *      Salida por pantalla del numero de poster ecendido
**/
void parar_programa(ABB &posterON){
    cout << posterON.getSize() << endl;
}

int main(int argc, char const *argv[])
{   
    int state = -1; // Estado del programa
    int i;  // Poster de entrada
    string comandInput; // Linea de comando de entrada
    
    ABB postersON;  // Registro de posters ecendidos
    
    do
    {
        cin >> comandInput; //  Recibir entrada de comando
        
        if (!comandInput.compare("CUANTOS_ENCENDER"))
        {
            state = CUANTOS_ENCENDER;   //  Cambiar estado del programa
            cin >> i;   //  Recibir entrada de poster
            cuantos_encender(i, postersON);    //   Comando de accion

        } else if (!comandInput.compare("ENCENDER"))
        {
            state = ENCENDER;
            cin >> i;
            encender(i, postersON);

        } else if (!comandInput.compare("PARAR_PROGRAMA"))
        {
            state = EXIT;
            parar_programa(postersON);
        }

    } while (state != -1);

    return 0;
}
