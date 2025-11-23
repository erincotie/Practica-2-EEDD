#include <iostream>
#include "ccontrol.h"

using namespace std;

int main()
{
    introducirSeed();
    inicializarABB();

    //prueba generar pedidos
    //Lista *l = new Lista();
    //generarPedidos(l);
    //para mostrar los pedidos
    //l->recorrerLista();

    bool continuar = true;
    while(continuar){
        continuar = loopPrincipal();
    }
    return 0;
}
