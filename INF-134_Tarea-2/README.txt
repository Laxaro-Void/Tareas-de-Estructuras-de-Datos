Problema1.cpp
    Para el correcto funcionamiento se requieren las siguientes cabezeras:

    Las librerias standar de C++:
    #include <string>
    #include <iostream>
    #include <fstream>

    Se incluye un archivo .cpp de nombre "LinkList.cpp", cual contine el TDA LinkList (Lista basada en nodos).
    El archivo "LinkList.cpp" debe estar en la misma carpeta que "Problema1.cpp" al momento de compilar.
        #include "LinkList.cpp"

    Se define:
    #define INSERTAR "INSERTAR"
    #define BORRAR "BORRAR"
    #define INTERCAMBIAR "INTERCAMBIAR"

    Y using namespace std

    Se debe contener el archivo "secuencias-nucleotidos.txt" en la misma carpeta del que el ejecutable.

    La funcion main esta contenida en "problema1.cpp", este es el archivo a compilar.

Problema2.cpp
    Para el correcto funcionamiento se requieren las siguientes cabezeras:

    Las libreiras estandar de C++:
    #include <iostream>
    #include <string>

    Se incluye un archivo .cpp de nombre "ABB.cpp", cual contiene el TDA ABB (Arbol de busqueda binaria sin repeticion).
    El archivo "ABB.cpp" debe estar en la misma carpeta que "Problema2.cpp" al momento de compilar.
        #include "ABB.cpp"

    Se define:
    #define EXIT -1
    #define ENCENDER 1
    #define CUANTOS_ENCENDER 2

    Y using namespace std;

    No requiere otros archivo de entradas. Entrada por standar input.

    La funcion main esta contenida en "Problema2.cpp", este es el archivo a compilar.


Ambos programas fueron probados usando "g++ -g ./File.cpp -o File -Wall" tanto en Linux Ubuntu y Windows 11
Puebas con "valgrind --leak-check=yes ./File" en Linux Ubuntu, exitosamente.