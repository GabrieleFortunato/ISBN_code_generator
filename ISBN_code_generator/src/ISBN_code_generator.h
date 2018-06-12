/*
 * ISBN_code_generator.h
 *
 *  Created on: 01 mag 2018
 *      Author: Gabriele Fortunato
 */

#ifndef ISBN_CODE_GENERATOR_H_
#define ISBN_CODE_GENERATOR_H_

#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

/**
 * Calcola il carattere di controllo di un ISBN
 * @pre isbn_code_standard assume valore 10 o 13
 * @pre isbn_code_str ha lunghezza pari a isbn_code_standard-1
 * @pre isbn_code_str contiene solo caratteri decimali
 * @post il carattere restituito e' un cifra o una X
 * @post il codice completo ISBN supera la verifica
 * @param isbn_code_str
 * @param isbn_code_standard
 * @return
 */
char isbn_crtl_code_generator(char isbn_code_str[], int isbn_code_standard);

#endif /* ISBN_CODE_GENERATOR_H_ */
