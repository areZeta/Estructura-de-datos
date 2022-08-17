//Arely Herrera Pamila  201877898
//Nestor Tellez Ronquillo 201826858
//Emiliano Villalpando PÃ©rez 201867879

/*el proposito de este programa consiste principalmente en aplicar elconcepto de memoriadinamica en listas ligadas pero ahora con una 
transformación mas practica cómo lo son listas doblemente ligadas las cuales tendran un campo mas que lista simples con el proposito
de ligar doblemente a los nodos para que asi se pueda acceder desde un apuntador a un nodo a otro nodo adelante y otro hacia atras es decir 
facilitara recorrer la lista de adelante hacia atras asi como de atras  hacia adelante*/
#define NULL false
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
    struct nodo *sig, *ant; 
};
// typedef define un nombre alternativo  a tipos existentes 
//es una manera de instanciar nodo ( ace referencia a que es un puntero de tipo nodo)
typedef struct nodo *lista, *p;

//prototipo de las funciones
bool listaVacia(lista &list );
void mostrarLD(lista &list);
void insertarInicio(lista &list, int date);
void insertarFinal(lista &list, int date);
void eliminarInicio(lista &list);
void eliminarFinal(lista &list);
void elimDuplicados(lista &list);
void primero(lista &list);
void posicion(lista &list, int date);
void menu();

//funcion principal 
int main()
{
    menu();
    //se hace una pausa esperando que el usuario presione alguna tecla
    system("pause"); 
    return 0;
}


//retorna un valor de tipo booleano - true en caso de que la lista este vacia
bool listaVacia(lista &list ){
    if (list == NULL) {
        cout<< "\n LISTA VACIA!!!\n";
        return true;
    }
    return false;
}
//este metodo imprime en pantalla los elementosexistentes en la lista
void mostrarLD(lista &list){
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
 
void insertarInicio(lista &list, int date)
{      //se crea un nuevo nodo auxiliar
         lista p =  new (struct nodo);
         //al cual se le asignan valores a sus campos
         p->dato = date;
         p->ant = NULL;
         p->sig = NULL;
        // si la lista esta vacia hace que list ocupe la posicion de p
        //es decir que directamente p pase a ser el primer nodo en la lista
       if(list !=NULL){
           //se enlazan doblemente  el apuntador al primer nodo de la lista 
           // con el apuntador al nodo auxiliar para conectar este a la lista
          list->ant = p;
          p->sig = list;
       }
       //el nodo al que apunta p se convierte en el primer nodo de la lista
       list = p;
}
void insertarFinal(lista &list, int date){
    //se crea un nodo y un apuntador auxiliar 
         struct nodo *aux;
         lista p =  new (struct nodo);
         //se asignan valores a lo campos del nodo
         p->dato = date;
         p->ant = NULL;
         p->sig = NULL;
         //si la lista esta vacia el nodo al que apunta p pasa a ser el primer
         // nodo de la lista
       if(list == NULL){
          list = p;
       }else{
           //si no es el caso auxiliar apunta a la primera poisicion y recorre 
           //la lista asta llegar al ultimo nodo
           aux = list;
           while(aux->sig != NULL){
              aux = aux ->sig;
           }
           //conecta doblemente al apuntador al nodo nuevo  con el apuntador
           //al ultimo nodo de l lista que es el que lleva el puntero auxiliar
           aux ->sig = p;
           p ->ant = aux;
       }
}
//funcion que elimina el nodo que se encuentra al inicio de la lista doblemente ligada
void eliminarInicio(lista &list){
    int elim;
    //valida que no este vacia para seguir con el proceso
    if(listaVacia(list) == false){
        //crea un apuntador auxiliar
        struct nodo *aux = list;
        //guarda en una variable temporal el dato a eliminar
        elim = list->dato;
        if(list->sig == NULL){
            delete(list);
            list = NULL;
        }else{
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
        cout<<"\n dato eliminado al inicio es : "<< elim;
    }
    
}
//funcion que elimina el nodo que se encuentra al final de la lista
void eliminarFinal(lista &list){
    int elim;
     //valida que no este vacia para seguir con el proceso
    if(listaVacia(list) == false){
        //crea un apuntador auxiliar
        struct nodo  *aux  = list;
        //si lista en su capo siguiente es null eso significa que solo hay un 
        // nodo dentro de la lista
        if(list->sig == NULL){
            //y a ese nodo solo hay que extraerle el dato a eliminar 
        	elim =list->dato; 
            //liberar la memoria
            delete(list);
            //reasignarle null al apuntador lista para referenciar vacio
            list = NULL;
        }else{
            //se asigna que apunte al primer nodo al puntero auxiliar
           aux = list;
           //se recorre el auxiliar comparando si dos nodos despues 
           //de su posicion existe null
           while (aux->sig->sig != NULL)
           {
              aux = aux ->sig ;
           }
           //se extrae el dato a eliminar
           elim = aux->sig->dato; 
           //se libera memoria 
           delete(aux->sig);
           //se desconecta null del nodo ya eliinado y apunta a null
           //referenciando que es el nodo en la ultima posicion de la lista
           aux->sig = NULL;
        }  
        cout<<"\n dato eliminado al final es : "<< elim;
    }
}

void primero(lista &list)
{ 
   int prim;
   if(listaVacia(list) == false)
   	prim =list->dato;                //list apunta al primer elemento
   	cout<<"\n El primer elemento es : "<< prim<<"\n";
   
   	
}

void posicion(lista &list, int date)
{
  if(listaVacia(list) == false){
  
	int cont=1;
	struct nodo *aux;
	aux=list;
	while(aux->sig!=NULL){
	  cont++;                    //cuenta los elementos en la lista
	  aux=aux->sig;}
	if(date>cont||date<1)
	  cout<<"\n Valor fuera de rango\n";
	else{
		aux=list;
		for(int i=1; i<date; i++)  //recorre la lista hasta llegar a la posicion
		 aux=aux->sig;
	    cout<<"\n El dato es: "<<aux->dato<<"\n";
		}
		
	}


	
}

void elimDuplicados(lista &list)
{
	if(listaVacia(list) == false && list->sig !=NULL){
		struct nodo *aux=list, *atras, *aux2;
		int e;
		
		while(aux->sig!=NULL){
		 e=aux->dato;
		 aux2=aux;
		 
		 while(aux2->sig!=NULL){
		  
		  if(e==aux2->sig->dato){
		  	
		  	atras=aux2->sig;
		 	if(aux2->sig->sig==NULL){
		 	  aux2->sig=NULL;
			   }
		 	else{
			  aux2->sig=atras->sig;}
		    delete(atras);
		    
		 }	
		 
		 if(aux2->sig != NULL){ 
		   aux2=aux2->sig;	
		   
		 }
		 }
		 atras = aux;
		 if(aux->sig != NULL){
		 
		 aux=aux->sig;
		 }
		}
		aux=list;
		
		
}
}
//Esta funcion solo muestra el menu de opciones de lista dinamica en pantalla
void menu(){
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
        cout<<" 6. ELIMINAR DUPLICADOS              "<<endl;
        cout<<" 7. ELEMENTO EN LA POSICION DADA     "<<endl;
        cout<<" 8. RECUPERAR EL PRIMERO             "<<endl;
        cout<<" 0. SALIR                            "<<endl;
 
        cout<<"\n INGRESE OPCION: ";
        cin>> op;
        switch(op)
        {
            case 1:
                 cout << "\n LISTA...\n";
                 mostrarLD(list);
            break;
            case 2:
                 cout<< "\nINGRESA NUMERO A INSERTAR: "; 
                 cin>> date;
                 insertarInicio(list, date );
            break;
            case 3:
                 cout<< "\nINGRESA NUMERO A INSERTAR : ";
                 cin>> date;
                 insertarFinal(list, date);
            break;
            case 4:
                 eliminarInicio(list);
            break;
            case 5:
                  eliminarFinal(list);
            break;
            case 6:
            	  elimDuplicados(list);
            break;
            case 7:
            	  cout<< "\n POSICION A BUSCAR : ";
                  cin>> date;
                  posicion(list, date);
            break;
            case 8:
            	  primero(list);
            break;
            case 0:
            break;
            default:
                 cout << "\n Opcion incorrecta ";
            break;
 
        }
    }while(op!=0);
}


