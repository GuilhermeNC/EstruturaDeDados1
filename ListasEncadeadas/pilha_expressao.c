#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct elemento{
  struct elemento *next;    
  struct elemento *prev;
  char dado; 
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

Elemento* criaElemento(char dado){
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

char insert(Pilha* pilha, char dado){
  Elemento* novo = criaElemento(dado);

  if(novo==NULL){
    return 'a';
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

char remover(Pilha* pilha){
  char save;
  if(empty(pilha)){
    return 'a';
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

bool verificaEXP(char abertura, char fechamento){
  if(abertura == '{' && fechamento == '}'){
    return true;
  }
  else if(abertura == '[' && fechamento == ']'){
    return true;
  }
  else if(abertura == '(' && fechamento == ')'){
    return true;
  }
  return false;
}

int receba(char *exp){
  
  Pilha* pilha = criaPilha();
  
  for(int i=0; i<strlen(exp); i++){  //recebe e percorre a expressao
    if(exp[i] == '[' || exp[i] == '{' || exp[i] == '('){
      insert(pilha, exp[i]);          //cada abertura insere na pilha
    }
    else if(exp[i] == ']' || exp[i] == '}' || exp[i] == ')'){  //cada fechamento remove da pilha
      
      if(empty(pilha)){                //tentar remover de pilha vazia = fechamentos demais
        limpaPilha(pilha);
        return-1;
      }
      
      if(verificaEXP(pilha -> top -> dado, exp[i])){  //verifica se fechamento bate com a abertura(topo)
        remover(pilha);
      }
      else{
        limpaPilha(pilha);          //erro de digitacao
        return-1;
      }
    }
  }
  if(!empty(pilha)){              //mais aberturas do que fechamentos
    limpaPilha(pilha);
    return-1;
  }
  limpaPilha(pilha);
  return 0;
}

void resultRECEBA(int r){
  if(r == -1){
    printf("\nExpressão incorretamente digitada\n\n");
  }
  else if(r == 0){
    printf("\nExpressão corretamente digitada\n\n");
  }
}

int main(){
  
  while(true){
    
    int menu=0;
    printf(" 1 - Digitar expressão \n 2- Sair \n\n");
    scanf("%i", &menu);
    
    if(menu == 1){
      char exp[100];
      printf("\nInsira a expressão abaixo: \n\n");
      scanf("%s", exp);
      int res = receba(exp);
      resultRECEBA(res);
    }
    else if(menu == 2) {
      break;
    }
  }
  return 0;
}
