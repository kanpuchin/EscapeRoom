#include <stdio.h>
#include <curses.h>
#include <stdlib.h>
#include "room.h"
#include "chat.h"
#include <pthread.h>

#define WIDTH 100	//col
#define HEIGHT 50	//row

void draw_window();
void draw_menu();
void remove_menu();
void choose_player();

int row, col;
char c;

int main(int argc, char* argv[]){
	pthread_t server_thread;
	int port;	
	int quit = 0;
	initscr();
	crmode();
	noecho();
	clear();

	/*initial menu*/
	draw_menu();

	while(1){
		c = getch();
		if( c==' ' ){
			if(row!=22){ //MULTI
				quit = 0;
				break;
			}
			else{ //EXIT
				quit = 1;
				break;	
			}
		}
		if(c == 'w' && row != 20){
			move(row, col);
			addch(' ');
			row--;
			move(row, col);
			addch('o');
			refresh();
		}else if(c == 's' && row != 22){
			move(row, col);
			addch(' ');
			row++;
			move(row, col);
			addch('o');
			refresh();
		}
	}
	
	if(quit==1){
		endwin();
		return 0;
	}else if(row == 20){ //solo
		erase();
		set_player('S');
		set_player_2('S');
		set_player_3('S');
		draw_level_window();
		level_1();
	}
	else if(row == 21){
		remove_menu();
		choose_player();
	
		while(1){
			c = getch();
			if(c == ' '){
				if(row == 20){ //player A
					erase();
					set_player('A');
					set_player_2('A');
					set_player_3('A');
					set_serv_player('A');
					draw_level_window();
					port = atoi(argv[3]);
					pthread_create(&server_thread, NULL, chat_serv, (void*)&port);					
					level_1_A(argv[1], atoi(argv[2]));
				}
				else if(row == 21){ //player B
					erase();
					set_player('B');
					set_player_2('B');
					set_player_3('B');
					set_serv_player('B');
					draw_level_window();
					port = atoi(argv[3]);
					pthread_create(&server_thread, NULL, chat_serv, (void*)&port);
					level_1_B(argv[1], atoi(argv[2]));
				}
			}
			else if((c == 'w' || c == 's') && row != 20){
				move(row,col); addch(' ');
				row--; move(row,col); addch('o');
				refresh();
			}
			else if((c == 'w' || c == 's') && row != 21){
				move(row,col); addch(' ');
				row++; move(row,col); addch('o');
				refresh();
			}
		}

	}
}


void draw_menu(){
	row = 17; col = 36; move(row,col);
	addstr("<ESCAPE ROOM GAME>");
	row = 20; col = 35; move(row,col);
	addstr("GAME START(SOLO)");
	row = 21; col = 35; move(row,col);
	addstr("GAME START(MULTI)");
	row = 22; col = 35; move(row, col);
	addstr("EXIT");
	row = 20; col = 33; move(row,col);
	addch('o');
	refresh();
}

void choose_player(){
	row = 17; col = 36; move(row,col);
	addstr("Choose which player you will be.");
	row = 20; col = 35; move(row,col);
	addstr("Player A");
	row = 21; col = 35; move(row,col);
	addstr("Player B");
	row = 20; col = 33; move(row,col);
	addch('o');
	refresh();
}

#define BLANK "                          "
void remove_menu(){
	row = 17; col = 31; move(row,col);
	addstr(BLANK);
	row = 20; col = 33; move(row,col);
	addstr(BLANK);
	row = 21; move(row,col);
	addstr(BLANK);
	row = 22; move(row, col);
	addstr(BLANK);
	refresh();
}
