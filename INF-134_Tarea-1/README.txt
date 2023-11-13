CasinoDeAlimentacion.cpp
    Solo exite una unica funcion llamada bool puedeConsumir(),
    Para el correcto funcinamiento, requiere que exista el archivo "saldos.bin" en la misma carpeta que el ejecutable
    Ademas usa una estructura de forma:

    struct SaldoColaborador {
        char rut[11];
        int saldo_desayuno;
        int saldo_almuerzo;
        int saldo_once;
        int saldo_cena;
    };

    Y las constantes globales:

    const int SERV_DESAYUNO = 0;
    const int SERV_ALMUERZO = 1;
    const int SERV_ONCE = 2;
    const int SERV_CENA = 3;

    Incluye las sigientes librerias estandar de C++:

    #include <iostream>
    #include <fstream>
    #include <cstring>

ListaDeLaSuerte.cpp
    Existen multiples funciones, no requiere archivos externos
    Para el correcto funcionamiento, la funcion main se debe declarar un array de
    n personas
    La estructurade la Personas es de forma:

    struct Persona
    {
        std::string nombre;
        char fecha[11]; //AAAA-MM-DD
        int tamanio_tarjeta = 0;
        int * tarjeta = NULL;
        bool quiere_intercambiar;
    };

    Se quiere iterar por el array dando valor por entrada estandar a; nombre, fecha (AAAA-MM-DD) y quiere_intercambiar.

    Incluye las siguiente librerias estandar de C++:

    #include <iostream>
    #include <fstream>
    #include <cstring>

Ambos programas fueron probados usando "g++ -g ./File.cpp -o File -Wall" tanto en Linux Ubuntu y Windows 10
Puebas con "valgrind --leak-check=yes ./File" en Linux Ubuntu, exitosamente.
