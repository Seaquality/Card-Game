struct Attribute {
	char name[25];
	int value;
};

struct Card{
	struct Attribute attribute;
};

struct Player {
	struct Card deck[10];
	int deckSize;
	char type[25]; 
	char name[25];
};

void getString(char *prompt, char *result);
void shuffle(struct Card deck[10]);
void generateDeck(struct Card deck[10]);
void printDeck(struct Card deck[10], int deckSize);
int findCard(struct Player *player, char *chosen);
void removeCard(struct Player *player, char *name);
void flipCard(struct Card *card, char *playerName);
int pickRandom(struct Player *player);
void line();