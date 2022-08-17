//Arely Herrera Pamila  201877898
//Nestor Tellez Ronquillo 201826858

/*el proposito de este programa consiste principalmente en aplicar elconcepto de memoriadinamica en listas ligadas pero ahora con una
transformación mas practica cómo lo son listas doblemente ligadas las cuales tendran un campo mas que lista simples con el proposito
de ligar doblemente a los nodos para que asi se pueda acceder desde un apuntador a un nodo a otro nodo adelante y otro hacia atras es decir
facilitara recorrer la lista de adelante hacia atras asi como de atras  hacia adelante*/
#define NULL 0
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;

// los elementos que vienen agrupados a continuaci�on entre llaves 
//componen una estructura
struct nodo {
    int dato;
    struct nodo *sig,  *ant;
};
// typedef define un nombre alternativo  a tipos existentes 
//es una manera de instanciar nodo ( ace referencia a que es un puntero de tipo nodo)
typedef struct nodo* lista;

//prototipo de las funciones
bool listaVacia(lista& list);
void mostrarLD(lista& list);
void insertarInicio(lista& list, int date);
void insertarFinal(lista& list, int date);
void eliminarInicio(lista& list);
void eliminarFinal(lista& list);
void primero(lista& list);
void posicion(lista& list, int date);
void mostrarUltimo(nodo* list);
void sucesor(nodo* list, int pos);
void predecesor(nodo* list, int pos);
void menu();

/*funcion principal 
int main()
{
    menu();
    //se hace una pausa esperando que el usuario presione alguna tecla
    system("pause");
    return 0;
}*/


//retorna un valor de tipo booleano - true en caso de que la lista este vacia
bool listaVacia(lista& list) {
    if (list == NULL) {
        //cout << "\n ARBOL VACIO!!!\n";
        return true;
    }
    return false;
}
//este metodo imprime en pantalla los elementosexistentes en la lista
void mostrarLD(lista& list) {
    //primero verifica que la lista no este vacia, para ello manda a llamar 
    //a la funcion listaVacia()
    if (listaVacia(list) == false) {
        struct nodo* p = list;
        cout << "\n    ";
        //con p se apunta al inicio de la lista que es donde se encuentra 
         //el puntero list, p se recorre hasta que llegue a la ultima posicion
          //de la lista
        while (p->sig != NULL) {
            cout << p->dato << " ";
            p = p->sig;
        }
        // while ya no entra a imprimir el elemento en la ultima posicion 
         //por su condicion, esta se imprime al final del ciclo
        cout << p->dato << "   \n";
    }

}

void insertarInicio(lista& list, int date)
{      //se crea un nuevo nodo auxiliar
    lista p = new (struct nodo);
    //al cual se le asignan valores a sus campos
    p->dato = date;
    p->ant = NULL;
    p->sig = NULL;
    // si la lista esta vacia hace que list ocupe la posicion de p
    //es decir que directamente p pase a ser el primer nodo en la lista
    if (list != NULL) {
        //se enlazan doblemente  el apuntador al primer nodo de la lista 
        // con el apuntador al nodo auxiliar para conectar este a la lista
        list->ant = p;
        p->sig = list;
    }
    //el nodo al que apunta p se convierte en el primer nodo de la lista
    list = p;
}
void insertarFinal(lista& list, int date) {
    //se crea un nodo y un apuntador auxiliar 
    struct nodo* aux;
    lista p = new (struct nodo);
    //se asignan valores a lo campos del nodo
    p->dato = date;
    p->ant = NULL;
    p->sig = NULL;
    //si la lista esta vacia el nodo al que apunta p pasa a ser el primer
    // nodo de la lista
    if (list == NULL) {
        list = p;
    }
    else {
        //si no es el caso auxiliar apunta a la primera poisicion y recorre 
        //la lista asta llegar al ultimo nodo
        aux = list;
        while (aux->sig != NULL) {
            aux = aux->sig;
        }
        //conecta doblemente al apuntador al nodo nuevo  con el apuntador
        //al ultimo nodo de l lista que es el que lleva el puntero auxiliar
        aux->sig = p;
        p->ant = aux;
    }
}
//metodo que inserta nodos hasta crear un arbol
void insertarArbol(lista& list, int date) {
    lista p = new (struct nodo); //crea un nodo nuevo de tipo lista con dos apuntadores
    //se asignan valores a lo campos del nodo
    p->dato = date;// el nodo toma un valor
    p->ant = NULL;// apuntador a la izquierda del nodo nuevo se inicializa en NULL , asi como tambien apuntador a derecha de nodo
    p->sig = NULL;
    list = p; // el nodo nuevo ya creado e i nicializado se agrega al arbol
}
//funcion que elimina el nodo que se encuentra al inicio de la lista doblemente ligada
void eliminarInicio(lista& list) {
    int elim;
    //valida que no este vacia para seguir con el proceso
    if (listaVacia(list) == false) {
        //crea un apuntador auxiliar
        struct nodo* aux = list;
        //guarda en una variable temporal el dato a eliminar
        elim = list->dato;
        if (list->sig == NULL) {
            delete(list);
            list = NULL;
        }
        else {
            //el puntero auxiliar guarda la posicion en la que se encuentra lista
            aux = list;
            //list cambia de posicion para indicar que ahora ese sera el nodo inicial
            list = list->sig;
            //se asigna BULL al campo anterior del nodo para desenlazar 
            //el nodo que se va a eliminar
            list->ant = NULL;
            //se libera la memoria donde se encontraba el nodo
            delete(aux);
        }
        cout << "\n dato eliminado al inicio es : " << elim;
    }

}
//funcion que elimina el nodo que se encuentra al final de la lista
void eliminarFinal(lista& list) {
    int elim;
    //valida que no este vacia para seguir con el proceso
    if (listaVacia(list) == false) {
        //crea un apuntador auxiliar
        struct nodo* aux = list;
        //si lista en su capo siguiente es null eso significa que solo hay un 
        // nodo dentro de la lista
        if (list->sig == NULL) {
            //y a ese nodo solo hay que extraerle el dato a eliminar 
            elim = list->dato;
            //liberar la memoria
            delete(list);
            //reasignarle null al apuntador lista para referenciar vacio
            list = NULL;
        }
        else {
            //se asigna que apunte al primer nodo al puntero auxiliar
            aux = list;
            //se recorre el auxiliar comparando si dos nodos despues 
            //de su posicion existe null
            while (aux->sig->sig != NULL)
            {
                aux = aux->sig;
            }
            //se extrae el dato a eliminar
            elim = aux->sig->dato;
            //se libera memoria 
            delete(aux->sig);
            //se desconecta null del nodo ya eliinado y apunta a null
            //referenciando que es el nodo en la ultima posicion de la lista
            aux->sig = NULL;
        }
        //cout << "\n dato eliminado al final es : " << elim;
    }
}

void eliminarFinal2(lista& list) {
 if(list != NULL){
    struct nodo *aux = list;
    while(aux != NULL){
      delete(aux);
      aux = aux -> sig;
   }  
 }  
}

void primero(lista& list)
{
    int prim;
    if (listaVacia(list) == false)
        prim = list->dato;                //list apunta al primer elemento
    cout << "\n El primer elemento es : " << prim << "\n";


}

void posicion(lista& list, int date)
{
    if (listaVacia(list) == false) {

        int cont = 1;
        struct nodo* aux;
        aux = list;
        while (aux->sig != NULL) {
            cont++;                    //cuenta los elementos en la lista
            aux = aux->sig;
        }
        if (date > cont || date < 1)
            cout << "\n Valor fuera de rango\n";
        else {
            aux = list;
            for (int i = 1; i < date; i++)  //recorre la lista hasta llegar a la posicion
                aux = aux->sig;
            cout << "\n El dato es: " << aux->dato << "\n";
        }

    }



}

//funcion que muetras el ultimo elemento de la lista
void mostrarUltimo(nodo* list) {

    //verificar que la lista no este vacia
    if (listaVacia(list) == false) {

        struct nodo* q;


        //conectandolo con la lista
        q = list;
        //while para recorrer la lista hasta el ultimo elento
        while (q->sig != NULL)
        {
            q = q->sig;
        }
        cout << "El ultimo elemento es " << q->dato << endl;

    }

}

//funcion para encontrar el sucesor de una posicion especifica
void sucesor(nodo* list, int pos) {
    //verificar que la lista no este vacia 
    if (listaVacia(list) == false) {
        //contador de elementos de lista para no trabajar con rangos erroneos
        int numElementos = 1;


        struct nodo* p;
        //conectando el nuevo nodo con la lista
        p = list;
        //contador de elementos de la lsita
        while (p->sig != NULL)
        {

            numElementos++;
            p = p->sig;

        }
        p = list;

        //caso de que su sucesor no exista
        if (numElementos < pos + 1)
        {
            cout << " ERROR DE RANGO \n";
        }
        else
        {
            //buscar el sucesor
            for (int i = 1; i < pos + 1; i++)
            {
                p = p->sig;

            }
            cout << "EL SUCESOR DE LA POSICION  [" << pos << "] ES " << "(" << p->dato << ")" << endl;
        }

    }
}

//funcion para encontrar el predecesor de una posicion especifica
void predecesor(nodo* list, int pos) {
    //verificar que la lista no este vacia
    if (listaVacia(list) == false) {
        //contador elementos
        int numElementos = 1;
        struct nodo* p;

        p = list;
        //comprobar cuantos nodos tiene
        while (p->sig != NULL)
        {

            numElementos++;
            p = p->sig;

        }
        //reiniciar posicion p
        p = list;
        //caso de que el predecesor no exista
        if (numElementos < pos || pos == 1)
        {
            cout << " ERROR DE RANGO \n";
        }

        else
            //buscar  predecesor
        {
            for (int i = 1; i < pos - 1; i++)
            {
                p = p->sig;

            }
            cout << "EL PREDECESOR DE LA POSICION  [" << pos << "] ES " << "(" << p->dato << ")" << endl;
        }

    }

}




/*/Esta funcion solo muestra el menu de opciones de lista dinamica en pantalla
void menu() {
    int op, date;
    //se inicializa lista en null para hacer referencia a que se encuentra vacia
    lista list = NULL;

    do
    {
        cout << "\n\tLISTAS\n";
        cout << " 1. MOSTRAR LISTA                    " << endl;
        cout << " 2. INSERTAR AL INICIO               " << endl;
        cout << " 3. INSERTAR AL FINAL                " << endl;
        cout << " 4. SUPRIMIR AL INICIO               " << endl;
        cout << " 5. SUPRIMIR AL FINAL                " << endl;
        cout << " 6. ELIMINAR DUPLICADOS              " << endl;
        cout << " 7. ELEMENTO EN LA POSICION DADA     " << endl;
        cout << " 8. RECUPERAR EL PRIMERO             " << endl;
        cout << " 9. RECUPERAR EL ULTIMO              " << endl;
        cout << " 10. RECUPERAR EL SUCESOR            " << endl;
        cout << " 11. RECUPERAR EL PREDECESOR         " << endl;
        cout << " 0. SALIR                            " << endl;

        cout << "\n INGRESE OPCION: ";
        cin >> op;
        switch (op)
        {
        case 1:
            cout << "\n LISTA...\n";
            mostrarLD(list);
            break;
        case 2:
            cout << "\nINGRESA NUMERO A INSERTAR: ";
            cin >> date;
            insertarInicio(list, date);
            break;
        case 3:
            cout << "\nINGRESA NUMERO A INSERTAR : ";
            cin >> date;
            insertarFinal(list, date);
            break;
        case 4:
            eliminarInicio(list);
            break;
        case 5:
            eliminarFinal(list);
            break;
        case 6:
            //elimDuplicados(list);
            break;
        case 7:
            cout << "\n POSICION A BUSCAR : ";
            cin >> date;
            posicion(list, date);
            break;
        case 8:
            primero(list);
            break;
        case 9:
            mostrarUltimo(list);
            break;
        case 10:
            cout << "\n BUSCAR EL SUCESOR DE LA POSICION  : ";
            cin >> date;
            sucesor(list, date);
            break;
        case 11:
            cout << "\n BUSCAR EL PREDECESOR DE LA POSICION  : ";
            cin >> date;
            predecesor(list, date);
            break;
        case 0:
            break;
        default:
            cout << "\n Opcion incorrecta ";
            break;

        }
    } while (op != 0);
}*/


