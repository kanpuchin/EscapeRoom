#include "room.h"
#include "chat.h"

#define WIDTH 80 
#define HEIGHT 40

#define LEFT_END 0 
#define RIGHT_END 80
#define UP_END 0
#define DOWN_END 40

int q = -1;
int door = -1;
int hint = 0;
char player;

void set_player(char p){
	player = p;
}

void draw_level_window(){
	int i;
	
	for(i=0; i<HEIGHT; i++){
		move(i,0);
		addch('|');
	}
	for(i=0; i<HEIGHT; i++){
		move(i,80);
		addch('|');
	}
	for(i=0; i<=WIDTH; i++){
		move(0,i);
		addch('-');
	}
	for(i=0; i<=WIDTH; i++){
		move(40,i);
		addch('-');
	}
	refresh();
}

void level_1_map(){
	int col, row;
	
	for(row=5; row<35; row++){
		col = 20;
		move(row, col);
		addch('|');
	}

	for(col=1; col<=20; col++){
		row = 5;
		move(row, col);
		addch('-');
	}
	
	for(col=20; col<80; col++){
		row = 35;
		move(row, col);
		addch('-');
		if(col >= 35){
			row = 30;
			move(row, col);
			addch('-');
		}
	}
	
	for(row=1; row<30; row++){
		col = 35;
		move(row, col);
		addch('|');
	}

	if(q == -1){
		row = 20;
		col = 26;	
		move(row, col);
		addch('[');
		col = 27;
		move(row, col);
		addch('h');
		col = 28;
		move(row, col);
		addch(']');
	}else{
		col = WIDTH;
		for(row = 31; row<35; row++){
			move(row,col-1); addch('(');
			move(row,col); addch(')');
		}
	}

	if(door == 1){
		col = WIDTH;
		for(row = 31; row<35; row++){
			move(row,col-1); addch(' ');
			move(row,col); addch(' ');
		}
	}

	refresh();
}
  
void level_1(){
	int col, row;
	char c;

	level_1_map();

	col = 1; row = 1;
	move(row,col);
	addch('o');
	while(1){
		c = getch();
		move(row,col);
		addch(' ');
		if(col > WIDTH){ //go next level
			erase();
			draw_level_window();
			level_2();
		}
		if(c == 'q'){
			endwin();
			execlp("./escape", "./escpae", NULL);
		}
		if(c=='w'){
			row--;
			move(row, col);
			if(inch() == '[' || inch() == 'h' || inch() == ']'){
				if((c = getch()) == ' '){
					q = Lv1_chest1();
					draw_level_window();
					level_1_map();
				}
				row++;
			}else if(inch() == '-' || inch() == '|' || row == UP_END)
				row++;
			move(row, col);

		}
		if(c=='s'){
			row++;
			move(row, col);
			if(inch() == '[' || inch() == 'h' || inch() == ']'){
				if((c = getch()) == ' '){
					q = Lv1_chest1();
					draw_level_window();
					level_1_map();
				}
				row--;
			}else if(inch() == '-' || inch() == '|' || row == DOWN_END)
				row--;
			move(row, col);
		}
		if(c=='a'){
			col--;
			move(row, col);
			if(inch() == ']'){
				if((c = getch()) == ' '){
					q = Lv1_chest1();
					draw_level_window();
					level_1_map();
				}
				col++;
			}else if(inch() == '-' || inch() == '|' || col == LEFT_END)
				col++;
			move(row, col);
		}
		if(c=='d'){
			col++;
			move(row, col);
			if(inch() == '('){
				if((c = getch()) == ' '){
					door = Lv1_door1();
					draw_level_window();
					level_1_map();
				}
				col--;
			}else if(inch() == '['){
				if((c = getch()) == ' '){
					q = Lv1_chest1();
					draw_level_window();
					level_1_map();
				}
				col--;
			}
			else if(door == 1)
				;
			else if(inch() == '-' || inch() == '|' || col == RIGHT_END)
				col--;
			move(row, col);
		}

		move(row,col);
		addch('o');
		refresh();
	} 
}

void level_1_A(char* hostname, int portnum){
	int col, row;
	char c;

	level_1_map();

	col = 1; row = 1;
	move(row,col);
	addch('o');
	while(1){
		c = getch();
		move(row,col);
		addch(' ');
		if(col > WIDTH){ //go next level
			erase();
			draw_level_window();
			level_2_A(hostname, portnum);
		}
		if(c == 'q'){
			endwin();
			execlp("./escape", "./escpae", NULL);
		}
		if(c=='w'){
			row--;
			move(row, col);
			if(inch() == '[' || inch() == 'h' || inch() == ']'){
				if((c = getch()) == ' '){
					q = Lv1_chest1();
					draw_level_window();
					level_1_map();
				}
				row++;
			}else if(inch() == '-' || inch() == '|' || row == UP_END)
				row++;
			move(row, col);

		}
		if(c=='s'){
			row++;
			move(row, col);
			if(inch() == '[' || inch() == 'h' || inch() == ']'){
				if((c = getch()) == ' '){
					q = Lv1_chest1();
					draw_level_window();
					level_1_map();
				}
				row--;
			}else if(inch() == '-' || inch() == '|' || row == DOWN_END)
				row--;
			move(row, col);
		}
		if(c=='a'){
			col--;
			move(row, col);
			if(inch() == ']'){
				if((c = getch()) == ' '){
					q = Lv1_chest1();
					draw_level_window();
					level_1_map();
				}
				col++;
			}else if(inch() == '-' || inch() == '|' || col == LEFT_END)
				col++;
			move(row, col);
		}
		if(c=='d'){
			col++;
			move(row, col);
			if(inch() == '('){
				if((c = getch()) == ' '){
					door = Lv1_door1();
					draw_level_window();
					level_1_map();
				}
				col--;
			}else if(inch() == '['){
				if((c = getch()) == ' '){
					q = Lv1_chest1();
					draw_level_window();
					level_1_map();
				}
				col--;
			}
			else if(door == 1)
				;
			else if(inch() == '-' || inch() == '|' || col == RIGHT_END)
				col--;
			move(row, col);
		}
		if(c=='c'){ //chatting
			chatting(hostname, portnum);
		}

		move(row,col);
		addch('o');
		refresh();
	} 
}

void level_1_B(char* hostname, int portnum){
	int col, row;
	char c;

	level_1_map();

	col = 1; row = 1;
	move(row,col);
	addch('o');
	while(1){
		c = getch();
		move(row,col);
		addch(' ');
		if(col > WIDTH){ //go next level
			erase();
			draw_level_window();
			level_2_B(hostname, portnum);
		}
		if(c == 'q'){
			endwin();
			execlp("./escape", "./escpae", NULL);
		}
		if(c=='w'){
			row--;
			move(row, col);
			if(inch() == '[' || inch() == 'h' || inch() == ']'){
				if((c = getch()) == ' '){
					q = Lv1_chest1();
					draw_level_window();
					level_1_map();
				}
				row++;
			}else if(inch() == '-' || inch() == '|' || row == UP_END)
				row++;
			move(row, col);

		}
		if(c=='s'){
			row++;
			move(row, col);
			if(inch() == '[' || inch() == 'h' || inch() == ']'){
				if((c = getch()) == ' '){
					q = Lv1_chest1();
					draw_level_window();
					level_1_map();
				}
				row--;
			}else if(inch() == '-' || inch() == '|' || row == DOWN_END)
				row--;
			move(row, col);
		}
		if(c=='a'){
			col--;
			move(row, col);
			if(inch() == ']'){
				if((c = getch()) == ' '){
					q = Lv1_chest1();
					draw_level_window();
					level_1_map();
				}
				col++;
			}else if(inch() == '-' || inch() == '|' || col == LEFT_END)
				col++;
			move(row, col);
		}
		if(c=='d'){
			col++;
			move(row, col);
			if(inch() == '('){
				if((c = getch()) == ' '){
					door = Lv1_door1();
					draw_level_window();
					level_1_map();
				}
				col--;
			}else if(inch() == '['){
				if((c = getch()) == ' '){
					q = Lv1_chest1();
					draw_level_window();
					level_1_map();
				}
				col--;
			}
			else if(door == 1)
				;
			else if(inch() == '-' || inch() == '|' || col == RIGHT_END)
				col--;
			move(row, col);
		}
		if(c=='c'){ //chatting
			chatting(hostname, portnum);
		}

		move(row,col);
		addch('o');
		refresh();
	} 
}

int Lv1_door1(){
	int r=22;
	char c;
	char answer[5];
	erase();
	draw_level_window();

	//퀴즈 띄우기
	move(15, 20);
	addstr("There is a lock : Three digit number");
	move(16, 20);
	addstr("(Write answer and press enter key)");

	move(20, 20);
	addstr("answer: ");
	move(20, 28);
	refresh();
	echo();
	getstr(answer);
	noecho();

	if(strcmp(answer,"639")==0 && player == 'B'){
		erase();
		move(20, 20);
		addstr("The door is open");
		move(22, 20);
		addstr("Press any key to continue game");
		c = getch();
		r = 1;
	}else if(strcmp(answer,"875")==0 && (player == 'A' || player == 'S')){
		erase();
		move(20,20);
		addstr("The door is open");
		move(22, 20);
		addstr("Press any key to continue game");
		c = getch();
		r = 1;
	}
	else{
		erase();
		move(20, 20);
		addstr("Please try again");
		move(22, 20);
		addstr("Press any key to continue game");
		c = getch();
		r = -1;
	}

	erase();
	refresh();
	
	return r;

}

int Lv1_chest1(){
	int k = 35;
	char c;
	char answer[5];

	erase();
	draw_level_window();

	move(10, 25);
	addstr("There's a hint in the chest");
	move(11, 25);
	addstr("To open the chest, find the rule");
	move(12, 25);
	addstr("and solve the problem");
	move(13, 25);
	addstr("(Enter your answer and press enter key)");
	move(15, 30);
	addstr("3 + 7 = 10");
	move(16, 30);
	addstr("9 + 4 = 1");
	move(17, 30);
	addstr("8 + 7 = 3");
	move(18, 30);
	addstr("4 + 5 = 9");
	move(19, 30);

	if(player == 'B'){ //for B
		addstr("6 + 8 = ?"); // ? = 2 -> this is answer for A
	}else{		//for A or Solo
		addstr("12 + 7 = ?");// ? = 7 -> this is answer for B or solo
	}

	if(player == 'A'){
		move(22, 20);
		addstr("What is B's answer?: ");
		move(22, 41);
	}else if(player == 'B'){
		move(22, 20);
		addstr("What is A's answer?: ");
		move(22, 41);
	}
	else if(player == 'S'){
		move(22, 30);
		addstr("answer: ");
		move(22, 38);
	}
	refresh();
	echo();
	getstr(answer);
	noecho();
	
	if(strcmp(answer, "2") == 0 && player == 'A'){
		erase();
		move(20, 20);
		addstr("The chest is open");
		move(21, 20);
		addstr("You got a note from the chest");
		move(23, 20);
		addstr("[ 111 x ??? = 76,923 ] "); //??? = 639 -> this is for B
		move(25, 20);
		addstr("Press any key to continue the game");
		hint++;
		door = 0;
		c = getch();
		k = 1;
	}else if(strcmp(answer, "7") == 0 && ((player == 'B') || (player == 'S'))){
		erase();
		move(20, 20);
		addstr("The chest is open");
		move(21, 20);
		addstr("You got a note from the chest");
		move(23, 20);
		addstr("[ 222 x ??? = 194,250 ]"); //??? = 875 -> this is for A or Solo
		move(25, 20);
		addstr("Press any key to continue the game");
		hint++;
		door = 0;
		c = getch();
		k = 1;
	}
	else{
		erase();
		move(20, 20);
		addstr("Please try again");
		move(21, 20);
		addstr("Press any key to continue the game");
		c = getch();
		k = -1;
	}

	
	erase();
	refresh();

	return k;
}
