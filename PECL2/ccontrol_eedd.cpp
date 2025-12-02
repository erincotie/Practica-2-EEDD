#include "ccontrol.h"

#define NUM_MATERIAS 6
string MateriasLista[NUM_MATERIAS] = {"Matematicas", "Historia","Lengua", "Musica", "Tecnologia", "Fisica" };

using namespace std;
int *estadistica = new int [6];

//Operador que sobrecarga el cout para imprimir los datos de un pedido en el formato necesario
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


//Operador que sobrecarga el cout para imprimir los datos de una libreria en el formato necesario
ostream& operator<<(ostream& out, const Libreria lib)
{
    out <<"ID: " << setw(3) << lib.id_libreria
    << "  Localidad: " << setw(12) << lib.localidad
    << " Num Pedidos: " << lib.listaPedidos->contarPedidos();
    return out;
}


//Funcion Mostrar, en conjunción con el operador que sobrecarga el cout, muestran los datos de la libreria
void Mostrar(Libreria lib){
    cout << lib << endl;
}


//Destructor de árbol, llama a Podar, que elimina todos los nodos a partir de la raíz
ArbolABB::~ArbolABB()
{
    Podar(raiz);
}


//Devuelve un booleano true si el árbol es vacío
bool ArbolABB::Vacio(NodoArb *r)
{
    return r==NULL;
}

//NodoArb es de tipo hoja, es decir no tiene hijos izquierdo y derecho
bool ArbolABB::EsHoja(NodoArb *r)
{
    return !r->derecho && !r->izquierdo;
}

//Coloca el nodo actual en raíz, para poder recorrer el árbol
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

// Insertar una libreria en el árbol ABB, asegurandose de que esté ordenado por ID libreria
void ArbolABB::Insertar(Libreria l)
{
   NodoArb *padre = NULL;

   actual = raiz;
   // Buscar la libreria en el árbol, manteniendo un puntero al nodo padre
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
   // Si el ID libreria es menor que el que contiene el nodo padre, lo insertamos
   // en la rama izquierda
   else if(l.id_libreria < padre->dato.id_libreria) padre->izquierdo = new NodoArb(l);
   // Si el ID libreria es mayor que el que contiene el nodo padre, lo insertamos
   // en la rama derecha
   else if(l.id_libreria > padre->dato.id_libreria) padre->derecho = new NodoArb(l);
}

// Eliminar una libreria de un árbol ABB
void ArbolABB::Borrar(Libreria l)
{
   NodoArb *padre = NULL;
   NodoArb *nodo;
   Libreria aux;

   actual = raiz;
   // Mientras sea posible que el valor esté en el árbol, es decir que recorramos el árbol hasta que esté vacío
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
            // Buscar el nodo menor de la rama derecha
            if(actual->derecho) {
               nodo = actual->derecho;
               while(nodo->izquierdo) {
                  padre = nodo;
                  nodo = nodo->izquierdo;
               }
            }
            // O buscar el nodo mayor de la rama izquierda
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


//Función Borrar, realiza la misma función que la anterior y con el mismo mecanismo de borrado,
//pero introduciendo el ID librería como el parámetro directamente
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
// void func(Libreria);
void ArbolABB::InOrden(void (*func)(Libreria) , NodoArb *nodo, bool r)
{
  if (raiz==NULL) {cout<<"Arbol vacio"<<endl; return;}
   if(r) nodo = raiz;
   //recorre primero la rama izquierda, procesando el nodo con la función que elijamos, luego la raíz
   if(nodo->izquierdo) InOrden(func, nodo->izquierdo, false);
   func(nodo->dato);
   //finalmente recorre la rama derecha
   if(nodo->derecho) InOrden(func, nodo->derecho, false);
}


//Recorrido del árbol en inorden, para distintas opciones, en este caso se utiliza una función que recoja una libreria y un string y devuelva void
//La funcion inorden tambien recoge ese mismo string como parametro para poder utilizarlo en la llamada de func.
//Tiene el mismo mecanismo de recorrido que la funcion anterior
void ArbolABB::InOrden(void (*func)(Libreria, const string*), const string *busquedaParam , NodoArb *nodo, bool r)
{
  if (raiz==NULL) {cout<<"Arbol vacio"<<endl; return;}
   if(r) nodo = raiz;
   if(nodo->izquierdo) InOrden(func, busquedaParam, nodo->izquierdo, false);
   func(nodo->dato, busquedaParam);
   if(nodo->derecho) InOrden(func, busquedaParam, nodo->derecho, false);
}


//Recorrido del árbol en Inorden, en este caso devuelve un puntero a Libreria cuando la funcion devuelve un true, al procesar el nodo
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


// Buscar un valor en el árbol, devuelve un true si se encuentra el valorm y si se recorre el arbol sin llegar a encontrar una libreria con el mismo ID, devuelve false.
bool ArbolABB::Buscar(Libreria l)
{
   actual = raiz;

   // Todavía puede aparecer, ya que quedan nodos por mirar
   while(!Vacio(actual)) {
      if(l.id_libreria == actual->dato.id_libreria) return true; // int encontrado
      else if(l.id_libreria > actual->dato.id_libreria) actual = actual->derecho; // Seguir por la derecha
      else if(l.id_libreria < actual->dato.id_libreria) actual = actual->izquierdo; // Seguir por la izquierda
   }
   return false; // No está en árbol
}


//Funcion Buscar: en este caso devuelve un puntero a Libreria si se encuentra una Libreria con el mismo ID que el parametro, y en caso contrario devuelve un nullptr
Libreria* ArbolABB::Buscar(int id)
{
   actual = raiz;

   // Todavía puede aparecer, ya que quedan nodos por mirar
   while(!Vacio(actual)) {
      if(id == actual->dato.id_libreria) return &actual->dato; // id encontrado
      else if(id > actual->dato.id_libreria) actual = actual->derecho; // Seguir por la derecha
      else if(id < actual->dato.id_libreria) actual = actual->izquierdo; // Seguir por la izquierda
   }
   return nullptr; // No está en árbol
}


// Calcular la altura del nodo que contiene la Libreria l
int ArbolABB::Altura(Libreria l)
{
   int altura = 0;
   actual = raiz;

   // Todavía puede aparecer, ya que quedan nodos por mirar
   while(!Vacio(actual)) {
      if(l.id_libreria == actual->dato.id_libreria) return altura; // Libreria encontrada
      else {
         altura++; // Incrementamos la altura, seguimos buscando
         if(l.id_libreria > actual->dato.id_libreria) actual = actual->derecho; //Sigue por la derecha
         else if(l.id_libreria < actual->dato.id_libreria) actual = actual->izquierdo; //Sigue por la izquierda
      }
   }
   return -1; // No está en árbol
}

// Contar el número de nodos
const int ArbolABB::NumeroNodos()
{
   contador = 0;

   auxContador(raiz); // Función auxiliar
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


//Destructor de Lista, mientras la cabeza no sea NULL se mueve un puntero auxiliar al siguiente y se borra el primer elemento
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

//Insertar Pedido en una lista, se inserta al final de la lista (sin ordenar)
void Lista::insertarPedido(Pedido p) {
    pnodo aux;

    if (listaVacia())
    {
        //Si la lista es vacia, se modifica la cabeza, final, y actual para que todos apunten al nuevo Nodo
        cabeza = new NodoLista(p, NULL);
        final=cabeza;
        actual=cabeza;
    }
    else
    {
        //Si no, se añade al final de la lista un nuevo Nodo, y se cambia el final
        aux= new NodoLista(p,NULL);
        final->siguiente=aux;
        final=aux;
    }
}


//Borrar pedido, recorre la lista hasta encontrar el pedido y lo borra
void Lista::borrarPedido(Pedido p) {
    pnodo anterior;

    //Si la lista está vacía, no se borra nada
    if (cabeza == NULL) return;
    else{
        actual = cabeza;

        //Se recorre la lista hasta que se encuentre un Pedido con el mismo ID o se termine la lista (que el siguiente sea NULL)
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
            //Borrado del nodo
            actual->siguiente=NULL;
            delete actual;
        }
        else return;
    }
}

//Funcion borrarPedido, realiza la misma tarea que que el anterior pero toma como parámetro el ID del pedido para comparar directamente
//Sigue el mismo mecanismo descrito antes
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


//Funcion buscarPedido, devuelve un puntero a un pedido si al recorrer la lista se encuentra uno con el mismo ID
//En el caso de no encontrarlo se devuelve un nullptr.
Pedido* Lista::buscarPedido(const string *id_p) {

    //Si la lista está vacia
    if (cabeza == NULL) return nullptr;
    else{
        actual = cabeza;

        //recorre la lista hasta encontrar el pedido, o que la lista se termine
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


//Funcion listaVacia, devuelve true si la lista está vacía, es decir la cabeza es NULL
bool Lista::listaVacia(){
    return cabeza == NULL;
}


//Funcion esCabeza, pone el puntero de actual a la cabeza de lista
void Lista::esCabeza()
{
    actual = cabeza;
}


//Funcion esFinal, pone el puntero de actual al final de lista, utilizando dos funciones auxiliares
void Lista::esFinal()
{
    esCabeza();
    if(!listaVacia())
        while(actual->siguiente)
            esSiguiente();
}


//Funcion esSiguiente, mueve el puntero de actual al siguiente elemento de la lista (a menos que sea NULL)
void Lista::esSiguiente()
{
    if(actual) actual = actual->siguiente;
}


//Funcion esActual, devuelve true si el puntero actual no es NULL
bool Lista::esActual()
{
    return actual != NULL;
}


//Funcion valorActual, devuelve el pedido que almacena el puntero actual
Pedido Lista::valorActual()
{
    return actual->valor;
}


//Funcion valorCabeza, devuelve el pedido que almacena el puntero cabeza
Pedido Lista::valorCabeza()
{
    return cabeza->valor;
}


//Funcion recorrerLista, imprime los valores de la lista, en conjunción con el operador que sobrecarga cout.
void Lista::recorrerLista()
{
    if(this->listaVacia())
    {
        //Si es vacía imprime un mensaje que lo indique
        cout << "(vacia)" << endl;
        return;
    }

    pnodo aux;
    aux = cabeza;

    //Mientras no esté vacía, imprime los datos de cada pedido
    while(aux)
    {
        cout << aux->valor << endl;

        aux = aux->siguiente;
    }
}


//Funcion contarPedidos, recorre la lista y suma 1 a un contador en cada iteracion, para contar el numero de elementos
int Lista::contarPedidos()
{
    pnodo aux;
    aux = cabeza;
    int cont =0;

    //recorre la lista hasta que este vacía, si comienza vacía devuelve 0 directamente
    while(aux)
    {
        cont ++;
        aux = aux->siguiente;
    }
    return cont;
}


//Funcion sumarUnidades, recorre la lista y suma las unidades de cada pedido
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


//Funcion InsertarInt, realiza la misma funcion que InsertarPedido, pero con una lista de enteros
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


//Funcion BorrarInt, realiza la misma funcion que BorrarPedido, pero con una lista de enteros
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


//Funcion esVacia, indica si la cabeza de lista es NULL, es decir la lista está vacía
bool intLista::esVacia(){
    return cabeza == NULL;
}


//Funcion recorrerLista, imprime los datos de la lista de enteros
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


//Funcion obtenerPosicion, devuelve el entero que se sitúe en la posicion indicada como el parametro
int intLista::obtenerPosicion(int posicion)
{
    int tamano = this->contarInts();
    //Si la posicion que se indica es mayor al numero de elementos o la lista es vacía se devuelve INT_MIN
    if(this->esVacia() || posicion > (tamano) )
    {
        return INT_MIN;
    }

    intNodoLista *aux;
    aux = cabeza;

    //Si no, se recorre la lista hasta llegar a la posicion y se devuelve el entero
    for(int i = 0; i < posicion; i++){
        aux = aux->siguiente;
    }

    return aux->valor;
}


//Funcion contarInts, recorre la lista y cuenta el numero de elementos
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


//Funcion contarMaterias, recorre una Lista y acumula el número de unidades de cada materia en un array,
//cuyas posiciones corresponden a las posiciones de las materias en su array de definicion
//devuelve el array con la acumulacion de unidades de cada materia
int* Lista::contarMaterias()
{
    pnodo aux;
    aux = cabeza;
    int *estadistica = new int [6]();

    //recorre la lista hasta que esta sea vacia
    while (aux)
    {
        //recorre el array materias, para encontrar la posicion de la materia y si coincide añadir las unidades al array estadistica
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
