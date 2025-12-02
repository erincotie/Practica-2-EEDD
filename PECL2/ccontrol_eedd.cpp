#include "ccontrol.h"

#define NUM_MATERIAS 6
string MateriasLista[NUM_MATERIAS] = {"Matematicas", "Historia","Lengua", "Musica", "Tecnologia", "Fisica" };

using namespace std;
int *estadistica = new int [6];

ostream& operator<<(ostream& out, const Pedido pedido)
{
    out << "|  "
        << setw(11) << pedido.id_libreria   << "|"
        << setw(11) << pedido.id_pedido     << "|"
        << setw(12) << pedido.cod_libro     << "|"
        << setw(12) << pedido.materia       << "|"
        << setw(10) << pedido.unidades      << "|"
        << setw(10) << pedido.fecha         << "|";
    return out;
}

ostream& operator<<(ostream& out, const Libreria lib)
{
    out <<"ID: " << setw(3) << lib.id_libreria
    << "  Localidad: " << setw(12) << lib.localidad
    << " Num Pedidos: " << lib.listaPedidos->contarPedidos();
    return out;
}

void Mostrar(Libreria lib){
    cout << lib << endl;
}

//Destructor
ArbolABB::~ArbolABB()
{
    Podar(raiz);
}

//Árbol vacío
bool ArbolABB::Vacio(NodoArb *r)
{
    return r==NULL;
}

//NodoArb es de tipo hoja
bool ArbolABB::EsHoja(NodoArb *r)
{
    return !r->derecho && !r->izquierdo;
}

//Coloca el nodo actual en raíz
void ArbolABB::Raiz()
{
    actual = raiz;
}

// Poda: borrar todos los nodos a partir de uno incluido
void ArbolABB::Podar(NodoArb* &nodo)
{
   // Algoritmo recursivo, recorrido en postorden
   if(nodo) {
      Podar(nodo->izquierdo); // Podar izquierdo
      Podar(nodo->derecho);   // Podar derecho
      delete nodo;            // Eliminar nodo
      nodo = NULL;
   }
}

// Insertar un int en el árbol ABB
void ArbolABB::Insertar(Libreria l)
{
   NodoArb *padre = NULL;

   actual = raiz;
   // Buscar el int en el árbol, manteniendo un puntero al nodo padre
   while(!Vacio(actual) && l.id_libreria != actual->dato.id_libreria) {
      padre = actual;
      if(l.id_libreria > actual->dato.id_libreria) actual = actual->derecho;
      else if(l.id_libreria < actual->dato.id_libreria) actual = actual->izquierdo;
   }

   // Si se ha encontrado el elemento, regresar sin insertar
   if(!Vacio(actual)) return;
   // Si padre es NULL, entonces el árbol estaba vacío, el nuevo nodo será
   // el nodo raiz
   if(Vacio(padre)) raiz = new NodoArb(l);
   // Si el int es menor que el que contiene el nodo padre, lo insertamos
   // en la rama izquierda
   else if(l.id_libreria < padre->dato.id_libreria) padre->izquierdo = new NodoArb(l);
   // Si el int es mayor que el que contiene el nodo padre, lo insertamos
   // en la rama derecha
   else if(l.id_libreria > padre->dato.id_libreria) padre->derecho = new NodoArb(l);
}

// Eliminar un elemento de un árbol ABB
void ArbolABB::Borrar(Libreria l)
{
   NodoArb *padre = NULL;
   NodoArb *nodo;
   Libreria aux;

   actual = raiz;
   // Mientras sea posible que el valor esté en el árbol
   while(!Vacio(actual)) {
      if(l.id_libreria == actual->dato.id_libreria) { // Si el valor está en el nodo actual
         if(EsHoja(actual)) { // Y si además es un nodo hoja: lo borramos
            if(padre){ // Si tiene padre (no es el nodo raiz)
               // Anulamos el puntero que le hace referencia
               if(padre->derecho == actual) padre->derecho = NULL;
               else if(padre->izquierdo == actual) padre->izquierdo = NULL;
            }
            else raiz=NULL;

            delete actual; // Borrar el nodo
            actual = NULL;
            return;
         }
         else { // Si el valor está en el nodo actual, pero no es hoja
            // Buscar nodo
            padre = actual;
            // Buscar nodo más izquierdo de rama derecha
            if(actual->derecho) {
               nodo = actual->derecho;
               while(nodo->izquierdo) {
                  padre = nodo;
                  nodo = nodo->izquierdo;
               }
            }
            // O buscar nodo más derecho de rama izquierda
            else {
               nodo = actual->izquierdo;
               while(nodo->derecho) {
                  padre = nodo;
                  nodo = nodo->derecho;
               }
            }
            // Intercambiar valores de no a borrar u nodo encontrado
            // y continuar, cerrando el bucle. El nodo encontrado no tiene
            // por qué ser un nodo hoja, cerrando el bucle nos aseguramos
            // de que sólo se eliminan nodos hoja.
            aux = actual->dato;
            actual->dato = nodo->dato;
            nodo->dato = aux;
            actual = nodo;
         }
      }
      else { // Todavía no hemos encontrado el valor, seguir buscándolo
         padre = actual;
         if(l.id_libreria > actual->dato.id_libreria) actual = actual->derecho;
         else if(l.id_libreria < actual->dato.id_libreria) actual = actual->izquierdo;
      }
   }
}

void ArbolABB::Borrar(int id_libreria)
{
   NodoArb *padre = NULL;
   NodoArb *nodo;
   Libreria aux;

   actual = raiz;
   // Mientras sea posible que el valor esté en el árbol
   while(!Vacio(actual)) {
      if(id_libreria == actual->dato.id_libreria) { // Si el valor está en el nodo actual
         if(EsHoja(actual)) { // Y si además es un nodo hoja: lo borramos
            if(padre){ // Si tiene padre (no es el nodo raiz)
               // Anulamos el puntero que le hace referencia
               if(padre->derecho == actual) padre->derecho = NULL;
               else if(padre->izquierdo == actual) padre->izquierdo = NULL;
            }
            else raiz=NULL;

            delete actual; // Borrar el nodo
            actual = NULL;
            return;
         }
         else { // Si el valor está en el nodo actual, pero no es hoja
            // Buscar nodo
            padre = actual;
            // Buscar nodo más izquierdo de rama derecha
            if(actual->derecho) {
               nodo = actual->derecho;
               while(nodo->izquierdo) {
                  padre = nodo;
                  nodo = nodo->izquierdo;
               }
            }
            // O buscar nodo más derecho de rama izquierda
            else {
               nodo = actual->izquierdo;
               while(nodo->derecho) {
                  padre = nodo;
                  nodo = nodo->derecho;
               }
            }
            // Intercambiar valores de no a borrar u nodo encontrado
            // y continuar, cerrando el bucle. El nodo encontrado no tiene
            // por qué ser un nodo hoja, cerrando el bucle nos aseguramos
            // de que sólo se eliminan nodos hoja.
            aux = actual->dato;
            actual->dato = nodo->dato;
            nodo->dato = aux;
            actual = nodo;
         }
      }
      else { // Todavía no hemos encontrado el valor, seguir buscándolo
         padre = actual;
         if(id_libreria > actual->dato.id_libreria) actual = actual->derecho;
         else if(id_libreria < actual->dato.id_libreria) actual = actual->izquierdo;
      }
   }
}

// Recorrido de árbol en inorden, aplicamos la función func, que tiene
// el prototipo:
// void func(int&);
void ArbolABB::InOrden(void (*func)(Libreria) , NodoArb *nodo, bool r)
{
  if (raiz==NULL) {cout<<"Arbol vacio"<<endl; return;}
   if(r) nodo = raiz;
   if(nodo->izquierdo) InOrden(func, nodo->izquierdo, false);
   func(nodo->dato);
   if(nodo->derecho) InOrden(func, nodo->derecho, false);
}

void ArbolABB::InOrden(void (*func)(Libreria, const string*), const string *busquedaParam , NodoArb *nodo, bool r)
{
  if (raiz==NULL) {cout<<"Arbol vacio"<<endl; return;}
   if(r) nodo = raiz;
   if(nodo->izquierdo) InOrden(func, busquedaParam, nodo->izquierdo, false);
   func(nodo->dato, busquedaParam);
   if(nodo->derecho) InOrden(func, busquedaParam, nodo->derecho, false);
}

Libreria* ArbolABB::InOrden(bool (*func)(const Libreria*, const string*), const string *busquedaParam, NodoArb *nodo, bool r)
{
    if (raiz==NULL) { return nullptr;}
    if(r) nodo = raiz;
    if(func(&(nodo->dato), busquedaParam)) return &(nodo->dato);
    if(nodo->izquierdo) return InOrden(func, busquedaParam, nodo->izquierdo, false);
    if(nodo->derecho) return InOrden(func, busquedaParam, nodo->derecho, false);
    return nullptr;
}

// Recorrido de árbol en preorden, aplicamos la función func, que tiene
// el prototipo:
// void func(int&);
void ArbolABB::PreOrden(void (*func)(Libreria), NodoArb *nodo, bool r)
{
      if (raiz==NULL) {cout<<"Arbol vacio"<<endl; return;}
   if(r) nodo = raiz;
   func(nodo->dato);
   if(nodo->izquierdo) PreOrden(func, nodo->izquierdo, false);
   if(nodo->derecho) PreOrden(func, nodo->derecho, false);
}

// Recorrido de árbol en postorden, aplicamos la función func, que tiene
// el prototipo:
// void func(Libreria&); que es la funcion que imprime los datos de libreria
void ArbolABB::PostOrden(void (*func)(Libreria), NodoArb *nodo, bool r)
{
      if (raiz==NULL) {cout<<"Arbol vacio"<<endl; return;}
   if(r) nodo = raiz;
   if(nodo->izquierdo) PostOrden(func, nodo->izquierdo, false);
   if(nodo->derecho) PostOrden(func, nodo->derecho, false);
   func(nodo->dato);
}

// Buscar un valor en el árbol
bool ArbolABB::Buscar(Libreria l)
{
   actual = raiz;

   // Todavía puede aparecer, ya que quedan nodos por mirar
   while(!Vacio(actual)) {
      if(l.id_libreria == actual->dato.id_libreria) return true; // int encontrado
      else if(l.id_libreria > actual->dato.id_libreria) actual = actual->derecho; // Seguir
      else if(l.id_libreria < actual->dato.id_libreria) actual = actual->izquierdo;
   }
   return false; // No está en árbol
}

Libreria* ArbolABB::Buscar(int id)
{
   actual = raiz;

   // Todavía puede aparecer, ya que quedan nodos por mirar
   while(!Vacio(actual)) {
      if(id == actual->dato.id_libreria) return &actual->dato; // id encontrado
      else if(id > actual->dato.id_libreria) actual = actual->derecho; // Seguir
      else if(id < actual->dato.id_libreria) actual = actual->izquierdo;
   }
   return nullptr; // No está en árbol
}


// Calcular la altura del nodo que contiene el int dat
int ArbolABB::Altura(Libreria l)
{
   int altura = 0;
   actual = raiz;

   // Todavía puede aparecer, ya que quedan nodos por mirar
   while(!Vacio(actual)) {
      if(l.id_libreria == actual->dato.id_libreria) return altura; // int encontrado
      else {
         altura++; // Incrementamos la altura, seguimos buscando
         if(l.id_libreria > actual->dato.id_libreria) actual = actual->derecho;
         else if(l.id_libreria < actual->dato.id_libreria) actual = actual->izquierdo;
      }
   }
   return -1; // No está en árbol
}

// Contar el número de nodos
const int ArbolABB::NumeroNodos()
{
   contador = 0;

   auxContador(raiz); // FUnción auxiliar
   return contador;
}

// Función auxiliar para contar nodos. Función recursiva de recorrido en
//   preorden, el proceso es aumentar el contador
void ArbolABB::auxContador(NodoArb *nodo)
{
   contador++;  // Otro nodo
   // Continuar recorrido
   if(nodo->izquierdo) auxContador(nodo->izquierdo);
   if(nodo->derecho)   auxContador(nodo->derecho);
}

// Calcular la altura del árbol, que es la altura del nodo de mayor altura.
const int ArbolABB::AlturaArbol()
{
   altura = 0;

   auxAltura(raiz, 0); // Función auxiliar
   return altura;
}

// Función auxiliar para calcular altura. Función recursiva de recorrido en
// postorden, el proceso es actualizar la altura sólo en nodos hojas de mayor
// altura de la máxima actual
void ArbolABB::auxAltura(NodoArb *nodo, int a)
{
   // Recorrido postorden
   if(nodo->izquierdo) auxAltura(nodo->izquierdo, a+1);
   if(nodo->derecho)   auxAltura(nodo->derecho, a+1);
   // Proceso, si es un nodo hoja, y su altura es mayor que la actual del
   // árbol, actualizamos la altura actual del árbol
   if(EsHoja(nodo) && a > altura) altura = a;
}

Lista::~Lista()
{
    pnodo aux;
    while(cabeza)
    {
        aux = cabeza;
        cabeza = cabeza->siguiente;
        delete aux;
    }
    actual = NULL;
}

void Lista::insertarPedido(Pedido p) {
    pnodo aux;

    if (listaVacia())
    {
        cabeza = new NodoLista(p, NULL);
        final=cabeza;
        actual=cabeza;
    }
    else
    {
        aux= new NodoLista(p,NULL);
        final->siguiente=aux;
        final=aux;
    }
}

void Lista::borrarPedido(Pedido p) {
    pnodo anterior;

    if (cabeza == NULL) return;
    else{
        actual = cabeza;

        while (actual->valor.id_pedido != p.id_pedido && (actual->siguiente)!=NULL)
        {
            anterior=actual;
            actual=actual->siguiente;
        }

        if (actual->valor.id_pedido == p.id_pedido){ //comprobación de que está v en la lista
            if(actual==cabeza) //si el que borramos es el primero en la lista, se modifica la cabeza
                cabeza = actual->siguiente;
            else
            {
                anterior->siguiente = actual->siguiente;
                if (actual==final) // si es el ultimo el que borramos, se modifica el final
                {
                    final=anterior;
                }
            }
            actual->siguiente=NULL;
            delete actual;
        }
        else return;
    }
}


void Lista::borrarPedido(const string *id_p) {
    pnodo anterior;

    if (cabeza == NULL) return;
    else{
        actual = cabeza;

        while (actual->valor.id_pedido != *id_p && (actual->siguiente)!=NULL)
        {
            anterior=actual;
            actual=actual->siguiente;
        }

        if (actual->valor.id_pedido == *id_p){ //comprobación de que está v en la lista
            if(actual==cabeza) //si el que borramos es el primero en la lista, se modifica la cabeza
                cabeza = actual->siguiente;
            else
            {
                anterior->siguiente = actual->siguiente;
                if (actual==final) // si es el ultimo el que borramos, se modifica el final
                {
                    final=anterior;
                }
            }
            actual->siguiente=NULL;
            delete actual;
        }
        else return;
    }
}

Pedido* Lista::buscarPedido(const string *id_p) {

    if (cabeza == NULL) return nullptr;
    else{
        actual = cabeza;

        while (actual->valor.id_pedido != *id_p && (actual->siguiente)!=NULL)
        {
            actual=actual->siguiente;
        }

        if (actual->valor.id_pedido == *id_p){ //comprobación de que está v en la lista
            return &actual->valor;
        }
        else return nullptr;
    }
}

bool Lista::listaVacia(){
    return cabeza == NULL;
}

void Lista::esCabeza()
{
    actual = cabeza;
}

void Lista::esFinal()
{
    esCabeza();
    if(!listaVacia())
        while(actual->siguiente)
            esSiguiente();
}

void Lista::esSiguiente()
{
    if(actual) actual = actual->siguiente;
}

bool Lista::esActual()
{
    return actual != NULL;
}

Pedido Lista::valorActual()
{
    return actual->valor;
}

Pedido Lista::valorCabeza()
{
    return cabeza->valor;
}

void Lista::recorrerLista()
{
    if(this->listaVacia())
    {
        cout << "(vacia)" << endl;
        return;
    }

    pnodo aux;
    aux = cabeza;

    while(aux)
    {
        cout << aux->valor << endl;

        aux = aux->siguiente;
    }
}

int Lista::contarPedidos()
{
    pnodo aux;
    aux = cabeza;
    int cont =0;

    while(aux)
    {
        cont ++;
        aux = aux->siguiente;
    }
    return cont;
}

int Lista::sumarUnidades()
{
    pnodo aux;
    aux = cabeza;
    int cont =0;

    while(aux)
    {
        cont += aux->valor.unidades;
        aux = aux->siguiente;
    }
    return cont;
}


void intLista::insertarInt(int i){
    intNodoLista *aux;

    if (esVacia())
    {
        cabeza = new intNodoLista(i, NULL);
        final=cabeza;
        actual=cabeza;
    }
    else
    {
        aux= new intNodoLista(i, NULL);
        final->siguiente=aux;
        final=aux;
    }
}

void intLista::borrarInt(int i) {
    intNodoLista *anterior;

    if (cabeza == NULL) return;
    else{
        actual = cabeza;

        while (actual->valor != i && (actual->siguiente)!=NULL)
        {
            anterior=actual;
            actual=actual->siguiente;
        }

        if (actual->valor == i){ //comprobación de que está v en la lista
            if(actual==cabeza) //si el que borramos es el primero en la lista, se modifica la cabeza
                cabeza = actual->siguiente;
            else
            {
                anterior->siguiente = actual->siguiente;
                if (actual==final) // si es el ultimo el que borramos, se modifica el final
                {
                    final=anterior;
                }
            }
            actual->siguiente=NULL;
            delete actual;
        }
        else return;
    }
}

bool intLista::esVacia(){
    return cabeza == NULL;
}

void intLista::recorrerLista()
{
    if(this->esVacia())
    {
        cout << "(vacia)" << endl;
        return;
    }

    intNodoLista *aux;
    aux = cabeza;

    while(aux)
    {
        cout << aux->valor << ",";

        aux = aux->siguiente;
    }
}

int intLista::obtenerPosicion(int posicion)
{
    int tamano = this->contarInts();
    if(this->esVacia() || posicion > (tamano) )
    {
        return INT_MIN;
    }

    intNodoLista *aux;
    aux = cabeza;

    for(int i = 0; i < posicion; i++){
        aux = aux->siguiente;
    }

    return aux->valor;
}

int intLista::contarInts()
{
    intNodoLista *aux;
    aux = cabeza;
    int cont =0;

    while(aux)
    {
        cont ++;
        aux = aux->siguiente;
    }
    return cont;
}

int* Lista::contarMaterias()
{
    pnodo aux;
    aux = cabeza;
    int *estadistica = new int [6]();

    while (aux)
    {
        for(int i = 0; i < NUM_MATERIAS; i++)
        {
            if(aux->valor.materia == MateriasLista[i])
            {
                estadistica[i]+= aux->valor.unidades;
                break;
            }
        }

        aux = aux->siguiente;
    }
    return estadistica;
}
