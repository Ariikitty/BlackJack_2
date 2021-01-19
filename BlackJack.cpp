#include <iostream>
// Number of cards in play
int cardsPlayed = 0;
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
// Declears functions
void new_deck(card(&cards)[52]);
void shuffle(card cards[], int n);
void draw_card(card playerCards[], card cards[], player_hand p_hand);
// Main code execution
int main()
{
    srand(time(0));

    // Array from 0 to 51 
    card cards[52];
    card playerCards[5]{ 0 };

    player_hand p_hand;

    new_deck(cards);
    shuffle(cards, 52);
    draw_card(playerCards, cards, p_hand);

    // Printing all shuffled elements of cards 
    for (int i = 0; i < 52; i++)
        std::cout << cards[i].rank << cards[i].suit << cards[i].value  << " ";
    std::cout << std::endl;

    std::cout << playerCards[0].rank << playerCards[0].suit << std::endl;

    return 0;
}
// Shuffle deck function
void shuffle(card cards[], int n)
{
    // Initialize seed randomly 
    for (int i = 0; i < n; i++)
    {
        // Random for remaining positions. 
        int r = i + (rand() % (52 - i));

        std::swap(cards[i], cards[r]);
    }
}
// Build deck function
void new_deck(card(&cards)[52]) {
    int i = 0;
    int n = 0;
    // Assigns suit and value
    for (; i < 13; i++)
    {
        cards[i].suit = 'S';
        cards[i].value = i % 13 + 1;
        if (cards[i].value > 10) {
            cards[i].value = 10;
        }
    }
    for (; i < 26; i++)
    {
        cards[i].suit = 'H';
        cards[i].value = i % 13 + 1;
        if (cards[i].value > 10) {
            cards[i].value = 10;
        }
    }
    for (; i < 39; i++)
    {
        cards[i].suit = 'C';
        cards[i].value = i % 13 + 1;
        if (cards[i].value > 10) {
            cards[i].value = 10;
        }
    }
    for (; i < 52; i++)
    {
        cards[i].suit = 'D';
        cards[i].value = i % 13 + 1;
        if (cards[i].value > 10) {
            cards[i].value = 10;
        }
    }
    // Assigns rank
    for (int x = 0; x < 4; x++) {
        i = 0;
        for (i = 0; i < 13; i++)
        {
            switch (i) {
            case 0:
                strcpy_s(cards[n].rank, 3, "A");
                break;
            case 1:
                strcpy_s(cards[n].rank, 3, "2");
                break;
            case 2:
                strcpy_s(cards[n].rank, 3, "3");
                break;
            case 3:
                strcpy_s(cards[n].rank, 3, "4");
                break;
            case 4:
                strcpy_s(cards[n].rank, 3, "5");
                break;
            case 5:
                strcpy_s(cards[n].rank, 3, "6");
                break;
            case 6:
                strcpy_s(cards[n].rank, 3, "7");
                break;
            case 7:
                strcpy_s(cards[n].rank, 3, "8");
                break;
            case 8:
                strcpy_s(cards[n].rank, 3, "9");
                break;
            case 9:
                strcpy_s(cards[n].rank, 3, "10");
                break;
            case 10:
                strcpy_s(cards[n].rank, 3, "J");
                break;
            case 11:
                strcpy_s(cards[n].rank, 3, "Q");
                break;
            case 12:
                strcpy_s(cards[n].rank, 3, "K");
                break;
            }
            n += 1;
        }
    }
}

void draw_card(card playerCards[], card cards[], player_hand p_hand)
{
    playerCards[p_hand.size] = cards[cardsPlayed];
    p_hand.size += 1;
    cardsPlayed += 1;
}