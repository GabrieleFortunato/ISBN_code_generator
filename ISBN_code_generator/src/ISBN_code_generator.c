/*+
 * ISBN_code_generator.c
 *
 *  Created on: 01 mag 2018
 *      Author: Gabriele Fortunato
 */

#include "ISBN_code_generator.h"

static const int THREE = 3;
static const int TWO = 2;
static const char X = 'X';
static const int ELEVEN = 11;
static const int ASCII = 48;
static const int ZERO = 0;
static const int TEN = 10;
static const int STD_10 = 10;
static const int STD_13 = 13;

static bool is_valid_isbn(char* isbn){
	bool flag = true;
	for (int i = ZERO; i < strlen(isbn) && flag; i++)
		flag = isdigit(isbn[i]);
	return flag;
}

static int get_sum_10(char* isbn){
	int sum = ZERO;
	for (int i = ZERO; i < strlen(isbn); i++)
		sum += (TEN - i) * (isbn[i] - ASCII);
	return sum;
}

static int get_res_10(int sum){
	int rest = sum % ELEVEN;
	return (rest == ZERO) ? ZERO : ELEVEN - rest;
}

static bool verify_10(char* isbn, int a){
	for (int i = ZERO; i < strlen(isbn); i++)
		a += (TEN - i) * (isbn[i] - ASCII);
	return (a % ELEVEN) == ZERO;
}

static char isbn_10(char* isbn){
	int sum = get_sum_10(isbn);
	int res = get_res_10(sum);
	assert(verify_10(isbn,res));
	return (res == TEN) ? X : res + ASCII;
}

static int get_sum_13(char* isbn){
	int sum = ZERO;
	for (int i = ZERO; i < strlen(isbn); i++)
		sum += (i % TWO == ZERO) ?
				(isbn[i] - ASCII) : THREE * (isbn[i] - ASCII);
	return sum;
}

static int get_res_13(int sum){
	int rest = sum % TEN;
	return TEN - rest;
}

static bool verify_13(char* isbn, int a){
	for (int i = ZERO; i < strlen(isbn); i++)
		a += (i % TWO == ZERO) ?
				(isbn[i] - ASCII) : THREE * (isbn[i] - ASCII);
	return (a % TEN) == ZERO;
}

static char isbn_13(char* isbn){
	int sum = get_sum_13(isbn);
	int res = get_res_13(sum);
	assert(verify_13(isbn,res));
	return res+ASCII;
}

char isbn_crtl_code_generator(char isbn_code_str[], int isbn_code_standard){
	assert(isbn_code_standard==STD_10||isbn_code_standard==STD_13);
	assert(is_valid_isbn(isbn_code_str));
	return (isbn_code_standard==STD_10) ? isbn_10(isbn_code_str) : isbn_13(isbn_code_str);
}

