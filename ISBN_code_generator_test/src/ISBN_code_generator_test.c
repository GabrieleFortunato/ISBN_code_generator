/*
 ============================================================================
 Name        : ISBN_code_generator_test.c
 Author      : Gabriele Fortunato
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <CUnit/basic.h>
#include <stdio.h>
#include "ISBN_code_generator.h"

void test_isbn_10(){
	 CU_ASSERT_EQUAL(isbn_crtl_code_generator("885152159",10),'X');
	 CU_ASSERT_EQUAL(isbn_crtl_code_generator("817525766",10),'0');
}

void test_isbn_13(){
	 CU_ASSERT_EQUAL(isbn_crtl_code_generator("978884302534",13),'3');
	 CU_ASSERT_EQUAL(isbn_crtl_code_generator("978817525766",13),'5')
}

int init_suite_default(){
	return 0;
}

int clear_suite_default(){
	return 0;
}

int main(void) {
	CU_initialize_registry();
	CU_pSuite pSuite_A=CU_add_suite("SUITE ISBN",init_suite_default,clear_suite_default);
	CU_add_test(pSuite_A,"test ISBN con lunghezza 10",test_isbn_10);
	CU_add_test(pSuite_A,"test ISBN con lunghezza 13",test_isbn_13);
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();
	return CU_get_error();
}
