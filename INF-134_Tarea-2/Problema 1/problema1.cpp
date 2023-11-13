#include <string>
#include <iostream>
#include <fstream>

#include "LinkList.cpp"

#define INSERTAR "INSERTAR"
#define BORRAR "BORRAR"
#define INTERCAMBIAR "INTERCAMBIAR"

using namespace std;

/**
*   void insertar(LinkList &edit_ADN, int position, char nucleotido)
* ***
*   Inserta en una posicion un nucleotido en un TDA de lista basada en nodos
* ***
*   Input:
*       LinkList &edit_ADN  :   Referencia del ADN a editar
*       int position    :   Posicion en donde insertar
*       char nucleotido :   Nuleotido a insertar en el ADN
* ***
*   Return  :   void
**/
void insertar(LinkList &edit_ADN, int position, char nucleotido){
    edit_ADN.moveToPos(position);
    edit_ADN.insert(nucleotido);
}

/**
*   void borrar(LinkList &edit_ADN, int position)
* ***
*   Borrar un nuclotido en una posicion dada en un TDA de lista basada en nodos
* ***
*   Input:
*       LinkList &edit_ADN  :   Referencia del ADN a editar
*       int position    :   Posicion en donde insertar
* ***
*   Return  :   void
**/
void borrar(LinkList &edit_ADN, int position){
    edit_ADN.moveToPos(position);
    edit_ADN.erase();
}

/**
*   void intercambiar(LinkList &edit_ADN, int position, char nucleotido)
* ***
*   Intercambia en una posicion dada un nucleotido por otro en un TDA de lista basada en nodos
* ***
*   Input:
*       LinkList &edit_ADN  :   Referencia del ADN a editar
*       int position    :   Posicion en donde insertar
*       char nucleotido :   Nuleotido a remplazar en el ADN
*
* ***
*   Return  :   void
**/
void intercambiar(LinkList &edit_ADN, int position, char nucleotido){
    edit_ADN.moveToPos(position);
    edit_ADN.replace(nucleotido);
}

/**
*   void writeADN(LinkList &new_ADN)
* ***
*   Escribe una cadena de ADN a un archivo de salida
* ***
*   Input:
*       LinkList &new_ADN  :   Referencia del ADN de salida
* ***
*   Return  :   void
    Exepcion    :   Salida por terminar si el archivo no fue abierto correctamente
**/
void writeADN(LinkList &new_ADN){
    fstream f_Salida;
    f_Salida.open("secuencias-reconstruidas.txt", ios::app);

    //Siempre verificar si se abrió correctamente
    if (!f_Salida.is_open())
    {
        cout << "Could not open this file: secuencias-reconstruidas.txt" << endl;
        return;
    }

    //Copiar valores del ADN al archivo
    for(new_ADN.moveToStart(); new_ADN.currPos() < new_ADN.length(); new_ADN.next()){
        f_Salida << new_ADN.getValue();
    }
    
    f_Salida << endl;
    f_Salida.close();   //Siempre cerrar archivo
}

/**
*   void readInstrucciones()
* ***
*   Lectura de archivo "secuencias-nucleotidos.txt", consigue toda informacion necesaria para
    la creacion de las secuencias de ADN.
* ***
*   Input   :   void
* ***
*   Return  :   void
*   Exepcion    :   Salida por terminar si el archivo no fue abierto correctamente
**/
void readInstrucciones(){
    fstream f_Instrucciones;
    f_Instrucciones.open("secuencias-nucleotidos.txt", ios::in);

    //Siempre verificar si se abrió correctamente
    if (!f_Instrucciones.is_open()){
        cout << "Could nor open File: secuencias-nucleotidos.txt" << endl;
        return;
    }

    int length; // Largo de ADN original
    LinkList original_ADN;  //ADN original

    // Lectura tamanio l y ADN principal
    f_Instrucciones >> length;
    f_Instrucciones.ignore(1); // Saltar espacio en blanco

    //Copiar informacion del archivo
    for (int i = 0; i < length; i++){
        original_ADN.append(f_Instrucciones.get());
    }
        
    // Lectura secuencias e instrucciones
    LinkList new_ADN;   //Nuevo ADN
    string comando;     //Linea de comando
    int posicion, secuencias, instrucciones;
    char nucleotido;

    f_Instrucciones >> secuencias;

    for (int i = 0; i < secuencias; i++)
    {  
        //Crear copia del ADN original
        for (original_ADN.moveToStart(); original_ADN.currPos() < original_ADN.length(); original_ADN.next())
        {
            new_ADN.append(original_ADN.getValue());
        }

        f_Instrucciones >> instrucciones;   //Obtener numero de instrucciones

        for (int j = 0; j < instrucciones; j++)
        {
            f_Instrucciones >> comando;

            if (!comando.compare(INSERTAR)){
                f_Instrucciones >> posicion;
                f_Instrucciones >> nucleotido;

                insertar(new_ADN, posicion, nucleotido);

            } else if (!comando.compare(BORRAR)){
                f_Instrucciones >> posicion;
                borrar(new_ADN, posicion);

            } else if (!comando.compare(INTERCAMBIAR)){
                f_Instrucciones >> posicion;
                f_Instrucciones >> nucleotido;
                intercambiar(new_ADN, posicion, nucleotido);
            }
        }

        writeADN(new_ADN);  //Salida del nuevo ADN
        new_ADN.clear();    //Limpiar ADN
    }

    f_Instrucciones.close();    //Siempre cerrar archivo
}

int main(int argc, char const *argv[])
{
    readInstrucciones();
    return 0;
}
