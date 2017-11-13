#include<ncurses.h>

int main()
{
 initscr();
 printw("Hello World!!!");
 printw("The second line.");
 refresh();
 getchar();
 endwin();
 return 0;
}
