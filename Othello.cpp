#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "Othello.h"
#include"graphics.h"

void initial_board(int board[])
{
	int i;
	for (i = 0; i < SQUARES; i++)
		board[i] = 0;
	board[3 * ROWS + 3] = white;
	board[3 * ROWS + 4] = black;
	board[4 * ROWS + 3] = black;
	board[4 * ROWS + 4] = white;
}

int count(int player, int board[])
{
	int i, cnt;
	cnt = 0;
	for (i = 0; i < SQUARES; i++)
		if (board[i] == player)
			cnt++;
	return cnt;
}


void display_board(int board[], int position) {

	clearviewport(); //clear window for update it.

	int x = 100 * (position / 10) - 50; //convert position to its equivalent on window 
	int y = 100 * (position % 10) - 50;

	setcolor(WHITE); //change the color of pen
	rectangle(0, 0, 800, 800); // draw a rectangle with first anf last Coordinates
	setfillstyle(SOLID_FILL, WHITE); //set painting method
	floodfill(400, 400, WHITE); //paint with first cordinate

	for (int i = 0; i < 8; i++) {
		setcolor(BLACK);
		line(0, (i + 1) * 100, 800, (i + 1) * 100); //draw line with first anf last Coordinates
		line((i + 1) * 100, 0, (i + 1) * 100, 800);
	}

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board[i * 8 + j] == white) {
				setcolor(GREEN);
				circle((i * 100) + 50, (j * 100) + 50, 45); //draw line with center Coordinates and radius
				setfillstyle(SOLID_FILL, GREEN);
				floodfill((i * 100) + 50, (j * 100) + 50, GREEN);
			}
			if (board[i * 8 + j] == black) {
				setcolor(BLACK);
				circle((i * 100) + 50, (j * 100) + 50, 45);
				setfillstyle(SOLID_FILL, BLACK);
				floodfill((i * 100) + 50, (j * 100) + 50, BLACK);
			}
		}
	}
	setcolor(LIGHTRED); //Draw rectangle for moving poibter for each changes
	rectangle(x - 15, y - 15, x + 15, y + 15);
	setfillstyle(SOLID_FILL, LIGHTRED);
	floodfill(x, y, LIGHTRED);
}

int get_opponent(int player)
{
	switch (player) {
	case black:
		return white;
	case white:
		return black;
	default:
		printf("Illegal player\n");
		return 0;
	}
}

int valid_position(int move)
{
	if (move >= 0 && move < 64)
		return 1;
	else
		return -1;
}

int check_valid_change_row(int source, int destination, int dir)
{
	int source_row = source / COLS;
	int destination_row = destination / COLS;
	if ((dir == UP_LEFT || dir == UP || dir == UP_RIGHT) && (destination_row - source_row != -1))
		return -1;
	else if ((dir == LEFT || dir == RIGHT) && (destination_row - source_row != 0))
		return -1;
	else if ((dir == DOWN_LEFT || dir == DOWN || dir == DOWN_RIGHT) && (destination_row - source_row != 1))
		return -1;
	else
		return 1;
}

int find_bracketing_piece(int square, int player, int board[], int dir)
{
	while (valid_position(square) != -1 &&
		(board[square] == get_opponent(player) && (check_valid_change_row(square, square + dir, dir) != -1)))
	{
		square = square + dir;
	}
	if (valid_position(square) == -1)
		return -1;
	else if (board[square] == player)
		return square;
	else if (check_valid_change_row(square, square + dir, dir) == -1)
		return -1;
	else
		return -1;
}

int would_flip(int move, int player, int board[], int dir)
{
	int c = move + dir;
	if ((valid_position(c) == -1) || (check_valid_change_row(move, c, dir) == -1))
		return -1;
	else if (board[c] == get_opponent(player))
		return find_bracketing_piece(c, player, board, dir);
	else
		return -1;
}

int legal_position(int move, int player, int board[])
{
	int ALLDIRECTIONS[8] = { UP_LEFT, UP, UP_RIGHT, LEFT, RIGHT, DOWN_LEFT, DOWN, DOWN_RIGHT };
	if (valid_position(move) == -1)
		return -1;
	if (board[move] == EMPTY) {
		int i = 0;
		while (i < 8 && (would_flip(move, player, board, ALLDIRECTIONS[i]) == -1))
			i++;
		if (i == 8)
			return -1;
		else
			return 1;
	}
	else
		return -1;
}

int any_legal_move(int player, int board[])
{
	int move = 0;
	while (move < 64 && (legal_position(move, player, board) == -1))
		move++;
	if (move < 64)
		return 1;
	else
		return -1;
}

void make_flips(int move, int player, int board[], int dir)
{
	int bracketer, c;
	bracketer = would_flip(move, player, board, dir);
	if (bracketer != -1) {
		c = move + dir;
		while (c != bracketer)
		{
			board[c] = player;
			c = c + dir;
			if (valid_position(c) == -1)
				break;
		}
	}
}

void make_move(int move, int player, int board[])
{
	int i;
	int ALLDIRECTIONS[8] = { UP_LEFT, UP, UP_RIGHT, LEFT, RIGHT, DOWN_LEFT, DOWN, DOWN_RIGHT };
	board[move] = player;
	for (i = 0; i <= 7; i++)
		make_flips(move, player, board, ALLDIRECTIONS[i]);
}

int check_endgame(int player, int board[])
{
	int black_score;
	int white_score;
	if (any_legal_move(player, board) == -1)
	{
		black_score = count(black, board);
		white_score = count(white, board);
		if (black_score > white_score)
			printf("The BLACK player has won!\n");
		else if (white_score > black_score)
			printf("The WHITE player has won!\n");
		else
			printf("The game has no winner\n");
		printf("Black: %d\n", black_score);
		printf("White: %d\n", white_score);
		return GAME_FINISHED;
	}
	return GAME_NOT_FINISHED;
}

void get_user_move(int* position, int player)
{
	int move;
	printf("%s player's turn :\n", player == black ? "BLACK" : "WHITE");
	char user_input;
	while ((user_input = getchar()) != ' ') { //getchar from user until he/she put space
		switch (user_input) 
		{ //upgrade position with input case
			case(SELECTUP):
			{
				*position -= 1; 
				break;
			}
			case(SELECTDOWN):
			{
				*position += 1;
				break;
			}
			case(SELECTLEFT):
			{
				*position -= 10;
				break;
			}
			case(SELECTRIGHT): 
			{
				*position += 10;
				break;
			}
		}
	}
}

int convert_user_input_to_board_index(int user_input)
{
	int index = (((user_input - 1) / 10) - 1) * 8 + ((user_input - 1) % 10);
	return index;
}

void othello(int board[64], int* position)
{
	int player = black;
	while (check_endgame(player, board) == GAME_NOT_FINISHED)
	{
		get_user_move(position, player); //Function for geting move from user by direction
		int move = convert_user_input_to_board_index(*position); //convert direction to index of board array
		if (legal_position(move, player, board) != -1) //check validation of input
		{
			make_move(move, player, board); //apply changes
			player = get_opponent(player); //change player turn
			display_board(board, *position); //show board
		}
		else
			printf("Invalid move. Please choose an appropriate square.\n");
	}
}