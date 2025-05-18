#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){
  int i, j, k;

  for (i = 0; i < 9; i++) {
      int fila[10] = {0};
      for (j = 0; j < 9; j++) {
        if (n->sudo[i][j] != 0) {
          if (fila[n->sudo[i][j]] == 1) return 0 ;
            }
            fila[n->sudo[i][j]] = 1 ;
        }
    }

  for (j = 0; j < 9; j++) {
    int test[10] = {0};
    for (i = 0; i < 9; i++) {
      if (n->sudo[i][j] != 0) {
        if (test[n->sudo[i][j]] == 1) return 0 ;
          }
          test[n->sudo[i][j]] = 1 ;
      }
  }

  for (int block_row = 0 ; block_row < 3; block_row++) {
    for (int block_col = 0 ; block_col < 3 ; block_col++) {
      int seen[10] = {0} ;
      for (int i = 0 ; i < 3 ; i++) {
        for (int j = 0 ; j < 3 ; j++) {
          int num = n->sudo[3*block_row + i][3*block_col + j] ;
          if (num != 0 && seen[num]++) return 0 ;
        }
      }
    }
  }
    return 1;
}


List* get_adj_nodes(Node* n){
  List* list=createList() ;

  for (int i = 0 ; i < 9 ; i++) {
    for (int j = 0 ; j < 9 ; j++) {
      if (n->sudo[i][j] == 0) {
        for (int num = 0 ; num < 9 ; num++) {
          Node * new = copy(n) ;
          new->sudo[i][j] = num ;

          addtolist(list, new) ;
        }
      }
    }
  }

  return list;
}


int is_final(Node* n){
  for (int i = 0; i < 9; i++)
    for (int j = 0; j < 9; j++)
      if (n->sudo[i][j] == 0)
        return 0 ;
  return 1 ;
}

Node* DFS(Node* initial, int* cont) {
  Stack* stack = createStack() ;
  push(stack, initial) ; 

  while (!is_empty(stack)) {
    Node* current = top(stack) ;
    pop(stack) ;
    (*cont)++ ;

    if (is_final(current)) {
        return current ;   
    }

    List* adj = get_adj_nodes(current);
    Node* adjNode = first(adj) ;
    while (adjNode) {
        push(stack, adjNode) ;
        adjNode = next(adj) ;
    }

    free(current) ;  
    free(adj) ;  
  }

  return NULL;
}

int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}