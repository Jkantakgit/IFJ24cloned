/*
 * Project: IFJ24
 *
 * File: symtable.h
 *
 * xholanp00
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef enum{
  VAR,
  FUNC
} TokenType;

typedef struct {
    char *name;
    TokenType type;
} Argument;


typedef struct Node{
  char *key;
  TokenType type;

  struct bTree *local_scope;
  struct bTree *arguments;

  struct node *left_child;
  struct node *right_child;
}*Node;


typedef struct bTree{
  Node root;
}*bTree;

bTree initTree();

int freeTree(bTree tree);

int insert(bTree tree, Node node);

Node find(bTree tree, char *key);

int delete_node(bTree tree, char *name);

Node create_node(char *key, TokenType type, bTree *local_scope, bTree *arguments);
