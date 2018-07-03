/*+
 * ISBN_code_generator.c
 *
 *  Created on: 01 mag 2018
 *      Author: Gabriele Fortunato
 */

#include "ISBN_code_generator.h"

static const char X = 'X';
static const int ELEVEN = 11;
static const int STD_13 = 13;
static const int STD_10 = 10;
static const int ASCII = 48;
static const int THREE = 3;
static const int TWO = 2;
static const int ZERO = 0;

static bool is_valid_isbn(char* isbn){
	bool flag = true;
	for (int i = ZERO; i < strlen(isbn) && flag;)
		flag = isdigit(isbn[i++]);
	return flag;
}

static int get_sum_thirteen(char* isbn){
	int sum = ZERO;
	for (int i = ZERO; i < strlen(isbn); i++)
		sum += ((i % TWO) == ZERO) ?
				(isbn[i] - ASCII) : THREE * (isbn[i] - ASCII);
	return sum;
}

static int get_res_thirteen(int sum){
	int rest = sum % STD_10;
	return (rest == ZERO) ? ZERO : STD_10 - rest;
}

static bool verify_thirteen(char* isbn, int res){
	for (int i = ZERO; i < strlen(isbn); i++)
		res += ((i % TWO) == ZERO) ?
				(isbn[i] - ASCII) : THREE * (isbn[i] - ASCII);
	return (res % STD_10) == ZERO;
}

static char isbn_thirteen(char* isbn){
	int sum = get_sum_thirteen(isbn);
	int res = get_res_thirteen(sum);
	char result = res + ASCII;
	assert(verify_thirteen(isbn,res));
	assert(isdigit(result));
	return result;
}

static int get_sum_ten(char* isbn){
	int sum = ZERO;
	for (int i = ZERO; i < strlen(isbn); i++)
		sum += (STD_10 - i) * (isbn[i] - ASCII);
	return sum;
}

static int get_res_ten(int sum){
	int rest = sum % ELEVEN;
	return (rest == ZERO) ? ZERO : ELEVEN - rest;
}

static bool verify_ten(char* isbn, int res){
	for (int i = ZERO; i < strlen(isbn); i++)
		res += (STD_10 - i) * (isbn[i] - ASCII);
	return (res % ELEVEN) == ZERO;
}

static char isbn_ten(char* isbn){
	int sum  = get_sum_ten(isbn);
	int res = get_res_ten(sum);
	char result = (res == STD_10) ? X : res + ASCII;
	assert(verify_ten(isbn,res));
	assert(isdigit(result) || result == X);
	return result;
}

char isbn_crtl_code_generator(char isbn_code_str[], int isbn_code_standard){
	assert(isbn_code_standard==STD_10 || isbn_code_standard==STD_13);
	assert(strlen(isbn_code_str));
	assert(is_valid_isbn(isbn_code_str));
	return (isbn_code_standard == STD_10) ?
			isbn_ten(isbn_code_str) : isbn_thirteen(isbn_code_str);
}
