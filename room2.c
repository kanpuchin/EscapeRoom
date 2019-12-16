#include "room.h"
#include "chat.h"

#define WIDTH	80
#define HEIGHT	40

#define LEFT_END	0
#define RIGHT_END	80
#define UP_END		0
#define DOWN_END	40

int keys[3] = {-1, -1, -1};
int doors[3] = {-1, -1, -1};
int final = -1;
int open = -1;
int player_row=UP_END+1, player_col=LEFT_END+1;
char player = 'o';
char player2;
char c;
int A_Hints[3] = {8, 5, 3};
int B_Hints[3] = {12, 9, 15};
void set_player_2(char p){
	player2 = p;
}

void level_2_map() { // 레벨 디자인
	int col, row; // col : 가로 ,  row : 세로
	draw_level_window();
	for(row = 1; row < 10; row++){
		col = 9;
		move(row, col);
		addch('|');
	}
	
	for(col = 9; col < 71; col++){
		row = 10;
		move(row, col);
		addch('-');
	}

	for(col = 1; col < 28; col++){
		row = 15;
		move(row, col);
		addch('-');
	}

	for(row = 16; row < DOWN_END; row++){
		col = 48;
		move(row, col);
		addch('|');
	}

	for(row = 35; row < DOWN_END; row++){
		col = 27;
		move(row, col);	addch('|');
	}
	for(row = 16; row < 29; row++){
		col = 27;
		move(row, col);
		addch('|');
	}

	for(col = 48; col < 51; col++) { // rom1
		row = 15;
		move(row, col); addch('-');
	}

	for(row = 16; row < 21; row++){ // rom1
		col = 50;
		move(row, col);	 addch('|');
	}
	for(col = 51; col < 71; col++){ // rom1
		row = 21;
		move(row, col);	addch('-');
	}
	for(col = 4; col < 28; col++){ // rom2
		row = 29;
		move(row,col);	addch('-');
		row = 34;
		move(row,col);	addch('-');
	}


	for(row = 30; row < 34; row++){ // rom2
		col = 4;
		move(row, col); addch('|');
	}

	for(row = 11; row < 21; row++){ // rom1
		col = 70;
		move(row, col);
		addch('|');
	}
	
	for(col = 1; col < 9; col++){ // door1
		row = 9;
		if(doors[0] == -1){
		move(row, col);
		if(col % 2 != 0) addch('(');
		else addch(')');
		}
		else addch(' ');
	}

	for(row = 11; row < 15; row++){ // door2
		col = 48;
		if(doors[1] == -1){
		move(row, col);
		addstr("()");
		}
		else addch(' ');
	}

	for(row = 30; row < 34; row++){ // door3
		col = 26;
		if(doors[2] == -1){
		move(row, col);
		addstr("()");
		}
		else addstr("  ");
	}

	if(keys[0] == -1){
	move(13, 3);
	addstr("[h]"); // door1 chest
	}

	if(keys[1] == -1){
	move(19, 65);	addstr("[h]");
	} // door2 chest

	if(keys[2] == -1){
	move(32,6); addstr("[h]");
	} // door3 chest

	
	if(keys[0] == 0 && keys[1] == 0 && keys[2] == 0) open = 0;
	if(open == 0) {
		if(final == 0){
			for(col = 28; col < 48; col++){	
				row = DOWN_END; move(row, col);
				addch(' ');
			}
		}
		else{
			for(col = 28; col < 48; col++){
				row = DOWN_END; move(row, col);
				if(col % 2 == 0) addch('(');
				else addch(')');
			}
		}
		move(39,49); addstr("next");
	}
	refresh();
}

void wrong_answer(){
	clear();
	draw_level_window();
	move(20, 20);
	addstr("Please try again");
	move(22, 20);
	addstr("Press any key to continue game");
	c = getch();

}

void correct_open_door(){
	clear();
	draw_level_window();
	move(20,20);
	addstr("The door is open");
	move(22,20);
	addstr("Press any key to continue game");
	c = getch();

}

void correct_hint(){
	clear();
	draw_level_window();
	move(20,20);
	addstr("The chest is open");
	move(22,20);
	addstr("Press any key to continue game");
	c = getch();
}

int Lv2_door1(){
	int row = 22, select = 1;
	clear();
	draw_level_window();

	move(15, 20);
	addstr("Identify whether the proposition is true or false.");
	move(19, 20);
	addstr("If you use a pipe, pipe[1] is fd of the writing end.");
	move(22, 20);	addstr("1) True");
	move(23, 20);	addstr("2) False");

	move(row, 17);	addstr(">>");
	refresh();
	
	while((c = getch()) != ' '){
		if(c == 'w' && row == 23){
			move(row, 17);
			addstr("  ");
			row--;
			move(row, 17);
			addstr(">>");
			select = 1;
			refresh();
		}else if(c == 's' && row == 22){
			move(row, 17);
			addstr("  ");
			row++;
			move(row, 17);
			addstr(">>");
			select = 2;
			refresh();
		}
	}
	
	switch(select){
		case 1:
			doors[0] = 0;
			correct_open_door();
			clear();
			return 0;
		case 2:
			wrong_answer();
			clear();
			return -1;
	}
}

int Lv2_door2(){
	int select = 2;
	char answer[15];
	clear();
	draw_level_window();
	echo();
	move(15, 15);
	addstr("What commands should be used to create a child process?");
	move(17, 15);
	addstr("Please enter a valid command.");
	move(20, 15);
	addstr("A : "); getstr(answer);
	noecho();

	if(strcmp(answer, "fork") != 0) select = 2;
	else select = 1;

	switch(select){
		case 1:
			doors[1] = 0;
			correct_open_door();
			clear();
			return 0;
		case 2:
			wrong_answer();
			clear();
			return -1;
	}
}

int Lv2_door3(){
	int row = 23, select = 1;
	clear();
	draw_level_window();

	move(15, 20);
	addstr("Identify whether the proposition is true or false.");
	move(19, 20);
	addstr("You don't have to pclose");
	move(20, 20);
	addstr("even if you use the popen command.");
	move(23, 20);	addstr("1) True");
	move(24, 20);	addstr("2) False");

	move(row, 17);	addstr(">>");
	refresh();
	
	while((c = getch()) != ' '){
		if(c == 'w' && row == 24){
			move(row, 17);
			addstr("  ");
			row--;
			move(row, 17);
			addstr(">>");
			select = 1;
			refresh();
		}else if(c == 's' && row == 23){
			move(row, 17);
			addstr("  ");
			row++;
			move(row, 17);
			addstr(">>");
			select = 2;
			refresh();
		}
	}
	
	switch(select){
		case 2:
			doors[2] = 0;
			correct_open_door();
			clear();
			return 0;
		case 1:
			wrong_answer();
			clear();
			return -1;
	}
}

int Lv2_chest1(){
	clear();
	draw_level_window();

	move(5,10); addstr("1. Who ate secretly?");
	move(8,10); addstr("A : B ate.");
	move(9,10); addstr("B : D ate it.");
	move(10,10); addstr("C : I didn't eat.");
	move(11,10); addstr("D : B is lying.");

	move(13,10); addstr("If only one word is true and the other three are lying, who ate?");
	move(14,10); addstr("Please enter the correct number.");

	move(17, 10);	addstr("1) A");
	move(18, 10);	addstr("2) B");
	move(19, 10);	addstr("3) C");
	move(20, 10);	addstr("4) D");

	
	if((c = getch()) == '3'){ // 정답
		keys[0] = 0;
		if(player2 == 'S'){
		correct_hint();
		clear();
		}
		else if(player2 == 'A'){
		clear();
		draw_level_window();
		move(15,20); printw("Your partner's 'hint 1' is %d", B_Hints[0]);
		c = getch();
		clear();
		}
		else if(player2 == 'B'){
		clear();
		draw_level_window();
		move(15,20); printw("Your partner's 'hint 1' is %d", A_Hints[0]);
		c = getch();
		clear();
		}
		return 0;
	}
	else{
		wrong_answer();
		clear();
		return -1;
	}
	
}

int Lv2_chest2(){
	clear();
	draw_level_window();

	move(5,3); addstr("Which is the advantage?");
	move(8,3); addstr("Two companies published job advertisements.");
	move(9,3); addstr("If all the conditions except for the following two are exactly the same,");
	move(10,3); addstr("which company would be an advantage based on revenue?");
	move(11,3); addstr("Please enter the correct number.");

	move(15, 3); addstr("1) Company A : Salary 10 million won. Raise 2 million won per year.");
	move(16, 3); addstr("2) Company B : 5 million won in half a year."); 
	move(17, 18); addstr("Raise 0.5 million won every six months.");


	if((c = getch()) == '2'){ // 정답
		keys[1] = 0;
		if(player2 == 'S'){
		correct_hint();
		clear();
		}
		else if(player2 == 'A'){
		clear();
		draw_level_window();
		move(15,20); printw("Your partner's 'hint 2' is %d", B_Hints[1]);
		c = getch();
		clear();
		}
		else if(player2 == 'B'){
		clear();
		draw_level_window();
		move(15,20); printw("Your partner's 'hint 2' is %d", A_Hints[1]);
		c = getch();
		clear();
		}
		return 0;
	}
	else{
		wrong_answer();
		clear();
		return -1;
	}
}

int Lv2_chest3(){
	int select=2;
	char answer[15];
	memset(answer, '\0', sizeof(answer));
	clear();
	draw_level_window();
	echo();
	move(5,4); addstr("The fertility of mice is awesome.");
	move(6,4); addstr("The mice are born once a month and have 12 pups at a time.");
	move(7,4); addstr("In addition, a born child is born from two months after birth.");

	move(9,4); addstr("If you started raising just one born mouse,");
	move(10,4); addstr("how many are there in 10 months?");

	move(12,4); addstr("A : "); getstr(answer);
	
	noecho();
	if(strcmp(answer, "1") == 0) select = 1;
	else select = 2;

	switch(select){
		case 1:
			keys[2] = 0;
		if(player2 == 'S'){
		correct_hint();
		clear();
		}
		else if(player2 == 'A'){
		clear();
		draw_level_window();
		move(15,20); printw("Your partner's 'hint 3' is %d", B_Hints[2]);
		c = getch();
		clear();
		}
		else if(player2 == 'B'){
		clear();
		draw_level_window();
		move(15,20); printw("Your partner's 'hint 3' is %d", A_Hints[2]);
		c = getch();
		clear();
		}
			return 0;
		case 2:
			wrong_answer();
			clear();
			return -1;
	}
}
int Lv2_door4(){
	int select = 2, calc;
	char answer[15];
	memset(answer, '\0', sizeof(answer));
	clear();
	draw_level_window();
	echo();
	if(player2 == 'S'){
	move(15, 15);
	addstr("There is a circular analog clock with hour and minute hands.");
	move(17, 15);
	addstr("How many times does the long hand surpass the short hand");
	move(18, 15); 
	addstr("exactly at 12 o'clock exactly 12 hours after 12 o'clock?");
	move(19, 15);
	addstr("Of course, it is assumed that the watch is operating normally.");

	move(21, 15);
	addstr("A : "); getstr(answer);

	noecho();
	if(strcmp(answer, "10") != 0) select = 2;
	else select = 1;


	}
	else if(player2 == 'A'){
		clear();
		draw_level_window();
		move(20, 20);
		addstr("Calculate the following formula:");
		move(22, 20);
		addstr(" (Hint1 + Hint3) * Hint2 ");
		calc = ( A_Hints[0] + A_Hints[2] ) * A_Hints[1];
		move(24, 20); addstr("A : "); getstr(answer);
		noecho();
		if(atoi(answer) == calc) select = 1;
		else select = 2;
	}
	else if(player2 == 'B'){
		clear();
		draw_level_window();
		move(20, 20);
		addstr("Calculate the following formula:");
		move(22, 20);
		addstr(" (Hint2 + Hint3) * Hint1 ");
		calc = ( B_Hints[1] + B_Hints[2] ) * B_Hints[0];
		move(24, 20); addstr("A : "); getstr(answer);
		noecho();
		if(atoi(answer) == calc) select = 1;
		else select = 2;
	}
		switch(select){
		case 1:
			final = 0;
			correct_open_door();
			clear();
			return 0;
		case 2:
			wrong_answer();
			clear();
			return -1;
		}
}
void level_2(){
	int test;

	set_player_2('S');
	level_2_map();
	refresh();
	
	move(player_row, player_col);
	addch(player);
	while(c = getch()){
		refresh();
		level_2_map();
		if(c == 'q'){
			endwin();
			execlp("./escape", "./escpae", NULL);			
		}
		if(c == 'a'){ // 왼쪽 이동
				move(player_row, player_col); addch(' ');
				player_col--;
				move(player_row, player_col);
				if(inch() == '|' || inch() == '-'){ // 벽 충돌
					player_col++;
					move(player_row, player_col); addch('o');
				}
				else if(inch() == '(' || inch() == ')'){ // door3 충돌
					if((c = getch()) == ' '){
						test = Lv2_door3();

						if(test == -1){
						player_col++;
						move(player_row, player_col); addch('o');
						}
					}
					else player_col++;
				}
			else if(inch() == '[' || inch() == 'h' || inch() == ']'){
				if((c = getch()) == ' '){			
					if(player_row == 13)	test = Lv2_chest1();
					else if(player_row == 19) test = Lv2_chest2();
					else test = Lv2_chest3();

					if(test == -1){ 
					player_col++; move(player_row, player_col);
					addch('o');
					}
				}
				else player_col++;
			}
				else addch('o');
		}
		else if(c == 's'){ // 아래쪽 이동
			move(player_row, player_col); addch(' ');
			player_row++;
			move(player_row, player_col);
			if(inch() == '|' || inch() == '-'){ // 벽 충돌
				player_row--;
				move(player_row, player_col);	addch('o');
			}
			else if(inch() == '(' || inch() == ')'){
				if((c = getch()) == ' '){
					if(player_row != DOWN_END){ // door1 충돌
						test = Lv2_door1();
						
						if(test == -1){ 
						player_row--; move(player_row, player_col);
						addch('o');
						}
					}
					else{ // final 충돌
						test = Lv2_door4();
						if(test == -1){
						player_row--; move(player_row, player_col);
						addch('o');
						}
					}
				}
				else player_row--;
			}
			else if(inch() == '[' || inch() == 'h' || inch() == ']'){
				if((c = getch()) == ' '){			
					if(player_row == 13)	test = Lv2_chest1();
					else if(player_row == 19) test = Lv2_chest2();
					else test = Lv2_chest3();

					if(test == -1){ 
					player_col++; move(player_row, player_col);
					addch('o');
					}
				}
				else player_row--;
			}
			else if(player_row > DOWN_END){ // go next level
				clear();
				draw_level_window();
				level_3();
			}
				else addch('o');
		}
		else if(c == 'd'){ // 오른쪽 이동
			move(player_row, player_col); addch(' ');
			player_col++;
			move(player_row, player_col);
			if(inch() == '|' || inch() == '-'){ // 벽 충돌
				player_col--;
				move(player_row, player_col);	addch(player);
			}
			else if(inch() == '(' || inch() == ')'){ // door2 충돌
				if( (c = getch()) == ' '){
				test = Lv2_door2();
					
				if(test == -1){ 
				player_col--; move(player_row, player_col);
				addch('o');
					}
				}
				else player_col--;
			}
			else if(inch() == '[' || inch() == 'h' || inch() == ']'){
				if((c = getch()) == ' '){			
					if(player_row == 13)	test = Lv2_chest1();
					else if(player_row == 19) test = Lv2_chest2();
					else test = Lv2_chest3();

					if(test == -1){ 
					player_col++; move(player_row, player_col);
					addch('o');
					}
				}
				else player_col--;
			}
				else addch('o');
		}
		else if(c == 'w'){
			move(player_row, player_col); addch(' ');
			player_row -= 1; move(player_row, player_col);
			if(inch() == '|' || inch() == '-') {
				player_row++;
				move(player_row, player_col); addch(player);
			}
			else if(inch() == '[' || inch() == 'h' || inch() == ']'){
				if((c = getch()) == ' '){			
					if(player_row == 13)	test = Lv2_chest1();
					else if(player_row == 19) test = Lv2_chest2();
					else test = Lv2_chest3();

					if(test == -1){ 
					player_col++; move(player_row, player_col);
					addch('o');
					}
				}
				else player_row++;
			}
			else addch('o');
		}
		level_2_map();
		move(player_row, player_col); addch('o');
		refresh(); // while문 끝
	}
}

void level_2_A(char* hostname, int portnum){
	int test;

	set_player_2('A');
	level_2_map();
	refresh();
	
	move(player_row, player_col);
	addch(player);
	while(c = getch()){
		refresh();
		level_2_map();
		if(c == 'q'){
			endwin();
			execlp("./escape", "./escpae", NULL);			
		}
		if(c == 'a'){ // 왼쪽 이동
				move(player_row, player_col); addch(' ');
				player_col--;
				move(player_row, player_col);
				if(inch() == '|' || inch() == '-'){ // 벽 충돌
					player_col++;
					move(player_row, player_col); addch('o');
				}
				else if(inch() == '(' || inch() == ')'){ // door3 충돌
					if((c = getch()) == ' '){
						test = Lv2_door3();

						if(test == -1){
						player_col++;
						move(player_row, player_col); addch('o');
						}
					}
					else player_col++;
				}
			else if(inch() == '[' || inch() == 'h' || inch() == ']'){
				if((c = getch()) == ' '){			
					if(player_row == 13)	test = Lv2_chest1();
					else if(player_row == 19) test = Lv2_chest2();
					else test = Lv2_chest3();

					if(test == -1){ 
					player_col++; move(player_row, player_col);
					addch('o');
					}
				}
				else player_col++;
			}
				else addch('o');
		}
		else if(c == 's'){ // 아래쪽 이동
			move(player_row, player_col); addch(' ');
			player_row++;
			move(player_row, player_col);
			if(inch() == '|' || inch() == '-'){ // 벽 충돌
				player_row--;
				move(player_row, player_col);	addch('o');
			}
			else if(inch() == '(' || inch() == ')'){
				if((c = getch()) == ' '){
					if(player_row != DOWN_END){ // door1 충돌
						test = Lv2_door1();
						
						if(test == -1){ 
						player_row--; move(player_row, player_col);
						addch('o');
						}
					}
					else{ // final 충돌
						test = Lv2_door4();
						if(test == -1){
						player_row--; move(player_row, player_col);
						addch('o');
						}
					}
				}
				else player_row--;
			}
			else if(inch() == '[' || inch() == 'h' || inch() == ']'){
				if((c = getch()) == ' '){			
					if(player_row == 13)	test = Lv2_chest1();
					else if(player_row == 19) test = Lv2_chest2();
					else test = Lv2_chest3();

					if(test == -1){ 
					player_col++; move(player_row, player_col);
					addch('o');
					}
				}
				else player_row--;
			}
			else if(player_row > DOWN_END){ // go next level
				clear();
				draw_level_window();
				level_3_A(hostname, portnum);
			}
				else addch('o');
		}
		else if(c == 'd'){ // 오른쪽 이동
			move(player_row, player_col); addch(' ');
			player_col++;
			move(player_row, player_col);
			if(inch() == '|' || inch() == '-'){ // 벽 충돌
				player_col--;
				move(player_row, player_col);	addch(player);
			}
			else if(inch() == '(' || inch() == ')'){ // door2 충돌
				if( (c = getch()) == ' '){
				test = Lv2_door2();
					
				if(test == -1){ 
				player_col--; move(player_row, player_col);
				addch('o');
					}
				}
				else player_col--;
			}
			else if(inch() == '[' || inch() == 'h' || inch() == ']'){
				if((c = getch()) == ' '){			
					if(player_row == 13)	test = Lv2_chest1();
					else if(player_row == 19) test = Lv2_chest2();
					else test = Lv2_chest3();

					if(test == -1){ 
					player_col++; move(player_row, player_col);
					addch('o');
					}
				}
				else player_col--;
			}
				else addch('o');
		}
		else if(c == 'w'){
			move(player_row, player_col); addch(' ');
			player_row -= 1; move(player_row, player_col);
			if(inch() == '|' || inch() == '-') {
				player_row++;
				move(player_row, player_col); addch(player);
			}
			else if(inch() == '[' || inch() == 'h' || inch() == ']'){
				if((c = getch()) == ' '){			
					if(player_row == 13)	test = Lv2_chest1();
					else if(player_row == 19) test = Lv2_chest2();
					else test = Lv2_chest3();

					if(test == -1){ 
					player_col++; move(player_row, player_col);
					addch('o');
					}
				}
				else player_row++;
			}
			else addch('o');
		}

		if(c=='c'){ //chatting
			chatting(hostname, portnum);
		}

		level_2_map();
		move(player_row, player_col); addch('o');
		refresh(); // while문 끝
	}
}


void level_2_B(char* hostname, int portnum){
	int test;

	set_player_2('B');
	level_2_map();
	refresh();
	
	move(player_row, player_col);
	addch(player);
	while(c = getch()){
		refresh();
		level_2_map();
		if(c == 'q'){
			endwin();
			execlp("./escape", "./escpae", NULL);			
		}
		if(c == 'a'){ // 왼쪽 이동
				move(player_row, player_col); addch(' ');
				player_col--;
				move(player_row, player_col);
				if(inch() == '|' || inch() == '-'){ // 벽 충돌
					player_col++;
					move(player_row, player_col); addch('o');
				}
				else if(inch() == '(' || inch() == ')'){ // door3 충돌
					if((c = getch()) == ' '){
						test = Lv2_door3();

						if(test == -1){
						player_col++;
						move(player_row, player_col); addch('o');
						}
					}
					else player_col++;
				}
			else if(inch() == '[' || inch() == 'h' || inch() == ']'){
				if((c = getch()) == ' '){			
					if(player_row == 13)	test = Lv2_chest1();
					else if(player_row == 19) test = Lv2_chest2();
					else test = Lv2_chest3();

					if(test == -1){ 
					player_col++; move(player_row, player_col);
					addch('o');
					}
				}
				else player_col++;
			}
				else addch('o');
		}
		else if(c == 's'){ // 아래쪽 이동
			move(player_row, player_col); addch(' ');
			player_row++;
			move(player_row, player_col);
			if(inch() == '|' || inch() == '-'){ // 벽 충돌
				player_row--;
				move(player_row, player_col);	addch('o');
			}
			else if(inch() == '(' || inch() == ')'){
				if((c = getch()) == ' '){
					if(player_row != DOWN_END){ // door1 충돌
						test = Lv2_door1();
						
						if(test == -1){ 
						player_row--; move(player_row, player_col);
						addch('o');
						}
					}
					else{ // final 충돌
						test = Lv2_door4();
						if(test == -1){
						player_row--; move(player_row, player_col);
						addch('o');
						}
					}
				}
				else player_row--;
			}
			else if(inch() == '[' || inch() == 'h' || inch() == ']'){
				if((c = getch()) == ' '){			
					if(player_row == 13)	test = Lv2_chest1();
					else if(player_row == 19) test = Lv2_chest2();
					else test = Lv2_chest3();

					if(test == -1){ 
					player_col++; move(player_row, player_col);
					addch('o');
					}
				}
				else player_row--;
			}
			else if(player_row > DOWN_END){ // go next level
				clear();
				draw_level_window();
				level_3_B(hostname, portnum);
			}
				else addch('o');
		}
		else if(c == 'd'){ // 오른쪽 이동
			move(player_row, player_col); addch(' ');
			player_col++;
			move(player_row, player_col);
			if(inch() == '|' || inch() == '-'){ // 벽 충돌
				player_col--;
				move(player_row, player_col);	addch(player);
			}
			else if(inch() == '(' || inch() == ')'){ // door2 충돌
				if( (c = getch()) == ' '){
				test = Lv2_door2();
					
				if(test == -1){ 
				player_col--; move(player_row, player_col);
				addch('o');
					}
				}
				else player_col--;
			}
			else if(inch() == '[' || inch() == 'h' || inch() == ']'){
				if((c = getch()) == ' '){			
					if(player_row == 13)	test = Lv2_chest1();
					else if(player_row == 19) test = Lv2_chest2();
					else test = Lv2_chest3();

					if(test == -1){ 
					player_col++; move(player_row, player_col);
					addch('o');
					}
				}
				else player_col--;
			}
				else addch('o');
		}
		else if(c == 'w'){
			move(player_row, player_col); addch(' ');
			player_row -= 1; move(player_row, player_col);
			if(inch() == '|' || inch() == '-') {
				player_row++;
				move(player_row, player_col); addch(player);
			}
			else if(inch() == '[' || inch() == 'h' || inch() == ']'){
				if((c = getch()) == ' '){			
					if(player_row == 13)	test = Lv2_chest1();
					else if(player_row == 19) test = Lv2_chest2();
					else test = Lv2_chest3();

					if(test == -1){ 
					player_col++; move(player_row, player_col);
					addch('o');
					}
				}
				else player_row++;
			}
			else addch('o');
		}

		if(c=='c'){ //chatting
			chatting(hostname, portnum);
		}

		level_2_map();
		move(player_row, player_col); addch('o');
		refresh(); // while문 끝
	}
}
