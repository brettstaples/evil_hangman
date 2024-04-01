#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"
#include "generic_vector.h"

int main(int argc, char* argv[]) {
	
	GENERIC_VECTOR arr[30];
	for (int i = 0; i < 30; i++) {
		arr[i] = generic_vector_init_default(my_string_init_copy, my_string_destroy);
		if (arr[i] == NULL) {
			printf("CAMI IT FAILED\n");
			exit(1);
		}
	}

	FILE* fp = fopen("dictionary.txt", "r");
	char ch = fgetc(fp);
	while(ch != EOF) {
		ungetc(ch, fp);
		MY_STRING hString = my_string_init_default();
		my_string_extraction(hString, fp);
		int size = my_string_get_size(hString);
		if (generic_vector_push_back(arr[size - 1], hString) == FAILURE) {
			printf("CAMI WHY DID VECTOR PUSH BACK FAIL\n");
			exit(1);
		}

		my_string_destroy(&hString);
		ch = fgetc(fp);
	}

	for (int i = 0; i < 30; i++) {
		if (atoi(argv[1]) == i + 1) {
			printf("CAMI THIS IS %d CHECK THE SIZE %d NOW THE CAP %d\n", i + 1, generic_vector_get_size(arr[i]), generic_vector_get_capacity(arr[i]));
		}
		while(!generic_vector_is_empty(arr[i])) {
			generic_vector_pop_back(arr[i]);
		}

		generic_vector_destroy(arr + i);
	}

	fclose(fp);
	
	MY_STRING hMy_string7 = NULL;
        FILE* fp3;
        hMy_string7 = my_string_init_default();
        fp3 = fopen("dictionary.txt", "r");
	int num = 0;
        while(my_string_extraction(hMy_string7, fp3)) {
		if (my_string_get_size(hMy_string7) == atoi(argv[1])) {
			my_string_insertion(hMy_string7, stdout);
			num++;
		}
        }

	printf("CAMI this %d\n", num);

        my_string_destroy(&hMy_string7);
        fclose(fp3);	
	
	
	/*
	MY_STRING arr[100];

	for (int i = 0; i < 100; i++) {
		arr[i] = NULL;
	}

	arr[0] = my_string_init_c_string("COPY ME!");

	for (int i = 1; i < 100; i++) {
		arr[i] = my_string_init_copy(arr[0]);
	}

	my_string_destroy(&(arr[0]));
	
	arr[0] = my_string_init_c_string("FIRST FIFTY!");

	for (int i = 1; i < 50; i++) {
		my_string_assignment(arr[i], arr[0]);
	}

	for (int i = 0; i < 50; i++) {
		my_string_swap(arr[i], arr[99 - i]);
	}

	for (int i = 0; i < 100; i++) {	
        	my_string_insertion(arr[i], stdout);
		printf("\n");
		my_string_destroy(&(arr[i]));
	}
	*/

	/*
	MY_STRING hString = NULL;
	hString = my_string_init_c_string("hello");
	MY_STRING hString2 = NULL;
	hString2 = my_string_init_c_string("cami");
	printf("Left:");
        my_string_insertion(hString, stdout);
        printf("\nRight:");
        my_string_insertion(hString2, stdout);
        printf("\n");
	my_string_swap(hString, hString2);
	printf("Left:");
        my_string_insertion(hString, stdout);
        printf("\nRight:");
        my_string_insertion(hString2, stdout);
        printf("\n");
	my_string_destroy(&hString);
	my_string_destroy(&hString2);
	*/

	/*	
	MY_STRING hString = NULL;
	hString = my_string_init_c_string("hello ahh");
	MY_STRING hString2 = NULL;
	hString2 = my_string_init_copy(hString);
	printf("Left:");
	my_string_insertion(hString, stdout);
	printf("\nRight:");
	my_string_insertion(hString2, stdout);
	printf("\n");
	my_string_destroy(&hString);
	my_string_destroy(&hString2);
	*/

	/*
	MY_STRING hStringR = NULL;
	MY_STRING hStringL = NULL;
	hStringR = my_string_init_c_string("hello ahh");
	hStringL = my_string_init_c_string("cami love");
	printf("Left:");
	my_string_insertion(hStringL, stdout);
	printf("\nRight:");
	my_string_insertion(hStringR, stdout);
	printf("\n");
	my_string_assignment(hStringL, hStringR);
	printf("Left:");
	my_string_insertion(hStringL, stdout);
	printf("\nRight:");
	my_string_insertion(hStringR, stdout);
	printf("\n");
	my_string_destroy(&hStringL);
	my_string_destroy(&hStringR);
	*/
	/*
	MY_STRING hMy_string = NULL;
	hMy_string = my_string_init_c_string("a");

	MY_STRING hMy_string2 = NULL;
	hMy_string2 = my_string_init_c_string("b");

	char* firstWord = my_string_c_str(hMy_string);
	if (firstWord != NULL) {
		printf("first %s\n", firstWord);
	}

	printf("capcity: %d\n", my_string_get_capacity(hMy_string));
	printf("size: %d\n", my_string_get_size(hMy_string));
	char* secondWord = my_string_c_str(hMy_string2);
	if (secondWord != NULL) {
		printf("second %s\n", secondWord);
	}
	printf("capcity: %d\n", my_string_get_capacity(hMy_string2));
	printf("size: %d\n", my_string_get_size(hMy_string2));
	printf("Compare: %d\n", my_string_compare(hMy_string, hMy_string2));
	my_string_destroy(&hMy_string);
	my_string_destroy(&hMy_string2);
	

	MY_STRING hMy_string3 = NULL;
	hMy_string3 = my_string_init_c_string("c");
	MY_STRING hMy_string4 = NULL;
	hMy_string4 = my_string_init_c_string("c");
	char* thirdWord = my_string_c_str(hMy_string3);
	if (thirdWord != NULL) {
		printf("first %s\n", firstWord);
	}
	char* fourthWord = my_string_c_str(hMy_string4);
	if (fourthWord != NULL) {
		printf("first %s\n", firstWord);
	}
	printf("capcity: %d\n", my_string_get_capacity(hMy_string3));
	printf("size: %d\n", my_string_get_size(hMy_string3));
	printf("capcity: %d\n", my_string_get_capacity(hMy_string4));
	printf("size: %d\n", my_string_get_size(hMy_string4));
	printf("Compare: %d\n", my_string_compare(hMy_string3, hMy_string4));
	my_string_destroy(&hMy_string3);
	my_string_destroy(&hMy_string4);

	
	MY_STRING hMy_string5 = NULL;
	hMy_string5 = my_string_init_default();
	MY_STRING hMy_string6 = NULL;
	hMy_string6 = my_string_init_default();

	my_string_push_back(hMy_string5, 'C');
	my_string_push_back(hMy_string5, 'a');
	my_string_push_back(hMy_string5, 'm');
	my_string_push_back(hMy_string5, 'i');
	my_string_push_back(hMy_string5, 'l');
	my_string_push_back(hMy_string5, 'a');
	char* fifthWord = my_string_c_str(hMy_string5);
	if (fifthWord != NULL) {
		printf("%s\n", fifthWord);
	}

	
	my_string_push_back(hMy_string6, 'B');
	my_string_push_back(hMy_string6, 'r');
	my_string_push_back(hMy_string6, 'e');
	my_string_push_back(hMy_string6, 't');
	my_string_push_back(hMy_string6, 't');
	my_string_pop_back(hMy_string6);
	char* sixWord = my_string_c_str(hMy_string6);
	if (sixWord != NULL) {
		printf("%s\n", sixWord);
	}

	my_string_concat(hMy_string5, hMy_string6);

	my_string_insertion(hMy_string5, stdout);
	printf("\n");

	my_string_destroy(&hMy_string5);
	my_string_destroy(&hMy_string6);
	*/
	/*
	MY_STRING hMy_string8 = NULL;
	hMy_string8 = my_string_init_c_string("abc");

	MY_STRING hMy_string9 = NULL;
	hMy_string9 = my_string_init_default();
	my_string_push_back(hMy_string9, 'a');
	my_string_push_back(hMy_string9, 'b');
	my_string_push_back(hMy_string9, 'c');
	my_string_push_back(hMy_string9, 'c');

	char* word = my_string_c_str(hMy_string8);
	char* word2 = my_string_c_str(hMy_string9);

	printf("Word: %s\n", word);
	printf("Word2: %s\n", word2);

	int compare = my_string_compare(hMy_string8, hMy_string9);
	printf("Compare: %d\n", compare);
        my_string_destroy(&hMy_string8);
        my_string_destroy(&hMy_string9);
	*/
	return 0;	
}
