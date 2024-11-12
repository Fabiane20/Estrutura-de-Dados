/***********************************************/ 
/* Lista Encadeada                             */
/* objetivo: Percurso DFS de um grafo          */
/* programador: Daniela Bagatini               */
/* referência www.programiz.com/dsa/graph-dfs  */
/* criado em: 01/11/2021                       */
/* data da ultima alteracao: 01/11/2022        */
/***********************************************/ 

#include <stdio.h>   // entrada e saída padrão: printf, scanf
#include <stdlib.h>  // exit, malloc, system


/***********************************************/ 
/* Definição do Registro e da Estrutura        */
/***********************************************/ 
struct NODO{
  int vertice;
  struct NODO *prox;
} NODO;

struct GRAFO{
  int numVertices;
  int *visitado;
  struct NODO **adjListas; // Para um array bidimensional dinâmico usamos **. Da mesma forma, usamos struct nodo** para armazenar um array para uma lista encadeada.
} GRAFO;

/* Observações sobre struct NODO **adjListas: adicionar um asterisco a mais significa
 que adjListas em si é um ponteiro para um array de ponteiros para a estrutura NODO. 
 Isso é comum quando você precisa alocar dinamicamente a memória para a lista de 
 adjacência. O ponteiro adjListas apontará para o primeiro elemento do array, que é 
 um array de ponteiros para a estrutura NODO. */ 

/***********************************************/ 
/* Definição das Funções                       */
/***********************************************/ 
void dfs( struct GRAFO* grafo, int vertice );                    // Algoritmo DFS de busca em profundidade.
struct NODO* criaNo( int valor );                                // Cria um novo nodo.
struct GRAFO* criaGrafo( int vertices );                         // Cria o grafo.
void adicionaNoGrafo( struct GRAFO* grafo, int origem, int destino );  // Adiciona relações no grafo (adjacências).
void imprimeGrafo( struct GRAFO* grafo );                        // Mostra o grafo.


/***********************************************/ 
/* Programa Principal                          */
/***********************************************/
int main(){
  int numeroVertices = 4;  // Número de vértices do grafo
  printf( " Informe o numero de vertices do grafo: %d\n", numeroVertices);
  //fflush(stdin);
  //scanf( "%d", &numeroVertices );
  
  struct GRAFO* grafo = criaGrafo( numeroVertices );  // Cria o grafo
  adicionaNoGrafo( grafo, 0, 1 );
  adicionaNoGrafo( grafo, 0, 2 );
  adicionaNoGrafo( grafo, 1, 2 );
  adicionaNoGrafo( grafo, 2, 3 );
  imprimeGrafo( grafo );

  if( grafo != NULL )      // Verifica se grafo não está vazio
  	  dfs( grafo, 2 );     // Percurso em profundidade no grafo a partir do vértice indicado como argumento

  return 0;
}


/************************************************ 
 * dfs                                          *
 * objetivo: algoritmo percurso em profundidade *
 * entrada : grafo, vertice de referência       *
 * saida   : percurso visitado                  *
 ************************************************/
void dfs( struct GRAFO* grafo, int vertice ){           // Vértice inicial
  struct NODO* temp = grafo->adjListas[ vertice ];      // Ponteiro temporário para caminhar pela lista de adjacência do vértice

  grafo->visitado[ vertice ] = 1;                       // Marca como vértice visitado. Isso é feito para evitar visitar o mesmo vértice várias vezes durante a busca em profundidade.   
  printf( "Visitado %d \n", vertice );                        
  
   while( temp != NULL ){                               // Percorre a lista de adjacência do vértice. Critério de parada da recursão.  
	    if( grafo->visitado[ temp->vertice ] == 0 )     // Verifica se o vértice adjacente ainda não foi visitado.
	      	dfs( grafo, temp->vertice );                // Repete o processo até que o vértice procurado seja encontrado ou não haja mais vértices adjacentes
	    temp = temp->prox;                              // Passa para próximo vértice adjacente na lista de adjacência.
   }      
}


/*
  while( temp != NULL ){                                // Critério de parada  
    int verticeConectado = temp->vertice;               // Vértice visitado torna-se o vértice inicial
    if( grafo->visitado[ verticeConectado ] == 0 )
      dfs( grafo, verticeConectado );                   // Repete o processo até que o vértice procurado seja encontrado ou não haja mais vértices adjacentes
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
 * entrada : número de vertices                 *
 * saida   : grafo criado                       *
 ************************************************/
struct GRAFO* criaGrafo( int vertices ) {
  struct GRAFO* grafo = ( struct GRAFO* ) malloc( sizeof( struct GRAFO ) );  // Aloca memória para o grafo.
  if( grafo == NULL )
  	  printf( "\n Não foi possível alocar memória!" );
  else{
	  grafo->numVertices = vertices;                                             // Inicializa o campo de número de vértices do grafo.
	  grafo->visitado = ( int* ) malloc( vertices * sizeof( int ) );             // Cria a lista de visitados conforme o número de vértices.	  
	  grafo->adjListas = ( struct NODO** ) malloc( vertices * sizeof( struct NODO* ) );  // Cria a lista de adjacências conforme o número de vértices.
	
	  int i;
	  for( i = 0; i < vertices; i++ ) {                                          // Inicializa todos os vértices com NULL.
	    grafo->adjListas[ i ] = NULL; 
	    grafo->visitado[ i ] = 0;
	  }
 }
 return grafo;
}


/************************************************ 
 * adicionaNoGrafo                              *
 * objetivo: adiciona na lista de adjacências   *
 * entrada : grafo, origem e destino            *
 * saída   : grafo (por referência)             *
 ************************************************/
void adicionaNoGrafo( struct GRAFO* grafo, int origem, int destino ){
  
  struct NODO* no = criaNo( destino );    // Cria o nodo do vértice destino.
  no->prox = grafo->adjListas[ origem ];  // Adiciona nó da origem para o destino.
  grafo->adjListas[ origem ] = no;        // Adiciona na lista de adjacências o vértice de destino.

  no = criaNo( origem );                  // Cria o nodo do vértice origem.
  no->prox = grafo->adjListas[ destino ]; // Adiciona nó do destino para a origem.
  grafo->adjListas[ destino ] = no;       // Adiciona na lista de adjacências o vértice de origem.
}


/************************************************ 
 * mostra    Grafo                              *
 * objetivo: imprimir o grafo                   *
 * entrada : grafo                              *
 * saída   : nenhuma                            *
 ************************************************/
void imprimeGrafo( struct GRAFO* grafo ){
  int i;
  for( i = 0; i < grafo->numVertices; i++ ){
    struct NODO* temp = grafo->adjListas[ i ];  // Cria um ponteiro temporário para caminhar pelo grafo.
    printf( "\n Lista de adjacencias do vertice %d\n ", i );
    while( temp ){  
      printf( "%d -> ", temp->vertice );
      temp = temp->prox;
    }
    printf( "\n" );
  }
}
