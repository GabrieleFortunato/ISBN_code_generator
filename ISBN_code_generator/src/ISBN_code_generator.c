/*+
 * ISBN_code_generator.c
 *
 *  Created on: 01 mag 2018
 *      Author: Gabriele Fortunato
 */

#include "ISBN_code_generator.h"

static bool isvalid(char* isbn){
	bool flag = true;
	for (int i=ZERO;i<strlen(isbn);i++)
		flag = isdigit(isbn[i]);
	return flag;
}

static bool verify_isbn_thirteen(char* isbn, int sum){
	int result = (TEN-sum%TEN);
	for (int i=ZERO;i<strlen(isbn);i++)
		result += (i%TWO==ZERO)?(isbn[i]-ASCII):THREE*(isbn[i]-ASCII);
	return result%TEN==ZERO;
}

static int get_rest_thirteen(int sum){
	int rest = sum%TEN;
	rest = (rest==ZERO)?ZERO:TEN-rest;
	return rest;
}

static int get_sum_thirteen(char* isbn){
	int sum = ZERO;
	for (int i=ZERO;i<strlen(isbn);i++)
		sum += (i%TWO==ZERO)?(isbn[i]-ASCII):THREE*(isbn[i]-ASCII);
	return sum;
}

static char isbn_thirteen(char* isbn){
	int sum =  get_sum_thirteen(isbn);
	int rest = get_rest_thirteen(sum);
	char result = rest+ASCII;
	assert(isdigit(result));
	assert(verify_isbn_thirteen(isbn,sum));
	return result;
}

static int get_sum_ten(char* isbn){
	int sum = ZERO;
	for (int i=ZERO;i<strlen(isbn);i++)
		sum += (LENGTH_TEN-i)*(isbn[i]-ASCII);
	return sum;
}

static int get_rest_ten(int sum){
	int rest = sum%ELEVEN;
	rest = (rest==ZERO)?ZERO:ELEVEN-rest;
	return rest;
}

static bool verify_isbn_ten(char* isbn, int sum){
	int result = ELEVEN-sum%ELEVEN;
	for (int i=ZERO;i<strlen(isbn);i++)
		result += (LENGTH_TEN-i)*(isbn[i]-ASCII);
	return result%ELEVEN==ZERO;
}

static char isbn_ten(char* isbn){
	int sum = get_sum_ten(isbn);
	int rest = get_rest_ten(sum);
	char result = rest==TEN?X:rest+ASCII;
	assert(isdigit(result)||result==X);
	assert(verify_isbn_ten(isbn,sum));
	return result;
}

char isbn_crtl_code_generator(char isbn_code_str[], int isbn_code_standard){
	assert(isbn_code_standard==LENGTH_TEN||isbn_code_standard==LENGTH_THIRTEEN);
	assert(strlen(isbn_code_str)==isbn_code_standard-ONE);
	assert(isvalid(isbn_code_str));
	return (isbn_code_standard==LENGTH_TEN)?isbn_ten(isbn_code_str):isbn_thirteen(isbn_code_str);
}
