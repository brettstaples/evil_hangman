#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "unit_test.h"

Status test_init_default_returns_nonNULL(char* buffer, int length) {
	MY_STRING hString = NULL;
	hString = my_string_init_default();
	if(hString == NULL) {
		strncpy(buffer, "test_init_default_returns_nonNULL\n"
		"my_string_init_default returns NULL", length);
		return FAILURE;
	} else {
		my_string_destroy(&hString);
		strncpy(buffer, "\ttest_init_default_returns_nonNULL\n", length);
		return SUCCESS;
	}
}

Status test_get_size_on_init_default_returns_0(char* buffer, int length) {
	MY_STRING hString = NULL;
	Status status;
	hString = my_string_init_default();
	if(my_string_get_size(hString) != 0) {
		status = FAILURE;
		printf("Expected a size of 0 but got %d\n", my_string_get_size(hString));
		strncpy(buffer, "test_get_size_on_init_default_returns_0\n"
		"Did not receive 0 from get_size after init_default\n", length);
	} else {
		status = SUCCESS;
		strncpy(buffer, "test_get_size_on_init_default_returns_0\n"
		, length);
	}

	my_string_destroy(&hString);
	return status;
}

Status test_bstaples_get_capacity_on_init_default_returns_7(char* buffer, int length) {
	MY_STRING hString = NULL;
        Status status;
        hString = my_string_init_default();
        if(my_string_get_capacity(hString) != 7) {
                status = FAILURE;
                printf("Expected a size of 7 but got %d\n", my_string_get_capacity(hString));
		strncpy(buffer, "test_bstaples_get_capacity_on_init_default_returns_7\n"
                "Did not receive 7 from get_capacity after init_default\n", length);
        } else {
                status = SUCCESS;
                strncpy(buffer, "test_bstaples_get_capacity_on_init_default_returns_7\n"
                , length);
        }

        my_string_destroy(&hString);	
	return status;
}

Status test_bstaples_string_init_c_string_returns_hi(char* buffer, int length) {
	MY_STRING hString = NULL;
        hString = my_string_init_c_string("hi");
	Status status = SUCCESS;
	char str[] = "hi";
	char* testStr = my_string_c_str(hString);
	for (int i = 0; i < 2; i++) {
		if (str[i] != testStr[i]) {
			status = FAILURE;
		}
	}

        if(status != SUCCESS) {
                status = FAILURE;
                printf("Expected a string of hi but got %s\n", testStr);                
		strncpy(buffer, "test_bstaples_string_init_c_string_returns_hi\n"
                "Did not receive hi after init_c_string\n", length);
        } else {
                status = SUCCESS;
                strncpy(buffer, "test_bstaples_string_init_c_string_returns_hi\n"
                , length);
        }

        my_string_destroy(&hString);
        return status;
}

Status test_bstaples_string_init_c_string_hello_size_returns_5(char* buffer, int length) {
	MY_STRING hString = NULL;                                                                
	Status status;                                                                           
        hString = my_string_init_c_string("hello");
	if(my_string_get_size(hString) != 5) {                                                       
		status = FAILURE;                                                                        
		printf("Expected a size of 5 but got %d\n", my_string_get_size(hString));                
		strncpy(buffer, "test_bstaples_string_init_c_string_hello_size_returns_5\n"
                "Did not receive 5 from get_capacity after init_default\n", length);
	} else {
                status = SUCCESS;
                strncpy(buffer, "test_bstaples_string_init_c_string_hello_size_returns_5\n"
                , length);
        }

        my_string_destroy(&hString);
        return status;
}

Status test_bstaples_string_compare_returns_0(char* buffer, int length) {
	MY_STRING hString = NULL;
        hString = my_string_init_c_string("hello");
	MY_STRING hString2 = NULL;
        hString2 = my_string_init_c_string("hello");
        Status status;
        if(my_string_compare(hString, hString2) != 0) {
                status = FAILURE;
                printf("Expected a return of 0 but got %d\n", my_string_compare(hString, hString2));
                strncpy(buffer, "test_bstaples_string_compare_returns_0\n"
                "Did not receive 0 from compare\n", length);
        } else {
                status = SUCCESS;
                strncpy(buffer, "test_bstaples_string_compare_returns_0\n"
                , length);
        }

        my_string_destroy(&hString);
        my_string_destroy(&hString2);
        return status;
}

Status test_bstaples_string_compare_returns_correct_lexographic_values(char* buffer, int length) {
	MY_STRING hString = NULL;
        hString = my_string_init_c_string("a");
        MY_STRING hString2 = NULL;
        hString2 = my_string_init_c_string("b");
        Status status;
        if(my_string_compare(hString, hString2) != -1) {
                status = FAILURE;
                printf("Expected a return of -1 but got %d\n", my_string_compare(hString, hString2));
                strncpy(buffer, "test_bstaples_string_compare_returns_correct_lexographic_values\n"
                "Did not receive -1 from compare\n", length);
        } else {
                status = SUCCESS;
                strncpy(buffer, "test_bstaples_string_compare_returns_correct_lexographic_values\n"
                , length);
        }

        my_string_destroy(&hString);
        my_string_destroy(&hString2);
        return status;
}

Status test_bstaples_my_string_extraction_and_my_string_insertion_check_file(char* buffer, int length) {
	MY_STRING hString = NULL;
        hString = my_string_init_default();
	MY_STRING hString2 = NULL;
        hString2 = my_string_init_default();
	Status status = SUCCESS;
	FILE* fp = fopen("temp.c", "w+");
	FILE* fp2 = fopen("temp2.c", "w+");
	fprintf(fp, "Hello World");
	fseek(fp, 0, SEEK_SET);
	my_string_extraction(hString, fp);
	my_string_insertion(hString, fp2);
	fseek(fp2, 0, SEEK_SET);
	my_string_extraction(hString2, fp2);
        if(my_string_compare(hString, hString2) != 0) {
                status = FAILURE;
                printf("Expected a return of 0 but got %d\n", my_string_compare(hString, hString2));
                strncpy(buffer, "test_bstaples_my_string_extraction_and_my_string_insertion_check_file\n"
                "Did not receive 0 from compare\n", length);
        } else {
                status = SUCCESS;
                strncpy(buffer, "test_bstaples_my_string_extraction_and_my_string_insertion_check_file\n"
                , length);
        }

        my_string_destroy(&hString);
        my_string_destroy(&hString2);
	fclose(fp);
	fclose(fp2);
	remove("temp.c");
	remove("temp2.c");
        return status;
}

Status test_bstaples_string_push_back_returns_abc(char* buffer, int length) {
	MY_STRING hString = NULL;
        hString = my_string_init_default();
	MY_STRING hString2 = NULL;
        hString2 = my_string_init_c_string("abc");
        Status status;
	my_string_push_back(hString, 'a');
	my_string_push_back(hString, 'b');
	my_string_push_back(hString, 'c');
        if(my_string_compare(hString, hString2) != 0) {
                status = FAILURE;
                printf("Expected a return of 0 but got %d\n", my_string_compare(hString, hString2));
                strncpy(buffer, "test_bstaples_string_push_back_returns_abc\n"
                "Did not receive 0 from compare\n", length);
        } else {
                status = SUCCESS;
                strncpy(buffer, "test_bstaples_string_push_back_returns_abc\n"
                , length);
        }

        my_string_destroy(&hString);
        my_string_destroy(&hString2);
        return status;	
}

Status test_bstaples_string_pop_back_returns_ab(char* buffer, int length) {
        MY_STRING hString = NULL;
	hString = my_string_init_default();
        MY_STRING hString2 = NULL;
        hString2 = my_string_init_c_string("ab");
        Status status;
        my_string_push_back(hString, 'a');
        my_string_push_back(hString, 'b');
        my_string_push_back(hString, 'c');
        my_string_pop_back(hString);
        if(my_string_compare(hString, hString2) != 0) {
                status = FAILURE;
                printf("Expected a return of 0 but got %d\n", my_string_compare(hString, hString2));
                strncpy(buffer, "test_bstaples_string_pop_back_returns_ab\n"
                "Did not receive 0 from compare\n", length);
        } else {
                status = SUCCESS;
                strncpy(buffer, "test_bstaples_string_pop_back_returns_ab\n"
                , length);
        }

        my_string_destroy(&hString);
        my_string_destroy(&hString2);
        return status;
}

Status test_bstaples_my_string_at_returns_w(char* buffer, int length) {
        MY_STRING hString = NULL;
        hString = my_string_init_c_string("pow");
        Status status;
	char* ch = my_string_at(hString, 2);
        if(*ch != 'w') {
                status = FAILURE;
                printf("Expected a return of w but did not get it\n");
                strncpy(buffer, "test_bstaples_my_string_at_returns_w\n"
                "Did not receive w from compare\n", length);
        } else {
                status = SUCCESS;
                strncpy(buffer, "test_bstaples_my_string_at_returns_w\n"
                , length);
        }

        my_string_destroy(&hString);
        return status;
}

Status test_bstaples_my_string_push_back_works_with_100_letters(char* buffer, int length) {
	MY_STRING hString = NULL;
        hString = my_string_init_default();
        Status status;
	for (int i = 0; i < 100; i++) {
        	my_string_push_back(hString, 'a');
	}

        if(my_string_get_size(hString) != 100) {
                status = FAILURE;
                printf("Expected a return of 100 but got %d\n", my_string_get_size(hString));
                strncpy(buffer, "test_bstaples_my_string_push_back_works_with_100_letters\n"
                "Did not receive 100 from compare\n", length);
        } else {
                status = SUCCESS;
                strncpy(buffer, "test_bstaples_my_string_push_back_works_with_100_letters\n"
                , length);
        }

        my_string_destroy(&hString);
        return status;
}

Status test_bstaples_my_string_pop_back_returns_10_letters(char* buffer, int length) {
	MY_STRING hString = NULL;
        hString = my_string_init_default();
        Status status;
        for (int i = 0; i < 11; i++) {
                my_string_push_back(hString, 'a');
        }

	my_string_pop_back(hString);
        if(my_string_get_size(hString) != 10) {
                status = FAILURE;
                printf("Expected a return of 10 but got %d\n", my_string_get_size(hString));
                strncpy(buffer, "test_bstaples_my_string_pop_back_returns_10_letters\n"
                "Did not receive 10 from compare\n", length);
        } else {
                status = SUCCESS;
                strncpy(buffer, "test_bstaples_my_string_pop_back_returns_10_letters\n"
                , length);
        }

        my_string_destroy(&hString);
        return status;
}

Status test_bstaples_my_string_c_str_returns_hello(char* buffer, int length) {
	MY_STRING hString = NULL;
        hString = my_string_init_c_string("hello");
        Status status;
	char* str = my_string_c_str(hString);
	MY_STRING hString2 = NULL;
        hString2 = my_string_init_c_string(str);

	if(my_string_compare(hString, hString2) != 0) {
                status = FAILURE;
                printf("Expected a return of 0 but got %d\n", my_string_compare(hString, hString2));
                strncpy(buffer, "test_bstaples_my_string_c_str_returns_hello\n"
                "Did not receive 0 from compare\n", length);
        } else {
                status = SUCCESS;
                strncpy(buffer, "test_bstaples_my_string_c_str_returns_hello\n"
                , length);
        }

        my_string_destroy(&hString);
        my_string_destroy(&hString2);
        return status;
}

Status test_bstaples_my_string_push_back_c_str_returns_abcdefgh(char* buffer, int length) {
	MY_STRING hString = NULL;
        hString = my_string_init_default();
	for (int i = 0; i < 8; i++) {
                my_string_push_back(hString, 'a' + i);
        }

        Status status;
        MY_STRING hString2 = NULL;
        hString2 = my_string_init_c_string("abcdefgh");
        if(my_string_compare(hString, hString2) != 0) {
                status = FAILURE;
                printf("Expected a return of 0 but got %d\n", my_string_compare(hString, hString2));
                strncpy(buffer, "test_bstaples_my_string_push_back_c_str_returns_abcdefgh\n"
                "Did not receive 0 from compare\n", length);
        } else {
                status = SUCCESS;
                strncpy(buffer, "test_bstaples_my_string_push_back_c_str_returns_abcdefgh\n"
                , length);
        }

        my_string_destroy(&hString);
        my_string_destroy(&hString2);
        return status;
}

Status test_bstaples_my_string_concat_returns_HelloWorld(char* buffer, int length) {
	MY_STRING hString = NULL;
        hString = my_string_init_c_string("Hello");
        MY_STRING hString2 = NULL;
        hString2 = my_string_init_c_string("World");
        MY_STRING hString3 = NULL;
        hString3 = my_string_init_c_string("HelloWorld");
        Status status;
	my_string_concat(hString, hString2);
        if(my_string_compare(hString, hString3) != 0) {
                status = FAILURE;
                printf("Expected a return of 0 but got %d\n", my_string_compare(hString, hString2));
                strncpy(buffer, "test_bstaples_my_string_concat_returns_HelloWorld\n"
                "Did not receive 0 from compare\n", length);
        } else {
                status = SUCCESS;
                strncpy(buffer, "test_bstaples_my_string_concat_returns_HelloWorld\n"
                , length);
        }

        my_string_destroy(&hString);
        my_string_destroy(&hString2);
        my_string_destroy(&hString3);
        return status;
}

Status test_bstaples_my_string_push_and_concat_returns_BinaryTree(char* buffer, int length) {
	MY_STRING hString = NULL;
        hString = my_string_init_default();
        my_string_push_back(hString, 'B');
        my_string_push_back(hString, 'i');
        my_string_push_back(hString, 'n');
        my_string_push_back(hString, 'a');
        my_string_push_back(hString, 'r');
        my_string_push_back(hString, 'y');
	MY_STRING hString2 = NULL;
        hString2 = my_string_init_default();
        my_string_push_back(hString2, 'T');
        my_string_push_back(hString2, 'r');
        my_string_push_back(hString2, 'e');
        my_string_push_back(hString2, 'e');
        MY_STRING hString3 = NULL;
        hString3 = my_string_init_c_string("BinaryTree");
        Status status;
        my_string_concat(hString, hString2);
        if(my_string_compare(hString, hString3) != 0) {
                status = FAILURE;
                printf("Expected a return of 0 but got %d\n", my_string_compare(hString, hString2));
                strncpy(buffer, "test_bstaples_my_string_push_and_concat_returns_BinaryTree\n"
                "Did not receive 0 from compare\n", length);
        } else {
                status = SUCCESS;
                strncpy(buffer, "test_bstaples_my_string_push_and_concat_returns_BinaryTree\n"
                , length);
        }

        my_string_destroy(&hString);
        my_string_destroy(&hString2);
        my_string_destroy(&hString3);
        return status;
}

Status test_bstaples_my_string_empty_after_push_returns_false(char* buffer, int length) {
	MY_STRING hString = NULL;
        hString = my_string_init_default();
        Status status = SUCCESS;
        my_string_push_back(hString, 'a');
        if(my_string_empty(hString) != FALSE) {
                status = FAILURE;
                printf("Expected a return of FALSE but got TRUE\n");
                strncpy(buffer, "test_bstaples_my_string_empty_after_push_returns_false\n"
                "Did not receive FALSE from my_string_empty\n", length);
        } else {
                status = SUCCESS;
                strncpy(buffer, "test_bstaples_my_string_empty_after_push_returns_false\n"
                , length);
        }

        my_string_destroy(&hString);
        return status;

}

Status test_bstaples_my_string_empty_after_pops_returns_true(char* buffer, int length) {
	MY_STRING hString = NULL;
        hString = my_string_init_default();
        Status status = SUCCESS;
        my_string_push_back(hString, 'a');
        my_string_pop_back(hString);
        if(my_string_empty(hString) == FALSE) {
                status = FAILURE;
                printf("Expected a return of TRUE but got FALSE\n");
                strncpy(buffer, "test_bstaples_my_string_empty_after_pops_returns_true\n"
                "Did not receive TRUE from my_string_empty\n", length);
        } else {
                status = SUCCESS;
                strncpy(buffer, "test_bstaples_my_string_empty_after_pops_returns_true\n"
                , length);
        }

        my_string_destroy(&hString);
        return status;
}

Status test_bstaples_my_string_pop_on_empty_returns_failure(char* buffer, int length) {
	MY_STRING hString = NULL;
        hString = my_string_init_default();
        Status status = SUCCESS;
        my_string_pop_back(hString);
        if(my_string_pop_back(hString) != FAILURE) {
                status = FAILURE;
                printf("Expected a return of FAILURE but got SUCCESS\n");
                strncpy(buffer, "test_bstaples_my_string_pop_on_empty_returns_failure\n"
                "Did not receive FAILURE from my_string_pop_back\n", length);
        } else {
                status = SUCCESS;
                strncpy(buffer, "test_bstaples_my_string_pop_on_empty_returns_failure\n"
                , length);
        }

        my_string_destroy(&hString);
        return status;
}

Status test_bstaples_my_string_c_str_overwrites_null_after_push(char* buffer, int length) {
	MY_STRING hString = NULL;
        hString = my_string_init_c_string("Hello");
        Status status = SUCCESS;
	char* str = my_string_c_str(hString);
        my_string_push_back(hString, 'a');
        if(str[5] != 'a') {
                status = FAILURE;
                printf("Expected a value of a\n");
                strncpy(buffer, "test_bstaples_my_string_c_str_overwrites_null_after_push\n"
                "Did not receive value of a\n", length);
        } else {
                status = SUCCESS;
                strncpy(buffer, "test_bstaples_my_string_c_str_overwrites_null_after_push\n"
                , length);
        }

        my_string_destroy(&hString);
        return status;
}

Status test_bstaples_my_string_concat_empty_strings_returns_empty_string(char* buffer, int length) {
	MY_STRING hString = NULL;
        hString = my_string_init_default();
        MY_STRING hString2 = NULL;
        hString2 = my_string_init_default();
        MY_STRING hString3 = NULL;
        hString3 = my_string_init_default();
        Status status;
	my_string_concat(hString, hString2);
        if(my_string_compare(hString, hString3) != 0) {
                status = FAILURE;
                printf("Expected a return of 0 but got %d\n", my_string_compare(hString, hString2));
                strncpy(buffer, "test_bstaples_my_string_concat_empty_strings_returns_empty_string\n"
                "Did not receive 0 from compare\n", length);
        } else {
                status = SUCCESS;
                strncpy(buffer, "test_bstaples_my_string_concat_empty_strings_returns_empty_string\n"
                , length);
        }

        my_string_destroy(&hString);
        my_string_destroy(&hString2);
        my_string_destroy(&hString3);
        return status;
}

Status test_bstaples_my_string_concat_resizes_correctly(char* buffer, int length) {
	MY_STRING hString = NULL;
        hString = my_string_init_c_string("Hello");
        MY_STRING hString2 = NULL;
        hString2 = my_string_init_c_string("World");
        Status status;
	my_string_concat(hString, hString2);
        if(my_string_get_capacity(hString) != 10) {
                status = FAILURE;
                printf("Expected a return of 10 but got %d\n", my_string_get_capacity(hString));
                strncpy(buffer, "test_bstaples_my_string_concat_resizes_correctly\n"
                "Did not receive 10 from get_capacity\n", length);
        } else {
                status = SUCCESS;
                strncpy(buffer, "test_bstaples_my_string_concat_resizes_correctly\n"
                , length);
        }

        my_string_destroy(&hString);
        my_string_destroy(&hString2);
        return status;
}

Status test_bstaples_my_string_at_returns_b_at_index_5(char* buffer, int length) {
        MY_STRING hString = NULL;
        hString = my_string_init_c_string("aywtob");
        Status status;
	char* ch = my_string_at(hString, 5);
        if(*ch != 'b') {
                status = FAILURE;
                printf("Expected a return of b but did not get it\n");
                strncpy(buffer, "test_bstaples_my_string_at_returns_b_at_index_5\n"
                "Did not receive b from compare\n", length);
        } else {
                status = SUCCESS;
                strncpy(buffer, "test_bstaples_my_string_at_returns_b_at_index_5\n"
                , length);
        }

        my_string_destroy(&hString);
        return status;
}

Status test_bstaples_my_string_push_back_resizes_correctly(char* buffer, int length) {
	MY_STRING hString = NULL;
        hString = my_string_init_default();
        Status status = SUCCESS;
        my_string_push_back(hString, 'a');
        if(my_string_get_size(hString) != 1) {
                status = FAILURE;
                printf("Expected a size of 1 but got %d\n", my_string_get_size(hString));
                strncpy(buffer, "test_bstaples_my_string_push_back_resizes_correctly\n"
                "Did not receive 1 from my_string_get_size\n", length);
        } else {
                status = SUCCESS;
                strncpy(buffer, "test_bstaples_my_string_push_back_resizes_correctly\n"
                , length);
        }

        my_string_destroy(&hString);
        return status;
}

