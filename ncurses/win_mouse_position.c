#include<ncurses.h>
#include<unistd.h>

int main(void)
{
 int key;
 int quit = 0;
 MEVENT event;

 initscr();
 raw();
 keypad(stdscr, TRUE);
 mousemask(BUTTON1_CLICKED | BUTTON2_CLICKED, 0);

 while(!quit)
 {
 key = getch();
 switch(key)
 {
 case KEY_MOUSE:
 getmouse(&event);
 printw("Y:%d X:%d\n", event.y, event.x);
 refresh();
 break;
 case 'q':
 quit = 1;
 break;
 default:
 printw("Key = %d\n", key);
 }
 }
 endwin();
 return 0;
}
