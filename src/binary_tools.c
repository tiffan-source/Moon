
#include "binary_tools.h"

// Lookup table simple pour 1ULL << index
const U64 pre_calculated_bit_shifts[64] = {
    0x1ULL, 0x2ULL, 0x4ULL, 0x8ULL, 0x10ULL, 0x20ULL, 0x40ULL, 0x80ULL,
    0x100ULL, 0x200ULL, 0x400ULL, 0x800ULL, 0x1000ULL, 0x2000ULL, 0x4000ULL, 0x8000ULL,
    0x10000ULL, 0x20000ULL, 0x40000ULL, 0x80000ULL, 0x100000ULL, 0x200000ULL, 0x400000ULL, 0x800000ULL,
    0x1000000ULL, 0x2000000ULL, 0x4000000ULL, 0x8000000ULL, 0x10000000ULL, 0x20000000ULL, 0x40000000ULL, 0x80000000ULL,
    0x100000000ULL, 0x200000000ULL, 0x400000000ULL, 0x800000000ULL, 0x1000000000ULL, 0x2000000000ULL, 0x4000000000ULL, 0x8000000000ULL,
    0x10000000000ULL, 0x20000000000ULL, 0x40000000000ULL, 0x80000000000ULL, 0x100000000000ULL, 0x200000000000ULL, 0x400000000000ULL, 0x800000000000ULL,
    0x1000000000000ULL, 0x2000000000000ULL, 0x4000000000000ULL, 0x8000000000000ULL, 0x10000000000000ULL, 0x20000000000000ULL, 0x40000000000000ULL, 0x80000000000000ULL,
    0x100000000000000ULL, 0x200000000000000ULL, 0x400000000000000ULL, 0x800000000000000ULL, 0x1000000000000000ULL, 0x2000000000000000ULL, 0x4000000000000000ULL, 0x8000000000000000ULL
};

const U64 pre_calculated_relevant_bits_minus_64[64] = {
    64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49,
    48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33,
    32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17,
    16, 15, 14, 13, 12, 11, 10,  9,  8,  7,  6,  5,  4,  3,  2,  1
};

/**
 * @brief Génère un nombre pseudo-aléatoire sur 64 bits.
 * @details Utilise rand() (généralement 15-31 bits) plusieurs fois pour remplir 64 bits.
 * Ce n'est pas cryptographiquement sûr, mais suffisant pour les hashs Zobrist ou les magic bitboards.
 */
U64 random_U64() {
    U64 n1 = (U64)(rand()) & 0xFFFF;
    U64 n2 = (U64)(rand()) & 0xFFFF;
    U64 n3 = (U64)(rand()) & 0xFFFF;
    U64 n4 = (U64)(rand()) & 0xFFFF;
    return n1 | (n2 << 16) | (n3 << 32) | (n4 << 48);
}

/**
 * @brief Crée une représentation textuelle (Hex) d'un U64.
 * @note Utilise un buffer statique. Pas thread-safe, mais évite malloc.
 */
char* string_representation_of_U64(U64 value) {
    static char buffer[32];
    sprintf(buffer, "0x%llX", value);
    return buffer;
}
