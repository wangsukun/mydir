#include<ncurses.h>

int main()
{
 int c,quit=1;
 initscr();
 clear();
 noecho();
 cbreak();
 keypad(stdscr, TRUE);
 printw("Hello World!!!\n");
 refresh();
 while(quit)
 {
 c = getch();
 switch(c)
 {
 case 10:
   quit = 0;
   break;
 }
 }
 def_prog_mode();
 endwin();
 system("/bin/sh");
 quit = 1;
 while(quit)
 {
 c = getch();
 switch(c)
 {
 case 10:
   quit = 0;
   break;
 }
 }
 reset_prog_mode();
 refresh();
 printw("Another String\n");
 refresh();
 quit = 1;
 while(quit)
 {
 c = getch();
 switch(c)
 {
 case 10:
  quit = 0;
  break;
 }
 }
 endwin();
 return 0;
}
