#include <iostream>
#include "ccontrol.h"

using namespace std;

int main()
{
    //seleccionarSeed();
    //crearArbolGlobal();
    ArbolABB *abb = new ArbolABB();
    generarArbolAleatorio(abb);
    abb->InOrden(Mostrar);


    //prueba generar pedidos
    Lista *l = new Lista();
    generarPedidos(l);
    //para mostrar los pedidos
    l->recorrerLista();

    bool continuar = true;
    while(continuar){
        continuar = loopPrincipal();
    }
    return 0;
}
