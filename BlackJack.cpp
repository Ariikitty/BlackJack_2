#include <iostream>

struct card {
    char suit;
    int value;
};

void new_deck(card* cards);
void shuffle(card cards[], int n);

int main()
{
    // Array from 0 to 51 
    card cards[52];

    new_deck(*cards);
    shuffle(cards, 52);

    // Printing all shuffled elements of cards 
    for (int i = 0; i < 52; i++)
        std::cout << &cards[i] << " ";
    std::cout << std::endl;

    return 0;
}

void shuffle(card cards[], int n)
{
    // Initialize seed randomly 
    srand(time(0));

    for (int i = 0; i < n; i++)
    {
        // Random for remaining positions. 
        int r = i + (rand() % (52 - i));

        std::swap(cards[i], cards[r]);
    }
}

void new_deck(card *cards) {
    for (int i = 0; i < 13; i++)
    {
        cards[i].suit = 'S';
    }
    for (int i = 0; i < 13; i++)
    {
        cards[i].suit = 'H';
    }
    for (int i = 0; i < 13; i++)
    {
        cards[i].suit = 'C';
    }
    for (int i = 0; i < 13; i++)
    {
        cards[i].suit = 'D';
    }
}