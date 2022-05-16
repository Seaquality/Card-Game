#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "playervalues.h"

void line() {
	printf("____________________________________________________________________\n");
}

void getString(char *prompt, char *result) {
	printf("%s", prompt);
	gets(result);
}

int findCard(struct Player *player, char *chosen) {
	for(int i = 0; i < player->deckSize; ++i) {
		if(!strcmp(player->deck[i].attribute.name, chosen)) {
			return i;
		}
	}

	return -1;
}

void flipCard(struct Card *card, char *playerName) {
	printf("In %s's deck, %s is flipped and its value is: \t%d\n\n", playerName, card->attribute.name, card->attribute.value);
}

void removeCard(struct Player *player, char *name) {
	int ind = findCard(player->deck, name);
	for(; ind < player->deckSize; ++ind) {
		player->deck[ind] = player->deck[ind + 1];
	}
	--player->deckSize;
}

void generateDeck(struct Card deck[10]) {
	int values[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	for(int i = 0; i < 9; ++i) {
		int randIndex = i+rand()%(9-i);
		int temp = values[i];
		values[i] = values[randIndex];
		values[randIndex] = temp;
	}

	char names[][50] = {"Dragon", "Zombie", "Gorgoyle", "Demon", "Angel", "Skeleton", "Reaper", "Troll", "Knight", "Warlock"};
	for(int i = 0; i < 9; ++i) {
		int randIndex = i+rand()%(9-i);
		char temp[50];
		strcpy(temp, names[i]);
		strcpy(names[i], names[randIndex]);
		strcpy(names[randIndex], temp);
	}

	for(int i = 0; i < 10; ++i) {
		deck[i].attribute.value = values[i];
		strcpy(deck[i].attribute.name, names[i]);
	}
}

void printDeck(struct Card deck[10], int deckSize) {
	for(int i = 0; i < deckSize; ++i)
		printf("%s ", deck[i].attribute.name);
	printf("\n");
}

int pickRandom(struct Player *player) {
	return rand() % player->deckSize;
}