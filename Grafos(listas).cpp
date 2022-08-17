//Arely Herrera Pamila  201877898
//Nestor Tellez Ronquillo 201826858

/*El proposito de este programa es optimizar el manejo de grafos mediante listas ligadas (lista de adyacencia), agregandole los distintos recorridos en el grafo
tales como a lo ancho y lo profundo, esto con el proposito de conocer las distintas alternativas de caminos para llegar de un punto a otro
pero siempre evitando los ciclos*/

#define NULL false //como en c++ no existe NULL como tal , se define a null como falso
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <tdalista.h>//archivo cabecera que incluye los m?todos del TDA Lista con ligeras modificaciones para adecuarlos a este programa

using namespace std;
void imprimir(lista &grafo);


typedef struct nodo *lista, *p; //definicion de tipos


void inicializar(lista &grafo, int v){  //aqui se crean los nodos principales correspondientes a los vertices del grafo
	    
    for(int i=0; i<v;i++){
    	//metodo de libreria tdaLista.h, que es la lista de vertices del grafo
    	insertarFinal(grafo); 
	} 
	ordenarMenMay(grafo);
}

void ingresarGrafo(lista &grafo){
	int op;
	char x,y;
	struct nodo *aux;
	do{
		cout<<"\n-------------------------------------------------------\n";
		cout<<"Ingresando las aristas (par de elementos relacionados) : \n\n";
		
			//se ingresan par de vertices que forman aristas hasta que el usuario presione 1
	        cout<<"Ingrese el primer vertice relacionado: \n"; 
            cin>>x; 
            cout<<"Ingrese el segundo vertice relacionado: \n"; 
            cin>>y;
         cout<<"\n-------------------------------------------------------\n";   
		int ban=0;
		aux=grafo;
		do{
		  if(x==aux->nombre){   //si el primer vertice existe, se crea el nodo correspondiente al vertice relacionado en el campo ady, que es 
		  insertarFinal2(aux->ady,y);//un apuntador a una lista, la de vertices relacionados
		  ban=1;}
		  aux=aux->sig;
	    }while(aux->sig!=NULL);
	    
	    if(aux->sig==NULL)      //valida el ultimo vertice
	     if(x==aux->nombre){
		  insertarFinal2(aux->ady,y);
		  ban=1;}
	    
	    if(ban==0) { //indicador de existencia del primer vertice
	     cout<<"El vertice inicial no existe \n"; }
		  
		  
        cout<<"Si desea ingresar un par de vertices mas presione 1, de lo contrario presione otro numero : \n\n"; 
        cin>>op;
    }while(op==1);
    aux = grafo;
    //ordena la lista de menor a mayor para hacer mas facil realizar el recorrido en el grafo
	while(aux->sig!=NULL){
		if(aux->ady != NULL ){
	       ordenarMenMay(aux->ady);// metodo de la libreria lista.h
		}
	    aux=aux->sig;
	}
	if(aux->ady != NULL ){
	       ordenarMenMay(aux->ady);// metodo de la libreria lista.h
	}
}


void imprimir(lista &grafo)
{
	struct nodo *aux;  //con aux se recorre la lista principal
	aux=grafo;
	while(aux->sig!=NULL){
		if(aux->ady!=NULL){
		cout<<"El vertice "<<aux->nombre<< " esta relacionado con:";
		mostrar(aux->ady);  //se imprime la lista de verices adyacentes apuntada por ady
		cout<<"\n";}else{
			cout<<"El vertice "<<aux->nombre<< " no tiene relaciones";
			cout<<"\n";
		}
		aux=aux->sig;
	}
	if(aux->sig==NULL){ //se valida el ultimo vertice
	   if(aux->ady!=NULL){
		cout<<"\nEl vertice "<<aux->nombre<< " esta relacionado con:";
		mostrar(aux->ady);  //se imprime la lista de verices adyacentes apuntada por ady
		cout<<"\n";}else{
			cout<<"\n El vertice "<<aux->nombre<< " no tiene relaciones";
			cout<<"\n";
		}
	} 
}

void adyacencia(lista &grafo){
	int op;
	char x,y;
	struct nodo *aux, *aux2; //aux recorre la lista principal y aux 2 recorre la lista de vertices adyacentes a cada nodo principal
	do{
	        cout<<"Ingrese el primer vertice : \n"; 
            cin>>x; 
            cout<<"Ingrese el segundo vertice : \n"; 
            cin>>y;
         
		int ban=0;   
		aux=grafo;
		while(aux->sig!=NULL){
		  if(x==aux->nombre){  //encuentra el nodo principal
		  	aux2=aux->ady;
		  	if(aux2!=NULL){
			  	while(aux2->sig!=NULL){
				  	if(aux2->nombre==y) //encuentra el nodo adyacente
				  	 ban=1;
				  	 aux2=aux2->sig;
			  	 }
			  	
			  	 if(aux2->sig==NULL) //valida el ultimo nodo en la lista de vertices adyacentes
			  	 if(aux2->nombre==y)
			     ban=1;
			}
	     }
		 aux=aux->sig;
	    }
	    
	   if(aux->sig==NULL)  //se valida el ultimo vertice principal
	    if(x==aux->nombre){
		  	aux2=aux->ady;
		  	if(aux2!=NULL){
		  	while(aux2->sig!=NULL){
		  	if(aux2->nombre==y)
		  	 ban=1;
		  	 aux2=aux2->sig;
		  	 }
		  	 
		  	 if(aux2->sig==NULL)
		  	  if(aux2->nombre==y)
		  	   ban=1;
		  }
		  }
	    
	    
	    if(ban==1){  //indicador que valida la adyacencia
	     cout<<"Los vertices estan relacionados \n"; 
	    }else{
	    	cout<<"Los vertices no estan relacionados \n"; 
		} 
		  
        cout<<"Si desea probar con un par de vertices mas presione 1, de lo contrario presione otro numero : \n\n"; 
        cin>>op;
    }while(op==1);
    
	
}
//metodo que resibe una matriz como parametro, el tyamaño del grafo y dos apuntadores a nodos(uno de nodo y el otro del nodo al inicio de la lista)
void bpp( char marca[][50],int,int,int v,lista &grafo,lista &aux){
	struct nodo *r = aux, *g =grafo; int ban2 = 0,ban = 0;
	for(int i = 0; i < v ; i++){ //busca en el arreglo marcas el nodo para marcarlo como visitado
		if( marca[0][i] ==  aux->nombre){
		   marca[1][i] = 'v';
		}
    }
	cout<<"\n"<< aux->nombre;// se imprimen los nodos quevan siendo visitados por la busqueda por profundidad
	while(g->sig != NULL){//se busca dentro del grafo algun nodo con el mismo nombre del nodo que que acaba de visitar
		if(aux->nombre == g->nombre ){
			ban = 1;
			break;// en el momento en el que lo encyuentre corta el ciclo con el objetivo que el apuntadore quede en el nodo que se busca
		}
		g = g->sig;
	}
	if(aux->nombre == g->nombre ){// se verifica en el caso anterior en el ultimo nodo ya que en el ciclo no logra se verificado
		ban = 1;
	}
	if(ban == 1 &&  g->ady != NULL ){
		r = g->ady;// en caso de que se haya encontrado , un apuntador apunta a sus adyacentes
		while(r != NULL){// con el apuntador a los adyacentes del nodo buscado se hace un ciclo 
			ban2 = 0;
			for(int i = 0; i < v; i++){//se verifica que los nodos adyacentes no hayan sido visitado antes
				if( marca[0][i] == r->nombre && marca[1][i] == 'n'){
				  ban2 = 1;// en caso de que no hayan sido visitados se ocupa una bandera para comprobar esto y seguir con la busqueda
				}
			}
			if(ban2 == 1){// si el nodo adyacente no a sido visitado se hace una llamada a si misma
			  bpp( marca,2,50,v,grafo,r);	
			}
			r = r->sig;
		}
   }
	// esta llamada a si misma es una manera de buscar caminos posibles hasta que ya no haya por donde seguir porque ya todos han sido visitados 
	//regresa hacia atras buscando caminos alternativos inexplorados.
}
//funcion que ayuda a identificar el nodo de partida dentro del grafo
void RecProfundo(lista &grafo, int v){
	char marca[2][50], nom; //se declara una matriz de que llevara el control de  los vertices  visitados y los no visitados 
	int ban = 0, index, ban2 = 0;
	struct nodo *aux = grafo; // apuntadores auxiliares
	for(int i = 0; i < v ; i++){ //ciclo que inicializa la matriz de marcas con la letra n señalando que los nodos no han sido visitados
		marca[0][i] = aux->nombre;
     	marca[1][i] = 'n';
     	aux = aux->sig;
    }
	do{
		cout<<"\n Ingresa nodo de partida \n";
		cin>>nom;
		aux = grafo;
		for(int i = 0; i < v ; i++){//ciclo que busca el nodo de partida en la lista de adyacencia
			if(aux->nombre == nom){
				ban = 1;
				break;
			}
			aux= aux->sig;
		}
		if(ban == 1){//si existe el nodo dentro de la lista , entonces busca el inidice que ocupa el nodo dentro de la matriz de marcas
			for(int i = 0; i < v; i++){
				if( marca[0][i] == nom){
				  index = i;
				}
			}
	    }
		if(ban == 0)cout<<"\nERROR, NODO INGRESADO NO EXISTE \n";
	}while(ban == 0);// se pregunta el nodo de partida, hasta que el usuario de un nodo  existente
	if(marca[1][index] == 'n'){ // con el indice encontrado que ocupa el nodo dentro de la matriz se verifica que no haya sido visitada
	    cout<<"\n -- Recorrido en lo profundo (bpp) --\n";
		bpp( marca,2,v,v,grafo,aux);//si no a sido visitada mada a llamar a la funcion de busqueda por profundidad
	}
	
}

//metodo que busca a lo ancho de un grafo y recibe como parametros una referencia al grafo y el numero de vertices de este
void recorridoAncho(lista &grafo, int v){
	struct nodo *cola = NULL, *aux = grafo, *aux2,*controlCola; //declaracion de la cola y los apuntadores auxiliares
	char marca[2][50], nom; //se declara una matriz de que llevara el control de  los vertices  visitados y los no visitados 
	int  index, ban = 0;
	bool existeAdy = false;
	for(int i = 0; i < v ; i++){ //ciclo que inicializa la matriz de marcas con la letra n señalando que los nodos no han sido visitados
		marca[0][i] = aux->nombre;
     	marca[1][i] = 'n';
     	aux = aux->sig;
    }
	aux=grafo;
	do{
		cout<<"\n Ingresa nodo de partida \n";
		cin>>nom;
		aux = grafo;
		for(int i = 0; i < v ; i++){//ciclo que busca el nodo de partida en la lista de adyacencia
			if(aux->nombre == nom){
				ban = 1;
				break;
			}
			aux= aux->sig;
		}
		if(ban == 1){//si existe el nodo dentro de la lista , entonces busca el inidice que ocupa el nodo dentro de la matriz de marcas
		    cout <<"\n-- Recorrido a lo ancho (bpa) --)\n";
			for(int i = 0; i < v; i++){//se busca en la matriz de marcas el nombre del nodo para marcarlo como visitado
				if( marca[0][i] == nom && marca[1][i] == 'n' ){
				  marca[1][i] = 'v';
				  insertarFinal2(cola,aux->nombre);
				}
			}
			if(aux->ady != NULL ){// verifica que el nodo inicial tenga un adyacente por lo menos
			  aux2 = aux->ady;// coloca un apuntador al inicio del nodo adyacente del nodo inicial
			  while(aux2 != NULL){ // ciclo que pasa por todos los nodos adyacentes
				nom = aux2->nombre;
				for(int i = 0; i < v; i++){// ciclo que ingresa los nodos a la cola en caso de que estos no hayan sido visitados y su nombre sea 
				// el correspondiente en la matriz marca
					if( marca[0][i] == nom  && marca[1][i] == 'n'){
					   marca[1][i] = 'v';	
					   insertarFinal2(cola,nom); // encolamos los adyacentes del nodo inicial
					   existeAdy = true;//bandera tipo bool que indica si el nodo inicial tiene adyacentes
					}
			    }	
				aux2  = aux2->sig;
		      }
		   }
	   }
		if(ban == 0)cout<<"\nERROR, NODO INGRESADO NO EXISTE \n";
	}while(ban == 0);
//caso cuando el nodo inicial no tenga adyacencia 
    if(existeAdy){//con la bandera tipo bool se verifica si el proceso de busqueda en anchura continua esto solo si el nodo de inicio tiene adyacentes
    	struct nodo *controlGrafo ;
    	while(listaVacia(cola) == false){// ciclo que verifica que todos los nodos sean visitados de acuerdo a su adyacencia(es decir de acuerdo al 
    	//orden en que fueron siendo ingresados a la cola
    		controlGrafo = grafo;
    		char x = eliminarInicio(cola); // el metodo eliminar al inicio(desEncolar) de lista.h devuelve el nombre del nodo eliminado al inicio
    		cout<<"\n "<<x;
    		if(listaVacia(cola) == false){// verifica en caso de que durante el proceso la cola se quede vacia 
    			nom = cola->nombre; // nom va tomando nombres de los nodos que estan en la cola para buscarlos en el grafo
	    	    for(int i = 0; i < v ; i++){ 
	    	    	if( controlGrafo->nombre == nom){
	    	    		if( marca[1][i] == 'n')marca[1][i] = 'v';
	    	    		break;
					}
					controlGrafo = controlGrafo->sig;//el apuntador auxiliar a grafo va cambiando de posicion hasta que el nodo de la cola sea encontrado en el grafo
				}
				//controlGrafo trae el apunbtador al nodo dentro del grafo
				if(controlGrafo->ady != NULL){// para cada nodo de la cola encontrado en el grafo verifica que tenga a lo menos un nodo adyacente
					aux2 = controlGrafo->ady;//con un auxiliar apunta al primer nodo adyacente 
					while(aux2!= NULL){// ciclo que pasa por todos los nodos adyacentes del de cada nodo del grafo
						nom = aux2->nombre;
						for(int i = 0; i < v; i++){
							if( marca[0][i] == nom  && marca[1][i] == 'n'){
							   marca[1][i] = 'v';// los marca como visitados si y solo si encuentra el nodo en alguna posicion de la marca y si no han sido visitados
							   insertarFinal2(cola,nom); // encola si y solo si encuentra el nodo en una posicion de la marca y si el nodo no ah sido visitado
							}
				       }
				       aux2 = aux2->sig;
					}
					
				}
			}
		}
    	
	}else{
		//en caso de que el nodo de inicio no tenga adyacentes(es decir no tenga opciones para formar caminos) se imprime directamente el nodo de inicio 
		cout<<" \n"<<cola->nombre;
		delete(cola);
	}
	
}
	
void menu()
{
	lista grafo = NULL;
	 //se definen variables v = guardara el numero de vertices y op = la opcion que el usuario desea
    int op,v;
    do{
    	cout<<"-------------------------------------------------------\n";
        cout<<"Bienvenido, ingrese el numero de vertices del grafo:\n ";
        cout<<"-------------------------------------------------------\n";
        cin>>v;
        if(v<=1)cout<<"El valor debe ser MAYOR a uno\n";
    }  while(v<=1);
    inicializar(grafo,v);
    ordenarMenMay(grafo);//desde un inicio se ordenan la lista de nodos del grafo, asi como las listas de sus adyacentes en el metodo inicializar
    ingresarGrafo(grafo);
    
     do
    { 
        cout<<"\n-------------------------------------------------------\n";
        cout<<"\n\tMENU\n";
        cout<<" 1. IMPRIMIR GRAFO                                           "<<endl;
        cout<<" 2. ADYACENCIA ENTRE ELEMENTOS                               "<<endl;
        cout<<" 3. CARDINALIDAD DEL GRAFO                                   "<<endl;
        cout<<" 4. RECORRIDO A LO PROFUNDO                                 "<<endl;
        cout<<" 5. RECORRIDO A LO ANCHO                                     "<<endl;
        cout<<" 0. SALIR                                                    "<<endl;
        cout<<"\n-------------------------------------------------------\n";
 
        cout<<"\n INGRESE OPCION: ";
        cin>> op;
        //para cada funcion llamada en cada caso
        //pasamos como parametro el grafo (lista de adyacencia)
        switch(op)
        {
            case 1:
                 cout << "\n Grafo\n";
                 imprimir(grafo);
            break;
            case 2:
            	 adyacencia(grafo);
            break;
            case 3:
                 cout << "\n Cardinalidad: "<< v <<"\n";
            break;
            case 4:
            	  RecProfundo(grafo, v);
            break;
            case 5:
            	  recorridoAncho(grafo,v);
            break;
            case 0:
            break;
            default:
                 cout << "\n Opcion incorrecta ";
            break;
 
        }
 
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


