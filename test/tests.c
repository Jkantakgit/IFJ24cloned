/*
 * Project: IFJ24
 *
 * File: tests.c
 *
 * xholanp00
 *
 */

#include <CUnit/CUError.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <CUnit/TestDB.h>
#include <stdlib.h>
#include <time.h>
#include "../src/symtable.h"

//SYMTABLE


/**
 * @brief Test case for testing symtable creation
 *
 */
void test_symtable_creation(void){
  bTree st = initTree();
  CU_ASSERT_PTR_NOT_NULL_FATAL(st);
  CU_ASSERT_EQUAL(st->root, NULL);
  freeTree(st);
}

/**
 * @brief Test case for testing symtable deletion
 *
 */
void test_symtable_destroy(void){
  bTree st = initTree();
  CU_ASSERT_PTR_NOT_NULL_FATAL(st);
  int success = freeTree(st);
  CU_ASSERT_PTR_NULL_FATAL(st);
  CU_ASSERT_EQUAL_FATAL(success,1);
}

/**
 * @brief Test case for creating symtable node
 *
 */
void test_symtable_create_node(void){
  Node node_var = create_node("Node", VAR, NULL, NULL);
  CU_ASSERT_NOT_EQUAL_FATAL(node_var, NULL);
  CU_ASSERT_STRING_EQUAL(node_var->key, "Node");
  CU_ASSERT_EQUAL(node_var->type, VAR);
  CU_ASSERT_EQUAL(node_var->local_scope, NULL);
  CU_ASSERT_EQUAL(node_var->arguments, NULL);

  free(node_var);


  bTree local_scope = initTree();
  CU_ASSERT_PTR_NOT_NULL_FATAL(local_scope);
  bTree arguments = initTree();
  CU_ASSERT_PTR_NOT_NULL_FATAL(arguments);

  Node node_func = create_node("Func node", FUNC, &local_scope, &arguments);
  CU_ASSERT_NOT_EQUAL_FATAL(node_func, NULL);
  CU_ASSERT_STRING_EQUAL(node_func->key, "Func node");
  CU_ASSERT_EQUAL(node_func->type, FUNC);
  CU_ASSERT_PTR_NOT_EQUAL(node_func->local_scope, NULL);
  CU_ASSERT_PTR_NOT_EQUAL(node_func->arguments, NULL);

  freeTree(node_func->local_scope);
  freeTree(node_func->arguments);
  free(node_func);
}


/**
 * @brief Test case for adding node to symtable
 *
 */
void test_symtable_add_node(void){
  bTree tree = initTree();

  Node node = create_node("Node", VAR, NULL, NULL);

  int success = insert(tree,node);
  CU_ASSERT_EQUAL(success, 1);

  success = freeTree(tree);
}

/**
 * @brief Test case for testing searching in symtable
 *
 */
void test_symtable_find_node(void){
  bTree tree = initTree();

  for (int i = 0; i < 100; i++){
    char key[4];
    snprintf(key, sizeof(key), "%d", i);
    Node node = create_node(key, VAR, NULL, NULL);
    insert(tree, node);
  }
  Node node1 = find(tree, "1");
  CU_ASSERT_PTR_NOT_NULL_FATAL(node1);
  CU_ASSERT_STRING_EQUAL(node1->key, "1");
  CU_ASSERT_EQUAL(node1->type, VAR);
  CU_ASSERT_EQUAL(node1->local_scope, NULL);
  CU_ASSERT_EQUAL(node1->arguments, NULL);

  Node node65 = find(tree, "65");
  CU_ASSERT_PTR_NOT_NULL_FATAL(node65);
  CU_ASSERT_STRING_EQUAL(node65->key, "65");
  CU_ASSERT_EQUAL(node65->type, VAR);
  CU_ASSERT_EQUAL(node65->local_scope, NULL);
  CU_ASSERT_EQUAL(node65->arguments, NULL);

  int success = freeTree(tree);

}


/**
 * @brief Test case for testing symtable deletion of node
 *
 */
void test_symtable_delete_node(void){
  bTree tree = initTree();

  for (int i = 0; i < 100; i++){
    char key[4];
    snprintf(key, sizeof(key), "%d", i);
    Node node = create_node(key, VAR, NULL, NULL);
    insert(tree, node);
  }
  int success = delete_node(tree, "16");
  CU_ASSERT_EQUAL_FATAL(success, 1);

  Node node16 = find(tree, "16");
  CU_ASSERT_EQUAL(node16, NULL);

  Node node65 = find(tree, "65");
  CU_ASSERT_EQUAL(node65, NULL);
}






//SCANNER


/**
 * @brief Test case for lexical scanner, testing functionality
 *
 */
void test_scanner(void){

}


//SYNTAX CHECK


/**
 * @brief Test case for syntaxing check
 *
 */
void test_syntax_check(void){

}

//SEMANTIC CHECK


/**
 * @brief Test case for semantic check
 *
 */
void test_semantic_check(void){

}


//CODE GENERATOR


/**
 * @brief Test case for code generator, tripple address instructions
 *
 */
void test_code_generator(void){

}

//OPTIMALIZATION


/**
 * @brief Test case for code optimalization segment of compiler
 *
 */
void test_code_optimalization(void){

}

/**
 * @brief Initializes resources before test suite
 *
 * @return int if initialization was successful
 */
int init_suite(void) { return 0; }

/**
 * @brief Cleans up any resources after all tests in suite are finished
 *
 * @return int if cleanup was successful
 */
int clean_suite(void) { return 0; }



/**
 * @brief Main class for tests
 *
 * @return int exit status
 */
int main() {
  /**Initializes tests registry */
  if (CUE_SUCCESS != CU_initialize_registry()){
    return CU_get_error();
  }

  /**adding suite for symtable */
  CU_pSuite symtableSuite = CU_add_suite("Symtable suite", init_suite, clean_suite);
  if (NULL == symtableSuite){
    CU_cleanup_registry();
    return CU_get_error();
  }

  /**adding test symtable creation */
  if (CU_add_test(symtableSuite, "Symtable creation", test_symtable_creation) == NULL){
    CU_cleanup_registry();
    return CU_get_error();
  }

  /**adding test symtable deletion */
  if (CU_add_test(symtableSuite, "Symtable deletion", test_symtable_destroy) == NULL){
    CU_cleanup_registry();
    return CU_get_error();
  }

  /**adding test symtable node creation */
  if (CU_add_test(symtableSuite, "Symtable node creation", test_symtable_create_node) == NULL){
    CU_cleanup_registry();
    return CU_get_error();
  }

  /**adding test symtable node insetion to tree */
  if (CU_add_test(symtableSuite, "Symtable node insertion to tree", test_symtable_add_node) == NULL){
    CU_cleanup_registry();
    return CU_get_error();
  }

  /**adding test symtable node lookup */
  if (CU_add_test(symtableSuite, "Symtable node lookup", test_symtable_find_node) == NULL){
    CU_cleanup_registry();
    return CU_get_error();
  }

  /**adding test symtable node deletion from tree */
  if (CU_add_test(symtableSuite, "Symtable node deletion from tree", test_symtable_delete_node) == NULL){
    CU_cleanup_registry();
    return CU_get_error();
  }










  /**running the tests */
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();

  /** cleans registry */
  CU_cleanup_registry();

  /** return reason for failiure */
  return CU_get_error();

}
