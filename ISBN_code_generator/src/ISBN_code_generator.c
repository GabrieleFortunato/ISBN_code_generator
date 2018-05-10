/*+
 * ISBN_code_generator.c
 *
 *  Created on: 01 mag 2018
 *      Author: Gabriele Fortunato
 */

#include "ISBN_code_generator.h"

static bool is_ok_length(char isbn_code_str[], int isbn_code_standard){
	return strlen(isbn_code_str)==isbn_code_standard-ONE;
}

static bool is_ok_standard(int standard){
	return standard==LENGTH_10||standard==LENGTH_13;
}

static bool is_ok_isbn_code_str(char* isbn_code_str){
	bool flag = true;
	for (int i=ZERO;i<strlen(isbn_code_str)&&flag;i++)
		flag = isdigit(isbn_code_str[i]);
	return flag;
}

static bool verify_TEN(char* isbn,int result){
	for (int i=ZERO;i<strlen(isbn);i++)
		result += (LENGTH_10-i)*(isbn[i]-FOURTYEIGHT);
	return (result%ELEVEN == ZERO);
}

static bool verify_THIRTEEN(char* isbn,int result){
	for (int i=ZERO;i<strlen(isbn);i++)
		(i%TWO==ZERO)?(result+=(isbn[i]-FOURTYEIGHT)):(result+=THREE*(isbn[i]-FOURTYEIGHT));
	return (result%TEN == ZERO);
}

static bool is_valid_result_TEN(char result){
	return isdigit(result)||result==X;
}

static int get_result_TEN(int sum){
	int rest = sum%ELEVEN;
	return ELEVEN-rest;
}

static int get_result_THIRTEEN(int sum){
	int rest = sum%TEN;
	return TEN-rest;
}

static int get_sum_TEN(char* isbn){
	int sum=ZERO;
	for (int i=ZERO;i<strlen(isbn);i++)
		sum += (LENGTH_10-i)*(isbn[i]-FOURTYEIGHT);
	return sum;
}

static int get_sum_THIRTEEN(char* isbn){
	int sum=ZERO;
	for (int i=ZERO;i<strlen(isbn);i++)
		(i%TWO==ZERO)?(sum+=(isbn[i]-FOURTYEIGHT)):(sum+=THREE*(isbn[i]-FOURTYEIGHT));
	return sum;
}

static char isbn_TEN(char* isbn){
	int sum=get_sum_TEN(isbn);
	int res = get_result_TEN(sum);
	char result = (res==LENGTH_10)?X:res+FOURTYEIGHT;
	assert(verify_TEN(isbn,res)&&is_valid_result_TEN(result));
	return result;
}

static char isbn_THIRTEEN(char* isbn){
	int sum=get_sum_THIRTEEN(isbn);
	int res = get_result_THIRTEEN(sum);
	char result = res+FOURTYEIGHT;
	assert(verify_THIRTEEN(isbn,res)&&isdigit(result));
	return result;
}

char isbn_crtl_code_generator(char isbn_code_str[], int isbn_code_standard){
	assert(is_ok_standard(isbn_code_standard));
	assert(is_ok_length(isbn_code_str,isbn_code_standard));
	assert(is_ok_isbn_code_str(isbn_code_str));
	return strlen(isbn_code_str)==(LENGTH_10-ONE)?isbn_TEN(isbn_code_str):isbn_THIRTEEN(isbn_code_str);
}
