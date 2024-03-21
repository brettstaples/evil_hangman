#ifndef UNIT_TEST_H
#define UNIT_TEST_H
#include "my_string.h"

Status test_init_default_returns_nonNULL(char* buffer, int length);
Status test_get_size_on_init_default_returns_0(char* buffer, int length);
Status test_bstaples_get_capacity_on_init_default_returns_7(char* buffer, int length);
Status test_bstaples_string_init_c_string_returns_hi(char* buffer, int length);
Status test_bstaples_string_init_c_string_hello_size_returns_5(char* buffer, int length);
Status test_bstaples_string_compare_returns_0(char* buffer, int length);
Status test_bstaples_string_compare_returns_correct_lexographic_values(char* buffer, int length);
Status test_bstaples_my_string_extraction_and_my_string_insertion_check_file(char* buffer, int length);
Status test_bstaples_string_push_back_returns_abc(char* buffer, int length);
Status test_bstaples_string_pop_back_returns_ab(char* buffer, int length);
Status test_bstaples_my_string_at_returns_w(char* buffer, int length);
Status test_bstaples_my_string_push_back_works_with_100_letters(char* buffer, int length);
Status test_bstaples_my_string_pop_back_returns_10_letters(char* buffer, int length);
Status test_bstaples_my_string_c_str_returns_hello(char* buffer, int length);
Status test_bstaples_my_string_push_back_c_str_returns_abcdefgh(char* buffer, int length);
Status test_bstaples_my_string_concat_returns_HelloWorld(char* buffer, int length);
Status test_bstaples_my_string_push_and_concat_returns_BinaryTree(char* buffer, int length);
Status test_bstaples_my_string_empty_after_push_returns_false(char* buffer, int length);
Status test_bstaples_my_string_empty_after_pops_returns_true(char* buffer, int length);
Status test_bstaples_my_string_pop_on_empty_returns_failure(char* buffer, int length);
Status test_bstaples_my_string_c_str_overwrites_null_after_push(char* buffer, int length);
Status test_bstaples_my_string_concat_empty_strings_returns_empty_string(char* buffer, int length);
Status test_bstaples_my_string_concat_resizes_correctly(char* buffer, int length);
Status test_bstaples_my_string_at_returns_b_at_index_5(char* buffer, int length);
Status test_bstaples_my_string_push_back_resizes_correctly(char* buffer, int length);

#endif
