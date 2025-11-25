#ifndef CCONTROL.H
#define CCONTROL.H

#include <iostream>
using namespace std;

#define N_LIBRERIAS  10  //se definen el numero de librerias creadas inicialmente
#define N_PEDIDOS  30  //se definen el numero de pedidos creados inicialmente y en la opcion 8


struct Pedido{
    int id_libreria;
    string id_pedido;
    string cod_libro;
    string materia;
    int unidades;
    string fecha;
};

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
    void borrarPedido(string id_p);
    Pedido* buscarPedido(string id_p);
    bool estaEnLista(string id_p);
    bool listaVacia();
    void esCabeza();
    void esFinal();
    void esSiguiente();
    bool esActual();
    Pedido valorActual();
    Pedido valorCabeza();
    void recorrerLista();
    int contarPedidos();

};

struct Libreria{
    int id_libreria;
    string localidad;
    Lista* listaPedidos;
};

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
        void InOrden(void (*func)(Libreria, string), string busquedaParam, NodoArb *nodo=NULL, bool r=true);
        void PreOrden(void (*func)(Libreria), NodoArb *nodo=NULL, bool r=true);
        void PostOrden(void (*func)(Libreria), NodoArb *nodo=NULL, bool r=true);
    private:
        // Funciones auxiliares
        void Podar(NodoArb* &);
        void auxContador(NodoArb*);
        void auxAltura(NodoArb*, int);
};

void Mostrar(Libreria l);

//Preparacion de pedidos que se muestran por pantalla y se preparan. Se usa al inicio del programa.
void prepararPedidos();

//Loop principal del programa.
bool loopPrincipal();

//Crear y mostrar arbol global.
void inicializarABB();

//Mostrar cabecera de datos.
void mostrarCabecera();

//Permite rellenar una lista con pedidos.
void generarPedidos(Lista *lista);

//Reparte los pedidos de la lista en el arbol. Vacia la lista en el proceso.
void repartirPedidos(Lista *lista, ArbolABB *arbol);

//Muestra por pantalla el contenido de una lista de pedidos.
void mostrarLista(Lista *lista);

void crearArbolGlobal();

Libreria generarLibAleatoria();

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

//Prepara el dispositivo Rand.
void introducirSeed();

#endif // CCONTROL
