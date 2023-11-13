#include <iostream>
#include <fstream>
#include <cstring>

struct Persona
{
    std::string nombre;
    char fecha[11]; //AAAA-MM-DD
    int tamanio_tarjeta = 0;
    int * tarjeta = NULL;
    bool quiere_intercambiar;
};

int Global_nPersonas;   //Variable Global, Largo de array de Personas

int * comprarTarjeta(std::string nombre, int dia, int &m)
{
    /****************************************
     * int * comprarTarjeta
     * **************************************
     * Crea un array de enteros segun el tamanio del std::string nombre
     * Asigna valores a cada elemenmto del array segun modulo del valor ASCII del nombre y el dia
     * **************************************
     *  Input:
     *      std::string nombre  :   Nombre de la persona que recibe la tarjeta
     *      int dia     :   Numero del dia para el calculo del valor de la tarjeta
     *      int &m  :   Referencia de entero para retornar el tamanio de la tarjeta
     * **************************************
     * Returns:
     *      int *   :   La direccion de memoria de la tarjeta, se tiene que asignar a un puntero
     *      Paso por referencia int &m  :   Tamanio de la tarjeta retornada, se tiene que asignar para iterar por la tarjeta
     ***************************************/

    m = nombre.length();
    int * tarjeta = new int[m];

    for (int i = 0; i < m; i++)
    {
        tarjeta[i] = nombre[i]%dia;
    }

    return tarjeta;
}

void intercambiarTarjeta(Persona * p1, Persona * p2)
{
    /***************************************
     * void intercambiarTarjeta
     * *************************************
     * Intercambia las tarjetas de las personas dado por los parametros siempre y cuando exista un numero igual en ambas tarjetas
     * *************************************
     * Input:
     *  Persona * p1    :   Direccion de Persona 1
     *  Persona * p2    :   Direccion de Persona 2
     * *************************************
     * Returns:
     *      Funcion metodo, genera cambios en Persona p1 y p2, intercambiando int * tarjeta y int tamanio_tarjeta.
    ***************************************/

    //Verificar si exite un numero en comun en las tarjetas
    bool puede_intercambiar = false;

    for (int i = 0; i < p1->tamanio_tarjeta || !puede_intercambiar; i++)
    {
        for (int j = 0; j < p2->tamanio_tarjeta; j++)
        {
            if (p1->tarjeta[i] == p2->tarjeta[j])
            {
                puede_intercambiar = true;
                break;
            }
        }
    }
    
    int * tempPointer;  //Puntero temporal para el intercambio
    int tempTamanio;    //Int temporal para el intercambio

    if (puede_intercambiar)
    {
        tempPointer = p1->tarjeta;
        tempTamanio = p1->tamanio_tarjeta;

        p1->tarjeta = p2->tarjeta;
        p1->tamanio_tarjeta = p2->tamanio_tarjeta;

        p2->tarjeta = tempPointer;
        p2->tamanio_tarjeta = tempTamanio;

        p1->quiere_intercambiar = false;    //Establece que la persona no quiere intercambiar
    }
}

int puntaje(Persona * p1)
{
    /******************************************************
     * int puntaje(Persona * p1)
     * *****************************************************
     * Calcula el puntaje de la persona segun el contenido de la tarjeta y el valor ASCII del numero de la fecha la posicion 0 y 10
     * *****************************************************
     * Input:
     *  Persona * p1    :   Direccion de la Persona 1 a calcular su puntaje
     * *****************************************************
     * Returns:
     *  int :   Puntaje calculado
     * ****************************************************/

    int ptj = 0;
    for (int i = 0; i <= p1->tamanio_tarjeta -1; i++)
    {
        ptj += (p1->tarjeta[i] * p1->fecha[i%10]);
    }
    
    return ptj;
}

Persona * unDia(Persona * personas, int dia)
{
    /*********************************************
     * Persona * unDia(Persona * personnas, int dia)
     * ******************************************
     * Corre la logica de un dia.
     * 1- Compra Tarjeta a cada persona
     * 2- Realiza el intercambio de tarjetas si solo si ambas personas quiere intercambiar
     * 3- Busca la persona con el maximo puntaje
     * ******************************************
     * Input:
     *  Persona * personas  :   Array de Personas
     *  int dia    :    Numero de dia
     * ******************************************
     * Return:
     *  Persona *   :   Corresponde a la direccion de la primera persona con el maximo puntaje
     * ******************************************/

    /*************** Comprar Tarjetas a cada Persona ****************/
    int tamanio_nueva_tarjeta;  //Variable del tamanio de la nueva tarjeta, paso por referencia.
    for (int i = 0; i < Global_nPersonas; i++)
    {    
        personas[i].tarjeta = comprarTarjeta(personas[i].nombre, dia, tamanio_nueva_tarjeta);
        personas[i].tamanio_tarjeta = tamanio_nueva_tarjeta;    //Guardar el tamanio de la nueva tarjeta en la persona i
    }

    /*************** Realizar Intercambio de Tarjetas ***************/
    for (int i = 0; i < Global_nPersonas; i++)
    {
        if (personas[i].quiere_intercambiar == true)    //Si persona i quiere intercambiar
        {
            for (int j = i + 1; j < Global_nPersonas; j++)  //Buscar perona j si quiere intercambiar, evitar intercambiar consigo mismo
            {
                if (personas[i].quiere_intercambiar && personas[j].quiere_intercambiar)     //Verificar si ambas personas quieren intercambiar
                {
                    intercambiarTarjeta(&personas[i], &personas[j]);
                }
            }
        }
    }

    /************* Buscar la Persona con el Puntaje Maximo ***********/
    int ptj = 0;    //Puntaje actual
    int max = 0;    //Puntaje MAXIMO actual
    int winerPosition = 0;      //Posicion de la persona con el Puntaje MAXIMO actual

    for (int j = 0; j < Global_nPersonas; j++)
    {
        ptj = puntaje(&personas[j]);

        if (ptj > max)  //Solo guarda el primer maximo puntaje.
        {
            max = ptj;
            winerPosition = j;
        }
    }

    return &personas[winerPosition];
}

void variosDias(Persona * personas, int cant_dias)
{
    /******************************************
     * void variosDias(Persona * personas, int cant_dias)
     * ***************************************
     * Llama la funcion unDia(personas, i) segun la cantidad de dias en busca de la personca con el puntaje mas alto para ser mostrado por pantalla
     * ***************************************
     * Input:
     *  Persona * Personas  :   Array de personas
     *  int cant_dias   :   Numero entero de la cantidad de dias
     * ***************************************
     * Retorno:
     *  Funcion Metodo  :   Imprime segun la cantidad de dias los ganadores de cada dia con su nombre, fecha y el puntaje
     * ****************************************/

    //Array que recuerde a travez de los dias quienes quieren intercambiar
    bool temp[Global_nPersonas]; 
    for (int i = 0; i < Global_nPersonas; i++)
    {
        temp[i] = personas[i].quiere_intercambiar;
    }
    
    Persona * ganador;  //Puntero a la persona ganadora del dia

    for (int i = 1; i <= cant_dias; i++)
    {
        ganador = unDia(personas, i);

        std::cout << ganador->nombre << " " << ganador->fecha << " " << puntaje(ganador) << std::endl;

        for (int j = 0; j < Global_nPersonas; j++)
        {
            personas[j].quiere_intercambiar = temp[j];      //Restablece quiere intercambiar para el siguiente dia.

            delete[] personas[j].tarjeta;   //Eliminar Tarjetas usado por el dia
            
            personas[j].tarjeta = NULL;     //Establecer la tarjeta a NULL despues de desalocar memoria.
            personas[j].tamanio_tarjeta = 0;
            
        }
    }
}

int main(int argc, char const *argv[])
{
    std::cin >> Global_nPersonas;

    Persona * Personas = new Persona[Global_nPersonas];

    for (int i = 0; i < Global_nPersonas; i++)  //Dar datos de personas
    {
        std::cin >> Personas[i].nombre;
        std::cin >> Personas[i].fecha;
        std::cin >> Personas[i].quiere_intercambiar;
        Personas[i].tarjeta = NULL;     //Siempre que punteros apunten a NULL
        Personas[i].tamanio_tarjeta = 0;
    }

    int dias;
    std::cout << "Numeros de dias: ";
    std::cin >> dias;

    variosDias(Personas, dias);

    delete[] Personas;      //Siempre eliminar memoria dinamica
    Personas = NULL;
    Global_nPersonas = 0;

    return 0;
}