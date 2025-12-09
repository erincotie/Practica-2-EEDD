#ifndef CCONTROL.H

#define CCONTROL.H

#include <iostream>
#include <iomanip>

using namespace std;

#define N_LIBRERIAS  10 //Define el numero de librerias creadas inicialmente.
#define N_PEDIDOS 30   //Define el numero de pedidos creados por iteracion.
#define SEED -1          //Define la Seed que usara la generacion de numeros pseudo-aleatorio
                        //-1 -> Se usa el reloj del sistema como Seed.
                        //Cualquier otro numero se usara como Seed.

struct Pedido{
    int id_libreria;
    string id_pedido;
    string cod_libro;
    string materia;
    int unidades;
    string fecha;
};

//Socrecarga de operador <<
//Muestra por pantalla la informacion de un Pedido al ser pasado a cout.
ostream& operator<<(ostream& out, const Pedido pedido);

class NodoLista
{
private:
    Pedido valor;
    NodoLista *siguiente;
    friend class Lista;

public:
    NodoLista(Pedido p, NodoLista *sig = NULL)
    {
        valor = p;
        siguiente = sig;
    }
};
typedef NodoLista *pnodo;

class Lista
{
private:
    pnodo cabeza, actual, final;

public:
    Lista()
    {
        cabeza = actual = final= NULL;
    }
    ~Lista();

    void insertarPedido(Pedido p);
    void borrarPedido(Pedido p);
    void borrarPedido(const string *id_p);
    Pedido* buscarPedido(const string *id_p);
    bool listaVacia();
    void esCabeza();
    void esFinal();
    void esSiguiente();
    bool esActual();
    Pedido valorActual();
    Pedido valorCabeza();
    void recorrerLista();
    int contarPedidos();
    int sumarUnidades();
    int* contarMaterias();

};

class intNodoLista
{
private:
    int valor;
    intNodoLista *siguiente;
    friend class intLista;

public:
    intNodoLista(int num, intNodoLista *sig = NULL)
    {
        valor = num;
        siguiente = sig;
    }
};

class intLista
{
private:
    intNodoLista *cabeza;
    intNodoLista *actual;
    intNodoLista *final;

public:
    intLista()
    {
        cabeza = actual = final = NULL;
    }
    ~intLista();

    void insertarInt(int i);
    void borrarInt(int i);
    int obtenerPosicion(int posicion);
    bool esVacia();
    void recorrerLista();
    int contarInts();

};

struct Libreria{
    int id_libreria;
    string localidad;
    Lista* listaPedidos;
};

//Socrecarga de operador <<
//Muestra por pantalla la informacion de una Libreria al ser pasado a cout.
ostream& operator<<(ostream& out, const Libreria pedido);

class NodoArb
{
    private:
        // Miembros:
        Libreria dato;
        NodoArb *izquierdo;
        NodoArb *derecho;
        friend class ArbolABB;

    public:
        // Constructor:
        NodoArb(Libreria l, NodoArb *izq=NULL, NodoArb *der=NULL) :
            dato(l), izquierdo(izq), derecho(der) {}

};

class ArbolABB
{
    private:
        // Punteros de la lista, para cabeza y nodo actual:
        NodoArb *raiz;
        NodoArb *actual;
        int contador;
        int altura;

    public:
        // Constructor y destructor básicos:
        ArbolABB() : raiz(NULL), actual(NULL) {}
        ~ArbolABB();
         // Insertar en árbol ordenado:
        void Insertar(Libreria l);
        // Borrar un elemento del árbol:
        void Borrar(Libreria l);
        //Borrar una libreria a través de su ID:
        void Borrar(int id);
        // Función de búsqueda:
        bool Buscar(Libreria l);
        //Devuelve un puntero a la libreria si está se encuentra en el árbol, por su ID.
        Libreria* Buscar(int id);
        //Busca un pedido dentro de todas las librerias
        Pedido* BusquedaInOrden(bool (*func)(string id_p) , NodoArb *nodo, bool r);
        // Comprobar si el árbol está vacío:
        bool Vacio(NodoArb *r);
        // Comprobar si es un nodo hoja:
        bool EsHoja(NodoArb *r);
        // Contar número de nodos:
        const int NumeroNodos();
        const int AlturaArbol();
        // Calcular altura de un int:
        int Altura(Libreria l);
        // Moverse al nodo raiz:
        void Raiz();
        // Aplicar una función a cada elemento del árbol:
        void InOrden(void (*func)(Libreria), NodoArb *nodo=NULL, bool r=true);
        void InOrden(void (*func)(Libreria, const string*), const string *busquedaParam, NodoArb *nodo=NULL, bool r=true);
        Libreria* InOrden(bool (*func)(const Libreria*, const string*), const string *busquedaParam, NodoArb *nodo=NULL, bool r=true);

        void PreOrden(void (*func)(Libreria), NodoArb *nodo=NULL, bool r=true);
        void PostOrden(void (*func)(Libreria), NodoArb *nodo=NULL, bool r=true);
    private:
        // Funciones auxiliares
        void Podar(NodoArb* &);
        void auxContador(NodoArb*);
        void auxAltura(NodoArb*, int);
};

void Mostrar(Libreria l);

//Loop principal del programa.
bool loopPrincipal();

//Llama varias veces una funcion tras confirmar por el usuario.
//Muestra el string 'msg' como mensaje de confirmacion y '(y/n)'.
void repetirAccionWrapper(void (*func)(void), string msg);

//Funcion de opcion para insertar una libreria.
void opcionInsertarLibreria();

//Funcion de opcion para eliminar una libreria por ID.
void opcionBorrarLibreria();

//Funcion de opcion para mostrar todos los pedidos de una libreria.
void opcionMostrarPedidos();

//Funcion de opcion para borrar un pedido de su libreria.
void opcionBorrarPedido();

//Funcion de opcion para mover un pedido de una libreria a otra.
void opcionMoverPedido();

//Funcion de opcion para mostrar estadisticas de cada libreria.
void opcionEstadistica();

//Preparacion de pedidos que se muestran por pantalla y se reparten. Se usa al inicio del programa.
void prepararPedidos();

//Mostrar cabecera de datos.
void mostrarCabecera();

//Genera una Libreria con datos aleatorios.
Libreria generarLibAleatoria();

//Si el string introducido tiene un tanaño menor a 6. Introduce una 'P' al inicio del string.
void formatearCodigoPedido(string *codigo);

//Devuelve true si el string es compatible a un codigo.
//Acepta un codigo introducido tanto si tiene la 'P' como si no.
bool esCodigoPedido(const string *codigo);

//Muestra por pantalla el contenido de la libreria donde se encuentra el pedido buscado (por codigo).
void mostrarLibreriaPorPedido(const Libreria lib, const string *codigo);

//Devuelve true si el pedido especificado (por codigo) se encuentra en la libreria.
bool buscarLibreriaPorPedido(const Libreria *lib, const string *codigo);

//Borra el pedido especificado (por codigo) en la libreria.
//Muestra por pantalla el resultado final.
void borrarPorPedido(Libreria lib, const string *codigo);

//Devuelve el nombre de la materia mas popular en la libreria.
string MateriaMasPopular(Libreria lib);

//Devuelve el nombre de la materia menos popular en la libreria.
string MateriaMenosPopular(Libreria lib);

/*
    Devuelve estadisticas de una libreria especifica.
    Estadisticas: Top 5 librerias con mas pedidos,
    en cada una de ellas decir la media de unidades por pedido,
    la materia mas / menos popular.
*/
void estadisticaTopLibreriasPedidos(Libreria lib);

//Permite rellenar una lista con pedidos.
void generarPedidos(Lista *lista);

//Reparte los pedidos de la lista en el arbol. Vacia la lista en el proceso.
void repartirPedidos(Lista *lista, ArbolABB *arbol);

//Muestra por pantalla el contenido de una lista de pedidos.
void mostrarLista(Lista *lista);

//Permite rellenar un arbol con librerias en sus nodos
void generarArbolAleatorio(ArbolABB *abb);

//Funciones para generar los pedidos de manera aleatoria (auxiliares para la funcion generar Pedido del main)
//Genera un numero aleatorio entre un minimo y maximo
int generarNumAleatorio(int minimo, int maximo);

//Genera una letra mayuscula aleatoria (usa caracteres ASCII)
char generarLetraMayusAleatoria();

//Genera un codigo libro aleatorio del formato NNNCNN (N:digito, C: letra mayuscula)
string generarCodigoLibro();

//Genera un codigo pedido aleatorio del formato 'P'NNNNN (N:digito)
string generarCodigoPedido();

//Crear y mostrar arbol global.
void inicializarABB();

//Prepara la generacion de numeros enteros pseudo-aleatorios.
void introducirSeed();

#endif
