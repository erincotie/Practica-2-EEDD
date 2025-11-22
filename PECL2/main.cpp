#include <iostream>
#include "ccontrol.h"

using namespace std;

int main()
{
    //seleccionarSeed();
    //crearArbolGlobal();
    //mostrarArbol();

    bool continuar = true;
    while(continuar){
        continuar = loopPrincipal();
    }
    return 0;
}
