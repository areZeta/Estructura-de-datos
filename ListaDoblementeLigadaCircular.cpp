//Arely Herrera Pamila  201877898
//Nestor Tellez Ronquillo 201826858
//Emiliano Villalpando PÃ©rez 201867879

/*el proposito de este programa es  aprender a identificar cuales son las ventajas de una lista doblemente ligada circular.
 la manipulacion de los datos cuando no hay campos en ninguno de los nodos que apunten al vacio (NULL) y
ese apuntador a campo siguiente o anterior sea verdaderamente util, ademas de identificar que para este caso ahora se
 manejan dos apuntadores dentro de lista uno que apunte siempre al nodo inicial y otro al ultimo nodo de la lista
esto con el proposito de observar las ventajas y lo practico que es ligar nodos de forma circular.*/

#define NULL 0 //null es una variable definida para todo el programa , su valor definido por defecto es (false)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;
// los elementos que vienen agrupados a continuacion entre llaves 
//componen una estructura
struct nodo {
    int dato;
    struct nodo* sig, * ant;
};

//se definen dos punteros de tipo nodo(es decir al apuntarlos a un nodo con ellos se podran acceder al campo anterior y al campo siguiente de un nodo)
typedef  struct nodo* lista, * ultimo;

//prototipo de funciones
bool listaVacia(lista& list);
void insertarInicioLDC(lista& list, ultimo& ultim, int date);
void insertarFinalLDC(lista& list, ultimo& ultim, int date);
void mostrarLDC(lista& list, ultimo& ultim);
void eliminarInicioLDC(lista& list, ultimo& ultim);
void eliminarFinalLDC(lista& list, ultimo& ultim);
void primero(lista& list);
void mostrarUltimo(nodo* list);
int elimDuplicados(lista &list, ultimo &ultim);
void sucesor(nodo* list, int pos);
void predecesor(nodo* list, int pos);
void posicion(lista& list, ultimo& ultim, int date);


void  menu();

//funcion principal 
int main()
{
    menu();
    //se hace una pausa esperando que el usuario presione alguna tecla
    system("pause");
    return 0;
}


//este metodo consiste en devolver un valor de tipo booleano dependiendo si la lista esta llena o vacia 
bool listaVacia(lista& list) {
    if (list == NULL) {
        cout << "lista vacia :(  \n";
        return true;
    }
    return false;
}

//metodo que consiste en insertar un elemento en la lista 
void insertarInicioLDC(lista& list, ultimo& ultim, int date) {
    //primero creando un nodo nuevo e insertando el elemento en el campo dato
    lista p = new (struct nodo);
    p->dato = date;
    //si la lista esta vacia entonces automaticamente apuntador list y ultim apuntan al primer nodo
    if (list == NULL) {
        list = p;
        ultim = p;
        //la lista es doblemente circular entonces hacemos que el apuntador al ultimo nodo en su campo siguiente apunte al primer nodo 
        //y viceversa hacemos que el primer nodo en su campo anterior apunte al ultimo nodo 
        ultim->sig = list;
        list->ant = ultim;
    }
    else {
        //en caso de que la lista ya contenga uno o mas elementos(o nodos ) lo que se hace 
        //es enlazar el nodo al inicio, primero se enlazan el nodo nuevo con el nodo al inicio de la lista actual
        list->ant = p;
        //viceversa el nodo nuevo se enlaza con el primer nodo dentro de la lista
        p->sig = list;
        //luego se enlaza el nodo nuevo en su campo anterior con el ultimo nodo y viceversa el ultimo nodo en su campo siguiente con el primer nodo
        p->ant = ultim;
        ultim->sig = p;
        //por ultimo el apuntador list(apunta al primer nodo dentro de la lista) cambia de posicion apuntando al nuevo nodo insertado
        list = p;
    }
}

//este metodo inserta un nuevo nodo al final de la lista actual
void insertarFinalLDC(lista& list, ultimo& ultim, int date) {
    //primero se crea un nuevo nodo, donde se inserta el elemento en el campo dato
    lista p = new (struct nodo);
    p->dato = date;
    //si la lista esta vacia entonces automaticamente apuntador list y ultim apuntan al primer nodo
    if (list == NULL) {
        list = p;
        ultim = p;
        //la lista es doblemente circular entonces hacemos que el apuntador al ultimo nodo en su campo siguiente apunte al primer nodo 
        //y viceversa hacemos que el primer nodo en su campo anterior apunte al ultimo nodo 
        ultim->sig = list;
        list->ant = ultim;
    }
    else {
        //en caso de que la lista ya contengas mas de un nodo
        //el apuntador al ultimo nodo en su campoo siguiente se enlaza con el nuevo nodo
        ultim->sig = p;
        //y viceversa el nodo nuevo en su campo anterior se enlaza con el ultimo nodo actual
        p->ant = ultim;
        //el nodo nuevo en su campo siguiente se enlaza con el apuntador al primer nodo en la lista
        p->sig = list;
        //y viceversa el apuntador al primer nodo en su campo anterior se enlaza con el nodo nuevo insertado al final
        list->ant = p;
        //por ultimo el apuntador al ultimo elemento cambia de posicion, apuntando ahora al nuevo nodo insertado
        ultim = p;
    }
}

//el metodo mostrar lo que hace es mostrar en pantalla los elementos que contiene la lista con un apuntador auxiliar que al inicio apunta al primer nodo
// en el campo dato conforme el auxiliar  vaya cambiando de posicion a lo largo de la lista
void mostrarLDC(lista& list, ultimo& ultim) {
    if (!listaVacia(list)) {
        struct nodo* aux;
        aux = list;
        cout << "lista... [ ";
        while (aux != ultim) {
            cout << aux->dato << " ";
            aux = aux->sig;
        }
        cout << aux->dato << " ] \n";
    }
}

//el metodo eliminar al inicio tiene como parametros dos apuntadores en lista 
void eliminarInicioLDC(lista& list, ultimo& ultim) {
    //	se crea un apuntador auxiliar de tipo nodo
    struct nodo* aux;
    //se llama a lista vacia y dependiendo de lo que retorne, el proceso continua en caso de que la lista este vacia el propio metodo llamado 
    //mostrara en pantalla que la accion no puede continuar
    if (!listaVacia(list)) {
        //auxiliar punta al nodo al inicio de la lista
        aux = list;
        //variable auxiliar que toma el valor del nodo(en su campo dato) que sera eliminado 
        int numAux = list->dato;
        //en caso de que la lista solo contenga un nodo
        //se liberara memoria que ocupa aux que ahora apunta al inicio 
        //y los apuntadores de lista(list y ultim) apuntaran a NULL(para indicar que ahora la lista se encuentra vacia)
        if (list->sig == list) {
            delete(aux);
            list = NULL;
            ultim = NULL;
        }
        else {
            //en caso de que la lista tenga mas de un nodo 
            //el apuntador al primer nodo en la lista cambia de posicion ahpora en el siguiente nodo que ahora sera el primer nodo dentro de la lista 
            list = aux->sig;
            //se desconecta el nodo a eliminar de la lista(el apuntador list en su campo anterior apunta al ultimo nodo y viceversa
            // el apuntador al ultimo nodo en su campo siguiente apunta al nodo en la primera posicion)
            list->ant = ultim;
            ultim->sig = list;
            //por ultimo se libera memoria (se elimina el primer nodo) del lugar hacia donde apunta (aux)
            delete(aux);
        }
        //se imprime en pantalla ele elemento eliminado
        cout << "elemento eliminado al inicio de la lista es: " << numAux;
    }
}

//el metodo elimina un nodo al final de la lista
void eliminarFinalLDC(lista& list, ultimo& ultim) {
    //se crea un apuntador auxiliar de tipo nodo 
    struct nodo* aux;
    // sila lista no esta vacia se continua con el proceso
    if (!listaVacia(list)) {
        //el apuntador auxiliar ahora apunta al ultimo  nodo de la lista
        aux = ultim;
        //se crea un auxiliar de tipo entero que guarda el valor del apuntador ultim en su campo dato
        int numAux = ultim->dato;
        //si la lista solo tiene un nodo se libera directamente el espacio al que este apuntado aux
        if (ultim->sig == ultim) {
            delete(aux);
            //asignar NULL a los dos apuntadores para inidcar vacio
            list = NULL;
            ultim = NULL;
        }
        else {
            //en caso de que en la lista haya mas de un nodo
            //se desenlaza el ultimo nodo, primero el apuntador a ultimo cambia de posicion ahora apuntara a un nodo antes del que apuntaba
            ultim = aux->ant;
            //apuntador a ultimo en su campo siguiente apunta  al primer nodo en la lista
            ultim->sig = list;
            // y viceversa apuntador al primer nodo en su campo anterior se liga con el ultimo nodo
            list->ant = ultim;
            //se libera el espacio de memoria al que apuntaba (aux)
            delete(aux);
        }
        //se muestra en pantalla el elemento que fue eliminado
        cout << "elemento eliminado al final es: " << numAux;
    }

}

void primero(lista& list)
{
    int prim;
    if (listaVacia(list) == false)
        prim = list->dato;                //list apunta al primer elemento
    cout << "\n El primer elemento es : " << prim << "\n";


}

void posicion(lista& list, ultimo& ultim, int date)
{
    if (listaVacia(list) == false) {

        int cont = 1;
        struct nodo* aux;
        aux = list;
        while (aux->sig != ultim) {
            cont++;                    //cuenta los elementos en la lista
            aux = aux->sig;
        }
        cont++;
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


//Funcion para mostrar el ultimo elemento de la lista
void mostrarUltimo(nodo* list, nodo* ultim) {
    //comprobar si lista vacia
    if (listaVacia(list) == false) {
        //usando apuntador al ultimo elemento facilmente
        cout << "El ultimo elemento es " << ultim->dato << endl;

    }
}

//funcion para encontrar el sucesor de una posicion especifica
void sucesor(nodo* list,nodo* ultim, int pos) {
    //verificar que la lista no este vacia 
    if (listaVacia(list) == false) {
        //contador de elementos de lista para no trabajar con rangos erroneos
        int numElementos = 1;


        struct nodo* p;
        //conectando el nuevo nodo con la lista
        p = list;
        //contador de elementos de la lsita
        while (p->sig != ultim)
        {

            numElementos++;
            p = p->sig;

        }
        p = list;
        //comprobar rango
        if (numElementos+1 < pos)
        {
            cout << " ERROR DE RANGO \n";
        }
        else
        {

        

            //caso de que su sucesor sea primero (ultim ----> primero)
            if (numElementos == pos)
            {
                cout << "EL SUCESOR DE LA POSICION  [" << pos << "] ES " << "(" << ultim->dato << ")" << endl;
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
}

//funcion para encontrar el predecesor de una posicion especifica
void predecesor(nodo* list,nodo* ultim, int pos) {
    //verificar que la lista no este vacia
    if (listaVacia(list) == false) {
        //contador elementos
        int numElementos = 1;
        struct nodo* p;

        p = list;
        //comprobar cuantos nodos tiene
        while (p->sig != ultim)
        {

            numElementos++;
            p = p->sig;

        }
        //reiniciar posicion p
        p = list;
        //caso de que el predecesor no exista
        if (numElementos+1 < pos)
        {
            cout << " ERROR DE RANGO \n";
        }
       
        else
           
        {
            //CASO
            if (pos==1)
            {
                cout << "EL PREDECESOR DE LA POSICION  [" << pos << "] ES " << "(" << ultim->dato << ")" << endl;
            }
            else {
                //caso en el que el predecesor sea la primera posicion
                for (int i = 1; i < pos - 1; i++)
                {
                    p = p->sig;

                }
                cout << "EL PREDECESOR DE LA POSICION  [" << pos << "] ES " << "(" << p->dato << ")" << endl;
                
            }
        }

    }

}

//pasa parametros por referencia tales como apuntador a lista al inicio y al final
int elimDuplicados(lista &list, ultimo &ultim)
{
    int ban = 0;  	
	if(listaVacia(list) == false && list->sig != list){// condicion en caso de que lista este vacia y en caso de que solo haya un nodo dentro de la lista 
		struct nodo *aux=list, *elim, *aux2;
		int e;
		// en el primer while recorre la lista y en una variable va asiganando los valores en cada nodo
		while(aux->sig!=list){
		   e=aux->dato;
		   //en cada regreso aux (aountador del segundo ciclo) regresa a la posicion donde va el apuntador del primer ciclo
		   aux2=aux;
		   while(aux2->sig!=list){
		   	//segundo ciclo recorre la lista buscando los elementos iguales
		     if(e==aux2->sig->dato){
		     	//cuando encuentra el elemento igual asigna un apuntador auxiliar al nodo donde se encuentra
		  	    elim=aux2->sig;
		  	    //en el caso 1 valida que el elemento se encuentre en el ultimo nodo de la lista
		       	if(aux2->sig->sig==list){
		       		//de ser asi enlaza el penultimo con el ultimo y 
		 	       aux2->sig=list;
		 	       list->ant = aux2;
		           ultim = aux2;
			    }else{
				   //struct nodo *desp =elim->sig;
			       aux2->sig=elim->sig;
			       elim->sig->ant = aux2;
				}
				cout<<"Elemento duplicado eliminado: \n "<< elim->dato<<"";
		        delete(elim);
		        ban =1;
		    
	      	 }	
		     if(aux2->sig != list){ 
		        aux2=aux2->sig;	 
		      }
	    	}
		    if(aux->sig != list){
		       aux=aux->sig;
		    }
	   }
	}
	return ban;
}



void  menu() {
    int op, date;
    //se inicializa la referencia a lista y a ultimo en NULL para hacer referencia a que se encuentra vacia al inicio del programa
    lista list = NULL;
    ultimo ultim = NULL;

    do
    {
        cout << "\n\tLISTA DOBLEMENTE LIGADA CIRCULAR\n";
        cout << " 1. MOSTRAR LISTA                    " << endl;
        cout << " 2. INSERTAR AL INICIO EN CIRCULAR   " << endl;
        cout << " 3. INSERTAR AL FINAL EN CIRCULAR    " << endl;
        cout << " 4. SUPRIMIR AL INICIO EN CIRCULAR   " << endl;
        cout << " 5. SUPRIMIR AL FINAL EN CIRCULAR    " << endl;
        cout << " 6. ELIMINAR DUPLICADOS EN CIRCULAR  " << endl;
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
            //dependiendo de la opcion que eliga el usuario se llama  cierto metodo
        case 1:
            cout << "\n LISTA...\n";
            mostrarLDC(list, ultim);
            break;
        case 2:
            cout << "\nINGRESA NUMERO A INSERTAR: ";
            cin >> date;
            insertarInicioLDC(list, ultim, date);
            break;
        case 3:
            cout << "\nINGRESA NUMERO A INSERTAR : ";
            cin >> date;
            insertarFinalLDC(list, ultim, date);
            break;
        case 4:
            eliminarInicioLDC(list, ultim);
            break;
        case 5:
            eliminarFinalLDC(list, ultim);
            break;
        case 6:
            if( elimDuplicados(list, ultim) == 0){
            	cout<<"NO SE ENCONTRARON ELEMENTOS DUPLICADOS";
			}
            break;
        case 7:
            cout << "\n POSICION A BUSCAR : ";
            cin >> date;
            posicion(list, ultim, date);
            break;
        case 8:
            primero(list);
            break;
        case 9:
            mostrarUltimo(list, ultim);
            break;
        case 10:
            cout << "\n BUSCAR EL SUCESOR DE LA POSICION  : ";
            cin >> date;
            sucesor(list,ultim, date);
            break;
        case 11:
            cout << "\n BUSCAR EL PREDECESOR DE LA POSICION  : ";
            cin >> date;
            predecesor(list,ultim, date);
            break;
        case 0:
            break;
        default:
            cout << "\n Opcion incorrecta ";
            break;

        }
    } while (op != 0);
}

