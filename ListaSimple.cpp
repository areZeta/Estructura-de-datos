 //Arely Herrera Pamila  201877898
 //Nestor Tellez Ronquillo 201826858
 //Emiliano Villalpando PÃ©rez 201867879

//el proposito de este programa consiste principalmente en aplicar el
//concepto de memoria dinamica relacionandola con listas ligadas
//comprender el manejo de nodos esto con la finalidad de aprender a utilizar  
// y diferenciar punteros, referencias a nodos y funciones con parametros de este tipo

#define NULL false //como en c++ no existe NULL como tal , se define a null como falso
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;
// los elementos que vienen agrupados a continuación entre llaves 
//componen una estructura
struct nodo {
    int dato;
    struct nodo *sig; 
};

// typedef define un nombre alternativo  a tipos existentes 
//de esta manera se instancia nodo
//* hace referencia a que es un puntero de tipo nodo
typedef struct nodo *lista, *p;
//utilizar en el futuro en vez de NULL

//funcion que devuelve un dato de tipo booleano, este indica si la lista 
// se encuentra vacia - true o si no lo esta - false
bool listaVacia(lista &list ){
    if (list == NULL) {
        cout<< "\n LISTA VACIA!!!";
        return true;
    }
    return false;
}

//este metodo imprime en pantalla los elementosexistentes en la lista
void mostrar(lista &list){
    //primero verifica que la lista no este vacia, para ello manda a llamar 
    //a la funcion listaVacia()
      if(listaVacia(list) == false){
         struct nodo *p = list;
         cout << "\n  [ ";
          //con p se apunta al inicio de la lista que es donde se encuentra 
           //el puntero list, p se recorre hasta que llegue a la ultima posicion
            //de la lista
         while (p->sig  != NULL){
            cout << p->dato <<" ";
            p = p->sig; 
         }
          // while ya no entra a imprimir el elemento en la ultima posicion 
           //por su condicion, esta se imprime al final del ciclo
         cout <<p->dato << " ] \n";
      }
        
}

 //inserta un elemento al inicio de la lista, tiene como parametros un entero que 
  // es el dato que ingresara el usuario y hace referencia a list (este es un nodo)
void insertarInicio(lista &list, int date){
     //inicia creando un nodo llamado p, en el cual inserta el dato
     //y en su camposiguiente asigna NULL
         lista p =  new (struct nodo);
         p->dato = date;
         p->sig = NULL;
        // si la lista esta vacia hace que list ocupe la posicion de p
        //es decir apunte a la posicion en donde seencuentra el primer elemento(primer nodo)
       if(list == NULL){
          list = p;
       }else{
           //en caso de que ya haya elementos enlaza el nodo p
           //con el primer nodo que es donde esta apuntando lista
           //despues cambia al puntero list para que esta siga apuntando
           //al primer nodo
           p->sig = list;
           list = p;
       }
        
}

//inserta un elemento al final de la lista, tiene como parametros un entero que 
//es el dato que ingresara el usuario y hace referencia a list (este es un nodo)
void insertarFinal(lista &list, int date)
{
    //inicia creando un nodo auxiliar llamado p, en el cual inserta el dato
    //y en su camposiguiente asigna NULL
    lista q =  new (struct nodo);
    struct nodo *aux ;
    q->dato  = date;
    q->sig = NULL;
    //si esta vacia solo se asigna lo que tiene el puntero q a list para que este
    //apunte al inicio de la lista
    if(list==NULL)
    {
        list = q;
    }
    //si no lo que hace es recorrer con un puntero auxiliar hasta el 
    //ultimo nodo y enlaza el campo siguiente de ese nodo con el nodo creado al inicio(p)
    else
    {
        aux = list;
        while(aux->sig !=NULL)
        {//recorre  el puntero auxiliar asignando a ese puntero la posicion en su
        //campo siguiente hasta que ya no cumpla la condicion
            aux = aux->sig;
        }
        aux->sig = q;
    }
 
}

//funcion que elimina el nodo que se encuentra al inicio de la lista
void eliminarInicio(lista &list)
{
    int elim;
    //valida que no este vacia para seguir con el proceso
    if(listaVacia(list) == false){
        //crea dos apuntadores auxiliares
        struct nodo *p;
        //guarda en una variable temporal el dato a eliminar
        elim = list->dato;
        if(list->sig == NULL){
            delete(list);
            list = NULL;
        }else{
            //el puntero auxiliar guarda la posicion en el campo siguiente en el que esta
            //apuntando list para no perder el campo en la memoria donde se encuentran
           // los elementos dela lista
           p = list->sig;
           //se libera la memoria donde se encontraba el nodo
           delete(list);
           //p le vuelve a asignar la posicion que guardo p
           list = p;
        }    
        cout<<"\n dato eliminado al inicio es : "<< elim;
    }
    
}

//funcion que elimina el nodo que se encuentra al final de la lista
void eliminarFinal(lista &list)
{
    int elim;
     //valida que no este vacia para seguir con el proceso
    if(listaVacia(list) == false){
        //crea dos apuntadores auxiliares
        struct nodo *p, *aux;
        if(list->sig == NULL){
        	elim =list->dato; 
            delete(list);
            list = NULL;
        }else{
            //se asigna que apunte al primer nodo, al puntero auxiliar
           aux = list;
           p = list->sig;
           while (p->sig  != NULL)
           {
              aux = p;
              p = p->sig; 
           }
           elim = p->dato; 
           delete(p);
           aux->sig = NULL;
        }  
        cout<<"\n dato eliminado al final es : "<< elim;
    }
}

//Esta funcion solo muestra el menu de opciones de lista dinamica en pantalla
void menu()
{
    int op,date;
    //se inicializa lista en null para hacer referencia a que se encuentra vacia
    lista list = NULL;

     do
    { 
        cout<<"\n\tLISTAS\n";
        cout<<" 1. MOSTRAR LISTA                    "<<endl;
        cout<<" 2. INSERTAR AL INICIO               "<<endl;
        cout<<" 3. INSERTAR AL FINAL                "<<endl;
        cout<<" 4. SUPRIMIR AL INICIO               "<<endl;
        cout<<" 5. SUPRIMIR AL FINAL                "<<endl;
        cout<<" 0. SALIR                            "<<endl;
 
        cout<<"\n INGRESE OPCION: ";
        cin>> op;
        switch(op)
        {
            case 1:
                 cout << "\n LISTA...\n";
                 mostrar(list);
            break;
            case 2:
                 cout<< "\n NUMERO A INSERTAR: "; 
                 cin>> date;
                 insertarInicio(list, date );
            break;
            case 3:
                 cout<< "\n NUMERO A INSERTAR : ";
                 cin>> date;
                 insertarFinal(list, date);
            break;
            case 4:
                 eliminarInicio(list);
            break;
            case 5:
                  eliminarFinal(list);
            break;
            case 0:
            break;
            default:
                 cout << "\n Opcion incorrecta ";
            break;
 
        }
        //cout<<endl<<endl;// indica que la linea a terminado  
        //system("pause");  system("cls");// borra lo de arriba y comienza  system("pause");  system("cls");
 
    }while(op!=0);
}

//funcion principal 
int main()
{
    menu();
    //se hace una pausa esperando que el usuario presione alguna tecla
    system("pause"); 
    return 0;
}
