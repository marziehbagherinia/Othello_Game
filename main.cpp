#define _CRT_SECURE_NO_WARNINGS

#include "Othello.h"
#include <stdio.h>
#include <conio.h>
#include"graphics.h"

int main()
{
	printf("Welcome to othello.\n");
	int position = 44; //Start position of pointer
	int board[64];
	initwindow(800, 800, "Othello Game"); //Draw a window with 800 width and height 
	initial_board(board);
	display_board(board, position);
	othello(board, &position);
	return 0;
}