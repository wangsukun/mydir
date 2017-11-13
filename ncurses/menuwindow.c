#include<menu.h>
#define ARRAY_SIZE(a)(sizeof(a)/sizeof(a[0]))
#define CTRLD 4
#include<stdlib.h>
#include<string.h>

char *choices[] = {
	"Choice 1",
	"Choice 2",
	"Choice 3",
	"Choice 4",
	"Exit",
	(char *)NULL,
	};

void print_in_middle(WINDOW *win,int starty,int startx,int width,char *string,chtype color);

int main()
{
 ITEM **my_items;
 int c;
 MENU *my_menu;
 WINDOW *my_menu_win;
 int n_choices,i;

 initscr();
 start_color();
 cbreak();
 noecho();
 keypad(stdscr, TRUE);
 init_pair(1, COLOR_RED, COLOR_BLACK);

 n_choices = ARRAY_SIZE(choices);
 my_items = (ITEM **)calloc(n_choices, sizeof(ITEM*));
 for(i = 0;i < n_choices; ++i)
	//my_items[i] = new_item(choices[i], choices[i]);
	my_items[i] = new_item(choices[i], choices[i]);

 my_menu = new_menu((ITEM **)my_items);

 my_menu_win = newwin(10, 40, 4, 4);
 keypad(my_menu_win, TRUE);
 set_menu_win(my_menu, my_menu_win);
 set_menu_sub(my_menu, derwin(my_menu_win, 6, 38, 3, 1));

 set_menu_mark(my_menu, "*");

 box(my_menu_win, 0, 0);
 print_in_middle(my_menu_win, 1, 0, 40, "My Menu", COLOR_PAIR(1));
 mvwaddch(my_menu_win, 2, 0, ACS_LTEE);
 mvwhline(my_menu_win, 2, 1, ACS_HLINE, 38);
 mvwaddch(my_menu_win, 2, 39, ACS_RTEE);
 mvprintw(LINES - 2, 0, "F1 to Exit");
 refresh();

 post_menu(my_menu);
 wrefresh(my_menu_win);

 while((c = wgetch(my_menu_win)) != KEY_F(1))
 {
 switch(c)
 {
 case KEY_DOWN:
 menu_driver(my_menu, REQ_DOWN_ITEM);
 break;
 case KEY_UP:
 menu_driver(my_menu, REQ_UP_ITEM);
 break;
 }
 wrefresh(my_menu_win);
 }

 unpost_menu(my_menu);
 free_menu(my_menu);
 for(i = 0; i < n_choices; ++ i)
  free_item(my_items[i]);
 endwin();
}

void print_in_middle(WINDOW *win,int starty,int startx,int width,char *string,chtype color)
{
 int length, x, y;
 float temp;
 if(win == NULL)
	win = stdscr;
 getyx(win, y, x);
 if(startx != 0)
	x = startx;
 if(starty != 0)
	y = starty;
 if(width == 0)
	width = 80;

 length = strlen(string);
 temp = (width - length)/2;
 x = startx + (int)temp;
 wattron(win, color);
 mvwprintw(win, y, x, "%s", string);
 wattroff(win, color);
 refresh();
}
