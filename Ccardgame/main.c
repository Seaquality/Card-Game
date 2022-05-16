#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include "playervalues.h"


int main(void) {

	// set the seed for the rng
	srand(time(0));

	// setting up player of the game and asking for name
	struct Player player;
	player.deckSize = 10;
	generateDeck(player.deck);
	getString("Enter your user ID: ", player.name);

	// asking if user wants predictable or random computer
	char computerChoice[50];
	while(strcmp(computerChoice, "p") && strcmp(computerChoice, "r")) {
		line();
		getString("Input p to choose a predictable opponent or r for a random opponent: ", computerChoice);
	}

	// used for predictable computer
	char cardNames[][25] = {"Dragon", "Zombie", "Gorgoyle", "Demon", "Angel", "Skeleton", "Reaper", "Troll", "Knight", "Warlock"};

	// holds if computer will be random
	bool randomComp = !strcmp(computerChoice, "r");

	// setting up the computer
	struct Player comp;
	comp.deckSize = 10;
	generateDeck(comp.deck);
	strcpy(comp.name, "Opponent");

	int compIndex = 0;
	if(randomComp) {
		compIndex = pickRandom(&comp);
	}

	while(player.deckSize && comp.deckSize) {
		// print out the current deck
		printf("%s, this is your current deck: \n", player.name);
		printDeck(player.deck, player.deckSize);
		line();

		// ask the player what card to flip
		char chosen[50] = {};
		int ind = -1;
		while((ind = findCard(&player, chosen)) == -1) {
			printf("What card do you want to flip, %s? ", player.name);
			gets(chosen);
		}
		struct Card playerCard = player.deck[ind];

		// setting up what card the computer will pick
		if(randomComp) {
			ind = pickRandom(&comp);
		} else {
			ind = findCard(&comp, cardNames[compIndex]);
		}
		struct Card compCard = comp.deck[ind];

		line();

		// flip both cards
		flipCard(&playerCard, player.name);
		flipCard(&compCard, comp.name);

		// display who won the round
		if(playerCard.attribute.value >= compCard.attribute.value) {
			printf("%s wins the round!\n", player.name);
			printf("%s is removed from their deck\n\n", playerCard.attribute.name);
			removeCard(&player, playerCard.attribute.name);
		} else {
			printf("%s wins the round!\n", comp.name);
			printf("%s is removed from their deck\n\n", compCard.attribute.name);
			removeCard(&comp, compCard.attribute.name);
			++compIndex;
		}
	}

	// display who won the game
	if(!player.deckSize) {
		printf("%s wins the game!\n", player.name);
	} else {
		printf("%s wins the game\n", comp.name);
	}
	
	return 0;
}