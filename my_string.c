#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"

struct word {
        int size;
        int capacity;
        char* data;
};

typedef struct word Word;



MY_STRING my_string_init_default(void) {
        Word* pWord = (Word*)malloc(sizeof(Word));
	if (pWord != NULL) {
		pWord->size = 0;
		pWord->capacity = 7;
        	pWord->data = (char*)malloc(sizeof(char) * pWord->capacity);
		if (pWord->data == NULL) {
			free(pWord);
			return NULL;
		}
	}

        return pWord;
}

void my_string_destroy(MY_STRING* phMy_string) {
        Word* pMy_string = (Word*)*phMy_string;
        free(pMy_string->data);
        free(pMy_string);
        *phMy_string = NULL;
}

MY_STRING my_string_init_c_string(const char* c_string) {
        Word* pWord = (Word*)malloc(sizeof(Word));
	if (pWord != NULL) {
        	int letterCount = 0;
        	while (c_string[letterCount] != '\0') {
        	        letterCount++;
        	}
	
	        pWord->size = letterCount;
	        pWord->capacity = letterCount + 1;
	        pWord->data = (char*)malloc(sizeof(char) * pWord->capacity);
		if (pWord->data == NULL) {
			return NULL;
		}
	        
		for (int i = 0; i <= pWord->size; i++) {
	                (pWord->data)[i] = c_string[i];
	        }
	}

        return pWord;
}

int my_string_get_capacity(MY_STRING hMy_string) {
        Word* pWord = (Word*)hMy_string;
        return pWord->capacity;
}

int my_string_get_size(MY_STRING hMy_string) {
        Word* pWord = (Word*)hMy_string;
        return pWord->size;
}

int my_string_compare(MY_STRING hLeft_string, MY_STRING hRight_string) {
        Word* pWordL = (Word*)hLeft_string;
        Word* pWordR = (Word*)hRight_string;
        int i = 0;
        while (pWordL->size > i || pWordR->size > i) {
		if (pWordL->size <= i) {
			return 1;
		}

		if (pWordR->size <= i) {
                        return -1;
		}

                if (pWordL->data[i] > pWordR->data[i]) {
                        return 1;
                }

                if (pWordR->data[i] > pWordL->data[i]) {
                        return -1;
                }
		
                i++;
        }

        return 0;
}

Status my_string_extraction(MY_STRING hMy_string, FILE* fp) {
	Word* pWord = (Word*)hMy_string;
	int letCount = 0;
	char c = (char)fgetc(fp);

	if (c == EOF) {
		return FAILURE;
	}

	while (c != '\n' && c != EOF) {
		pWord->data[letCount] = c;
		if (letCount >= pWord->capacity - 1) {
			pWord->data = realloc(pWord->data, pWord->capacity + 5);
			pWord->capacity += 5;
		}

		letCount++;
		c = (char)fgetc(fp);
	}


	pWord->data[letCount] = c;
	if (letCount >= pWord->capacity - 1) {
		pWord->data = realloc(pWord->data, pWord->capacity + 1);
		pWord->capacity += 1;
	}

	pWord->data[letCount + 1] = '\0';
	pWord->size = letCount;

	return SUCCESS;
}

Status my_string_insertion(MY_STRING hMy_string, FILE* fp) {
	Word* pWord = (Word*)hMy_string;
	if (fprintf(fp, "%s", pWord->data) >= 0) {
		return SUCCESS;
	}

	return FAILURE;
}

Status my_string_push_back(MY_STRING hMy_string, char item) {
	Word* pWord = (Word*)hMy_string;

	if (pWord->size >= pWord->capacity) {
		char* temp = (char*)malloc(pWord->capacity * 2);
		int i;
		if (temp == NULL) {
			return FAILURE;
		}
	
		for (i = 0; i < pWord->size; i++) {
			temp[i] = pWord->data[i];
		}

		free(pWord->data);
		pWord->data = temp;
		pWord->capacity *= 2;
	}
	

	pWord->data[pWord->size] = item;
	pWord->size++;
	return SUCCESS;
}

Status my_string_pop_back(MY_STRING hMy_string) {
	Word* pWord = (Word*)hMy_string;
	
	if (my_string_empty(pWord) == TRUE) {
		return FAILURE;
	}

	pWord->size--;
	return SUCCESS;
}

char* my_string_at(MY_STRING hMy_string, int index) {
	Word* pWord = (Word*)hMy_string;

	if (index < 0 || index >= pWord->capacity) {
		return NULL;
	}

	return pWord->data + index;
}

char* my_string_c_str(MY_STRING hMy_string) {
	Word* pWord = (Word*)hMy_string;

	if (pWord->size >= pWord->capacity) {
		char* temp = (char*)malloc(pWord->capacity + 1);
		int i;
		if (temp == NULL) {
			return NULL;
		}

		for (i = 0; i < pWord->size; i++) {
			temp[i] = pWord->data[i];
		}

		free(pWord->data);
		pWord->data = temp;
		pWord->capacity++;
	}

	pWord->data[pWord->size] = '\0';
	return pWord->data;
}

Status my_string_concat(MY_STRING hResult, MY_STRING hAppend) {
	Word* pWordOrig = (Word*)hResult;
	Word* pWordApp = (Word*)hAppend;

	if (pWordOrig->capacity < pWordOrig->size + pWordApp->size) {
		char* temp = (char*)malloc(pWordOrig->size + pWordApp->size);
		int i;
		if (temp == NULL) {
			return FAILURE;
		}

		for (i = 0; i < pWordOrig->size; i++) {
			temp[i] = pWordOrig->data[i];
		}

		free(pWordOrig->data);
		pWordOrig->data = temp;
		pWordOrig->capacity = pWordOrig->size + pWordApp->size;
	}

	int j = 0;
	while (j < pWordApp->size) {
		pWordOrig->data[pWordOrig->size] = pWordApp->data[j];
		pWordOrig->size++;
		j++;
	}

	return SUCCESS;
}

Boolean my_string_empty(MY_STRING hMy_string) {
	Word* pWord = (Word*)hMy_string;
	return (pWord->size <= 0) ? TRUE : FALSE;
}

Status my_string_assignment(MY_STRING hLeft, MY_STRING hRight) {
	Word* pWordR = (Word*)hRight;
	Word* pWordL = (Word*)hLeft;
	char* org = (char*)malloc(sizeof(char) * pWordL->capacity);
	int orgCap = pWordL->capacity;
	int orgSize = pWordL->size;
	for (int i = 0; i < pWordL->capacity; i++) {
		org[i] = pWordL->data[i];
	}

	if (pWordR->size > pWordL->capacity) {
		char* temp = (char*)malloc(pWordR->capacity);
		if (temp == NULL) {
			return FAILURE;
		}

		free(pWordL->data);
		pWordL->data = temp;
		pWordL->capacity = pWordR->capacity;
	}
	
	pWordL->size = 0;
	for (int i = 0; i < pWordR->size; i++) {
		if (my_string_push_back(pWordL, pWordR->data[i]) == FAILURE) {
			free(pWordL->data);
			pWordL->data = org;
			pWordL->capacity = orgCap;
			pWordL->size = orgSize;
			return FAILURE;
		}
	}

	free(org);
	return SUCCESS;
}

MY_STRING my_string_init_copy(MY_STRING hMy_string) {
	MY_STRING hString = NULL;
	hString = my_string_init_c_string(my_string_c_str(hMy_string));
	return hString;
}

void my_string_swap(MY_STRING hLeft, MY_STRING hRight) {
	Word* pWordL = (Word*)hLeft;
	Word* pWordR = (Word*)hRight;
	char* temp = pWordR->data;
	pWordR->data = pWordL->data;
	pWordL->data = temp;

	int size = pWordR->size;
	pWordR->size = pWordL->size;
	pWordL->size = size;

	int cap = pWordR->capacity;
	pWordR->capacity = pWordL->capacity;
	pWordL->capacity = cap;
}

