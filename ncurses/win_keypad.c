#include<stdio.h>
#include<ncurses.h>

#define WIDTH 30
#define HEIGHT 10

int startx = 0;
int starty = 0;

char *choices[] = {
	"Choice 1",
	"Choice 2",
	"Choice 3",
	"Choice 4",
	"Exit    ",
	};
int n_choices = sizeof(choices)/sizeof(char *);;
void print_menu(WINDOW *menu_win,int highlight);

int main()
{
 WINDOW *menu_win;
 int highlight = 1;
 int choice = 0;
 int line;
 int c;

 initscr();
 clear();
 noecho();
 cbreak();
 startx = (80 - WIDTH)/2;
 starty = (24 - HEIGHT)/2;
 
 menu_win = newwin(HEIGHT, WIDTH, starty, startx);
 keypad(menu_win, TRUE);
 mvprintw(0, 0, "Use arrow keys to go up and down,Press enter to select a choice");
 refresh();
 print_menu(menu_win, highlight);
 while(1)
 {
 c = wgetch(menu_win);
 switch(c)
 {
/*向上键，如果已经到顶了，则从底部开始循环，否则一直往上走*/
 case KEY_UP:
	if(highlight == 1)
		highlight = n_choices;
	else
		--highlight;
	break;
/*向下键，如果已经到底了，则从顶部开始循环，否则一直往下走*/
 case KEY_DOWN:
	if(highlight == n_choices)
		highlight = 1;
	else
		++highlight;
 	break;
 //case 101:  case值取为101值，即键盘按下101键时，才会退出程序
 case 10:
	choice = highlight;
	break;
 default:
    line = highlight;
    mvprintw(22, 0, "You chose choice %d with choice string %s", line, choices[line - 1]);
    mvprintw(23, 0,"Character pressed is = %3d Hopefully it can be printed as '%c'", c, c);//放在这个地方，是为了实时刷新
    //mvprintw(22, 0, "You chose choice %d with choice string %s", highlight, choices[highlight - 1]);
	refresh();
	break;
 }

 print_menu(menu_win, highlight);
 if(choice != 0)
	break;/*按了Enter键之后退出程序*/
 
 }
 
 clrtoeol();
 refresh();
 endwin();
 return 0;
}

void print_menu(WINDOW *menu_win, int  highlight)
{
 int x,y,i;
 x = 2;
 y = 2;
 box(menu_win, 0, 0);
 for(i = 0;i < n_choices; ++i)
 {
 /*highlight初始化为1,所以会将第一行高亮打印，后续的
 * 行正常打印出来，每打印一行，y的值会自动加1,使得choices数组的
 * 打印信息按行打印出来*/
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
