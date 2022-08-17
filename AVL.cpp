
//Arely Herrera Pamila  201877898
//Nestor Tellez Ronquillo 201826858

/*El proposito de este programa es crear arboles a partir de tda's ya existentes esto con el proposito de reutilizar codigo y comprender que temas
 anteriores son base para llegar a comprender este, asi como encontrar la relacion que un arbol tiene con un grafo y de esta manera lograr crear 
 a lo que se le llama un *arbol ordenado* , en esta ultima version se completan todas las operaciones que se pueden hacer con un arbol */
 
#define NULL false //como en c++ no existe NULL como tal , se define a null como falso
#include <stdio.h> // encabezado estandar de entrada y salida de c para definicion de constantes, operaciones de salida etc.
#include <stdlib.h> // libreria cabezera para gestión de memoria dinámica, control de procesos y otras
#include <iostream>// componente de biblioteca estandar de c++ para hacer uso de objetos cin, cout, cerr y clog.
#include <tdalistadoble.h>//archivo cabecera que incluye los m?todos del TDA Lista doblemente ligada con ligeras modificaciones para adecuarlos a este programa

using namespace std;

typedef struct nodo *arbol ; //nombre alternativo a nodo(apuntador a nodo,se crea con atributos propios de un nodo)
typedef struct nodo *cola; // estructura auxiliar para guardar nodos y mandarlos a mostrar en caso de que cumplan cierto requisito
int ban = 0;
//proptotipo de funciones
void insertar(arbol &arb, int date);
void mostrarArbol(arbol &arb, int cont);
void hojas2(arbol &arb, cola &colhojas);
bool validarEquilibrio(arbol &arb, cola &colhojas);
int altura(arbol &arb, cola &colhojas, int a);
int caminoEntreDosNodos2(arbol &arb, int a , int b);
void Izqui_Izqui(arbol &arb, cola &colhojas);
void Der_Der(arbol &arb, cola &colhojas);
void Izqui_Der(arbol &arb, cola &colhojas);
void Der_Izqui(arbol &arb, cola &colhojas);
void menu();

//funcion principal 
int main()
{ 
    menu();
    //se hace una pausa esperando que el usuario presione alguna tecla
    system("pause");
    return 0;
}
//este metodo inserta cada nodos en un arbol de manera ordenada (menores a nodo raiz a la izquierda y mayores a la derecha )
void insertar(arbol &arb, int date){
		struct nodo *aux = arb, *aux2;// se crea dos apuntadores auxiliares que ayudaran a moverse dentro del arbol aux apunta a la raiz al inicio
		int ban = 0; // utilizamos bandera para saber cuando se ingresa el primer elemento para que sea considerado como raiz
	   	while(aux != NULL){// ciclo que se mueve por el arbol con apuntador  auxiliar si y solo si ya hay elementos existentes en el arbol
	   		aux2 = aux;// auxiliar 2 solo guarda el lugar al que apunta auxiliar antes de llegar a un campo NULL
		   if(date >= aux->dato)  aux = aux->sig; // en caso de que el elemento ingresado desde el teclado sea igual o mayor a la raiz  este se mueve a la derecha
	   	   else aux = aux->ant;	// caso contrario se mueve a la izquierda(menores a la raiz)
	   	   ban = 1;// cambiando el valor de la bandera a 1 sabemos que el dato ingresado ya es hijo de la raiz 
		}
		if(ban == 1){
			aux = aux2; // se regresa auxiliar un nodo antes del que esta apuntado , ya que si se queda en su posicion estara apuntando a NULL
		}
		//apuntador auxiliar lo que apunta es el nodo padre al que se le insertara un hijo
		if(!listaVacia(aux)){// cuando el arbol no este vacio este se empezara a ingrsar a partir del apuntador a raiz(arb)
			if(date >= aux->dato){// en caso de ser mayor o igual el dato a ingresar que el dato del nodo padre este se insertara a la derecha 
			   insertarArbol(aux->sig, date);
		    }else insertarArbol(aux->ant, date);//caso contrario se insetrara a la izquierda
		}else{
			insertarArbol(arb, date);// en caso de que el arbol este vacio es decir arb apuntador a inicio de arbol, sea NULL este se ingresa como 
			// como referencia para que apunte al primer nodo, es decir al nodo raiz y de ahi comienze a contruirse el arbol
		}
}	 

//metodo que muestra el arbol impreso de forma vertical
void mostrarArbol(arbol &arb, int cont){
	if(!listaVacia(arb)){ // primero verifica si arb apuntador a arbol no esta vacio 
		mostrarArbol(arb->sig, cont+1);// primero recorre los nodos del arbol que estan a la derecha , llamandose a si misma
		cout <<"\n ";
		for(int i = 0; i < cont ;i++){
			cout<<"      " ;// imprime espacio para dar formato a la impresion de arbol
		}
		cout<< arb->dato<< endl;// imprime dato de cada nodo 
		
		mostrarArbol(arb->ant, cont+1);// luego recorre los nodos del arbol que estan a la izquierda , llamandose a si misma   
	}
	
}

void menu(){ 
	arbol arb = NULL;
	cola colhojas=NULL;
	int n, opc, cont = 0, op,hijo,a,b,grad;
	do{
	    cout << "\n----------------------------------------------------------"<<endl;
        cout << "\t ARBOLES \n";
        cout << " 1. INSERTAR ELEMENTOS EN ARBOL      " << endl;
        cout << " 2. MOSTRAR ARBOL                    " << endl;
        cout << " 0. SALIR                    " << endl;
        cout << "----------------------------------------------------------"<< endl;
        cin>> op;
        switch(op){
        	case 1:
        		cout<<" Ingrese su numero: \n"; 
		        cout<<" ";cin>>n; 
				insertar(arb,n);
				if(!validarEquilibrio(arb,colhojas)) cout <<"Hay desEquilibrio"<< endl;
				else cout << "No hay desequilibrio" << endl;
        	break;
        	case 2: // en los casos en los que hay que recorrer el rabol, primero se verifica que no este vacio, si es asi se muestra un mensaje en pantalla
        		if(listaVacia(arb)) cout << "\n ARBOL VACIO!!!\n";
                else{
                	cout << " \n ARBOL IMPRESO DE FORMA VERTICAL   "<< endl;
        	    	mostrarArbol(arb, cont);
        	    	cout<<"\n";
				} 
        	break;
        	case 0:
            break;
            default:
                 cout << "\n Opcion incorrecta ";
            break;
		}
    }while(op != 0);
	
}


//este metodo obtiene la altura del nodo solicitado
int altura(arbol &arb, cola &colhojas, int a){
	hojas2(arb,colhojas);
	struct nodo *aux = colhojas;
	int max=0,rec;
	while(aux->sig!=NULL){
	  rec=caminoEntreDosNodos2(arb,a,aux->dato);    //se obtiene la longitud de cada camino entre el nodo ingresado y las hojas
	  if(rec>max)                                       //y se va guardando la longitud maxima
	   max=rec;                                          
	  aux=aux->sig;
	}
	
	if(aux->sig==NULL){
      rec=caminoEntreDosNodos2(arb,a,aux->dato);    //valida el ultimo nodo de la lista de hojas
	  if(rec>max) max=rec;
	}
	   
	return max;
		
		 
}
//metodo que lista las hojas del arbol y las guarda en una cola
void hojas2(arbol &arb, cola &colhojas){
	if(!listaVacia(arb)){//como la funcion es recursiva cada vez que se vuelva a llamar se tiene que validar que cada sub-arbol a la derecha o a la
	//izquierda del arbol todavia tenga hijos
		if(arb->ant==NULL &&arb->sig==NULL)   //se valida que el nodo cumpla las caracteristicas de una hoja para poder guardarlo
		 insertarFinal(colhojas,arb->dato);
	    
	    hojas2(arb->ant,colhojas);  // depues de mostrar la raiz se recorre por la rama izquierda hasta llegar a una hoja
		hojas2(arb->sig,colhojas);  // luego se regresa por la derecha de cada sub-arbol
		
		
	}	
}

int caminoEntreDosNodos2(arbol &arb, int a , int b){
	struct nodo *aux = arb;
	
   while(aux->dato != a ){ // en este primer ciclo lo que hace es moverse por todo el arbol hasta encontrar el primer nodo
		if(a >= aux->dato)aux = aux->sig; // moverse por rama derecha
    	else aux = aux->ant;// o rama izquierda
	}

	 // una vez encontrado el primer nodo, se parte de ahi para buscar un mcamino al segundo
	int cont=0; // se inicializa el contador que almacenara la longitud
	while(aux != NULL ){// segundo nodo comienza a buscar el segundo nodo iniciando  del primer nodo encontrado hasta que se llegue al nodo buscado o hasta que 
	//apuntador auxiliar se a= NULL
		if(b >= aux->dato)aux = aux->sig;// se mueve por rama derecha
		else aux = aux->ant; // o se mueve por rama izquierda
		if(aux != NULL){ // se verifica el caso de que al moverse por alguna de las ramas encuentre NULL antes de volver al ciclo
			cont++; // se incrementa el contador de longitud
			if(b == aux->dato){ //en caso de que se llegue al nodo requrido 
				
				return cont; // se retorna el contador de longitud
			}
	    }
	}
	return 0; // en caso de que se llegue al fnal del ciclo sin exito se retorna 0
}

//metodo que cada vez que se inserta un nodo valida si el arbol esta equilibrado (recibe parametro como referencia el apuntador a arbol y el apuntador a una cola de hojas auxiliar)
bool validarEquilibrio(arbol &arb,cola &colhojas){
	if(altura(arb, colhojas, arb->dato) > 1){ // valida que el arbol ya tenga una altura de mas de 1 
	cout<<"altura"<<altura(arb, colhojas, arb->dato)<<endl;
		int FE2, FE;
		struct nodo *aux, *temp;
	  	if(arb->sig != NULL && arb->ant != NULL ){ //valida que en los dos campos de la raiz esten ocupadas para poder obtener la altura del nodo raiz
			FE = (altura(arb, colhojas, arb->sig->dato)+1) - (altura(arb, colhojas, arb->ant->dato)+1);  // FE = alturaRamaDerecha - alturaRamaIzquierda
	    }
	  	if(arb->ant == NULL){ // caso en el que en la rama izquierda este apuntando a null es decir que alturaRamaIzquierda se igual a 0
			FE = (altura(arb, colhojas, arb->sig->dato)+1) ; 
		}else if(arb->sig == NULL)  FE = -1*(altura(arb, colhojas, arb->ant->dato)+1); 
		//se calcula el segundo Factor de Equilibrio para determinar que rotacion realizar
		cout <<" FE "<< FE<<endl;
		
		if(FE <= -2 || FE >= 2){  // valida que el FE este en el rango de los factores que deducen si el arbol esta en desequilibrio}
		    if(FE == -2) aux = arb->ant; 
			if(FE == 2)   aux = arb->sig; 
			
			if(aux->sig != NULL && aux->ant != NULL ){ //valida que en los dos campos de la raiz esten ocupadas para poder obtener la altura del nodo raiz
				 FE2 = altura(arb, colhojas, aux->sig->dato)- altura(arb, colhojas, aux->ant->dato);  // FE = alturaRamaDerecha - alturaRamaIzquierda
		    }
		  	if(aux->ant == NULL){ // caso en el que en la rama izquierda este apuntando a null es decir que alturaRamaIzquierda sea igual a 0
				FE2 = (altura(arb, colhojas, aux->dato)) ;  cout <<"FE2 "<<FE2 <<endl;
			}else if(aux->sig == NULL)  FE2 = -1*(altura(arb, colhojas, aux->dato)); 
			//se analizan los factores de equilibrio para saber que rotacion es conveniente utilizar 	
		    if(FE == -2 && FE2 == -1)  Izqui_Izqui(arb, colhojas);
		    if(FE == 2 && FE2 == 1)  Der_Der(arb, colhojas);
		    if(FE == -2 && FE2 == 1)  Izqui_Der(arb, colhojas); 
		    if(FE == 2 && FE2 == -1)  Der_Izqui(arb, colhojas);
			return false;
		}
	}
	return true;
}

//este metodo realiza rotacion doble a la izquierda;  es lo mismo a decir que realiza una rotacion simple a la derecha 
void Izqui_Izqui(arbol &arb, cola &colhojas){ 
    struct nodo *aux = arb->ant, *temp; 
    // si el FE en la rama izquierda de la raiz y el hijo de la rama izquierda de la raiz son signos negativos
	// esto significa que esta sobrecargado dos veces a la izquierda
    //aqui es donde se tiene que hacer una rotacion *simple a la derecha*
    temp = aux->sig; // temporal apunta a hijo derecho de nodo izquierdo de la raiz
	aux->sig = arb; // hijo a la izquierda de la raiz en su campo derecho, ahora apunta  a la raiz
	arb->ant = temp; // la raiz en su campo izquierda ahora apunta hacia donde apuntaba temporal
	arb = aux;  // ahora el hijo d ela raiz a la izquierda se convierte en la raiz 
}

//este metodo realiza rotacion doble a la derceha;  es lo mismo decir que realiza una rotacion simple a la izquierda
void Der_Der(arbol &arb, cola &colhojas){
		struct nodo *aux = arb->sig, *temp;
		 // si el FE en la rama derecha de la raiz y en el hijo de la rama derecha de la raiz son signos positivos
		// esto significa que esta sobrecargado dos veces a la derecha
	    //aqui es donde se tiene que hacer una rotacion *simple a la izquierda*
        temp = aux->ant; // temporal apunta a hijo izquierdo  de nodo derecho de la raiz
		aux->ant = arb; // hijo a la derecha de la raiz en su campo izquierdo, ahora apunta  a la raiz
		arb->sig = temp; // la raiz en su campo derechi ahora apunta hacia donde apuntaba temporal
		arb = aux;  // ahora se actualiza la raiz; el hijo de la raiz a la derecha se convierte en la raiz 
}

//este metodo realiza una rotacion izquierda - derecha siempre y cuando el arbol este sobrecargada a la izquierda 
// luego en el hijo izquierdo de la raiz este sobrecargado a la derecha
void Izqui_Der(arbol &arb, cola &colhojas){
	struct nodo *temp2 =arb->ant->sig; //apunta al hijo en la rama derecha del subarbol, que esta a la izquierda de la raiz
	Der_Der(arb->ant, colhojas); //manda a llamar rotacion simple derecha pero tomando como referencia el nodo hijo actual a la izquierda de la raiz
	arb->ant = temp2; // ahora el hijo del subarbol a la izquierda aera el nuevo hijo del nodo raiz
	Izqui_Izqui(arb, colhojas); // luego partiendo del nodo raiz se hace una rotacion simple a la derecha, donde la raiz ahora cambiara de posicion, siendo 
	// el temporal la nueva raiz
} 

//este metodo realiza una rotacion  derecha- izquierda siempre y cuando el arbol este sobrecargada a la derecha 
// luego en el hijo derecho de la raiz haya crecido a la izquierda
void Der_Izqui(arbol &arb, cola &colhojas){
	struct nodo *temp2 =arb->sig->ant;  //apunta al hijo en la rama izquierda del subarbol, que esta a la derecha de la raiz
	Izqui_Izqui(arb->sig, colhojas); // ahora se aplica primero rotacion simple a la derecha
	arb->sig = temp2; // se actualiza el hijo de la raiz a la derecha, tomando lugar lo que temporal esta apuntando
	Der_Der(arb, colhojas); // luego una rotacion simple a la izquierda que es donde se actualiza la nueva raiz, la cual sera el nodo al que apunta temp
} 
