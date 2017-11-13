#include<ncurses.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
 int ch, prev;
 FILE *fp; /*Get the file*/
 int goto_prev = FALSE, y, x;
 if(argc != 2)
 {
 printf("Usage:%s<a c file name>\n", argv[0]);
 exit(1);
 }
 fp = fopen(argv[1], "r");
 if(fp == NULL)
 {
 perror("Cannot open input file.");
 exit(1);
 }
 initscr();
 prev = EOF;
 while((ch = fgetc(fp))!= EOF)
 {
 if(prev == '/' && ch == '*')
 {
 attron(A_BOLD);/*Attributes the contents*/
 goto_prev = TRUE;
 }
 if(goto_prev == TRUE)
 {
 getyx(stdscr, y, x);
 move(y, x - 1);
 printw("%c%c", '/', ch);
 ch = 'a';
 goto_prev = FALSE;
 }
 else printw("%c", ch);
// chgat(-3,A_STANDOUT,0,NULL);
 refresh();
 if(prev == '*' && ch == '/')
    attroff(A_BOLD);
 prev = ch;
 }
 getch();
 endwin();
 return 0;
}
