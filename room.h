#include <stdio.h>
#include <curses.h>
#include <string.h>
#include <unistd.h>

void set_player(char);
void set_player_2(char);
void set_player_3(char);
void draw_level_window();

void level_1();
void level_1_A(char*,int);
void level_1_B(char*,int);
void level_1_map();
int Lv1_door1();
int Lv1_door2();
int Lv1_door3();
int Lv1_chest1();
int Lv1_chest2();
int Lv1_chest3();

void level_2();
void level_2_A(char*,int);
void level_2_B(char*,int);
void level_2_map();
int Lv2_door1();
int Lv2_door2();
int Lv2_door3();
int Lv2_chest1();
int Lv2_chest2();
int Lv2_chest3();

void level_3();
void level_3_A(char*,int);
void level_3_B(char*,int);
void level_3_map();
int Lv3_door1();
int Lv3_door2();
int Lv3_door3();
int Lv3_door4();
int Lv3_chest1();
int Lv3_chest2();
int Lv3_chest3();
