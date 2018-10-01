#include <ncurses.h>
#include <stdlib.h>

typedef struct Room
{
	int xPosition;
	int yPosition;
	int height;
	int width;
	// Monster ** monsters;
	// Item ** items;
} Room;

typedef struct Player
{
	int xPosition;
	int yPosition;
	int health;
	// Room * room;
} Player;

int screenSetUp();
Room ** mapSetUp();
Player * playerSetUp();
int handleInput(int input, Player * user);
int playerMove(int y, int x, Player * user);
int checkPosition(int newY, int newX, Player * user);

/* room functions */
Room * createRoom(int x, int y, int height, int width);
int drawRoom(Room * room);

int main()
{
	Player * user;
	int ch;
	screenSetUp();

	mapSetUp();

	user = playerSetUp();

	while ((ch = getch()) != 'q')
	{
		handleInput(ch, user);
	}
	endwin();
	return 1;

}

int screenSetUp()
{
	initscr();
	printw("Hello, World!");
	noecho();
	refresh();

	return 1;
}

Room ** mapSetUp()
{
	Room ** rooms;
	rooms = malloc(sizeof(Room)*6);

	// mvprintw(13, 13, "--------");
	// mvprintw(14, 13, "|......|");
	// mvprintw(15, 13, "|......|");
	// mvprintw(16, 13, "|......|");
	// mvprintw(17, 13, "|......|");
	// mvprintw(18, 13, "--------");

	// mvprintw(2, 40, "--------");
	// mvprintw(3, 40, "|......|");
	// mvprintw(4, 40, "|......|");
	// mvprintw(5, 40, "|......|");
	// mvprintw(6, 40, "--------");
	rooms[0] = createRoom(13, 13, 6, 8);
	rooms[1] = createRoom(40, 2, 6, 8);
	rooms[2] = createRoom(40, 10, 6, 12);
	drawRoom(rooms[0]);
	drawRoom(rooms[1]);
	drawRoom(rooms[2]);

	return rooms;
}

int drawRoom(Room * room)
{
	int x;
	int y;

	/*draw top and bottom*/
	for (x = room->xPosition; x < room->xPosition + room->width; x++)
	{
		mvprintw(room->yPosition, x, "-"); /* top */
		mvprintw(room->yPosition + room->height - 1, x, "-");
	}

	/*draw floors and side walls */
	for (y = room->yPosition + 1; y < room->yPosition + room->height - 1; y++)
	{
		/*draw side walls */
		mvprintw(y, room->xPosition, "|");
		mvprintw(y, room->xPosition + room->width - 1, "|");

		/* draw floors */
		for (x = room->xPosition + 1; x < room->xPosition + room->width - 1; x++)
		{
			mvprintw(y, x, ".");
		}
	}
}


Room * createRoom(int x, int y, int height, int width)
{
	Room * newRoom;
	newRoom = malloc(sizeof(Room));

	newRoom->xPosition = x;
	newRoom->yPosition = y;
	newRoom->height = height;
	newRoom->width = width;

	return newRoom;
}

Player * playerSetUp()
{
	Player * newPlayer;
	newPlayer = malloc(sizeof(Player));

	newPlayer->xPosition = 14;
	newPlayer->yPosition = 14;
	newPlayer->health = 20;

	playerMove(14, 14, newPlayer);
	return newPlayer;
}

int handleInput(int input, Player * user)
{
	int newY;
	int newX;
	switch (input) {
		case 'w':
		case 'W':
			newY = user->yPosition - 1;
			newX = user->xPosition;
			break;
		case 'a':
		case 'A':
			newY = user->yPosition;
			newX = user->xPosition - 1;
			break;
		case 's':
		case 'S':
			newY = user->yPosition + 1;
			newX = user->xPosition;
			break;
		case 'd':
		case 'D':
			newY = user->yPosition;
			newX = user->xPosition + 1;
			break;

		defualt:
			break;
	}

	checkPosition(newY, newX, user);
}

/* check what is at next position */
int checkPosition(int newY, int newX, Player * user)
{
	int space;
	switch (mvinch(newY, newX))
	{
		case '.':
			playerMove(newY, newX, user);
			break;
		default:
			move(user->yPosition, user->xPosition);
			break;
	}
}

int playerMove(int y, int x, Player * user)
{
	mvprintw(user->yPosition, user->xPosition, ".");

	user->yPosition = y;
	user->xPosition = x;

	mvprintw(user->yPosition, user->xPosition, "@");
	move(user->yPosition, user->xPosition);
}
