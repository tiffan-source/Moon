
#ifndef BINARY_TOOLS_H
#define BINARY_TOOLS_H

#include "std_lib.h"

// --- Macro Definitions for Bit Manipulation ---
// Operations bit à bit fondamentales pour les bitboards.
// U64 est un entier 64 bits (unsigned long long).

// Définir le bit à l'index donné (le mettre à 1)
#define SET_BIT(bitboard, index)    ((bitboard) |= (1ULL << (index)))

// Obtenir la valeur du bit à l'index donné (0 ou 1)
#define GET_BIT(bitboard, index)    (((bitboard) >> (index)) & 1ULL)

// Supprimer le bit à l'index donné (le mettre à 0)
// Utilise un masque inversé (~) pour conserver tous les bits sauf celui ciblé.
#define POP_BIT(bitboard, index)    ((bitboard) &= ~(1ULL << (index)))

// Calculer l'index du bit de poids faible (Least Significant Bit)
// __builtin_ctzll : Count Trailing Zeros (GCC intrinsic). 
// Retourne -1 si la valeur est 0 (gestion d'erreur basique).
#define GET_LSB_INDEX(value) ((value) ? __builtin_ctzll(value) : -1)

// Compter le nombre de bits à 1
#define COUNT_BITS_SET(v) ((int)__builtin_popcountll((unsigned long long)(v)))

#define RANDOM_U64_FEWBITS() (random_U64() & random_U64() & random_U64())

#define HASH_FUNCTION_FOR_INDEXING_U64_CONFIGURATION(blocker_configuration, magic_number, relevant_bits) \
    ((((blocker_configuration) * (magic_number)) >> pre_calculated_relevant_bits_minus_64[relevant_bits]))

typedef unsigned long long int U64;

// Tableaux de recherche pré-calculés pour la performance (Lookup Tables)
extern const U64 pre_calculated_bit_shifts[64];
extern const U64 pre_calculated_relevant_bits_minus_64[64];

char* string_representation_of_U64(U64 value);
U64 random_U64();

#endif // BINARY_TOOLS_H
