
#include "unity.h"
#include "board_utils.h"
#include <string.h>
#include <stdlib.h> 

// Hack: Include the dependency source to define global lookup tables 
// that are needed by the macros but not linked by default in isolated testing.
// Alternative: Mock the array, but it's constant data.
#include "binary_tools.c"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_square_enum_integrity(void) {
    TEST_ASSERT_EQUAL_INT(0, A8);
    TEST_ASSERT_EQUAL_INT(7, H8);
    TEST_ASSERT_EQUAL_INT(56, A1);
    TEST_ASSERT_EQUAL_INT(63, H1);
}

void test_rank_masks(void) {
    TEST_ASSERT_EQUAL_HEX64(0x00000000000000FF, RANK_8);
    TEST_ASSERT_EQUAL_HEX64(0xFF00000000000000, RANK_1);
}

void test_file_masks(void) {
    U64 expected_file_a = 0ULL;
    expected_file_a |= (1ULL << A8);
    expected_file_a |= (1ULL << A7);
    expected_file_a |= (1ULL << A6);
    expected_file_a |= (1ULL << A5);
    expected_file_a |= (1ULL << A4);
    expected_file_a |= (1ULL << A3);
    expected_file_a |= (1ULL << A2);
    expected_file_a |= (1ULL << A1);
    
    TEST_ASSERT_EQUAL_HEX64(expected_file_a, FILE_A);
}

void test_macros_hit_rank_file(void) {
    U64 pos = 0ULL;
    SET_BIT_ON_BITBOARD(pos, A8); 
    
    TEST_ASSERT_TRUE(BIT_ON_BITBOARD_HIT_8_RANK(pos));
    TEST_ASSERT_TRUE(BIT_ON_BITBOARD_HIT_A_FILE(pos));
    TEST_ASSERT_FALSE(BIT_ON_BITBOARD_HIT_1_RANK(pos));
    TEST_ASSERT_FALSE(BIT_ON_BITBOARD_HIT_H_FILE(pos));

    U64 pos2 = 0ULL;
    SET_BIT_ON_BITBOARD(pos2, G2);
    TEST_ASSERT_TRUE(BIT_ON_BITBOARD_HIT_2_RANK(pos2));
    TEST_ASSERT_TRUE(BIT_ON_BITBOARD_HIT_G_FILE(pos2));
}

void test_square_to_string_conversion(void) {
    TEST_ASSERT_EQUAL_STRING("a8", square_to_string[A8]);
    TEST_ASSERT_EQUAL_STRING("h8", square_to_string[H8]);
    TEST_ASSERT_EQUAL_STRING("e4", square_to_string[E4]);
    TEST_ASSERT_EQUAL_STRING("a1", square_to_string[A1]);
    TEST_ASSERT_EQUAL_STRING("h1", square_to_string[H1]);
}

void test_print_bitboard(void) {
    U64 pos = 0ULL;
    SET_BIT_ON_BITBOARD(pos, A8);
    SET_BIT_ON_BITBOARD(pos, H1);

    char* output = print_bitboard_on_chess_board(pos);
    
    TEST_ASSERT_NOT_NULL(output);
    TEST_ASSERT_NOT_EQUAL(NULL, strstr(output, "1"));
}
