# Moon
An chess engine

## Architecture Techniques
### Binary Tools & Bitboards
Le module `binary_tools` fournit l'infrastructure fondamentale pour la représentation de l'échiquier sous forme de **Bitboards**.

**Théorie :**
Un échiquier 8x8 contient 64 cases. Un entier non signé de 64 bits (`U64`) est parfait pour représenter un ensemble de cases (par exemple, toutes les cases occupées par des pions blancs). Cette approche permet de réaliser des opérations sur tout le plateau en une seule instruction CPU (bitwise AND, OR, XOR).

**Fonctionnalités Clés :**

- **Type U64** : Alias pour `unsigned long long`.
- **Manipulations** : Macros `SET_BIT`, `GET_BIT`, `POP_BIT` pour une performance maximale (inlining).
- **Optimisations** :
  - `pre_calculated_bit_shifts` : Table de correspondance pour éviter de recalculer `1ULL << index` répétitivement.
### Board Utils & Coordinate System
Le module `board_utils` fournit les outils pour se repérer sur l'échiquier et visualiser les données.

**Système de Coordonnées (Mapping) :**
- **Orientation** : L'indexation suit une logique de lecture "Occidentale" (Haut-Gauche vers Bas-Droite).
    - **Index 0 (LSB)** : Case **A8**.
    - **Index 63 (MSB)** : Case **H1**.
- **Conséquence** :
    - `RANK_8` correspond aux bits de poids faible (0-7).
    - `RANK_1` correspond aux bits de poids fort (56-63).
    - Cela simplifie l'affichage (boucle simple 0..63) mais diffère du standard "LERF" (Little-Endian Rank-File où A1=0).

**Fonctionnalités :**
- **Enum Square** : Constantes `A8`...`H1` pour la lisibilité.
- **Visualisation** : `print_bitboard_on_chess_board` génère une grille ASCII instantanée d'un `U64`.
- **Masques** : `RANK_X` et `FILE_Y` pour les opérations sur des rangées/colonnes entières.
