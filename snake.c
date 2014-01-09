#include <ncurses.h>

#define HEIGHT 30 //41
#define WIDTH 40  // 144

int main()
{	
	int ch;
	char body = '=';
	int MaxX, MaxY;
	int x, y;
	x = y = 0;

	initscr();			/* Start curses mode 		*/
	curs_set(0);
	raw();				/* Line buffering disabled	*/
	noecho();			/* Don't echo() while we do getch */

	keypad(stdscr, TRUE);		/* We get F1, F2 etc..		*/

	getmaxyx(stdscr, MaxX, MaxY);
    	mvprintw(x, y, "%c",body);

	while(1)
	{
		ch = wgetch(stdscr);
		switch(ch)
		{
			case KEY_UP:  
					mvprintw(x, y, " "); 
					if ( x > 0 )
						x--;
					mvprintw(x, y, "%c",body);
				        break;
			case KEY_DOWN:
					mvprintw(x, y, " ");
					if ( x < MaxX-1 )
						x++;
					mvprintw(x, y, "%c",body);
					break;
			case KEY_RIGHT:
					mvprintw(x, y, " ");
					if ( y < MaxY-1 )
						y++;
					mvprintw(x, y, "%c",body);
					break;
			case KEY_LEFT:
					mvprintw(x, y, " ");
					if ( y > 0 )
						y--;
					mvprintw(x, y, "%c",body); 
					break;
			default:	
					mvprintw(x, y, "%c",body);
					break;
		}
		if ( ch == 'Q' || ch == 'q' )
			break;
	}

	refresh();			/* Print it on to the real screen */
	endwin();			/* End curses mode		  */

	return 0;
}
