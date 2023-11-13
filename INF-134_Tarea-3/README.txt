Problema1.cpp
    Para el coreccto funcionameinto se debe tener en cuenta que:

    Se incluyes dos archivos .cpp de nombre "Login.cpp", que contiene el TDA Login
    y el archivo de nombre "UnsortedDict.cpp", que contiene el TDA UnsortedDict
    Ambos archivos deben estar en la misma carpeta al momento de compilar.
    "Login.cpp" debe incluir "UnsortedDict.cpp"
        -   #include "UnsortedDict.cpp"

    y Problema1 debe incluir "Login.cpp"
        -   #include "Login.cpp"

    Se realizan las siguentes definiciones:
        #define INICIAR_SESION "INICIAR_SESION"
        #define REGISTRAR "REGISTRAR"
        #define ACTUALIZAR "ACTUALIZAR"
        #define FINALIZAR "FINALIZAR"

    Se incluyen las siguentes librerias estandars según los archivos:
    -   "Login.cpp"
        - <srtring>
        - <iostream>
    
    -   "UnsortedDict.cpp"
        - <typeinfo>    //  Intento uso de templates, se queria usar un hash para string y un hash para integers, pero no se separaban en el precompilado

    Y using namespace std;

    No requiere archivos de textos extras.

    La funcion main está contenida en "Problema1.cpp" El archivo a compilar

Problema2.cpp
    Para el coreccto funcionameinto se debe tener en cuenta que:

    Se incluye un archivo .cpp de nombre "PriorityQueue.cpp", que contiene el TDA PriorityQueue
    El archivo debe estar en la misma carpeta al momento de compilar.
        -   #include "PriorityQueue.cpp"

    Se realizan las siguientes definiciones:
        #define PUSHCOMAND "PUSHCOMAND"
        #define GET "GET"
        #define TERMINATE "TERMINATE"

    Se incluyen las libreas estandars
        -   <string>
        -   <iostream>

    y using namespace std;

    No requiere archivos de textos extras.

    La funcion main está contenida en "problema2.cpp" El archivo a compilar

Ambos programas fueron probados usando "g++ -g ./File.cpp -o File -Wall" tanto en Linux Ubuntu y Windows 11
Puebas con "valgrind --leak-check=yes ./File" en Linux Ubuntu, exitosamente.
