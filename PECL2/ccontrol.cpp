#include "ccontrol.h"

using namespace std;

Lista *listaGlobal = new Lista();
ArbolABB *arbolGlobal;

intLista *listaIDs = new intLista();

#define NUM_LOCALIDADES 20
string Localidades[NUM_LOCALIDADES] ={"Mostoles", "Alcala", "Leganes", "Fuenlabrada", "Getafe", "Alcorcon", "Torrejon", "Parla", "Alcobendas", "Coslada", "Pozuelo", "Rivas", "Valdemoro","Majadahonda", "Aranjuez", "Arganda", "Boadilla", "Pinto", "Colmenar", "Tres Cantos"};

#define NUM_MATERIAS 6
string Materias[NUM_MATERIAS] = {"Matematicas", "Historia","Lengua", "Musica", "Tecnologia", "Fisica" };

void mostrarCabecera(){
    cout << "---------------------------------------------------------------------------"  <<endl
    <<      "| ID Libreria | ID Pedido | Cod. Libro |   Materia  | Unidades |   Fecha  |" <<endl
    <<      "---------------------------------------------------------------------------"  <<endl;
}

Libreria generarLibAleatoria(){
    int idLib = generarNumAleatorio(0, 1000);
    listaIDs->insertarInt(idLib);

    Lista *libLista = new Lista();
    Libreria libreria = {idLib, Localidades[generarNumAleatorio(0, NUM_LOCALIDADES)], libLista};
    return libreria;
}

void prepararPedidos(){

    //Primer paso: Generar pedidos nuevos.
    cout << "Creando los siguientes nuevos pedidos." << endl;
    generarPedidos(listaGlobal);
    mostrarCabecera();
    listaGlobal->recorrerLista();
    cout << "<<< Presione ENTER para continuar >>>" << endl;

    cin.ignore();
    cin.clear();
    cin.get();

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
    listaIDs->insertarInt(nuevaLib.id_libreria);

    arbolGlobal->Insertar(nuevaLib);
    arbolGlobal->InOrden(Mostrar);
}

void opcionBorrarLibreria(){
    cout << "Introduzca el ID de libreria que desea borrar: " << endl;
    int id;
    cin >> id;
    if(cin.fail())
    {
        cout << "Error: El ID introducido no es valido, introduzca un numero entero" <<endl;
        cin.clear();
        cin.ignore(10000, '\n');
        return;
    }

    if(arbolGlobal->Buscar(id) == nullptr){
        cout << endl << "La libreria del ID especificado no existe." << endl;
    }
    else{
        cout << endl<< "Borrando la libreria con ID: "<< id << endl;
        arbolGlobal->Borrar(id);
    }
    arbolGlobal->InOrden(Mostrar);
}

void opcionMostrarPedidos(){
    cout << "Introduzca el ID de libreria que desea mostrar: " << endl;
    int id;
    cin >> id;
    if(cin.fail())
    {
        cout <<"Error: El ID introducido no es valido, introduzca un numero entero" << endl << endl;
        cin.clear();
        cin.ignore(10000, '\n');
        return;
    }

    Libreria* l = arbolGlobal->Buscar(id);
    if(l != nullptr){
        mostrarCabecera();
        l->listaPedidos->recorrerLista();
        cout << endl << endl;
    } else{
        cout <<endl <<"Libreria incorrecta, no existe en el sistema"<<endl<<endl;
    }
}

//Introduce la famosa P al inicio de un codigo dado.
void formatearCodigoPedido(string *codigo){
     if(codigo->size() < 6) codigo->insert(0, "P");
}

bool esCodigoPedido(string *codigo){
    if(codigo->size() > 6) return false;
    if(codigo->size() < 5) return false;
    int i = 0;
    if(codigo->size() == 6){
        if(codigo->at(0) != 'P' && codigo->at(0) != 'p') return false;

        else i++;
    }

    for(i; i < codigo->size(); i++){
        if(codigo->at(i) < 48 || codigo->at(i) > 57) return false;
    }

    return true;
}

void buscarPorPedidoID(Libreria lib, string codigo){
    Pedido* p = lib.listaPedidos->buscarPedido(codigo);
    if(p){
        cout<< "Encontrado en libreria:"<<endl;
        cout << lib << endl;
        cout<<endl;
        mostrarCabecera();
        lib.listaPedidos->recorrerLista();
    }
}

void borrarPorPedidoID(Libreria lib, string codigo){
    if(lib.listaPedidos->buscarPedido(codigo)){
        lib.listaPedidos->borrarPedido(codigo);
        cout<< "Datos de libreria: "<<endl;
        cout << lib << endl;
        cout<<endl;
        mostrarCabecera();
        lib.listaPedidos->recorrerLista();
        cout<<endl;
    }
}

void opcionBuscarPedido(){
    string id;
    cout <<"Introduzca el ID del pedido que desea mostrar: " << endl;
    cin >> id;
    if(esCodigoPedido(&id)){
        formatearCodigoPedido(&id);
        //Funcion para buscar pedido por ID.
        cout << "Buscando pedido en arbol..." << endl;
        arbolGlobal->InOrden(buscarPorPedidoID, id);

    }
    else {
        cout << "El codigo introducido no corresponde a un codigo real." << endl;
    }
}

void opcionBorrarPedido(){
    string id;
    cout <<"Introduzca el ID del pedido que desea borrar: " << endl;
    cin >> id;
    if(esCodigoPedido(&id)){
        formatearCodigoPedido(&id);
        //Funcion para borrar pedido por ID.
        cout << "Borrando pedido en arbol..." << endl;
        arbolGlobal->InOrden(borrarPorPedidoID, id);
    }
    else {
        cout << "El codigo introducido no corresponde a un codigo real." << endl;
    }
}

bool buscarLibreriaPorPedidoID(Libreria *lib, string codigo){
    Pedido* p = lib->listaPedidos->buscarPedido(codigo);
    if(p){
        return true;
    }
    else return false;
}

void opcionMoverPedido(){
    cout << "Introduce el ID del Pedido que quieres mover: ";
    string id;
    cin >> id;

    if(!esCodigoPedido(&id)){
        cout << "ERROR: El codigo introducido no corresponde a un pedido real." << endl;
        cout << endl;
        return;
    }
    formatearCodigoPedido(&id);

    Libreria* lib1 = arbolGlobal->InOrden(buscarLibreriaPorPedidoID, id);
    if(lib1 == nullptr){
        cout << "ERROR: El codigo introducido no ha sido encontrado en ninguna de las librerias." << endl
        << endl;
        return;
    }

    Pedido* pedido = lib1->listaPedidos->buscarPedido(id);

    cout << "El pedido buscado ha sido encontrado. Info. de la libreria:" << endl;
    cout << *lib1 << endl;

    cout << "Introduce el ID de la Libreria donde quieres que el pedido sea movido: ";
    int libID;
    cin >> libID;

    if(cin.fail()){
        cout <<"ERROR: El ID de la libreria debe ser un numero entero."<<endl<<endl;
        cin.clear();
        cin.ignore(10000, '\n');
        return;
    }

    if(libID == lib1->id_libreria){
        cout << "El ID introducido de la libreria destino es igual al de fuente." << endl
        << "Ninguna libreria ha sido modificada." << endl << endl;
        return;
    }

    Libreria* lib2 = arbolGlobal->Buscar(libID);

    if(lib2 == nullptr){
        cout << "ERROR: El codigo introducido no corresponde a una libreria real." << endl;
        cout << endl;
        return;
    }

    pedido->id_libreria = lib2->id_libreria;

    lib2->listaPedidos->insertarPedido(*pedido);
    lib1->listaPedidos->borrarPedido(id);

    cout << "El pedido ha sido movido exitosamente." << endl
    << endl;
    cout << *lib1 << endl;
    mostrarCabecera();
    lib1->listaPedidos->recorrerLista();

    cout << *lib2 << endl;
    mostrarCabecera();
    lib2->listaPedidos->recorrerLista();
}

string MateriaMasPopular(Libreria lib)
{
    int *materiaEstadistica = lib.listaPedidos->contarMaterias();
    int indexMayor = -1;

    for (int i =0; i < NUM_MATERIAS; i++)
    {
        if (materiaEstadistica[i] > 0 &&(materiaEstadistica[i] > materiaEstadistica[indexMayor]))
        {
            indexMayor=i;
        }
    }

    if(indexMayor == -1) return "No existen pedidos.";
    else
    {
        return Materias[indexMayor] +"->" + to_string(materiaEstadistica[indexMayor]) + " pedidos";
    }
}

string MateriaMenosPopular(Libreria lib)
{
    int *materiaEstadistica = lib.listaPedidos->contarMaterias();
    int indexMenor = -1;

    for (int i =0; i < NUM_MATERIAS; i++)
    {
        if (materiaEstadistica[i] > 0 && (indexMenor == -1 || materiaEstadistica[i] < materiaEstadistica[indexMenor]))
        {
            indexMenor = i;
        }
    }
    if(indexMenor == -1) return "No existen pedidos.";
    else
    {
        return Materias[indexMenor] +"->" + to_string(materiaEstadistica[indexMenor]) + " pedidos";
    }
}

void estadisticaTopLibreriasPedidos(Libreria lib){
    int numPedidos = lib.listaPedidos->contarPedidos();
    float media = 0;
    if(numPedidos > 0){
        int sumUnidades = lib.listaPedidos->sumarUnidades();
        media = sumUnidades/numPedidos;
    }

    cout << "Estadisticas de la libreria con ID: " << lib.id_libreria << endl;
    cout<<"--------------------------------------------------------------------------------------------"<<endl
        <<"| ID Libreria | Num Pedidos | Uds/Pedido |  Materia mas popular  |  Materia menos popular  |"<<endl
        <<"--------------------------------------------------------------------------------------------"<<endl
        << "|  "
        << setw(11) << lib.id_libreria << "|"
        << setw(13) << numPedidos   << "|"
        << setw(12) << media   <<"|"
        << setw(23) << MateriaMasPopular(lib) << "|"
        << setw(25) << MateriaMenosPopular(lib) << "|"
        << endl<<endl;

}

void opcionEstadistica(){
    /*
      Estadistica: Top 5 librerias con mas pedidos, en cada una de ellas decir la media de unidades por pedido,
      la materia mas / menos popular.
    */
    arbolGlobal->InOrden(estadisticaTopLibreriasPedidos);
}


bool loopPrincipal(){

    //Opciones del menú
    cout << "Opciones disponibles:" << endl
    << "1- Insertar una libreria de forma manual." << endl
    << "2- Borrar una libreria del arbol." << endl
    << "3- Mostrar los datos de los pedidos de una libreria dada." << endl
    << "4- Buscar un pedido concreto por su ID." << endl
    << "5- Extraer un pedido concreto. (Eliminar)." << endl
    << "6- Llevar un pedido concreto de una libreria a otra." << endl
    << "7- Mostrar una estadistica de las librerias. (EN DESARROLLO)" << endl
    << "8- Continuar con la distribucion de pedidos." << endl
    << "0- Salir del programa" << endl;

    cout << "Seleccione una opcion del menu: " << endl;
    int opcion;
    cin >> opcion;

    //Proteccion para entrada de SOLO enteros. Solo entra al switch si no falla el cin.
    //En caso de fallo del cin, se muestra un mensaje de error y se vuelve a pedir opcion.
    if(cin.fail()){
        cout <<"Opcion no valida, introduce un numero entero."<<endl<<endl;
        cin.clear();
        cin.ignore(10000, '\n');
        return true;
    }

    switch(opcion)
        {
        case 0:
            return false;
            break;
        case 1:
            opcionInsertarLibreria();
            break;
        case 2:
            opcionBorrarLibreria();
            break;
        case 3:
            opcionMostrarPedidos();
            break;
        case 4:
            opcionBuscarPedido();
            break;
        case 5:
            opcionBorrarPedido();
            break;
        case 6:
            opcionMoverPedido();
            break;
        case 7:
            opcionEstadistica();
            break;
        case 8:
            prepararPedidos();
            break;
        // caso de que no falle el cin (es un numero) pero no sea uno de los casos especificados
        default:
            cout <<"Opcion no valida, introduce un numero del 0 al 8"<<endl<<endl;
            cin.clear();
            cin.ignore(10000,'\n');
            break;
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
        int idLib = listaIDs->obtenerPosicion(generarNumAleatorio(0, listaIDs->contarInts()));
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

void introducirSeed()
{
    if(SEED != -1) srand (SEED);
    else srand (time(NULL));
}

void inicializarABB(){
    cout << "Creando el ABB con " << N_LIBRERIAS << " nodos:" << endl;

    arbolGlobal = new ArbolABB();
    generarArbolAleatorio(arbolGlobal);

    cout << "Arbol vacio creado:" << endl;
    arbolGlobal->InOrden(Mostrar);

}
