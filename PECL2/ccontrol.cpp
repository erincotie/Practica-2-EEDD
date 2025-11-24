#include<iostream>
#include <iomanip>
#include "ccontrol.h"

using namespace std;

Lista *listaGlobal = new Lista();
ArbolABB *arbolGlobal;

//Solucion temporal
int *libIds = new int[100];
int idsPointer = 0;

#define NUM_LOCALIDADES 20
string Localidades[NUM_LOCALIDADES] ={"Mostoles", "Alcala", "Leganes", "Fuenlabrada", "Getafe", "Alcorcon", "Torrejon", "Parla", "Alcobendas", "Coslada", "Pozuelo", "Rivas", "Valdemoro","Majadahonda", "Aranjuez", "Arganda", "Boadilla", "Pinto", "Colmenar", "Tres Cantos"};
#define NUM_MATERIAS 6
string Materias[NUM_MATERIAS] = {"Matematicas", "Historia","Lengua", "Musica", "Tecnologia", "Fisica" };

void introducirSeed()
{
    //if(SEED > 0) srand (SEED);
    //else srand (time(NULL));
    srand(time(NULL));
}

Libreria generarLibAleatoria(){
    int idLib = generarNumAleatorio(0, 1000);
    //Solucion temporal horrible AQUI
    libIds[idsPointer] = idLib;
    idsPointer++;
    Lista *libLista = new Lista();
    Libreria libreria = {idLib, Localidades[generarNumAleatorio(0, NUM_LOCALIDADES)], libLista};
    return libreria;
}

void mostrarCabecera(){
    //cout << titulo << ":" << endl
             cout << "---------------------------------------------------------------------------"<<endl
             <<      "| ID Libreria | ID Pedido | Cod. Libro |   Materia  | Unidades |   Fecha   |"<<endl
             <<      "---------------------------------------------------------------------------"<<endl;
}

void prepararPedidos(){

    //Primer paso: Generar pedidos nuevos.
    cout << "Creando los siguientes nuevos pedidos." << endl;
    generarPedidos(listaGlobal);
    mostrarCabecera();
    listaGlobal->recorrerLista();
    cout << "<<< Presione cualquier tecla para continuar >>>" << endl;

    cin.get();
    cin.clear();
    cin.ignore();

    //Segundo paso: Repartir los pedidos y dar opciones al usuario.
    repartirPedidos(listaGlobal, arbolGlobal);
    cout << "Pedidos repartidos. Estado del arbol:" << endl;
    arbolGlobal->InOrden(Mostrar);
}

//Considerar añadir una opcion para cancelar y volver al menu.
void opcionInsertarLibreria(){
    bool enProceso = true;
    Libreria nuevaLib = {-1,"", nullptr};

    cout << "Creando nueva libreria." << endl;
    while(enProceso)
    {
        if(nuevaLib.id_libreria == -1)
        {
            int newID;
            cout << "Introduce el ID: " << endl;
            cin >> newID;
            if(!cin.fail())
            {
                if(newID < 1000 || newID > 0)
                {
                    if(!arbolGlobal->Buscar(newID)){
                        nuevaLib.id_libreria = newID;
                        continue;
                    }
                    else{
                        cout << "Error: El ID NO puede coincidir con uno ya existente en el arbol." << endl;
                        cin.clear();
                        cin.ignore(10000, '\n');
                        continue;
                    }
                }
                else{
                    cout << "Error: El ID debe ser un numero entero de 3 cifras." << endl;
                    cin.clear();
                    cin.ignore(10000, '\n');
                    continue;
                }
            }
            else
            {
                cout << "Error: Introduce un entero como ID." << endl;
                cin.clear();
                cin.ignore(10000, '\n');
                continue;
            }
        }

        if(nuevaLib.localidad == "")
        {
            cout << "Introduce la localidad: " << endl;
            cin >> nuevaLib.localidad;
            continue;
        }

        else{
            enProceso = false;
        }
    }
    nuevaLib.listaPedidos = new Lista();
    arbolGlobal->Insertar(nuevaLib);
    arbolGlobal->InOrden(Mostrar);
}

void OpcionBorrarLibreria(int id){
    if(arbolGlobal->Buscar(id) == nullptr){
        cout << endl << "La libreria del ID especificado no existe." << endl;
    }
    else{
        cout << endl<< "Borrando la libreria con ID: "<< id << endl;
        arbolGlobal->Borrar(id);
    }
    arbolGlobal->InOrden(Mostrar);
}

void OpcionMostrarPedidos(int id){
    Libreria* l = arbolGlobal->Buscar(id);
    if(l != nullptr){
        mostrarCabecera();
        l->listaPedidos->recorrerLista();
        cout << endl << endl;
    } else{
        cout <<endl <<"Libreria incorrecta, no existe en el sistema"<<endl<<endl;
    }
}

bool esCodigoPedido(string codigo){
    if(codigo.size() > 6) return false;
    if(codigo.size() < 5) return false;
    if(codigo.size() == 6){
        if(codigo.at(0) != 'P' && codigo.at(0) != 'p') return false;

        else codigo.erase(0,1);
    }

    for(int i = 0; i < codigo.size(); i++){
        if(codigo.at(i) < 48 || codigo.at(i) > 57) return false;
    }

    return true;
}

void opcionBuscarPedido(){
    string id;
    cout <<"Introduzca el ID del pedido que desea mostrar: " << endl;
    cin >> id;
    if(esCodigoPedido(id)){
        //Funcion para buscar pedido por ID.
        cout << "Buscando pedido en arbol..." << endl;
    }
    else {
        cout << "El codigo introducido no corresponde a un codigo real." << endl;
    }
}

void opcionBorrarPedido(){
    string id;
    cout <<"Introduzca el ID del pedido que desea borrar: " << endl;
    cin >> id;
    if(esCodigoPedido(id)){
        //Funcion para borrar pedido por ID.
        cout << "Borrando pedido en arbol..." << endl;
    }
    else {
        cout << "El codigo introducido no corresponde a un codigo real." << endl;
    }
}

void opcionMoverPedido(){
    string id;
    cout <<"Introduzca el ID del pedido que desea mover: " << endl;
    cin >> id;
    if(esCodigoPedido(id)){
        //Aqui se buscaria el pedido, y en caso de encontrarlo se guardaria para ponerlo despues.


        cout << "Introduzca el ID de la libreria donde lo quiere guardar: " <<endl;
        int libID;
        cin >> libID;
        if(!cin.fail())
        {
            Libreria *lib = arbolGlobal->Buscar(libID);
            if(lib){
                cout << "Moviendo pedido en arbol..." << endl;
            }
            else{
                cout <<"Error: La biblioteca buscada no existe." <<endl;
            }
        }
        else
        {
            cout <<"Error: El ID debe ser un numero entero"<<endl<<endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }
    else {
        cout << "El codigo introducido no corresponde a un codigo real." << endl;
    }
}

bool loopPrincipal(){

    //Opciones del menú

    cout << "Opciones disponibles:" << endl
    << "1- Insertar una libreria de forma manual." << endl
    << "2- Borrar una libreria del arbol." << endl
    << "3- Mostrar los datos de los pedidos de una libreria dada." << endl
    << "4- Buscar un pedido concreto por su ID. (EN DESARROLLO)" << endl
    << "5- Extraer un pedido concreto. (Eliminar). (EN DESARROLLO)" << endl
    << "6- Llevar un pedido concreto de una libreria a otra. (EN DESARROLLO)" << endl
    << "7- Mostrar una estadistica de las librerias. (NO IMPLEMENTADO)" << endl
    << "8- Continuar con la distribucion de pedidos." << endl
    << "0- Salir del programa" << endl;

    cout << "Seleccione una opcion del menu: " << endl;
    int opcion;
    cin >> opcion;
    // proteccion para entrada de SOLO enteros. Solo entra al switch si no falla el cin.
    if (!cin.fail())
    {
        switch(opcion)
        {
        case 0:
            return false;
            break;
        case 1:
            {
                opcionInsertarLibreria();
                break;
            }
        case 2:
            {
               // borrar libreria
                cout <<endl<<"Introduzca el ID de libreria que desea borrar: " <<endl;
                int id;
                cin >> id;
                if(!cin.fail()){
                    OpcionBorrarLibreria(id);
                } else{
                    cout <<"Introduzca un numero entero"<<endl<<endl;
                    cin.clear();
                    cin.ignore(10000, '\n');
                }
                break;
            }
        case 3:
            //mostrar libreria
            cout <<endl<<"Introduzca el ID de libreria que desea mostrar: " <<endl;
                int id;
                cin >> id;
                if(!cin.fail()){
                    OpcionMostrarPedidos(id);
                } else{
                    cout <<"Introduzca un numero entero"<<endl<<endl;
                    cin.clear();
                    cin.ignore(10000, '\n');
                }
            break;
        case 4:
            opcionBuscarPedido();
            break;
        case 5:
            opcionBorrarPedido();
            break;
        case 6:
            //mover un pedido de una libreria a otra
            opcionMoverPedido();
            break;
        case 7:
            //estadisticas
            break;
        case 8:
            //generar pedidos de nuevo y repartir
            prepararPedidos();
            break;
        // caso de que no falle el cin (es un numero) pero no sea uno de los casos especificados
        default:
            cout <<"Opcion no valida, introduce un numero del 0 al 8"<<endl<<endl;
            cin.clear();
            cin.ignore(10000,'\n');
            break;
        }
    }

    //En caso de fallo del cin, se muestra un mensaje de error y se vuelve a pedir opcion.
    else
    {
        cout <<"Opcion no valida, introduce un numero"<<endl<<endl;
        cin.clear();
        cin.ignore(10000, '\n');
    }
    return true;
}

void generarArbolAleatorio(ArbolABB *abb){
    for (int i = 0; i< N_LIBRERIAS; i++){
        Libreria l = generarLibAleatoria();
        abb->Insertar(l);
    }

}

void repartirPedidos(Lista *lista, ArbolABB *arbol){
    while(!lista->listaVacia()){
        Pedido pedido = lista->valorCabeza();
        Libreria *lib = arbol->Buscar(pedido.id_libreria);
        if(lib){
            lib->listaPedidos->insertarPedido(pedido);
        }
        lista->borrarPedido(pedido);
    }
}

void generarPedidos(Lista *lista){
    for (int i =0; i < N_PEDIDOS; i++){
        int idLib = libIds[generarNumAleatorio(0, idsPointer)];
        string id_pedido = generarCodigoPedido();
        string cod_libro = generarCodigoLibro();
        string materia = Materias[generarNumAleatorio(0, NUM_MATERIAS)];
        int unidades = generarNumAleatorio(1,1000);
        string fecha = to_string(generarNumAleatorio(1,30+1)) + "/" +to_string(generarNumAleatorio(1,12+1)) + "/2025";
        Pedido p = {idLib, id_pedido,cod_libro,materia,unidades,fecha};
        lista->insertarPedido(p);
    }
}

int generarNumAleatorio(int minimo, int maximo){
    return (rand() % (maximo-minimo) ) + minimo;
};

//Genera una letra mayuscula (A-Z).
char generarLetraMayusAleatoria()
{
    //26->Diferencia entre A y Z.
    //65->A en mayuscula.
    return (char)(rand() % 26) + 65;
}

//Genera el codigo del libro en formato NNNCNN (N: Cifra decimal, C: Caracter)
string generarCodigoLibro()
{
    string nuevoCodigo;

    int primerNumero = generarNumAleatorio(100, 999);
    nuevoCodigo += to_string(primerNumero);

    char letra = generarLetraMayusAleatoria();
    nuevoCodigo += letra;

    int segundoNumero = generarNumAleatorio(10, 99);
    nuevoCodigo += to_string(segundoNumero);

    return nuevoCodigo;

}

//Genera el codigo del libro en formato 'P'NNNNN (N: Cifra decimal)
string generarCodigoPedido()
{
    string nuevoCodigo = "P";

    int numero = generarNumAleatorio(10000, 99999);
    nuevoCodigo += to_string(numero);

    return nuevoCodigo;

}

void inicializarABB(){
    cout << "Creando el ABB con " << N_LIBRERIAS << " nodos:" << endl;

    arbolGlobal = new ArbolABB();
    generarArbolAleatorio(arbolGlobal);

    cout << "Arbol vacio creado:" << endl;
    arbolGlobal->InOrden(Mostrar);

}
