/***********************************************/ 
/* Lista Encadeada                             */
/* objetivo: Percurso DFS de um grafo          */
/* programador: Daniela Bagatini               */
/* refer�ncia www.programiz.com/dsa/graph-dfs  */
/* criado em: 01/11/2021                       */
/* data da ultima alteracao: 01/11/2022        */
/***********************************************/ 

#include <stdio.h>   // entrada e sa�da padr�o: printf, scanf
#include <stdlib.h>  // exit, malloc, system


/***********************************************/ 
/* Defini��o do Registro e da Estrutura        */
/***********************************************/ 
struct NODO{
  int vertice;
  struct NODO *prox;
} NODO;

struct GRAFO{
  int numVertices;
  int *visitado;
  struct NODO **adjListas; // Para um array bidimensional din�mico usamos **. Da mesma forma, usamos struct nodo** para armazenar um array para uma lista encadeada.
} GRAFO;

/* Observa��es sobre struct NODO **adjListas: adicionar um asterisco a mais significa
 que adjListas em si � um ponteiro para um array de ponteiros para a estrutura NODO. 
 Isso � comum quando voc� precisa alocar dinamicamente a mem�ria para a lista de 
 adjac�ncia. O ponteiro adjListas apontar� para o primeiro elemento do array, que � 
 um array de ponteiros para a estrutura NODO. */ 

/***********************************************/ 
/* Defini��o das Fun��es                       */
/***********************************************/ 
void dfs( struct GRAFO* grafo, int vertice );                    // Algoritmo DFS de busca em profundidade.
struct NODO* criaNo( int valor );                                // Cria um novo nodo.
struct GRAFO* criaGrafo( int vertices );                         // Cria o grafo.
void adicionaNoGrafo( struct GRAFO* grafo, int origem, int destino );  // Adiciona rela��es no grafo (adjac�ncias).
void imprimeGrafo( struct GRAFO* grafo );                        // Mostra o grafo.


/***********************************************/ 
/* Programa Principal                          */
/***********************************************/
int main(){
  int numeroVertices = 4;  // N�mero de v�rtices do grafo
  printf( " Informe o numero de vertices do grafo: %d\n", numeroVertices);
  //fflush(stdin);
  //scanf( "%d", &numeroVertices );
  
  struct GRAFO* grafo = criaGrafo( numeroVertices );  // Cria o grafo
  adicionaNoGrafo( grafo, 0, 1 );
  adicionaNoGrafo( grafo, 0, 2 );
  adicionaNoGrafo( grafo, 1, 2 );
  adicionaNoGrafo( grafo, 2, 3 );
  imprimeGrafo( grafo );

  if( grafo != NULL )      // Verifica se grafo n�o est� vazio
  	  dfs( grafo, 2 );     // Percurso em profundidade no grafo a partir do v�rtice indicado como argumento

  return 0;
}


/************************************************ 
 * dfs                                          *
 * objetivo: algoritmo percurso em profundidade *
 * entrada : grafo, vertice de refer�ncia       *
 * saida   : percurso visitado                  *
 ************************************************/
void dfs( struct GRAFO* grafo, int vertice ){           // V�rtice inicial
  struct NODO* temp = grafo->adjListas[ vertice ];      // Ponteiro tempor�rio para caminhar pela lista de adjac�ncia do v�rtice

  grafo->visitado[ vertice ] = 1;                       // Marca como v�rtice visitado. Isso � feito para evitar visitar o mesmo v�rtice v�rias vezes durante a busca em profundidade.   
  printf( "Visitado %d \n", vertice );                        
  
   while( temp != NULL ){                               // Percorre a lista de adjac�ncia do v�rtice. Crit�rio de parada da recurs�o.  
	    if( grafo->visitado[ temp->vertice ] == 0 )     // Verifica se o v�rtice adjacente ainda n�o foi visitado.
	      	dfs( grafo, temp->vertice );                // Repete o processo at� que o v�rtice procurado seja encontrado ou n�o haja mais v�rtices adjacentes
	    temp = temp->prox;                              // Passa para pr�ximo v�rtice adjacente na lista de adjac�ncia.
   }      
}


/*
  while( temp != NULL ){                                // Crit�rio de parada  
    int verticeConectado = temp->vertice;               // V�rtice visitado torna-se o v�rtice inicial
    if( grafo->visitado[ verticeConectado ] == 0 )
      dfs( grafo, verticeConectado );                   // Repete o processo at� que o v�rtice procurado seja encontrado ou n�o haja mais v�rtices adjacentes
    temp = temp->prox;
  }
*/

/************************************************ 
 * criaNodo                                     *
 * objetivo: cria novo nodo                     *
 * entrada : valor do nodo                      *
 * saida   : nodo criado                        *
 ************************************************/
struct NODO* criaNo( int valor ){
  struct NODO* no = ( struct NODO* ) malloc( sizeof( struct NODO ) );
  no->vertice = valor;
  no->prox = NULL;
  return no;
}


/************************************************ 
 * criaGrafo                                    *
 * objetivo: cria o grafo                       *
 * entrada : n�mero de vertices                 *
 * saida   : grafo criado                       *
 ************************************************/
struct GRAFO* criaGrafo( int vertices ) {
  struct GRAFO* grafo = ( struct GRAFO* ) malloc( sizeof( struct GRAFO ) );  // Aloca mem�ria para o grafo.
  if( grafo == NULL )
  	  printf( "\n N�o foi poss�vel alocar mem�ria!" );
  else{
	  grafo->numVertices = vertices;                                             // Inicializa o campo de n�mero de v�rtices do grafo.
	  grafo->visitado = ( int* ) malloc( vertices * sizeof( int ) );             // Cria a lista de visitados conforme o n�mero de v�rtices.	  
	  grafo->adjListas = ( struct NODO** ) malloc( vertices * sizeof( struct NODO* ) );  // Cria a lista de adjac�ncias conforme o n�mero de v�rtices.
	
	  int i;
	  for( i = 0; i < vertices; i++ ) {                                          // Inicializa todos os v�rtices com NULL.
	    grafo->adjListas[ i ] = NULL; 
	    grafo->visitado[ i ] = 0;
	  }
 }
 return grafo;
}


/************************************************ 
 * adicionaNoGrafo                              *
 * objetivo: adiciona na lista de adjac�ncias   *
 * entrada : grafo, origem e destino            *
 * sa�da   : grafo (por refer�ncia)             *
 ************************************************/
void adicionaNoGrafo( struct GRAFO* grafo, int origem, int destino ){
  
  struct NODO* no = criaNo( destino );    // Cria o nodo do v�rtice destino.
  no->prox = grafo->adjListas[ origem ];  // Adiciona n� da origem para o destino.
  grafo->adjListas[ origem ] = no;        // Adiciona na lista de adjac�ncias o v�rtice de destino.

  no = criaNo( origem );                  // Cria o nodo do v�rtice origem.
  no->prox = grafo->adjListas[ destino ]; // Adiciona n� do destino para a origem.
  grafo->adjListas[ destino ] = no;       // Adiciona na lista de adjac�ncias o v�rtice de origem.
}


/************************************************ 
 * mostra    Grafo                              *
 * objetivo: imprimir o grafo                   *
 * entrada : grafo                              *
 * sa�da   : nenhuma                            *
 ************************************************/
void imprimeGrafo( struct GRAFO* grafo ){
  int i;
  for( i = 0; i < grafo->numVertices; i++ ){
    struct NODO* temp = grafo->adjListas[ i ];  // Cria um ponteiro tempor�rio para caminhar pelo grafo.
    printf( "\n Lista de adjacencias do vertice %d\n ", i );
    while( temp ){  
      printf( "%d -> ", temp->vertice );
      temp = temp->prox;
    }
    printf( "\n" );
  }
}
