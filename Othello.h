#define _CRT_SECURE_NO_WARNINGS

#define EMPTY 0
#define black 1
#define white 2
#define OUTER 3

#define ROWS 8
#define COLS 8
#define SQUARES 64

#define UP_LEFT -9
#define UP -8
#define UP_RIGHT -7
#define LEFT -1
#define RIGHT 1
#define DOWN_LEFT 7
#define DOWN 8
#define DOWN_RIGHT 9

#define GAME_FINISHED 1
#define GAME_NOT_FINISHED -1

#define W 'w'
#define B 'b'
#define DOT '.'

#define SELECTUP 'w'
#define SELECTDOWN 's'
#define SELECTLEFT 'a'
#define SELECTRIGHT 'd'

void initial_board(int board[]); //initialize start board
int count(int player, int board[]); //Counting the player's pieces
void display_board(int board[], int choicePosition); //show the game board
void get_user_move(int* choicePosition, int player); //get new position of piece from players
int convert_user_input_to_board_index(int user_input);
int get_opponent(int player); //change the player turn
int valid_position(int move); //check if new position is valid or not
int check_valid_change_row(int source, int destination, int dir);
int find_bracketing_piece(int square, int player, int board[], int dir);
int would_flip(int move, int player, int board[], int dir);
int legal_position(int move, int player, int board[]);
int any_legal_move(int player, int board[]);
void make_flips(int move, int player, int board[], int dir);
void make_move(int move, int player, int board[]);
int check_endgame(int player, int board[]); //everytime check if the game is finished or not
void othello(int board[64], int* choicePosition); //function for handling the game process#pragma once
