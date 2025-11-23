#include <iostream>
#include "ccontrol.h"

using namespace std;

int main()
{
    introducirSeed();
    inicializarABB();


    bool continuar = true;
    while(continuar){
        continuar = loopPrincipal();
    }
    return 0;
}
