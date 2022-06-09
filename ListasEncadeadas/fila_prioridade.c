#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct elemento{
  struct elemento *next;    
  struct elemento *prev;
  int dado; 
} Elemento;

typedef struct {
  Elemento *front;
  Elemento *rear;						 
  int size;
} Fila;

Fila* criaFila(){
  Fila* fila;
  fila = (Fila*) malloc(sizeof(Fila));
  if (fila == NULL)
    return NULL;
  else {
    fila->front = NULL;						
    fila->rear = NULL;
    fila->size = 0;
  }
  return fila;
}

Elemento* criaElemento(int dado){
  Elemento* pivoento;
  pivoento = (Elemento*) malloc(sizeof(Elemento));
  if (pivoento == NULL)
    return NULL;								
  else {
    pivoento -> next = NULL;
    pivoento -> prev = NULL;
    pivoento -> dado = dado;
  }
  return pivoento;
}

bool empty(Fila* fila){
  if(fila->size==0){
    return true;
  }
  return false;
}

int insert(Fila* fila, int dado){
  Elemento* novo = criaElemento(dado);
  
  if(empty(fila)){
    fila -> front = novo;
    fila -> rear = novo;
  }
  else{
    novo -> prev = fila -> rear;  
    fila -> rear -> next = novo;
    fila -> rear = novo;    //adiciona depois do rear
  }
  
  fila -> size++;
  return novo -> dado;
}

void percorreFila(Fila* fila, int d){
  Elemento* aux;

  if(empty(fila)){
    printf("\nFila vazia!\n");
    return;
  }

  if(d == 1){
    aux = fila->front;
    
    while(aux != NULL){									
      printf("%i, ", aux -> dado);
      aux = aux -> next;
    }
  }	
  else if (d == -1){
    aux = fila->rear;
    
    while(aux != NULL){									
      printf("%i, ", aux -> dado);
      aux = aux -> prev;
    }
  }
	printf("\n");
}

int remover(Fila* fila, int d){

  if(empty(fila)){
		return -1;
	}	

  int dado;
	Elemento * pivo = fila -> front;
	int aux = pivo -> dado;
	Elemento * backup = pivo;
	
	if(d == -1){
		for(int i = 0; i < fila -> size ; i++) {
			if(pivo -> dado < aux){
				aux = pivo -> dado;
				backup = pivo;								//procura o elemento com menor valor
			}
			pivo = pivo -> next;
		}
	}if(d == 1){
		for(int i = 0; i < fila -> size ; i++) {
			if(pivo -> dado > aux){
				aux = pivo -> dado;
				backup = pivo;							 //procura o elemento com maior valor
			}
			pivo = pivo -> next;
		}
	}
	
	pivo = backup;

	if(pivo == fila -> front){      //Caso seja o primeiro elemento 
		fila -> front = pivo -> next;
    
		if(fila -> front == NULL){      //acabou a lista
			fila -> rear = NULL;
		}
		else {												        
			fila -> front -> prev = NULL;
		}
    
	} else {                     
		pivo -> prev -> next = pivo -> next;  //linkando o que vem antes do pivo com o que vem depois
		
		if(pivo -> next == NULL){    // Removeu a ultima casa
			fila -> rear = pivo -> prev;
		}                        
		else{
			pivo -> next -> prev = pivo -> prev;  //linkando o que vem depois do pivo com o que vem antes *
		}
	}

  dado = pivo -> dado;
	free (pivo);
	fila -> size --;

	return dado;
  
}

Elemento* pesquisaNaFila(Fila* fila, int dado){
  Elemento* aux;
  aux = fila -> front;
  
  while(aux != NULL){
    if (aux -> dado == dado){
        return aux;
    }
    aux = aux -> next;
  }
  return NULL;
}

void limpaFila(Fila* fila){
    while(fila -> front != NULL){
      remover(fila, 1);
    }
    free(fila);
}

int main(){
    int dado;
    Fila* fila = criaFila();
    if (fila == NULL){
        printf("\nImpossivel alocar memoria para a fila.\n");
        return -1;
    }

  
    dado = insert(fila, 55);
		printf("\nNumero %i inserido na fila\n", dado);
    dado = insert(fila, 473);
		printf("\nNumero %i inserido na fila\n", dado);
    dado = insert(fila, 7);
		printf("\nNumero %i inserido na fila\n", dado);

    //Monstrando a fila do começo(cabeça) -> fim(cauda)
    percorreFila(fila,1);
    //Monstrando a fila do fim(cauda) -> começo(cabeça)
		percorreFila(fila,-1);

  
    dado = remover(fila, 1);
    printf("\nExcluido o valor %i da fila\n", dado);

    //Monstrando a fila do fim(cauda) -> começo(cabeça)
		percorreFila(fila,1);
  
		dado = remover(fila, -1);
    printf("\nExcluido o valor %i da fila\n", dado);
  
    //Monstrando a fila do começo(cabeça) -> fim(cauda)
		percorreFila(fila,1);

    //Limpando a fila e liberando memória
    limpaFila(fila);
    return 0;
}
