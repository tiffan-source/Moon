
#include "board_utils.h"

const char* square_to_string[64] = {
    "a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8",
    "a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7",
    "a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6",
    "a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5",
    "a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4",
    "a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3",
    "a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2",
    "a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1"
};

/**
 * @brief  Visualise un bitboard sous forme de grille texte.
 * @param  position Le U64 bitboard à afficher.
 * @return char* Pointeur vers un buffer statique contenant la représentation.
 */
char* print_bitboard_on_chess_board(Bitboard position) {
    // Buffer assez grand pour :  
    // 8 rangées * (8 caractères + espaces +  newline) + bordures + null terminator
    // Disons ~256 bytes par sécurité.
    static char buffer[512]; 
    int buffer_pos = 0;
    
    // Reset buffer
    buffer[0] = '\0';

    buffer_pos += sprintf(buffer + buffer_pos, "\n");

    // L'ordre de l'énumération Square est A8(0)..H8(7)...H1(63).
    // Cela correspond à un balayage de gauche à droite, haut en bas.
    // C'est parfait pour l'affichage.
    for (int rank = 0; rank < 8; rank++) {
        // Afficher numéro de rang (8, 7...)
        buffer_pos += sprintf(buffer + buffer_pos, "%d  ", 8 - rank);
        
        for (int file = 0; file < 8; file++) {
            // Calculer l'index du carré (0..63)
            int square_index = rank * 8 + file;
            
            // Vérifier si le bit est set à cet index
            int bit = GET_BIT(position, square_index);
            
            buffer_pos += sprintf(buffer + buffer_pos, "%d ", bit);
        }
        buffer_pos += sprintf(buffer + buffer_pos, "\n");
    }

    buffer_pos += sprintf(buffer + buffer_pos, "\n   a b c d e f g h\n");
    
    return buffer;
}

