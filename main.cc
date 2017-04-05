/*
 * main.cc
 *
 *  Created on: Mar 10, 2017
 *      Author(s): Logan Francisco, Jacob Lai, Steven Harvey
 */




#include <iostream>

using namespace std;

/*
 * Each object of the piece class represents a single square on the checkerboard, empty or otherwise.
 */

class piece {
 public:
  int color = 0;  // 0 is none, 1 is white, 2 is black
  bool king = 0;  // 0 is normal piece, 1 is king

};

/*
 * Primary class. Contains all relevant info on the status of the game.
 */

class checkerboard {
 public:
   piece board[8][8];
   checkerboard();
   void display();
   void action_sequence(char, int);
   bool move_check(int, int);
   bool jump_check(int, int);
   void move(piece *, piece *);

};

int main(){

	char user_input_row;
	int user_input_col;
	checkerboard a;

	// Displays checkerboard
	a.display();

	cout << "Please select a piece to move." << endl;
	cout << "Enter Row: ";
	cin >> user_input_row;
	cout << "Enter Column: ";
	cin >> user_input_col;

	a.action_sequence(user_input_row, user_input_col);
}

/*
 * checkerboard::checkerboard
 * Purpose:
 * Initializes board to correct configuration.
 */

checkerboard::checkerboard(){

/*
 * Initialize "1" or white in the top half of the board.
 */
	for(int row = 0; row < 3; row++){

		for(int col = 0; col < 8; col += 2){
			board[col+(row%2)][row].color = 1;
		}
	}

/*
 * Initialize "2" or black in the bottom half of the board.
 */
	for(int row = 5; row < 8; row++){

		for(int col = 0; col < 8; col += 2){
			board[col+(row%2)][row].color = 2;
		}
	}

}

/*
 * checkerboard::display
 * Purpose:
 * Display checkerboard in a user-friendly interface.
 */

void checkerboard::display(){

	char row_offset = 'A';

	for(int row=0; row < 8; row++){

		// row labeling
		cout << row_offset << "  ";
		row_offset++;

		// Converts the number representation within our code into letter representation.
		for(int col=0; col < 8; col++){
			char type;

			if(board[col][row].color == 1) type = 'W';
			else if(board[col][row].color == 2) type = 'B';
			else if(board[col][row].color == 0) type = '-';

			cout << type << "  ";
		}

		cout << endl;
	}

	// column labeling
	cout << endl << "   1  2  3  4  5  6  7  8" << endl;
}

/*
 * checkerboard::action_sequence
 * Purpose:
 * Performs all necessary actions for movement and jumping.
 */

void checkerboard::action_sequence(char start_row, int start_col){

	int int_start_row, int_finish_row, finish_col;
	char finish_row;
	piece start, finish;

	// Converts selected piece's row in letters to a numerical input.
	int_start_row = start_row - 'A';

	// col-1 is subtracting 1 from the input of the user's column, because the user is given column from 1-8 and the array is from 0-7
	start_col = start_col - 1;


	cout << "Which space would you like to move to?" << endl << "Enter Row to move to: ";
	cin >> finish_row;
	int_finish_row = finish_row - 'A';

	cout << "Enter Column to move to: ";
	cin >> finish_col;
	finish_col = finish_col-1;

	start = board[int_start_row][start_col];
	finish = board[int_finish_row][finish_col];

	move(&start, &finish);


/*
	if(move_check(int_row, col)){
		cout << "error" << endl;
	}

	if(jump_check(int_row, col)){
		cout << "error" << endl;
	}
*/

}

/*
 * checkerboard::move_check
 * Purpose:
 * Checks if the user's input of movement is valid.
 */

bool checkerboard::move_check(int row, int col){
	bool error = false;


	return error;
}

/*
 * checkerboard::jump_check
 * Purpose:
 * Check for possible jump points.
 */

bool checkerboard::jump_check(int row, int col){
	bool error = false;


	return error;
}

/*
 * checkerboard::move
 * Purpose:
 * Moves a piece into a new position.
 */

void checkerboard::move(piece *start, piece *finish){

	finish->color = start->color;
	finish->king = start->king;
	start->color = 0;
	start->king = false;

	cout << "Color: " << finish->color << " king? " << finish->king << endl;
}
