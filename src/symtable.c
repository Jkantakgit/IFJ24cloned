/*
 * Project: IFJ24
 *
 * File: symtable.c
 *
 * xholanp00
 *
 */


#include <stdlib.h>
#include <string.h>

#include "symtable.h"


bTree initTree(){
    bTree tree = (bTree) malloc(sizeof(struct bTree));
    if (tree == NULL){
        return NULL;
    }
    tree->root = NULL;
    return tree;
}


int freeTree(bTree tree){
  return 0;
}


int insert(bTree tree, Node node){
  return 0;
}

Node find(bTree tree, char *key){
  return NULL;
}

int delete_node(bTree tree, char *name){
  return 0;
}

Node create_node(char *key, TokenType type, bTree *local_scope, bTree *arguments){
  return NULL;
}
