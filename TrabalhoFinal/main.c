#include <stdio.h>
#include <stdlib.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 53

typedef struct elemento{
	struct elemento *next;     
	struct elemento *prev;
	char *name; 
} Elemento;

typedef struct {
	Elemento *head;
	Elemento *tail;						
	int size;
} Lista;

Lista* criaLista(){
	Lista* lista;
	lista = (Lista*) malloc(sizeof(Lista));
	if (lista == NULL)
		return NULL;
	else {
		lista->head = NULL;						//Alocar lista
		lista->tail = NULL;
		lista->size = 0;
	}
	
	return lista;
}

Elemento* criaElemento(char* name){
	Elemento* elemento;
	elemento = (Elemento*) malloc(sizeof(Elemento));
	if (elemento == NULL)
		return NULL;								//Aloca elemento
	else {
		elemento -> next = NULL;
		elemento -> prev = NULL;
		elemento -> name = name;
	}
	
	return elemento;
}

char* inserir(Lista* lista, char* name){
	Elemento* novo = criaElemento(name);

	if (novo == NULL){
		return "-1";
	}
	
	if( lista -> size == 0 ){
		lista -> head = novo;
		lista -> tail = novo;
	} else {
		novo -> prev = lista -> tail;
    lista -> tail -> next = novo;
    lista -> tail = novo;
	}

	lista -> size++;
	return novo -> name;
}

int percorreLista(Lista* lista, int decisao){
	Elemento* aux;

	if(lista -> size == 0){
		return -1;
	}

	if(decisao == 1){
		aux = lista->head;
		
		while(aux != NULL){									
			printf("\n%s", aux->name);
			aux = aux->next;
		}
	}	else if (decisao == -1){
		aux = lista->tail;
		
		while(aux != NULL){									
			printf("%s, ", aux->name);
			aux = aux->prev;
		}
	}
	printf("\n");
	return 0;
}

char* remover(Lista* lista, Elemento* elem){
	if(elem != NULL && lista -> size != 0){
		if(elem == lista ->head){
			lista -> head = elem -> next;
			if(lista -> head == NULL){
				lista -> tail = NULL;
			}
			else {
				elem -> next -> prev = NULL;
			}
		}
		else{
			elem -> prev -> next = elem -> next;
			if(elem -> next == NULL){
				lista -> tail = elem-> prev;
			}
			else{
				elem -> next -> prev = elem -> prev;
			}
		}
	} else {
		return "-1";
	}

  char* backup = elem->name;
	free (elem);
	lista -> size --;

	return backup;
}

Elemento* pesquisaNaLista(Lista* lista, char* name){
	Elemento* aux;
	aux = lista -> head;
	
	while(aux != NULL){
		if (strcmp(aux -> name, name) == 0){
			return aux;
		}
		aux = aux -> next;
	}
	return NULL;
}

void limpaLista(Lista* lista){
	while(lista -> head != NULL){
		remover(lista, lista->head);
	}
	
	free(lista);
}

void resultInserir(char* n){
  if(strcmp(n, "-1") == 0){
    printf("\nNão recebemos names\n");
  }
  else if(strcmp(n, "-2") == 0){    
    printf("\nSó aceita pivo nulo na inserção do primeiro elemento\n");
  }
  else{
    printf("\nNome %s inserido na lista\n", n);
  }
}

void resultRemover(char* n){
  if(strcmp(n, "-1") == 0){
    printf("\nSó é possível remover quando a lista não é vazio e o pivo também não for nulo\n");
  }
  else{
    printf("\nExcluido o nome %s da lista\n", n);    
  }
}

void criarMatriz(Lista** lista){
  for(int i=0; i<TAM; i++){
    lista[i]=criaLista();
  }
}

int funcaoHash(char* name){
  int tamName = strlen(name);
  unsigned int hash = 0;

  for(int i=0; i<tamName; i++){
    hash+=name[i] * (i+1);
  }
  return hash % TAM;
}

int main(void) {
  Lista* VetorListas[TAM];
  criarMatriz(VetorListas);

  //---------testando---------------------
  char* teste;
  teste = inserir(VetorListas[0], "TESTE");
  resultInserir(teste);

  percorreLista(VetorListas[0], 1);
  
  Elemento* pivo;  
  pivo = pesquisaNaLista(VetorListas[0], "TESTE");
  teste = remover(VetorListas[0], pivo);
  resultRemover(teste);
  
  percorreLista(VetorListas[0], 1);
  //--------------------------------------------------
  
	FILE *file; //declarando o ponteiro com os nomes
	file = fopen("nomes.txt","r"); //recebendo os nomes no ponteiro
	if(file == NULL){ //verificando se o txt era vazio
		printf("Não foi possível ler o arquivo\n");
		return 0;
	}

	char nome[100];
  int cont=0;
  while(fgets(nome,100,file) != NULL){
    int indice = funcaoHash(nome);
    teste = inserir(VetorListas[39], nome);
    resultInserir(teste);
    //percorreLista(VetorListas[indice], 1);
    if(cont==-1){
      teste = inserir(VetorListas[39], "WALDICLEI");
      resultInserir(teste);
      percorreLista(VetorListas[39], 1);
      printf("%d", 39);
    }
    printf("%d", indice);
    if(cont>4){
      break;
    }
    cont++;
  }
  percorreLista(VetorListas[39], 1);
}
