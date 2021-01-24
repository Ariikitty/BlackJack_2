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
	// Initialisation of needed veriables for the menus
	int d_choice = 0;
	int choice = 0;
	float balence = 500;
	do {
		// Writes the title of the program
		system("cls");
		std::cout << "Blackjack 21" << std::endl;
		std::cout << "------------" << std::endl;
		std::cout << "Your balance is " << balence << std::endl;
		// This will check if the user has any money left. If they don't then the program will exit
		if (balence < 1)
		{
			std::cout << "You are out of money. Thanks for playing!" << std::endl;
			Sleep(2000);
			return 0;
		}
		// FIX THIS: Had to put the 4 lines here to be able to successfully restart the game. A better solution should be used if found in time. 
		card playerCards[5]{ 0 };
		card dealerCards[5]{ 0 };
		// Initialises the hand structs
		player_hand p_hand{ 0, 0 };
		dealer_hand d_hand{ 0, 0 };
		std::cout << std::endl;
		// The main menu
		std::cout << "1: Quit game" << std::endl;
		std::cout << "2: Play game" << std::endl;
		std::cout << "3: How to play" << std::endl;
		std::cout << "4: Debug mode" << std::endl;
		std::cout << std::endl;
		std::cout << "What would you like to do (Please enter a number): ";
		std::cin >> choice;
		// Switch case for the main menu choices
		switch (choice)
		{
		case 1:
			std::cout << "Goodbye" << std::endl;
			return 0;
		case 2:
			// Game code here
			gamePlaying = 1; // Set's the game playing as true
			playerTurn = 1; // Set's the player's turn to true
			// Initalises the betting system
			float bet;
			float pot;
			system("cls");
			std::cout << "How much would you like to bet? ";
			std::cin >> bet;
			balence -= bet;
			pot = bet * 2;
			playerWinState = 4;
			// Creates a new deck of cards
			new_deck(cards);
			// Shuffles the cards
			shuffle(cards, 52);
			// The first draw of two cards for both the dealer and the player
			for (int i = 0; i < 2; i++) {
				draw_card(playerCards, cards, p_hand);
				dealer_draw(dealerCards, cards, d_hand);
			}
			// Checks to see if anyone has an ace and if they do then it will convert it to an 11 unless it will cause the user to go over
			ace_rule(playerCards, p_hand, dealerCards, d_hand);
			do {
				// Asks the player if they want to hit or stick
				int choice = 0;
				// draw_screen will draw the screen with the set UI layout
				draw_screen(dealerCards, d_hand, p_hand, playerCards, pot, balence, cards);
				std::cout << std::endl;
				std::cout << "You are under by " << 21 - p_hand.value << std::endl;
				std::cout << "What would you like to do?" << std::endl;
				std::cout << "1: Hit" << std::endl;
				std::cout << "2: Stick" << std::endl;
				std::cout << "Please enter a number: ";
				std::cin >> choice;
				switch (choice)
				{
				case 1:
					// When the player wants to hit, they will draw a new card, check for aces and then checks to see if the player has won
					draw_card(playerCards, cards, p_hand);
					ace_rule(playerCards, p_hand, dealerCards, d_hand);
					win_check(p_hand, d_hand);
					break;
				case 2:
					// Ends the player's turn and starts the dealer's turn
					playerTurn = 0;
				}
			// Will keep going until the player ends their turn
			} while (playerTurn == 1);
			// His to check if the player has won or gone bust before playing
			if (playerWinState == 4) {
				// If the dealer is more then 4 away from 21 then they will keep drawing
				while (21 - d_hand.value > 4) {
					// Same as the player's just with the dealer's hand instead
					dealer_draw(dealerCards, cards, d_hand);
					ace_rule(playerCards, p_hand, dealerCards, d_hand);
					win_check(p_hand, d_hand);
				};
			}
			// Draws the screen with the UI of the game
			draw_screen(dealerCards, d_hand, p_hand, playerCards, pot, balence, cards);
			// Gameend_check is similar to win_check but is only called after the game to see who wins on value
			gameend_check(p_hand, d_hand);
			// Switch statement to decide on how the player finished the game
			switch (playerWinState)
			{
			case 0:
				// Called when the dealer scores higher then the player
				std::cout << "You lost, better luck next time!";
				break;
			case 1:
				// Called when the player goes bust
				std::cout << "You went bust, be more careful next time!";
				break;
			case 2:
				// Called when the player gets exactly 21, has 5 cards in their hand without going bust or scores higher then the dealer
				std::cout << "You won!! You got " << pot;
				balence += pot;
				break;
			case 3:
				// Called when the player and the dealer score the exact same value
				std::cout << "You both got the same value, you neither won or lost";
				balence += bet;
				break;
			}
			// Pauses on the game end screen for 5 seconds before continuing back to the menu
			Sleep(5000);
			break;
		case 3:
			// How to play here
			system("cls");
			std::cout << "Welcome to balckjack!!" << std::endl;
			std::cout << std::endl;
			Sleep(2000);
			std::cout << "How to play" << std::endl;
			std::cout << "-----------" << std::endl;
			std::cout << "This game rquires you to get a hand of 21." << std::endl;
			std::cout << "Going over 21 will cause you to bust and you will lose the round" << std::endl;
			std::cout << "If you get exactly 21 or have 5 cards in your hand without going bust then you automatically win the round" << std::endl;
			std::cout << std::endl;
			Sleep(5000);
			std::cout << "To help you get to 21, you can choose to hit or stick" << std::endl;
			std::cout << "Hitting will cause you to draw another card from the deck" << std::endl;
			std::cout << "Sticking will keep your current hand and end your turn so only do this if you think you are going to go over 21" << std::endl;
			std::cout << std::endl;
			Sleep(5000);
			std::cout << "Every card is worth their face value" << std::endl;
			std::cout << "Aces are worth either 1 or 11 depending on if you will go bust or not" << std::endl;
			std::cout << "Jacks, Queens and Kings are all worth 10 points" << std::endl;
			Sleep(10000);
			break;
		case 4:
			system("cls");
			std::cout << "Are you sure you want to turn on debug mode? (This will ruin the game)" << std::endl;
			std::cout << "1: yes" << std::endl;
			std::cout << "2: no" << std::endl;
			std::cout << std::endl;
			std::cout << "Please enter a number: ";
			std::cin >> d_choice;
			switch (d_choice)
			{
			case 1:
				debugMode = 1;
				std::cout << "Debug mode is now on. To turn it off, go back into the debug mode and choose no";
				Sleep(2000);
				break;
			case 2:
				debugMode = 0;
				std::cout << "Debug mode is now off";
				Sleep(2000);
				break;
			}
			break;
		default:
			// FIX THIS: There is a bug here if the user enters a letter, this will just loop. I'm not sure what causes it or how to fix it :c
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
void draw_card(card playerCards[], card cards[], player_hand& p_hand)
{
	if (cardsPlayed == 52)
	{
		shuffle(cards, 52);
	}
	playerCards[p_hand.size] = cards[cardsPlayed];
	p_hand.value += playerCards[p_hand.size].value;
	p_hand.size += 1;
	cardsPlayed += 1;
}
// Function for dealer draw
void dealer_draw(card dealerCards[], card cards[], dealer_hand& d_hand)
{
	if (cardsPlayed == 52)
	{
		shuffle(cards, 52);
	}
	dealerCards[d_hand.size] = cards[cardsPlayed];
	d_hand.value += cards[cardsPlayed].value;
	d_hand.size += 1;
	cardsPlayed += 1;
}
// Function to draw the screen
void draw_screen(card dealerCards[], dealer_hand d_hand, player_hand p_hand, card playerCards[], float pot, float balence, card cards[])
{
	system("cls");
	std::cout << std::setw(0) << "Dealer";
	if (playerTurn == 1 && debugMode == 0) {
		std::cout << std::setw(4) << "??";
		for (int i = 0; i < 4; i++)
		{
			std::cout << std::setw(3) << dealerCards[i + 1].rank << dealerCards[i + 1].suit;
		}
		std::cout << std::setw(7) << "Total: ??";
	}
	else {
		for (int i = 0; i < 5; i++)
		{
			std::cout << std::setw(3) << dealerCards[i].rank << dealerCards[i].suit;
		}
		std::cout << std::setw(7) << "Total: " << d_hand.value;
	}
	std::cout << std::setw(7) << "Pot: " << pot << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::setw(6) << "You";
	for (int i = 0; i < 5; i++)
	{
		std::cout << std::setw(3) << playerCards[i].rank << playerCards[i].suit;
	}
	std::cout << std::setw(8) << "Total: " << p_hand.value;
	std::cout << std::setw(12) << "Balance: " << balence << std::endl;
}

void win_check(player_hand p_hand, dealer_hand d_hand)
{
	if (p_hand.value == 21)
	{
		playerTurn = 0;
		gamePlaying = 0;
		playerWinState = 2;
	}
	else if (p_hand.value > 21) {
		playerTurn = 0;
		gamePlaying = 0;
		playerWinState = 1;
	}
	else if (p_hand.size == 5) {
		playerTurn = 0;
		gamePlaying = 0;
		playerWinState = 2;
	}
	else if (d_hand.value > 21) {
		gamePlaying = 0;
		playerWinState = 2;
	}
}

void gameend_check(player_hand p_hand, dealer_hand d_hand)
{
	if (p_hand.value < 21 && p_hand.value > d_hand.value)
	{
		gamePlaying = 0;
		playerWinState = 2;
	}
	else if (p_hand.value == d_hand.value) {
		gamePlaying = 0;
		playerWinState = 3;
	}
	else if (d_hand.value > 21) {
		gamePlaying = 0;
		playerWinState = 2;
	}
	else if (d_hand.value > p_hand.value) {
		gamePlaying = 0;
		playerWinState = 0;
	}
}

void ace_rule(card playerCards[], player_hand& p_hand, card dealerCards[], dealer_hand& d_hand)
{
	for (int i = 0; i < 5; i++)
	{
		if (playerCards[i].value == 1)
		{
			playerCards[i].value = 11;
			p_hand.value += 10;
		}
		if (p_hand.value > 21)
		{
			if (playerCards[i].value == 11)
			{
				playerCards[i].value = 1;
				p_hand.value -= 10;
			}
		}
	}
	for (int i = 0; i < 5; i++)
	{
		if (dealerCards[i].value == 1)
		{
			dealerCards[i].value = 11;
			d_hand.value += 10;
		}
		if (d_hand.value > 21)
		{
			if (dealerCards[i].value == 11)
			{
				dealerCards[i].value = 1;
				d_hand.value -= 10;
			}
		}
	}
}