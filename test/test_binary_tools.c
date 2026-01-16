
#include "unity.h"

#include "binary_tools.h"

#include "std_lib.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_definitions_should_be_accurate(void)
{
    TEST_ASSERT_EQUAL_UINT64(8, sizeof(U64));
}

void test_macros_BIT_SET_GET_POP(void) {
    U64 bitboard = 0ULL;

    // Test SET_BIT
    SET_BIT(bitboard, 0);
    SET_BIT(bitboard, 63);
    TEST_ASSERT_EQUAL_UINT64(0x8000000000000001ULL, bitboard);

    // Test GET_BIT
    TEST_ASSERT_EQUAL_UINT64(1, GET_BIT(bitboard, 0));
    TEST_ASSERT_EQUAL_UINT64(1, GET_BIT(bitboard, 63));
    TEST_ASSERT_EQUAL_UINT64(0, GET_BIT(bitboard, 30));

    // Test POP_BIT
    POP_BIT(bitboard, 0);
    TEST_ASSERT_EQUAL_UINT64(0x8000000000000000ULL, bitboard);
    POP_BIT(bitboard, 63);
    TEST_ASSERT_EQUAL_UINT64(0ULL, bitboard);
}

void test_GET_LSB_INDEX(void) {
    U64 val = 0x8000000000000010ULL; // Big bit at 63, small at 4
    
    int index = GET_LSB_INDEX(val);
    TEST_ASSERT_EQUAL_INT(4, index);

    // Test 0 case (should handle gracefully, usually -1 or undefined, header implementation says -1)
    TEST_ASSERT_EQUAL_INT(-1, GET_LSB_INDEX(0ULL));
}

void test_COUNT_BITS_SET(void) {
    U64 val = 0xF0F0F0F0F0F0F0F0ULL; // 4 * 8 = 32 bits
    TEST_ASSERT_EQUAL_INT(32, COUNT_BITS_SET(val));
    TEST_ASSERT_EQUAL_INT(0, COUNT_BITS_SET(0ULL));
    TEST_ASSERT_EQUAL_INT(64, COUNT_BITS_SET(~0ULL));
}

void test_pre_calculated_bit_shifts(void) {
    // Check a few values to ensure the lookup table is initialized correctly
    TEST_ASSERT_EQUAL_UINT64(1ULL, pre_calculated_bit_shifts[0]);
    TEST_ASSERT_EQUAL_UINT64(1ULL << 15, pre_calculated_bit_shifts[15]);
    TEST_ASSERT_EQUAL_UINT64(1ULL << 63, pre_calculated_bit_shifts[63]);
}

void test_random_U64_should_return_varied_values(void) {
    U64 r1 = random_U64();
    U64 r2 = random_U64();
    TEST_ASSERT_NOT_EQUAL(r1, r2); 
}

void test_string_representation_of_U64(void) {
    U64 val = 1ULL;
    char* str = string_representation_of_U64(val);
    TEST_ASSERT_NOT_NULL(str);
}
