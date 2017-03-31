/*
 * main.cc
 *
 *  Created on: Mar 10, 2017
 *      Author(s): Logan Francisco, Jacob Lai, Steven Harvey
 */




#include <iostream>

using namespace std;

class piece {
 public:
  int color = 0;  // 0 is none, 1 is white, 2 is black
  bool king = 0;  // 0 is normal piece, 1 is king
  int position;

};

class checkerboard {
 public:
   piece board[8][8];
   checkerboard();
   void display();
   void action_sequence(char, int);
   bool move_check(int, int);

};

int main(){

	char user_input_row;
	int user_input_col;
	checkerboard a;

	a.display();

	cout << "Please select a piece to move." << endl;
	cout << "Enter Row: ";
	cin >> user_input_row;
	cout << "Enter Column: ";
	cin >> user_input_col;

	a.action_sequence(user_input_row, user_input_col);
}

/*
 * Initializes board to correct configuration.
 */

checkerboard::checkerboard(){

/*
 * Initialize "1" or top half of board.
 */
	for(int row = 0; row < 3; row++){

		for(int col = 0; col < 8; col += 2){
			board[col+(row%2)][row].color = 1;
		}
	}

/*
 * Initialize "2" or bottom half of board.
 */
	for(int row = 5; row < 8; row++){

		for(int col = 0; col < 8; col += 2){
			board[col+(row%2)][row].color = 2;
		}
	}

	for(int row=0; row < 8; row++){

		for(int col = 0; col < 8; col++){
			board[col][row].position = (col+1) + (row * 8);
		}
	}

}

void checkerboard::display(){

	for(int row=0; row < 8; row++){

		switch(row){
			case 0:
				cout << "A  ";
				break;
			case 1:
				cout << "B  ";
				break;
			case 2:
				cout << "C  ";
				break;
			case 3:
				cout << "D  ";
				break;
			case 4:
				cout << "E  ";
				break;
			case 5:
				cout << "F  ";
				break;
			case 6:
				cout << "G  ";
				break;
			case 7:
				cout << "H  ";
				break;
		}

		for(int col=0; col < 8; col++){
			char type;

			if(board[col][row].color == 1) type = 'W';
			else if(board[col][row].color == 2) type = 'B';
			else if(board[col][row].color == 0) type = '-';

			cout << type << "  ";
		}

		cout << endl;
	}

	cout << endl << "   1  2  3  4  5  6  7  8" << endl;
}

void checkerboard::action_sequence(char row, int col){

	int int_row;

	cout << "Inside act_seq!!!" << endl;

	int_row = row - 'A';

	if(move_check(int_row, col-1)){
		cout << "error" << endl;
	}
}

bool checkerboard::move_check(int row, int col){
	bool error;


	return error;
}
