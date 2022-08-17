#define NULL false 

char elim;
using namespace std;
struct nodo {  //declaracion de la estructura de los nodos
    char nombre;
    struct nodo *ady=NULL, *sig; 
};
typedef struct nodo *lista, *p;

//funcion que devuelve un dato de tipo booleano, este indica si la lista 
// se encuentra vacia - true o si no lo esta - false
bool listaVacia(lista &list ){
    if (list == NULL) {
        //cout<< "\n LISTA VACIA!!!";
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
            cout << p->nombre <<" ";
            p = p->sig; 
         }
          // while ya no entra a imprimir el elemento en la ultima posicion 
           //por su condicion, esta se imprime al final del ciclo
         cout <<p->nombre << " ] \n";
      }
        
}

 //inserta un elemento al inicio de la lista, tiene como parametros un entero que 
  // es el dato que ingresara el usuario y hace referencia a list (este es un nodo)
void insertarInicio(lista &list, int date){
     //inicia creando un nodo llamado p, en el cual inserta el dato
     //y en su camposiguiente asigna NULL
         lista p =  new (struct nodo);
         p->nombre = date;
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
void insertarFinal(lista &list)
{
    //inicia creando un nodo auxiliar llamado p, en el cual inserta el dato
    //y en su camposiguiente asigna NULL
    lista q =  new (struct nodo);
    struct nodo *aux ;
    char date;
    int cost;
    do{
       cout<<"Ingrese el nombre del nodo (numeros o letras): \n"; 
       cin>>date;
       if(date < 48 || (date > 57 && date < 97) || date >122)cout <<"\n  Error nombre fuera de rango\n";
    }while(date < 48 || (date > 57 && date < 97) || date >122);
    q->nombre  = date;
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

//inserta un elemento al final de la lista, tiene como parametros un entero que 
//es el dato que ingresara el usuario y hace referencia a list (este es un nodo)
void insertarFinal2(lista &list,char n)
{
    //inicia creando un nodo auxiliar llamado p, en el cual inserta el dato
    //y en su camposiguiente asigna NULL
    lista q =  new (struct nodo);
    struct nodo *aux ;
    
    q->nombre  = n;
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
int eliminarInicio(lista &list)
{
    //valida que no este vacia para seguir con el proceso
    if(listaVacia(list) == false){
        //crea dos apuntadores auxiliares
        struct nodo *p;
        //guarda en una variable temporal el dato a eliminar
        elim = list->nombre;
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
        //cout<<"\n dato eliminado al inicio es : "<< elim;
    }
    return elim;
    
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
        	elim =list->nombre; 
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
           elim = p->nombre; 
           delete(p);
           aux->sig = NULL;
        }  
        cout<<"\n dato eliminado al final es : "<< elim;
    }
}

void primero(lista &list)
{ 
   int prim;
   if(listaVacia(list) == false)
   	prim =list->nombre;                //list apunta al primer elemento
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
	    cout<<"\n El dato es: "<<aux->nombre<<"\n";
		}
		
	}


	
}

void elimDuplicados(lista &list)
{// verifica que la lista no este vacia
	if(listaVacia(list) == false && list->sig !=NULL){
		struct nodo *aux=list, *atras, *aux2;
		int e;
		//ciclo que pasa por todos los nodos de la lista
		while(aux->sig!=NULL){
		 e=aux->nombre;// e va tomando nombres de cada nodo
		 aux2=aux;
		 
		 while(aux2->sig!=NULL){ //ciclo que va comparando 
         // los nombres que va tomando e con los de la lista
		  if(e==aux2->sig->nombre){
		  	// compara para el segundo nodo
		  	atras=aux2->sig;// posiciona el apuntador un nodo adelante
              // compara para el caso del penultimo nodo
		 	if(aux2->sig->sig==NULL){
		 	  aux2->sig=NULL;
			   }
		 	else{
			  aux2->sig=atras->sig;}
		    delete(atras);//elimina en caso de haber encontrado
            //iguales
		    
		 }	
		 //verifica para el nodo en la ultima posicion
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

//con metodo buburbuja ordena los nodos de menor a mayor 
void ordenarMenMay(lista &list){
    struct nodo *actual = list , *aux;
     char nom;
     //primer ciclo pasa por los nodos de la lista
     while(actual->sig != NULL)
     {
           aux= actual;//pero va tomando sus nombres para compararlos
          while(aux -> sig !=NULL)
          {//segundo ciclo pasa por todos los nodos comparando nombres
               if(actual->nombre > aux->sig->nombre)
               {  //en caso de encontrar mayores sustituye con ayuda de una variable los valores en el campo nombre de cada nodo 
                    nom = aux->sig->nombre;
                    aux->sig->nombre = actual->nombre;
                    actual->nombre = nom;          
               }
               aux = aux->sig;                    
          }    
          actual = actual->sig;  
     }
}

//imprimir matriz de adyacencia
void imprimir(int m[][30], int f, int c,int v){
	for(int i=0; i<v; i++){
	 for(int j=0; j<v; ++j){
	    cout<<m[i][j];
		cout<<"\t";	
	 }
	cout<<"\n"; }
}
