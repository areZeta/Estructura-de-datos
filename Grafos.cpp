 //Arely Herrera Pamila  201877898
 //Nestor Tellez Ronquillo 201826858
 //Emiliano Villalpando PÃƒÂ©rez 201867879
 /*el proposito de este programa es familiarizarse con el concepto de grafo y su representacion computacional por medio de 
 una matriz de adyacencia, tambien el conocimiento acerca del concepto de longitud de camino 2 y longitud de camino 3*/
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;
//inicializamos la matriz de v x v dada por el usuario en ceros
void inicializar(int m[][20],int , int, int v){
	    //se inicializa la matriz
    for(int i=0; i<v;i++){
    	 for(int j=0; j<v; j++){
    	 	m[i][j]=0;
		 }
	}	
}
//esta funcion es llamada para ingresar las aristas del grafo dentro de la matriz
void ingresarGrafo(int m[][20], int, int, int v){
	int x, y, op;
	do{
		cout<<"-------------------------------------------------------------- \n\n";
		cout<<"Ingresando las aristas (par de elementos relacionados) : \n\n";
		do{
			//se ingresan par de vertices que forman aristas hasta que el usuario presione 1
	        cout<<"Ingrese el primer vertice relacionado: \n"; 
            cin>>x; 
            cout<<"Ingrese el segundo vertice relacionado: \n"; 
            cin>>y;
            cout<<"-------------------------------------------------------------- \n\n";
            //se valida el rango del par de vertices a ingresar y se manda un mensaje en caso de que este fuera de rango
            if(x<= 0 || x>v || y<= 0 || y>v) cout << "\n ERROR, FUERA DE RANGO \n";
		}while(x<= 0 || x>v || y<= 0 || y>v );
		//se ubica la posicion de los indices en la matriz con el par de vertices ingresado y se le asigna un (1) para 
		//referenciar la adyacencia entre este par de vertices
        m[x-1][y-1] = 1;
        cout<<"Si desea ingresar un par de vertices mas preione 1, de lo contrario presione otro numero : \n\n"; 
        cin>>op;
    }while(op==1);
	
}

//este metodo se encarga de imprimir lo que contiene la matriz de adyacencia 
void imprimir(int m[][20], int f, int c,int v){
	for(int i=0; i<v; i++){
	 for(int j=0; j<v; ++j){
	    cout<<m[i][j];
		cout<<"\t";	
	 }
	cout<<"\n"; }
}

//el metodo se encarga de ver si existe adyacencia entre par de vertices que ingrese el usuario y devuelve un booleano
bool adyacenciaVertices(int m[][20], int , int ,int v){
	int f, c;
	//se ingresan desde teclado un par de vertices
	do{
		cout<<"Ingrese par de vertices: \n";
	    cin>>f;cin>>c;
	    //se valida que el par de vertices este entre el rango permitido
	}while(f<= 0 || f> v || c <= 0 || c > v);  //Valida que los valores no estén fuera del rango de la matriz
    if( m[f-1][c-1] == 1){
    	//en caso de que en ese par de vertices(indices en la matriz) se encuentre el elemento (1)
    	//se retorna un booleano ( true)
		return true;
	}
	//en caso contrario  false
    return false;
}
//en este metodo se verifica si la matriz es dirigida o no dirigida devolviendo un booleano
bool esDirigido(int m[][20], int , int ,int v){
	//con dos ciclos for se desplaza por la matriz para buscar (1's)
	for(int i=0; i< v; i++){
	    for(int j=0; j<v; j++){
	    	//cuando encuentra unos , pregunta por el elemento en la posicion ahora intercambiando fila en columna y viceversa
	        if(m[i][j] == 1 && m[j][i] != 1 ){
	        	//en caso de que al intercambiar fila y columna en el indice no encuentra  1 entonces devolvera false
	        	//dando a entender que el grafo es dirigido y por lo tanto la matriz no es simetrica
	            return false;
	        }
	    }
    }
    //en caso de que al recorrer la matriz no encuentre incongruencia entre los indices en su verdadera pocision e intercambiados 
    //retornara false indicando que la matriz es simetrica y el grafo es no dirigido
	return true;
}
// lo que este metodo realiza es elevar al cuadrado la matriz de adyacencia (esto es multiplicar la original matriz por su transpuesta)
void lon2(int m[][20], int ,int, int v, int c[][20], int , int){
	int aux = 0;
	// primer ciclo multiplica toda una fila por cada una de loas columnas
	for(int i = 0; i < v; i++){
		//en el segundo ciclo con p va cambiando el indice en el lugar de la columna
		for(int p = 0;  p < v; p++){
			//tercer ciclo controla el indice de la columnas del primer ciclo y el indice de las columnas del segundo ciclo
			for(int j = 0; j < v; j++){
				//aux solo es una variable que guarda el resultado de multiplicar fila por culumna e irlos sumando
			   aux +=( m[i][j] * m[j][p]);
		    }
		    //al final en una matriz auxiliar se guardan los resultados de la suma de los productos de fila por columnas
		    c[i][p] = aux;
		    aux = 0;
		}
	}
}

//los parametros de la llamada a esta funcion son la matriz original con sus respectivo tamaño	
//el num de vertices, la matriz aux para cuando es elevado al cuadrado, y la matriz aux para cuando es elvada al cubo
void lon3(int m[][20], int ,int, int v, int c[][20], int , int,int cub[][20],int , int){
	//llamada al metodo que eleva al cuadrado la matriz original
	lon2( m,20 ,20, v, c, 20,20);
	int aux = 0;
	// primer ciclo multiplica toda una fila por cada una de loas columnas
	for(int i = 0; i < v; i++){
		//en el segundo ciclo con p va cambiando el indice en el lugar de la columna
		for(int p = 0;  p < v; p++){
			//tercer ciclo controla el indice de la columnas del primer ciclo y el indice de las columnas del segundo ciclo
			for(int j = 0; j < v; j++){
				//aux solo es una variable que guarda el resultado de multiplicar fila por culumna e irlos sumando
			   aux +=( c[i][j] * m[j][p]);
		    }
		    //al final en una matriz auxiliar se guardan los resultados de la suma de los productos de fila por columnas
		    cub[i][p] = aux;
		    aux = 0;
		}
	}
}

void menu()
{
	//se define la matriz por default
	 int ma[20][20], cuadrado[20][20], cubo[20][20];
	 //se definen variables v = guardara el numero de vertices y op = la opcion que el usuario desea
    int op,v;
    do{
        cout<<"Bienvenido, ingrese el numero de vertices del grafo:\n ";
        cin>>v;
        if(v<=0)cout<<"El valor debe ser positivo\n";
    }  while(v<=0);
    inicializar(ma,20,20,v);
    ingresarGrafo(ma,20,20,v);
    
     do
    { 
        cout<<"\n\tMENU\n";
        cout<<" 1. IMPRIMIR GRAFO (MATRIZ DE ADYACENCIA)                    "<<endl;
        cout<<" 2. ADYACENCIA ENTRE ELEMENTOS                               "<<endl;
        cout<<" 3. CARDINALIDAD DEL GRAFO                                   "<<endl;
        cout<<" 4. VERIFICAR SI ES O NO DIRIGIDO                            "<<endl;
        cout<<" 5. LONGITUD 2                                               "<<endl;
        cout<<" 6. LONGITUD 3                                               "<<endl;
        cout<<" 0. SALIR                                                    "<<endl;
 
        cout<<"\n INGRESE OPCION: ";
        cin>> op;
        //para cada funcion llamada en cada caso
        //pasamos como parametros la matriz, el numero de filas y columnas por default , por ultimo el numero de vertices
        //con el que se delimita el numero de espacios vxv que ocupamos para la matriz de adyacencia dentro de la matriz definida por default
        switch(op)
        {
            case 1:
                 cout << "\n Matriz de Adyacencia\n";
                 imprimir( ma, 20, 20,v);
            break;
            case 2:
            	if( adyacenciaVertices(ma,20,20,v) == true){
            	   cout << "\n Existe adyacencia entre los vertices \n";	
				}else  cout << "\n NO existe adyacencia entre los vertices \n";
            break;
            case 3:
                 cout << "\n Cardinalidad: "<< v <<"\n";
            break;
            case 4:
	           if(esDirigido(ma,20,20,v)) {cout << "\nEL GRAFO NO ES DIRIGID0 \n";}else{ cout << "\nEL GRAFO ES DIRIGIDO \n";}
            break;
            case 5:
            	lon2(ma,20,20,v,cuadrado,20,20);
            	imprimir(cuadrado,20,20,v);
            break;
            case 6:
            	lon3(ma,20, 20,v,cuadrado,20,20,cubo,20,20);
            	imprimir(cubo,20,20,v);
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
