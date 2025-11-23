#include <iostream>
#include "ccontrol.h"

using namespace std;

int main()
{
    //seleccionarSeed();
    //crearArbolGlobal();
    //mostrarArbol();

    //prueba generar pedidos
    Lista *l = new Lista();
    generarPedidos(l);
    l->recorrerLista();

    bool continuar = true;
    while(continuar){
        continuar = loopPrincipal();
    }
    return 0;
}
