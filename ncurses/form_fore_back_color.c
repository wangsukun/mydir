#include<form.h>
#include<curses.h>
#include<stdlib.h>
#include<string.h>

int main()
{
 FIELD *field[3];
 FORM *my_form;
 int ch;

 initscr();
 start_color();
 cbreak();
 noecho();
 keypad(stdscr, TRUE);

 init_pair(1, COLOR_WHITE, COLOR_BLUE);
 init_pair(2, COLOR_WHITE, COLOR_BLACK);

 field[0] = new_field(1, 10, 4, 18, 0, 0);
 field[1] = new_field(1, 10, 6, 18, 0, 0);
 field[2] = NULL;

 set_field_fore(field[0], COLOR_PAIR(1));
 set_field_back(field[0], COLOR_PAIR(2));
 field_opts_off(field[0], O_AUTOSKIP);

 set_field_back(field[1], A_UNDERLINE);
 field_opts_off(field[1], O_AUTOSKIP);

 my_form = new_form(field);
 post_form(my_form);
 refresh();

 set_current_field(my_form, field[0]);
 mvprintw(4, 10, "Value 1:");
 mvprintw(6, 10, "Value 2:");
 mvprintw(LINES - 2, 0, "Use UP, DOWN arrow keys to switch between fields");
 refresh();

 while((ch = getch()) != KEY_F(1))
 {
 switch(ch)
 {
 case KEY_DOWN:
 form_driver(my_form, REQ_NEXT_FIELD);
 form_driver(my_form, REQ_END_LINE);
 break;
 case KEY_UP:
 form_driver(my_form, REQ_PREV_FIELD);
 form_driver(my_form, REQ_END_LINE);
 break;
 default:
 form_driver(my_form, ch);
 break;
 }
 }
 unpost_form(my_form);
 free_form(my_form);
 free_field(field[0]);
 free_field(field[1]);
 endwin();
 return 0;
}
