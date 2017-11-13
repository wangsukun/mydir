#include<ncurses.h>
#include<stdlib.h>
#include<string.h>
#define WIDTH 30
#define HEIGHT 10

int startx = 0;
int starty = 0;

char *choices[] = {
	"Choice 1",
	"Choice 2",
	"Choice 3",
	"Choice 4",
	"Exit",};

int n_choices = sizeof(choices)/sizeof(char *);

void print_menu(WINDOW *menu_win,int highlight);
void report_choice(int mouse_x,int mouse_y,int *p_choice);

int main()
{
 int c, choice = 0;
 int* choice_point;
 WINDOW *menu_win;
 MEVENT event;

 initscr();
 clear();
 noecho();
 cbreak();

 startx = (80 - WIDTH)/2;
 starty = (24 - HEIGHT)/2;

 attron(A_REVERSE);
 mvprintw(23, 1, "Click on Exit to quit(Works best in a virtual console)");
 refresh();
 attroff(A_REVERSE);

 menu_win = newwin(HEIGHT, WIDTH, starty, startx);
 print_menu(menu_win, 1);
keypad(menu_win, TRUE);//少了该项将分不清键盘和鼠标的敲击
mousemask(BUTTON1_CLICKED | BUTTON2_CLICKED, 0);

 while(1)
 {
 c = wgetch(menu_win);
 switch(c)
 {
 case KEY_MOUSE:
 if(getmouse(&event) == OK)
 {
    //mvprintw(1, 1, "Y:  %d  X:%d \n", event.y, event.x);
	if(BUTTON1_DOUBLE_CLICKED)
	{
    int beginx,beginy,exity;
    beginx = startx + 2;
    beginy = starty + 2;
    exity = beginy + n_choices - 1;
	//report_choice(event.x,event.y, choice_point);
	if((event.y == exity)&&(event.x>=beginx)&&(event.x<= beginx + strlen(choices[n_choices - 1])))
        {
        endwin();
        return 0;
        }
    else if((event.y>= beginy) && (event.y < exity)&&(event.x>=beginx)&&(event.x<= beginx + strlen(choices[event.y - beginy])))     
	mvprintw(22, 1, "Choice made is: %d String Chosen is \"%10s\"",event.y - beginy,choices[event.y - beginy]);
    else
    //wprintw(menu_win, "Y: %d  X:%d ", event.y, event.x);
    mvprintw(22, 1, "Y: %d  X:%d                                                       ", event.y, event.x);
	refresh();
 	}
    break;
 }
 case 'q':
   {
    endwin();
    return 0;
   }
 default:
	wprintw(menu_win, "Key = %d\n", c);
 print_menu(menu_win, choice);
 }
 }
 endwin();
 return 0;
}

void print_menu(WINDOW *menu_win,int highlight)
{
 int x,y,i;

 x = 2;
 y = 2;
 box(menu_win, 0, 0);
 for(i = 0;i < n_choices; ++i)
 {
  if(highlight == i + 1)
  {
  wattron(menu_win, A_REVERSE);
  mvwprintw(menu_win, y, x, "%s", choices[i]);
  wattroff(menu_win, A_REVERSE);
  }
  else
	mvwprintw(menu_win, y, x, "%s", choices[i]);
  ++y;
 }
 wrefresh(menu_win);
}

/*void report_choice(int mouse_x,int mouse_y,int *p_choice)
{
 int i,j,choice;
 
 i = startx + 2;
 j = starty + 2 + n_choices - 1;

  if((mouse_y == j ) && (mouse_x >= i) && (mouse_x <= i + strlen(choices[choice])))
	*p_choice = -1;
  
}
*/
