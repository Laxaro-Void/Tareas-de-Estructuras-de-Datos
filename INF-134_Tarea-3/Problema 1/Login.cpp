#include <string>
#include <iostream>

#include "UnsortedDict.cpp"

class Login
{
private:
    UnsortedDict<std::string, std::string> Registro;    //  Registro de logins

    const size_t MIN_CLAVE_LEN = 8;     //  Tamanio minimo de clave secreta

public:
    Login();

    bool iniciar_sesion(std::string usario, std::string clave);

    bool crear_nuevo_usuario(std::string usuario, std::string clave);

    bool cambiar_clave(std::string usuario, std::string clave);

    ~Login();
};

/**
 * Login::login()
 * ***
 * Contructor de login
 * O(1)
*/
Login::Login()
{
}

/**
 * bool Login::iniciar_sesion(string usuario, string clave)
 * ***
 * Verifica si usuario posee registro en la base de datos
 * O(1)
 * ***
 * Inputs:
 *      string usuario  :   nombre de usuario ingresado
 *      string clave    :   clave ingresado
 * ***
 * Returns:
 *      bool    :   true si exitoso, false lo contrario
**/
bool Login::iniciar_sesion(std::string usuario, std::string clave)
{
    auto reg = Registro.get(usuario);

    if (reg == Registro.end())  //  No existe en Registro
    {
        std::cout << "El usuario no se encuentra registrado" << std::endl;
        return false;
    }

    if (*(reg) != clave)    //  Existe en Registro, No coincide la clave
    {
        std::cout << "La clave ingresada no coincide" << std::endl;
        return false;
    }

    //  Exite en Registro, Clave coincide
    std::cout << "Sesion iniciada con exito" << std::endl;
    return true;
}

/**
 * bool Login::crear_nuevo_usuario(string usuario, string clave)
 * ***
 * Crea un nuevo usuario al registro
 * Claves de tamanio minimo 8
 * O(1)
 * ***
 * Inputs:
 *      string usuario  :   Nombre de usuario a crear
 *      string clave    :   Calve de Usuario a crear
 * ***
 * Returns:
 *      bool    :   True si usuario registrado exitosamente, false lo contrario
**/
bool Login::crear_nuevo_usuario(std::string usuario, std::string clave)
{
    auto reg = Registro.get(usuario);

    if (reg != Registro.end())  //  Ya existe en Registro
    {
        std::cout << "El usuario ya se encuentra registrado" << std::endl;
        return false;
    }

    if (clave.length() < MIN_CLAVE_LEN)
    {
        std::cout << "La clave debe tener al menos " << MIN_CLAVE_LEN << " caracteres" << std::endl;
        return false;
    }

    reg = Registro.insert(usuario, clave);

    if (reg == Registro.end())  //  Inserccion no exitosa, algo fue muy mal
    {
        std::cout << "Expetion: BAD_INSERT at key: " << usuario << std::endl;
        exit(1);
    }

    //  Inserccion exitosa
    std::cout << "Usuario registrado con exito" << std::endl;
    return true;
}

/**
 * bool Login::cambiar_clave(string usuario, string clave)
 * ***
 * Cambia la clave asociado al usuario
 * Clave de tamanio minimo 8
 * O(1)
 * ***
 * Inputs:
 *      string usuario  :   Nombre de usuario a cambiar la clave
 *      string clave    :   Nueva clave a cambiar
 * ***
 * Returns:
 *      bool    :   True si remplazo exitoso, false lo contrario
**/
bool Login::cambiar_clave(std::string usuario, std::string clave)
{
    auto reg = Registro.get(usuario);

    if (reg == Registro.end())  //  No existe en Registro
    {
        std::cout << "El usuario no se encuentra registrado" << std::endl;
        return false;
    }

    if (clave.length() < MIN_CLAVE_LEN)
    {
        std::cout << "La clave debe tener al menos " << MIN_CLAVE_LEN << " caracteres" << std::endl;
        return false;
    }

    reg = Registro.replace(usuario, clave);

    if (reg == Registro.end())  //  Remplaso no exitosa, algo fue muy mal
    {
        std::cout << "Expetion: BAD_REPLACE at key: " << usuario << std::endl;
        exit(1);
    }

    //  Remplazo exitoso
    std::cout << "Calve actualizada con exito" << std::endl;
    return true;
}

/**
 * Login::~login()
 * ***
 * Destructor
 * O(1)
**/
Login::~Login()
{
}
