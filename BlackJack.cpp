#include <iostream>
#include <iomanip>
#include <Windows.h>
#include "BlackJack.h"
// Main code execution
int main()
{
    // Set's the seed
    srand(time(0));
    // Array from 0 to 51 
    card cards[52];
    card playerCards[5]{ 0 };
    card dealerCards[5]{ 0 };
    // Initialises the hand structs
    player_hand p_hand{ 0, 0 };
    dealer_hand d_hand{ 0, 0 };
    //Start's game
    int choice = 0;
    float balence = 500;
    do {
        system("cls");
        std::cout << "Blackjack 21" << std::endl;
        std::cout << "------------" << std::endl;
        std::cout << "Your balence is " << balence << std::endl;
        if (balence < 1)
        {
            std::cout << "You are out of money. Thanks for playing!" << std::endl;
            Sleep(2000);
            return 0;
        }
        std::cout << std::endl;
        std::cout << "1: Quit game" << std::endl;
        std::cout << "2: Play game" << std::endl;
        std::cout << "3: How to play" << std::endl;
        std::cout << std::endl;
        std::cout << "What would you like to do (Please enter a number): ";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            std::cout << "Goodbye" << std::endl;
            return 0;
        case 2:
            // Game code here please
            float bet;
            float pot;
            system("cls");
            std::cout << "How much would you like to bet? ";
            std::cin >> bet;
            balence -= bet;
            pot = bet * 2;
            new_deck(cards);
            shuffle(cards, 52);
            for (int i = 0; i < 2; i++) {
                draw_card(playerCards, cards, p_hand);
                dealer_draw(dealerCards, cards, d_hand);
            }
            draw_screen(dealerCards, d_hand, p_hand, playerCards, pot, balence);
            Sleep(10000);
            break;
        case 3:
            // How to play here
            break;
        default:
            // There is a bug here if the user enters a letter, this will just loop. I'm not sure what causes it or how to fix it :c
            system("cls");
            std::cout << "You have entered an invalid option.\nPlease enter a number between 1 and 3!" << std::endl;
            std::cout << std::endl;
            Sleep(2000);
            std::cin.clear();
            choice = 0;
        }
    } while (choice != 1);
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
// Function for player draw
void draw_card(card playerCards[], card cards[], player_hand &p_hand)
{
    playerCards[p_hand.size] = cards[cardsPlayed];
    p_hand.value += playerCards[p_hand.size].value;
    p_hand.size += 1;
    cardsPlayed += 1;
}
// Function for dealer draw
void dealer_draw(card dealerCards[], card cards[], dealer_hand &d_hand)
{
    dealerCards[d_hand.size] = cards[cardsPlayed];
    d_hand.value += cards[cardsPlayed].value;
    d_hand.size += 1;
    cardsPlayed += 1;
}
// Function to draw the screen
void draw_screen(card dealerCards[], dealer_hand d_hand, player_hand p_hand, card playerCards[], float pot, float balence)
{
    system("cls");
    std::cout << std::setw(0) << "Dealer";
    for (int i = 0; i < 5; i++) 
    {
        std::cout << std::setw(2) << dealerCards[i].rank << dealerCards[i].suit;
    }
    std::cout << std::setw(7) << "Total: ??";
    std::cout << std::setw(7) << "Pot: " << pot << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::setw(6) << "You";
    for (int i = 0; i < 5; i++)
    {
        std::cout << std::setw(2) << playerCards[i].rank << playerCards[i].suit;
    }
    std::cout << std::setw(7) << "Total: " << p_hand.value;
    std::cout << std::setw(11) << "Balence: " << balence << std::endl;
}
