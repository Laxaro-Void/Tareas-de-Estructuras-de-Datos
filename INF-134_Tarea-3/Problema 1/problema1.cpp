#include "Login.cpp"    //  Include <iostream>, <string>

#define INICIAR_SESION "INICIAR_SESION"
#define REGISTRAR "REGISTRAR"
#define ACTUALIZAR "ACTUALIZAR"
#define FINALIZAR "FINALIZAR"

using namespace std;

int main(int argc, char const *argv[])
{
    Login log;  //  Registro
    string comando, user, pass;     //  Lineas de comnado, user, pass

    do
    {
        cin >> comando; //  obtener comando
        if (comando == INICIAR_SESION)
        {
            cin >> user;
            cin >> pass;
            log.iniciar_sesion(user, pass);
            continue;
        }

        if (comando == REGISTRAR)
        {
            cin >> user;
            cin >> pass;
            log.crear_nuevo_usuario(user, pass);
            continue;
        }

        if (comando == ACTUALIZAR)
        {
            cin >> user;
            cin >> pass;
            log.cambiar_clave(user, pass);
            continue;
        }

    } while (comando != FINALIZAR);
    
    return 0;
}
