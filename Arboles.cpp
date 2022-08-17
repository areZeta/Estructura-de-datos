
//Arely Herrera Pamila  201877898
//Nestor Tellez Ronquillo 201826858

/*El proposito de este programa es crear arboles a partir de tda's ya existentes esto con el proposito de reutilizar codigo y comprender que temas
 anteriores son base para llegar a comprender este, asi como encontrar la relacion que un arbol tiene con un grafo y de esta manera lograr crear 
 a lo que se le llama un *arbol ordenado*  */
 
#define NULL false //como en c++ no existe NULL como tal , se define a null como falso
#include <stdio.h> // encabezado estandar de entrada y salida de c para definicion de constantes, operaciones de salida etc.
#include <stdlib.h> // libreria cabezera para gestión de memoria dinámica, control de procesos y otras
#include <iostream>// componente de biblioteca estandar de c++ para hacer uso de objetos cin, cout, cerr y clog.
#include <tdalistadoble.h>//archivo cabecera que incluye los m?todos del TDA Lista doblemente ligada con ligeras modificaciones para adecuarlos a este programa

using namespace std;

typedef struct nodo *arbol; //nombre alternativo a nodo(apuntador a nodo,se crea con atributos propios de un nodo)
typedef struct nodo *cola; // estructura auxiliar para guardar nodos y mandarlos a mostrar en caso de que cumplan cierto requisito
//proptotipo de funciones
void insertar(arbol &arb, int date);
void mostrarArbol(arbol &arb, int cont);
void posOrden(arbol &arb);  
void inOrden(arbol &arb);
void preOrden(arbol &arb);
void hijos(arbol &arb, int nodo);
bool indicaPadre(arbol &arb, int hijo);
void hojas(arbol &arb);
bool hermano(arbol &arb, int hermano);
bool existeNodo(arbol &arb,cola &col,int a);
bool caminoEntreDosNodos(arbol &arb, cola &col,int a, int b);
void descendientes(arbol &arb, cola &col, int date);
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
	cola col = NULL;
	int n, opc, cont = 0, op,hijo,a,b;
	do{
        cout << "\n\t ARBOLES \n";
        cout << " 1. INSERTAR ELEMENTOS EN ARBOL      " << endl;
        cout << " 2. MOSTRAR ARBOL                    " << endl;
        cout << " 3. RECORRIDO EN POS-ORDEN            " << endl;
        cout << " 4. RECORRIDO EN IN-ORDEN            " << endl;
        cout << " 5. RECORRIDO EN PRE-ORDEN            " << endl;
        cout << " 6. DADO UN NODO ME INDIQUE SUS HIJOS " << endl;
        cout << " 7. DADO UN NODO ME INDIQUE SU PADRE " << endl;
        cout << " 8. LISTAR LAS HOJAS                 " << endl;
        cout << " 9. DADO UN NODO ME INDIQUE SU HERMANO " << endl;
        cout << " 10. CAMINO ENTRE DOS NODOS               "<< endl;
        cout << " 11. DESCENDIENTES DE UN NODO             "<< endl;
        cout << " 0. SALIR                    " << endl;
        cin>> op;
        switch(op){
        	case 1:
        		cout<<"Ingrese su numero: \n"; 
		        cin>>n; 
				insertar(arb,n);
        	break;
        	case 2: // en los casos en los que hay que recorrer el rabol, primero se verifica que no este vacio, si es asi se muestra un mensaje en pantalla
        		if(listaVacia(arb)) cout << "\n ARBOL VACIO!!!\n";
                else{
                	cout << "  \n ARBOL IMPRESO DE FORMA VERTICAL   "<< endl;
        	    	mostrarArbol(arb, cont);
        	    	cout<<"\n";
				} 
        	break;
        	case 3:
        		if(listaVacia(arb)) cout << "\n ARBOL VACIO!!!\n";
	        	else{
	        		cout << "  \n RECORRIDO Pos-Orden\n   "<< endl;
	        		posOrden(arb);
				}
        	break;
        	case 4:
        		if(listaVacia(arb)) cout << "\n ARBOL VACIO!!!\n";
	        	else{
	        		cout << "  \n RECORRIDO In-Orden\n   "<< endl;
	        		inOrden(arb);
				}
            break;
            case 5:
            	if(listaVacia(arb)) cout << "\n ARBOL VACIO!!!\n";
	            else{
	            	cout << "  \n RECORRIDO Pre-Orden\n   "<< endl;
	        		preOrden(arb);
				}
            break;
            case 6:
            	if(listaVacia(arb)) cout << "\n ARBOL VACIO!!!\n";
            	else{
            		
            		cout<<"Ingrese el nodo: \n"; 
		            cin>>n; 
				    hijos(arb,n);
				}
            	
        	break;
        	case 7:
        		if(listaVacia(arb)) cout << "\n ARBOL VACIO!!!\n";
	            else{
	            	cout << " \n  Ingrese nodo hijo    "<< endl;
	            	cin>> hijo;
	            	if(!indicaPadre(arb,hijo)) cout <<" \n Nodo hijo no existe dentro de arbol"<< endl;
				}
			break; 
			case 8:
				if(listaVacia(arb)) cout << "\n ARBOL VACIO!!!\n";
				else
				hojas(arb);
			break;
			case 9:
				if(listaVacia(arb)) cout << "\n ARBOL VACIO!!!\n";
	            else{
	            	cout << " \n  Ingrese nodo     "<< endl;
	            	cin>> n;
	            	if(!hermano(arb,n)) cout <<" \n Nodo ingresado no existe dentro de arbol"<< endl;
				}
			break; // para los siguientes casos se verifica que los nodos ingresados por el usuario existan¡
			case 10:
            	if(listaVacia(arb)) cout << "\n ARBOL VACIO!!!\n";
	            else{
	            	cout << " \n  Ingrese  nodos : \n "<< "a: ";
	            	cin>> a; 
					cout << "\n b: "; cin >> b;
	            	if(existeNodo(arb,col,a) && existeNodo(arb,col,b)){
	            		if(!caminoEntreDosNodos(arb,col, a, b) && a != b) cout <<" \n No existe camino de nodo " << a <<"  a  " << b <<endl;
					}else cout <<"\n No existen tales nodos dentro del arbol"<< endl;
				}
            break;
            case 11:
            	if(listaVacia(arb)) cout << "\n ARBOL VACIO!!!\n";
	            else{
	            	cout << " \n  Ingrese  nodo a listar descendientes   "<< endl;
	            	cin>> a;
	            	if(existeNodo(arb,col,a) ){
	            		descendientes(arb,col, a);
					}else cout <<"\n No existe nodo dentro de arbol"<< endl;
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

//recorrido en Pos-Orden (Izquierda Derecha Visita (IDV))
void posOrden(arbol &arb){
	if(!listaVacia(arb)){ // como la funcion es recursiva cada vez que se vuelva a llamar se tiene que validar que cada sub-arbol a la derecha o a la
	//izquierda del arbol todavia tenga hijos
		posOrden(arb->ant); // primero se va sobre por las ramas de la izquierda hasta llegar a una hoja
		posOrden(arb->sig);//  luego regresa por las ramas de la derecha derecha
		cout <<"  "<< arb->dato; //por ultimo muestra los hijos de cada sub-arbol de la rama izquierda, enseguida los padres
		//luego lo mismo en la rama derecha y por ultimo la raiz
	}
}
// recorrido In-Orden(Izquierda Visita Derecha (IVD))
void inOrden(arbol &arb){
	if(!listaVacia(arb)){//como la funcion es recursiva cada vez que se vuelva a llamar se tiene que validar que cada sub-arbol a la derecha o a la
	//izquierda del arbol todavia tenga hijos
		inOrden(arb->ant);// primero se va a recorrer las ramas del arbol por la izquierda hasta llegar a una hoja
		cout <<"  "<< arb->dato; //y va mostrando los nodos por los que va regresando 
		// en si muestra primero toda la rama a la izquierda , luego la raiz y por ultimo la rama derecha del arbol
		inOrden(arb->sig); // luego una vez impreso el hijo a la izquierda y el padre imprime el hijo a la derecha
	}
}
//recorrido en pre-Orden(Visita Izquierda Derecha(VID))
void preOrden(arbol &arb){
	if(!listaVacia(arb)){//como la funcion es recursiva cada vez que se vuelva a llamar se tiene que validar que cada sub-arbol a la derecha o a la
	//izquierda del arbol todavia tenga hijos
		cout <<"  "<< arb->dato; // muestra primero el nodo raiz, luego muestra los padre de cada sub-arbol y por ultimo hijos,(empezando por las hojas)
		preOrden(arb->ant);// depues de mostrar la raiz se recorre por la rama izquierda hasta llegar a una hoja
		preOrden(arb->sig);// luego se regresa por la derecha de cada sub-arbol
	}
}
//metodo que dado un nodo, lista sus hijos
void hijos(arbol &arb, int nodo){
    if(!listaVacia(arb)){ //como la funcion es recursiva cada vez que se vuelva a llamar se tiene que validar que cada sub-arbol a la derecha o a la
	//izquierda del arbol todavia tenga hijos
		if(arb->dato==nodo){ //busca el nodo solicitado
			if(arb->ant!=NULL)
			cout <<"  "<< arb->ant->dato;       //se verifica la existencia del hijo antes de mandar a imprimirlo
			if(arb->sig!=NULL)
			cout <<"  "<< arb->sig->dato;
		}
	    
	    hijos(arb->ant,nodo); // depues de mostrar la raiz se recorre por la rama izquierda hasta llegar a una hoja
		hijos(arb->sig,nodo); // luego se regresa por la derecha de cada sub-arbol
		
		
	}	
}

// metodo que busca primero el nodo hijo dentro del arbol con dos apuntadores: uno al nodo padre y otro al nodo hijo dentro del ciclo de busqueda
bool indicaPadre(arbol &arb, int hijo){
	int ban =0; //  solo se utiliza para verificar que el nodo hijo buscado no sea la raiz 
	struct nodo *b = arb, *a; // apuntadores auxiliares (b) es el que ira por delante buscando al nodo hijo y (b) se quedara detras(es decir en el padre)   
	while(!listaVacia(b)){ // mientras el auxiliar que va buscando el nodo hijo no sea NULL el ciclo sigue buscando
		if(b->dato == hijo){// en caso de que se encuentre el nodo hijo ,se imprime el apuntador auxilia a nodo padre en su campo dato
			if(ban == 0){ // con ban solo se verifica que el nodo hijo buscado sea la raiz del arbol
				cout << hijo <<"  ES NODO RAIZ(NO TIENE PADRE)  " <<endl;
			}else cout <<" \n El padre de nodo " << hijo << " es "<< a->dato << endl;// en caso de que no sea la raiz este imprime su padre
			return true; // retorna verdadero notificar que el nodo hijo buscado  existe en el arbol
		}
		a = b; //se iguala auxilia a con b para que antes de moverse b el auxiliar a quede apuntando al nodo padre
		if(hijo >= b->dato)  b= b->sig; // se mueve a la derecha en caso de que el nodo hijo buscado se mayor(mayores a raiz)
	   	else b = b->ant;	// caso contrario se mueve a la izquierda(menores a la raiz)
	   	ban = 1; // solo notifica que a apartir de que encienda , el nodo que se encuentre no es raiz
	}
	return false;// retorna falso en caso de que haya hecho el ciclo y no haya encontrado el nodo hijo dentro del arbol
}

//metodo que lista las hojas del arbol
void hojas(arbol &arb){
	if(!listaVacia(arb)){//como la funcion es recursiva cada vez que se vuelva a llamar se tiene que validar que cada sub-arbol a la derecha o a la
	//izquierda del arbol todavia tenga hijos
		if(arb->ant==NULL &&arb->sig==NULL)   //se valida que el nodo cumpla las caracteristicas de una hoja para poder imprimirlo
		 cout <<"  "<< arb->dato;
	    
	    hojas(arb->ant);  // depues de mostrar la raiz se recorre por la rama izquierda hasta llegar a una hoja
		hojas(arb->sig);  // luego se regresa por la derecha de cada sub-arbol
		
		
	}	
}

bool hermano(arbol &arb, int hermano){
	struct nodo *b = arb, *a; // apuntadores auxiliares (b) es el que ira por delante buscando al nodo hermano y (b) se quedara detras(es decir en el padre)  
	int ban = 0, pad;//  ban solo se utiliza para verificar que el nodo hijo buscado no sea la raiz, pad almacena el padre 
	while(!listaVacia(b)){ // mientras el auxiliar que va buscando el nodo hijo no sea NULL el ciclo sigue buscando
		if(b->dato == hermano){
			if(ban == 0){ // con ban solo se verifica que el nodo hijo buscado sea la raiz del arbol
				cout << hermano <<"  ES NODO RAIZ  " <<endl;
			}else{
				pad=a->dato;
				if(hermano<pad){
				 if(a->sig!=NULL)
				 cout << "EL HERMANO DE "<< hermano <<" ES "<< a->sig->dato <<endl;
				 else
				 cout << hermano <<" NO TIENE HERMANO "<<endl;}                   //se valida de que lado esta el hermano a imprimir
				else{
				 if(a->ant!=NULL)
				 cout << "EL HERMANO DE "<< hermano <<" ES "<< a->ant->dato <<endl;
				 else
				  cout << hermano <<" NO TIENE HERMANO "<<endl;
				}
				 
			} 
			return true; // retorna verdadero notificar que el nodo hijo buscado  existe en el arbol
		}
		a = b; //se iguala auxilia a con b para que antes de moverse b el auxiliar a quede apuntando al nodo padre
		if(hermano >= b->dato)  b= b->sig; // se mueve a la derecha en caso de que el nodo hijo buscado se mayor(mayores a raiz)
	   	else b = b->ant;	// caso contrario se mueve a la izquierda(menores a la raiz)
	   	ban = 1; // solo notifica que a apartir de que encienda , el nodo que se encuentre no es raiz
	}
	return false;// retorna falso en caso de que haya hecho el ciclo y no haya encontrado el nodo hijo dentro del arbol
}
 
//metodo usado para verificar que dentro del arbol exista el nodo con el cual se quiere operar
bool existeNodo(arbol &arb, cola &col, int date){
	 struct nodo *aux = arb; // se crea un apuntador auxiliar y se iguala a la raiz del arbol , retorna booleano
	 while(aux != NULL){
	 	if(aux->dato == date){
	 	  col =  aux;
		  return true; // en caso de que el nodo buscado se encuentre , inmediatamente se retorna verdadero
	    }
		if(date >= aux->dato)aux = aux->sig; //  si el nodo buscado es mayor o igual al dato al que apunta auxiliar, se mueve por la rama derecha
		else aux = aux->ant; // menores se mueve por la rama izquierda
	 }
	 return false; // en caso de haber recorrido el arbol y nop haber encontrado nada , este retorna falso
}
bool caminoEntreDosNodos(arbol &arb,cola &col, int a , int b){
	struct nodo *aux = arb;
	if(a == b){ // primero en el caso de que los dos nodos sean iguales se busca si hay dos nodos iguales en el arbol
	    aux = col; //el apuntador auxiliar global col asigna el lugar donde quedo apuntando despues de la ejecucion del metodo existeNodo()
	    //para desde ahi comenzar a buscar a la derecha un nodo igual (se va a la derecha con seguridad porque a la derecha agregamos los mayores o iguales a un nodo)
		if(!existeNodo(aux->sig, col, b)){
			cout << " \n no existen dos nodos iguales "<< endl; // en caso de que no exista dos nodos iguales manda un mensaje en pantalla y returna falso
			return false;
		}
	}
	col = NULL; //apuntador auxliar global ahora apunta a NULL
   while(aux->dato != a ){ // en este primer ciclo lo que hace es moverse por todo el arbol hasta encontrar el primer nodo
		if(a >= aux->dato)aux = aux->sig; // moverse por rama derecha
    	else aux = aux->ant;// o rama izquierda
	}
	//struct nodo *co = col;
	 // una vez encontrado el primer nodo, se parte de ahi para buscar un mcamino al segundo
	insertarFinal(col,aux->dato); // se inserta el primer nodo a la cola
	while(aux != NULL ){// segundo nodo comienza a buscar el segundo nodo iniciando  del primer nodo encontrado hasta que se llegue al nodo buscado o hasta que 
	//apuntador auxiliar se a= NULL
		if(b >= aux->dato)aux = aux->sig;// se mueve por rama derecha
		else aux = aux->ant; // o se mueve por rama izquierda
		if(aux != NULL){ // se verifica el caso de que al moverse por alguna de las ramas encuentre NULL antes de volver al ciclo
			insertarFinal(col,aux->dato); // se insertan los nodos que van formando el camino en la cola auxiliar
			if(b == aux->dato){ //en caso de que se llegue al nodo requrido 
				cout<<" \n Camino de nodo "<< a << " a " << b<< endl; // se imprime el camino que cola auxiliar guardo
				mostrarLD(col);
				return true; // y se retorna verdadero para indicar que se concluyo el proceso exitosamente
			}
	    }
	}
	return false; // en caso de que se llegue al fnal del ciclo sin exito tambien se indica con un falso
}

// el metodo lo que busca son los descendientes de un nodo ingresado por el usuario
void descendientes(arbol &arb ,cola &col, int date){
	struct nodo *aux = arb, *aux2; // se crean dos apuntadores auxiliares
	aux = col; // el apuntador auxiliar global que quedo apuntando al nodo en el que se encontro el nodo buscado
	cout << "\n Descendientes de "<< date << "\n" <<endl; 
	if(aux->ant == NULL && aux->sig == NULL)cout << "\n " << date <<" No tiene descendientes \n"<< endl; // si apuntador a nodo buscado por la izquierda y derecha
	//apuntan a NULL esto quiere decir que aux es una hoja por tanto no tien descendientes
	if(aux->ant != NULL){ // primero  imprime descendiente por la rama izquierda
	  aux2 = aux;
	  aux = aux->ant;
	  preOrden(aux);
	}
	if(aux2->sig != NULL){ // luego imprime descendientes por la rama derecha
	  aux2 = aux2->sig;
	  preOrden(aux2);
	}
}
