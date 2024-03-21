#include <stdio.h>
#include "unit_test.h"

int main(int argc, char* argv[]) {
	Status (*tests[])(char*, int) =
	{
		test_init_default_returns_nonNULL,
		test_get_size_on_init_default_returns_0,
		test_bstaples_get_capacity_on_init_default_returns_7,
		test_bstaples_string_init_c_string_returns_hi,
		test_bstaples_string_init_c_string_hello_size_returns_5,
		test_bstaples_string_compare_returns_0,
		test_bstaples_string_compare_returns_correct_lexographic_values,
		test_bstaples_my_string_extraction_and_my_string_insertion_check_file,
		test_bstaples_string_push_back_returns_abc,
		test_bstaples_string_pop_back_returns_ab,
		test_bstaples_my_string_at_returns_w,
		test_bstaples_my_string_push_back_works_with_100_letters,
		test_bstaples_my_string_pop_back_returns_10_letters,
		test_bstaples_my_string_c_str_returns_hello,
		test_bstaples_my_string_push_back_c_str_returns_abcdefgh,
		test_bstaples_my_string_concat_returns_HelloWorld,
		test_bstaples_my_string_push_and_concat_returns_BinaryTree,
		test_bstaples_my_string_empty_after_push_returns_false,
		test_bstaples_my_string_empty_after_pops_returns_true,
		test_bstaples_my_string_pop_on_empty_returns_failure,
		test_bstaples_my_string_c_str_overwrites_null_after_push,
		test_bstaples_my_string_concat_empty_strings_returns_empty_string,
		test_bstaples_my_string_concat_resizes_correctly,
		test_bstaples_my_string_at_returns_b_at_index_5,
		test_bstaples_my_string_push_back_resizes_correctly

	};
	int number_of_functions = sizeof(tests) / sizeof(tests[0]);
	int i;
	char buffer[500];
	int success_count = 0;
	int failure_count = 0;
	for (i = 0; i < number_of_functions; i++) {
		if (tests[i](buffer, 500) == FAILURE) {
			printf("FAILED: Test %d failed miserably\n", i + 1);
			printf("\t%s\n", buffer);
			failure_count++;
		} else {
			//printf("PASS: Test %d passed\n", i + 1);
			//printf("\t%s\n", buffer);
			success_count++;
		}
	}
	
	printf("Total number of tests: %d\n", number_of_functions);
	printf("%d/%d Pass, %d/%d Failure\n", success_count,
	number_of_functions, failure_count, number_of_functions);
	
	return 0;
}
