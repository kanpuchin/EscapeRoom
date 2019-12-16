#include "room.h"
#include "chat.h"

#define WIDTH 80 
#define HEIGHT 40

#define LEFT_END 0 
#define RIGHT_END 80
#define UP_END 0
#define DOWN_END 40

int door3 = -1;
int q3[6] = {-1, -1, -1, -1, -1, -1};
int hint3 = 0;
char player3;

void set_player_3(char p){
	player3 = p;
}

void level_3_map(){
	int col, row;

	for(row=5; row<35; row++){
		col = 20;
		if(row < 20 || row > 25){
			move(row, col);
			addch('|');
		}
	}

	for(col=1; col<=20; col++){
		row = 5;
		move(row, col);
		addch('-');
		row = 20;
		move(row, col);
		addch('-');
		row = 25;
		move(row, col);
		addch('-');
	}

	for(col=20; col<80; col++){
		row = 35;
		move(row, col);
		addch('-');
		if(col >= 35){
			row = 5;
			move(row, col);
			addch('-');
			row = 30;
			move(row, col);
			addch('-');
		}
	}

	for(row=6; row<30; row++){
		col = 35;
		if(row < 10 || row > 15){
			move(row, col);
			addch('|');
		}
	}

	for(col=35; col<=70; col++){
		row = 10;
		move(row, col);
		addch('-');
		if(col <= 65){
			row = 15;
			move(row, col);
			addch('-');
		}
		if(col >= 65){
			row = 25;
			move(row, col);
			addch('-');
		}
	}

	for(row=11; row<25; row++){
		col = 70;
		move(row, col);
		addch('|');
		if(row > 15){
			col = 65;
			move(row, col);
			addch('|');
		}
	}

	if(q3[0] == -1){
		for(row=1; row<5; row++){
			col = 40;
			move(row, col);
			addch('(');
			col = 41;
			move(row, col);
			addch(')');
		}
	}

	if(q3[1] == -1){
		for(row=11; row<15; row++){
			col = 60;
			move(row, col);
			addch('(');
			col = 61;
			move(row, col);
			addch(')');
		}
	}

	if(q3[2] == -1){
		for(row=21; row<25; row++){
			col = 15;
			move(row, col);
			addch('(');
			col = 16;
			move(row, col);
			addch(')');
		}
	}

	if(q3[3] == -1){
		move(3, 76);
		addch('[');
		move(3, 77);
		addch('h');
		move(3, 78);
		addch(']');
	}

	if(q3[4] == -1){
		move(23, 2);
		addch('[');
		move(23, 3);
		addch('h');
		move(23, 4);
		addch(']');
	}

	if(q3[5] == -1){
		move(23, 67);
		addch('[');
		move(23, 68);
		addch('h');
		move(23, 69);
		addch(']');
	}

	if(hint3 == 3){
		move(31, 79);
		addstr("()");
		move(32, 79);
		addstr("()");
		move(33, 79);
		addstr("()");
		move(34, 79);
		addstr("()");
	}

	if(door3 == 1){
		move(31, 79);
		addstr("  ");
		move(32, 79);
		addstr("  ");
		move(33, 79);
		addstr("  ");
		move(34, 79);
		addstr("  ");
	}

	refresh();
}
  
void level_3(){
	int col, row;
	char c;

	level_3_map();

	col = 1; row = 1;
	move(row,col);
	addch('o');
	while(1){
		c = getch();
		move(row,col);
		addch(' ');
		if(col > WIDTH){
			erase();
			move(20,20);
			addstr("Congratulations! You escaped!");
			refresh();
			move(22,20);
			addstr("Press any key to return to main menu.");
			getch();
			endwin();
			execlp("./escape", "./escape", NULL);
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
					if(row == 3)
						q3[3] = Lv3_chest1();
					else if(col < 35)
						q3[4] = Lv3_chest2();
					else
						q3[5] = Lv3_chest3();
					draw_level_window();
					level_3_map();
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
					if(row == 3)
						q3[3] = Lv3_chest1();
					else if(col < 35)
						q3[4] = Lv3_chest2();
					else
						q3[5] = Lv3_chest3();
					draw_level_window();
					level_3_map();
				}
				row--;
			}else if(inch() == '-' || inch() == '|' || row == DOWN_END)
				row--;
			move(row, col);
		}
		if(c=='a'){
			col--;
			move(row, col);
			if(inch() == ')'){
				if((c = getch()) == ' '){
					q3[2] = Lv3_door3();
					draw_level_window();
					level_3_map();
				}
				col++;
			}else if(inch() == ']'){
				if((c = getch()) == ' '){
					if(row == 3)
						q3[3] = Lv3_chest1();
					else if(col < 35)
						q3[4] = Lv3_chest2();
					else
						q3[5] = Lv3_chest3();
					draw_level_window();
					level_3_map();
				}
				col++;
			}else if(inch() == '-' || inch() == '|' || col == LEFT_END)
				col++;
			move(row, col);
		}
		if(c=='d'){
			col++;
			move(row, col);
			if(inch() == '(' && row <= 5){
				if((c = getch()) == ' '){
					q3[0] = Lv3_door1();
					draw_level_window();
					level_3_map();
				}
				col--;
			}else if(inch() == '['){
				if((c = getch()) == ' '){
					if(row == 3)
						q3[3] = Lv3_chest1();
					else if(col < 35)
						q3[4] = Lv3_chest2();
					else
						q3[5] = Lv3_chest3();
					draw_level_window();
					level_3_map();
				}
				col--;
			}else if(inch() == '(' && row > 5 && row < 20){
				if((c = getch()) == ' '){
					q3[1] = Lv3_door2();
					draw_level_window();
					level_3_map();
				}
				col--;
			}else if(inch() == '(' && row > 20){
				if((c = getch()) == ' '){
					door3 = Lv3_door4();
					draw_level_window();
					level_3_map();
				}
				col--;
			}
			move(row, col);
		}

		move(row,col);
		addch('o');
		refresh();
	} 
}

void level_3_A(char* hostname, int portnum){
	int col, row;
	char c;

	level_3_map();

	col = 1; row = 1;
	move(row,col);
	addch('o');
	while(1){
		c = getch();
		move(row,col);
		addch(' ');
		if(col > WIDTH){
			erase();
			move(20,20);
			addstr("Congratulations! You escaped!");
			refresh();
			move(22,20);
			addstr("Press any key to return to main menu.");
			getch();
			endwin();
			execlp("./escape", "./escape", NULL);
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
					if(row == 3)
						q3[3] = Lv3_chest1();
					else if(col < 35)
						q3[4] = Lv3_chest2();
					else
						q3[5] = Lv3_chest3();
					draw_level_window();
					level_3_map();
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
					if(row == 3)
						q3[3] = Lv3_chest1();
					else if(col < 35)
						q3[4] = Lv3_chest2();
					else
						q3[5] = Lv3_chest3();
					draw_level_window();
					level_3_map();
				}
				row--;
			}else if(inch() == '-' || inch() == '|' || row == DOWN_END)
				row--;
			move(row, col);
		}
		if(c=='a'){
			col--;
			move(row, col);
			if(inch() == ')'){
				if((c = getch()) == ' '){
					q3[2] = Lv3_door3();
					draw_level_window();
					level_3_map();
				}
				col++;
			}else if(inch() == ']'){
				if((c = getch()) == ' '){
					if(row == 3)
						q3[3] = Lv3_chest1();
					else if(col < 35)
						q3[4] = Lv3_chest2();
					else
						q3[5] = Lv3_chest3();
					draw_level_window();
					level_3_map();
				}
				col++;
			}else if(inch() == '-' || inch() == '|' || col == LEFT_END)
				col++;
			move(row, col);
		}
		if(c=='d'){
			col++;
			move(row, col);
			if(inch() == '(' && row <= 5){
				if((c = getch()) == ' '){
					q3[0] = Lv3_door1();
					draw_level_window();
					level_3_map();
				}
				col--;
			}else if(inch() == '['){
				if((c = getch()) == ' '){
					if(row == 3)
						q3[3] = Lv3_chest1();
					else if(col < 35)
						q3[4] = Lv3_chest2();
					else
						q3[5] = Lv3_chest3();
					draw_level_window();
					level_3_map();
				}
				col--;
			}else if(inch() == '(' && row > 5 && row < 20){
				if((c = getch()) == ' '){
					q3[1] = Lv3_door2();
					draw_level_window();
					level_3_map();
				}
				col--;
			}else if(inch() == '(' && row > 20){
				if((c = getch()) == ' '){
					door3 = Lv3_door4();
					draw_level_window();
					level_3_map();
				}
				col--;
			}
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

void level_3_B(char* hostname, int portnum){
	int col, row;
	char c;

	level_3_map();

	col = 1; row = 1;
	move(row,col);
	addch('o');
	while(1){
		c = getch();
		move(row,col);
		addch(' ');
		if(col > WIDTH){
			erase();
			move(20,20);
			addstr("Congratulations! You escaped!");
			refresh();
			move(22,20);
			addstr("Press any key to return to main menu.");
			getch();
			endwin();
			execlp("./escape", "./escape", NULL);
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
					if(row == 3)
						q3[3] = Lv3_chest1();
					else if(col < 35)
						q3[4] = Lv3_chest2();
					else
						q3[5] = Lv3_chest3();
					draw_level_window();
					level_3_map();
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
					if(row == 3)
						q3[3] = Lv3_chest1();
					else if(col < 35)
						q3[4] = Lv3_chest2();
					else
						q3[5] = Lv3_chest3();
					draw_level_window();
					level_3_map();
				}
				row--;
			}else if(inch() == '-' || inch() == '|' || row == DOWN_END)
				row--;
			move(row, col);
		}
		if(c=='a'){
			col--;
			move(row, col);
			if(inch() == ')'){
				if((c = getch()) == ' '){
					q3[2] = Lv3_door3();
					draw_level_window();
					level_3_map();
				}
				col++;
			}else if(inch() == ']'){
				if((c = getch()) == ' '){
					if(row == 3)
						q3[3] = Lv3_chest1();
					else if(col < 35)
						q3[4] = Lv3_chest2();
					else
						q3[5] = Lv3_chest3();
					draw_level_window();
					level_3_map();
				}
				col++;
			}else if(inch() == '-' || inch() == '|' || col == LEFT_END)
				col++;
			move(row, col);
		}
		if(c=='d'){
			col++;
			move(row, col);
			if(inch() == '(' && row <= 5){
				if((c = getch()) == ' '){
					q3[0] = Lv3_door1();
					draw_level_window();
					level_3_map();
				}
				col--;
			}else if(inch() == '['){
				if((c = getch()) == ' '){
					if(row == 3)
						q3[3] = Lv3_chest1();
					else if(col < 35)
						q3[4] = Lv3_chest2();
					else
						q3[5] = Lv3_chest3();
					draw_level_window();
					level_3_map();
				}
				col--;
			}else if(inch() == '(' && row > 5 && row < 20){
				if((c = getch()) == ' '){
					q3[1] = Lv3_door2();
					draw_level_window();
					level_3_map();
				}
				col--;
			}else if(inch() == '(' && row > 20){
				if((c = getch()) == ' '){
					door3 = Lv3_door4();
					draw_level_window();
					level_3_map();
				}
				col--;
			}
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

int Lv3_door1(){
	int r=22;
	char c;
	erase();
	draw_level_window();

	//퀴즈 띄우기
	move(17, 20);
	addstr("Q1. Fill in the blank to open the door");
	move(19, 20);
	addstr("Linux/Unix always assigns new connection to the");
	move(20, 20);
	addstr("(       ) available file descriptor");
	move(22, 20);
	addstr("1) Highest");
	move(23, 20);
	addstr("2) Lowest");
	refresh();

	//정답 선택

	move(22, 19);
	addch('o');
	refresh();

	while((c = getch()) != ' '){
		if(c == 'w' && r == 23){
			move(r, 19);
			addch(' ');
			r--;
			move(r, 19);
			addch('o');
			refresh();
		}else if(c == 's' && r == 22){
			move(r, 19);
			addch(' ');
			r++;
			move(r, 19);
			addch('o');
			refresh();
		}
	}

	//정답 확인
	if(r == 22){
		erase();
		move(20, 20);
		addstr("Please try again");
		move(22, 20);
		addstr("Press any key to continue game");
		c = getch();
		r = -1;
	}else{
		erase();
		move(20, 20);
		addstr("The door is open");
		move(22, 20);
		addstr("Press any key to continue game");
		c = getch();
		r = 1;
	}

	erase();
	refresh();
	
	return r;

}

int Lv3_door2(){
	int k = 28, s = 0;
	char c;
	char answer[15];

	erase();
	draw_level_window();

	move(15, 20);
	addstr("Q2. When you want to ignore the signal...");
	move(17, 25);
	addstr("signal(SIGINT, _______);");
	move(19, 20);
	addstr("Please write appropriate word.");
	move(21, 20);
	addstr("(Press space to check the answer)");

	while((c = getch()) != ' '){
		if(c == ''){
			move(25, --k);
			addch(' ');
			answer[--s] = '\0';
		}else{
			move(25, k++);
			addch(c);
			answer[s++] = c;
		}
		refresh();
	}

	if(strncmp(answer, "SIG_IGN", 7) != 0){
		erase();
		move(20, 20);
		addstr("Please try again");
		move(22, 20);
		addstr("Press any key to continue game");
		c = getch();
		k = -1;
	}
	else{
		erase();
		move(20, 20);
		addstr("The door is open");
		move(22, 20);
		addstr("Press any key to continue game");
		c = getch();
		k = 1;
	}

	erase();
	refresh();

	return k;
}

int Lv3_door3(){
	int r = 20;
	char c;

	erase();
	draw_level_window();

	move(15, 20);
	addstr("Q3. When you create Thread(s), they share data resource");
	move(16, 20);
	addstr("except (        ) space.");
	move(18, 20);
	addstr("(Press space to check the answer");
	move(20, 30);
	addstr("1) Code");
	move(21, 30);
	addstr("2) Static");
	move(22, 30);
	addstr("3) Heap");
	move(23, 30);
	addstr("4) Stack");

	move(r, 29);
	addch('o');
	refresh();

	while((c = getch()) != ' '){
		if(c == 'w' && r != 20){
			move(r, 29);
			addch(' ');
			r--;
			move(r, 29);
			addch('o');
			refresh();
		}else if(c == 's' && r != 23){
			move(r, 29);
			addch(' ');
			r++;
			move(r, 29);
			addch('o');
			refresh();
		}
	}

	if(r == 23){
		erase();
		move(20, 20);
		addstr("The door is open");
		move(21, 20);
		addstr("Press any key to continue the game");
		c = getch();
		r = 1;
	}
	else{
		erase();
		move(20, 20);
		addstr("Please try again");
		move(21, 20);
		addstr("Press any key to continue the game");
		c = getch();
		r = -1;
	}

	erase();
	refresh();

	return r;

}

int Lv3_chest1(){
	int k = 35;
	char c;

	erase();
	draw_level_window();

	move(10, 25);
	addstr("There's a hint in the chest");
	move(11, 25);
	addstr("To open the chest, find the rule");
	move(12, 25);
	addstr("and solve the problem");
	move(13, 25);
	addstr("(Press the number key)");
	move(15, 30);
	addstr("O O O O O = 0");
	move(16, 30);
	addstr("O O O O # = 1");
	move(17, 30);
	addstr("O O O # O = 2");
	move(18, 30);
	addstr("O O O # # = 3");
	move(19, 30);
	addstr("O O # O # = 5");
	move(20, 30);
	addstr("O O # # O = 6");
	move(21, 30);
	addstr("O # O O # = ?");

	refresh();
	
	if((c = getch()) == '9'){
		erase();
		move(20, 20);
		addstr("The chest is open");
		move(21, 20);
		addstr("You got a note from the chest(hint 1)");
		move(23, 20);
		if(player3 == 'A' || player3 == 'S'){
			addstr("[ The third Thursday of December 1999 is the ??th ]");
		}else{
			addstr("[ The second Friday of March 1999 is the ?th ]");
		}
		move(25, 20);
		addstr("Press any key to continue the game");
		hint3++;
		c = getch();
		k = 1;
	}else{
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

int Lv3_chest2(){
	int k = 30, s = 0;
	char c, answer[15];

	erase();

	move(15, 20);
	addstr("There's a hint in the chest");
	move(16, 20);
	addstr("To open the chest, guess what day is it today.");
	move(18, 20);
	addstr("\"I hope yesterday is tomorrow. Then today will be Friday.\"");
	move(20, 20);
	addstr("(Press space to check the answer)");

	while((c = getch()) != ' '){
		if(c == ''){
			move(24, --k);
			addch(' ');
			answer[--s] = '\0';
		}else{
			move(24, k++);
			addch(c);
			answer[s++] = c;
		}
		refresh();
	}
	
	k = -1;

	if(strncmp(answer, "Wednesday", 9) == 0 || strncmp(answer, "Sunday", 6) == 0){
		erase();
		move(20, 20);
		addstr("The chest is open");
		move(21, 20);
		addstr("You got a note from the chest(hint 2)");
		move(23, 20);
		if(player3 == 'A' || player3 == 'S')
			addstr("[ 2 @ 3 = 9, 5 @ 4 = 26, then, 7 @ 4 = ?? ]");
		else
			addstr("[ 2 @ 3 = 9, 5 @ 4 = 26, then, 4 @ 1 = ?? ]");
		move(25, 20);
		addstr("Press any key to continue the game");
		c = getch();
		k = 1;
		hint3++;
	}else{
		erase();
		move(20, 20);
		addstr("Please try again");
		move(21, 20);
		addstr("Press any key to continue the game");
		c = getch();
	}

	erase();
	refresh();

	return k;
}

int Lv3_chest3(){
	int r = 26;
	char c;

	erase();

	move(15, 20);
	addstr("There's a hint in the chest");
	move(16, 20);
	addstr("To open the chest, find the rule");
	move(17, 20);
	addstr("and solve the problem");
	move(18, 20);
	addstr("(Press space to check the answer");
	move(20, 30);
	addstr("5 + 3 = 28");
	move(21, 30);
	addstr("9 + 1 = 810");
	move(22, 30);
	addstr("8 + 6 = 214");
	move(23, 30);
	addstr("5 + 4 = 19");
	move(24, 30);
	addstr("7 + 3 = ?");
	move(26, 20);
	addstr("1) 308");
	move(27, 20);
	addstr("2) 410");
	move(28, 20);
	addstr("3) 512");
	move(29, 20);
	addstr("4) 614");

	move(r, 19);
	addch('o');

	while((c = getch()) != ' '){
		if(c == 'w' && r != 26){
			move(r--, 19);
			addch(' ');
			move(r, 19);
			addch('o');
		}else if(c == 's' && r != 29){
			move(r++, 19);
			addch(' ');
			move(r, 19);
			addch('o');
		}
		refresh();
	}

	if(r == 27){
		erase();
		move(20, 20);
		addstr("The chest is open");
		move(21, 20);
		addstr("You got a note from the chest");
		move(23, 20);
		if(player3 == 'A' || player3 == 'S')
			addstr("[ (sin x) / n + 1 = ? ]");
		else
			addstr("[ (sin x) / n - 4 = ? ]");
		move(25, 20);
		addstr("Press any key to continue the game");
		r = 1;
		hint3++;
	}else{
		erase();
		move(20, 20);
		addstr("Please try again");
		move(21, 20);
		addstr("Press any key to continue the game");
		r = -1;
	}
 
	c = getch();

	erase();
	refresh();

	return r;
}

int Lv3_door4(){
	int r = 22;
	char c;
	char answer[5];
	erase();
	draw_level_window();

	move(15, 20);
	if(player3 == 'S')
		addstr("There is a lock: hint1 * hint3 + hint2");
	else if(player3 == 'A'){
		addstr("There is a lock: hint1 * hint2 * hint3");
		move(16, 20);
		addstr("Use B's hint");
	}else{
		addstr("There is a lock: hint1 * hint3 + hint2");
		move(16, 20);
		addstr("Use A's hint");
	}
	move(17, 20);
	addstr("(Write answer and press enter key)");

	move(20, 20);
	addstr("answer: ");
	move(20, 28);
	refresh();
	echo();
	getstr(answer);
	noecho();

	if(strcmp(answer, "165") == 0 && (player3 == 'B' || player3 == 'S')){
		erase();
		move(20, 20);
		addstr("The door is open");
		move(22, 20);
		addstr("Press any key to continue the game");
		c = getch();
		r = 1;
	}else if(strcmp(answer, "270") == 0 && player3 == 'A'){
		erase();
		move(20, 20);
		addstr("The door is open");
		move(22, 20);
		addstr("Press any key to continue the game");
		c = getch();
		r = 1;
	}else{
		erase();
		move(20, 20);
		addstr("Please try again");
		move(22, 20);
		addstr("Press any key to continue the game");
		c = getch();
		r = -1;
	}

	erase();
	refresh();

	return r;
}
