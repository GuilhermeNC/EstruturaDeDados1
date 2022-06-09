#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct elemento{
  struct elemento *next;    
  struct elemento *prev;
  int dado; 
} Elemento;

typedef struct {
  Elemento *top;					 
  int size;
} Pilha;

Pilha* criaPilha(){
  Pilha* pilha;
  pilha = (Pilha*) malloc(sizeof(Pilha));
  if (pilha == NULL){
    return NULL;
  }
  else {
    pilha->top = NULL;	
    pilha->size = 0;
  }
  return pilha;
}

bool empty(Pilha* pilha){
  if(pilha->size==0){
    return true;
  }
  return false;
}

Elemento* criaElemento(int dado){
  Elemento* elemento;
  elemento = (Elemento*) malloc(sizeof(Elemento));
  if (elemento == NULL){
    return NULL;								
  }
  else {
    elemento -> next = NULL;
    elemento -> prev = NULL;
    elemento -> dado = dado;
  }
  return elemento;
}

int insert(Pilha* pilha, int dado){
  Elemento* novo = criaElemento(dado);

  if(novo==NULL){
    return-1;
  }
  
  if(empty(pilha)){
    pilha -> top = novo;
  }
  else{
    novo -> prev = pilha -> top; 
    pilha -> top -> next = novo;
    pilha -> top = novo;
  }
  
  pilha -> size++;
  return novo -> dado;
}

void percorrePilha(Pilha* pilha){
  Elemento* aux;

  if(empty(pilha)){
    printf("\nPilha vazia!\n");
    return;
  }

  aux = pilha->top;
  
  while(aux != NULL){									
    printf("%i\n", aux->dado);
    aux = aux->prev;
  }
  printf("\n");
}

int remover(Pilha* pilha){
  int save = 0;
  if(empty(pilha)){
    return-1;
  }
  else{
    Elemento* temp = pilha -> top;
    pilha -> top = pilha -> top -> prev;
    if(pilha -> top != NULL){
      pilha -> top -> next = NULL;
    }
    save = temp -> dado;
    pilha -> size--;
    free(temp);
  }
  return save;
}

void limpaPilha(Pilha* pilha){
    while(pilha -> top != NULL){
      remover(pilha);
    }
    free(pilha);
}

void resultInserir(int n){
  if(n==-1){
    printf("Não foi possível inserir\n\n");
  }
  else{
    printf("Numero %i inserido na pilha\n\n", n);
  }
}

void resultRemover(int n){
  if(n==-1){
    printf("Não é possível remover de pilha vazia\n");
  }
  else{
    printf("Excluido o valor %i da pilha\n\n", n);    
  }
}

int main(){
    int dado;
    Elemento* pivo;
    int teste;
    Pilha* pilha = criaPilha();
    if (pilha == NULL){
        printf("\nImpossivel alocar memoria para a pilha.\n");
        return -1;
    }

  
    //Inserindo elementos
    teste = insert(pilha, 5);
    resultInserir(teste);
    teste = insert(pilha, 4);
    resultInserir(teste);  
    teste = insert(pilha, 3);
    resultInserir(teste);  
    teste = insert(pilha, 2);
    resultInserir(teste);   
    teste = insert(pilha, 1);
    resultInserir(teste);   

    //Monstrando a pilha
    percorrePilha(pilha);

    //Removendo elementos 
    dado = remover(pilha);
    resultRemover(dado);

    //Monstrando a pilha
    percorrePilha(pilha);

    //Limpando a pilha e liberando memória
    limpaPilha(pilha);
    return 0;
}
