#pragma once
// Number of cards in play
int cardsPlayed = 0;
bool gamePlaying = 0;
bool playerTurn = 1;
// Player win state can be in 5 positions
// 0: Lost
// 1: Bust
// 2: Win
// 3: Draw
// 4: No positions
int playerWinState = 4;
bool debugMode = 0;
// Builds a card object
struct card {
    char suit;
    char rank[3];
    int value;
};
// Builds a player's hand object
struct player_hand {
    int size;
    int value;
};
// Builds a dealer's hand object
struct dealer_hand {
    int size;
    int value;
};
// Declears functions
void new_deck(card(&cards)[52]);
void shuffle(card cards[], int n);
void draw_card(card playerCards[], card cards[], player_hand& p_hand);
void dealer_draw(card dealerCards[], card cards[], dealer_hand& d_hand);
void draw_screen(card dealerCards[], dealer_hand d_hand, player_hand p_hand, card playerCards[], float pot, float balence, card cards[]);
void win_check(player_hand p_hand, dealer_hand d_hand);
void gameend_check(player_hand p_hand, dealer_hand d_hand);
void ace_rule(card playerCards[], player_hand& p_hand, card dealerCards[], dealer_hand& d_hand);