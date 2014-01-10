#include <ncurses.h>
#include <time.h>
#include <stdlib.h>

struct snake
{
	int x;
	int y;
	struct snake *next;
} *snk, *temp, *prev;

int main()
{	
	int ch;
	char body = '=';
	int MaxX, MaxY;
	int curx, cury, oldx, oldy, randX, randY;
	randX = randY = -1;

	int FOOD = 0;
	int GAME = 1;
	int snk_len = 1;
	snk = (struct snake *)malloc(sizeof(struct snake));
	snk->next = NULL;

	initscr();			/* Start curses mode 		*/
	curs_set(0);
	raw();				/* Line buffering disabled	*/
	noecho();			/* Don't echo() while we do getch */

	keypad(stdscr, TRUE);		/* We get F1, F2 etc..		*/

	getmaxyx(stdscr, MaxX, MaxY);	
	curx = MaxX/2;
	cury = MaxY/2-6;
	//curx = 10;
	//cury = 10;
	snk->x = curx;
	snk->y = cury;
    	mvprintw(curx, cury, "%c",body);

	while(1)
	{
		ch = wgetch(stdscr);
		oldx = snk->x;
		oldy = snk->y;
		switch(ch)
		{
			case KEY_UP:
					temp = snk;
					prev = NULL;
					while(temp->next)
					{
						temp->x = temp->next->x;
						temp->y = temp->next->y;

						prev = temp;
						temp = temp->next;
					}

					if ( temp->x > 0 )
					{
//						if (!prev || (prev->x != temp->x-1 && prev->y != temp->y))
//						{
							curx--;
							temp->x = temp->x - 1;
//						}
					}
					else
						GAME = 0;
				        break;
			case KEY_DOWN:
					temp = snk;
					prev = NULL;
					while(temp->next)
					{
						temp->x = temp->next->x;
						temp->y = temp->next->y;

						prev = temp;
						temp = temp->next;
					}

					if ( temp->x < MaxX-1 )
					{
//						if (!prev || (prev->x != temp->x+1 && prev->y != temp->y))
//						{
							curx++;
							temp->x = temp->x + 1;
//						}
					}
					else
						GAME = 0;
					break;
			case KEY_RIGHT:
					temp = snk;
					prev = NULL;
					while(temp->next)
					{
						temp->x = temp->next->x;
						temp->y = temp->next->y;

						prev = temp;
						temp = temp->next;
					}

					if ( temp->y < MaxY-1 )
					{
//						if (!prev || (prev->y != temp->y+1 && prev->x != temp->x))
//						{
							cury++;
							temp->y = temp->y + 1;	
//						}
					}
					else
						GAME = 0;
					break;
			case KEY_LEFT:
					temp = snk;
					prev = NULL;
					while(temp->next)
					{
						temp->x = temp->next->x;
						temp->y = temp->next->y;

						prev = temp;
						temp = temp->next;
					}

					if ( temp->y > 0 )
					{
//						if (!prev || (prev->y != temp->y+1 && prev->x != temp->x))
//						{
							cury--;
							temp->y = temp->y - 1;
//						}
					}
					else
						GAME = 0;
					break;
			default:	
					break;
		}
		if ( ch == 'Q' || ch == 'q' )
			break;

		temp = snk;
		while(temp->next)
		{
			if ( temp->x == curx && temp->y == cury )
			{
				GAME = 0;
				break;
			}
			temp = temp->next;
		}

		if ( GAME == 0 )
		{
			start_color();
			init_pair(1, COLOR_RED, COLOR_BLACK);
			attron(COLOR_PAIR(1));

			mvprintw(MaxX/2, MaxY/2-6, "GAME OVER");
			while(1)
			{
				ch = wgetch(stdscr);
				if ( ch == 'q' || ch == 'Q' )
					break;
			}
			break;
		}

		mvprintw(oldx, oldy, " ");

		temp = snk;
		while(temp)
		{
			mvprintw(temp->x, temp->y, "=");
			temp = temp->next;
		}

		if ( curx == randX && cury == randY )
		{
			snk_len++;
			temp = (struct snake *)malloc(sizeof(struct snake));
			temp->x = oldx;
			temp->y = oldy;
			temp->next = snk;
			snk = temp;

			FOOD = 0;
		}

		if (!FOOD)
		{
			srand ( time(NULL) );
			randX = rand()%MaxX;
			srand ( time(NULL) );
			randY = rand()%MaxY;
			mvprintw(randX, randY, "$");

			FOOD = 1;
		}
	}

	refresh();			/* Print it on to the real screen */
	endwin();			/* End curses mode		  */

	while(snk)
	{
		temp = snk;
		snk = snk->next;
		temp->next = NULL;
		free(temp);
	}

	return 0;
}
