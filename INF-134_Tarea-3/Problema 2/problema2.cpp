#include <string>
#include <iostream>

#include "PriorityQueue.cpp"

#define PUSHCOMMAND "PUSHCOMMAND"
#define GET "GET"
#define TERMINATE "TERMINATE"

using namespace std;

struct Comand
{
    string ID;
    string Instruction;
};

/**
 * void PushComand(PriorityQueue<size_t, Comand> &PQ, size_t &creados)
 * ***
 * Obtiene a traves de stdio el comando a insertar en la cola de prioridad
 * Imprime cuantos comandos hay en la cola
 * O(log n)
 * ***
 * Inputs:
 *      PriorityQueue<size_t, Comand> &PQ   :   Referencia de la cola de prioridada
 *      size_t  &creados    :   Referencia a la cuenta de comandos creados
**/
void PushComand(PriorityQueue<size_t, Comand> &PQ, size_t &creados)
{
    Comand info;
    string id, instruction;
    size_t priority;

    //  Inputs
    cin >> id;
    cin >> priority;
    cin.ignore(1);  //  Skip espacio en blanco
    getline(cin, instruction);

    //  Crear bloque de comando
    info.ID = id;
    info.Instruction = instruction;

    //  Insertar en PQ
    PQ.insert(priority, info);

    creados++;

    cout << PQ.size() << " PENDING" << endl; 
}

/**
 * void Get(PriorityQueue<size_t, Comand> &PQ, size_t &enviados)
 * ***
 * Obtiene a traves de stdio la cantidad de comandos a conseguir de la cola de prioridad
 * Imprime la cantidad de  ncomando obtenidos, segido por sus id
 * y las n lineas de comandos en orden según su prioridad
 * O(min(n, PQ.size()))
 * ***
 * Inputs:
 *      PriorityQueue<size_t, Comand> &PQ   :   Referencia de la cola de prioridad
 *      size_t &enviados    :   Referencia de la cuentas de comandos enviados
**/
void Get(PriorityQueue<size_t, Comand> &PQ, size_t &enviados)
{
    size_t N;
    cin >> N;
    
    string * ids = new string[N];
    string * instrucciones = new string[N];
    size_t size = 0;

    for (size_t i = 0; i < N && PQ.size() != 0; i++)
    {
        ids[i] = PQ.front().ID;
        instrucciones[i] = PQ.front().Instruction;
        PQ.pop();
        size++;
        enviados++;
    }

    if (size == 0)
    {
        cout << "0" << endl;

        delete[] ids;
        delete[] instrucciones;

        return;
    }

    cout << size;
    for (size_t i = 0; i < size; i++)
    {
        cout << " " << ids[i];
    }
    cout << endl;

    for (size_t i = 0; i < size; i++)
    {
        cout << instrucciones[i] << endl;
    }
    
    delete[] ids;
    delete[] instrucciones;
}

int main(int argc, char const *argv[])
{
    PriorityQueue<size_t, Comand> PQ(false);
    string comando;
    size_t enviados = 0, creados = 0;

    do
    {
        cin >> comando;
        
        if (comando == PUSHCOMMAND)
        {
            PushComand(PQ, creados);
            continue;
        }

        if (comando == GET)
        {
            Get(PQ, enviados);
            continue;
        }

        if (comando == TERMINATE)
        {
            cout << enviados << " SENT " << creados << " CREATED" << endl;
        }
        
    } while (comando != TERMINATE);
    
    return 0;
}
