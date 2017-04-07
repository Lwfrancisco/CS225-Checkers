/*
 * checkerboard.h
 *
 *  Created on: 10Mar.,2017
 *      Author: logan
 */

#ifndef CHECKERBOARD_H_
#define CHECKERBOARD_H_

using namespace std;

/*
 * Each object of the piece class represents a single square on the checkerboard, empty or otherwise.
 */

class piece {
 public:
  int color = 0;  // 0 is none, 1 is white, 2 is black
  bool king = 0;  // 0 is normal piece, 1 is king
    void operator=(piece& p){   // Assignment operator overloading.

        color = p.color;
        king = p.king;

    }
};

/*
 * Primary class. Contains all relevant info on the status of the game.
 */

class checkerboard {
 public:
   piece board[8][8];
   checkerboard();
   void display();
   void load_game();
   void action_sequence();
   bool move_check(piece&, int, int, piece&, int, int);
   bool move_check(piece&);
   bool jump_check(int, int);
   void move(piece&, piece&);
   bool end_game_check();

};


/*
 * checkerboard::checkerboard
 * Purpose:
 * Initializes board to correct configuration.
 */

checkerboard::checkerboard(){

/*
 * Initialize "1" or white in the top half of the board.
 */
//	for(int row = 0; row < 3; row++){
//
//		for(int col = 0; col < 8; col += 2){
//			board[col+(row%2)][row].color = 1;
//		}
//	}

	for(int row = 0; row < 3; row++){

        for(int col = 0; col < 8; col += 2)
            board[row][col+(row%2)].color = 1;

	}

/*
 * Initialize "2" or black in the bottom half of the board.
 */
	for(int row = 5; row < 8; row++){

		for(int col = 0; col < 8; col += 2){
			board[row][col+(row%2)].color = 2;
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

	cout << "Checkers Board: " << endl;

	for(int row=0; row < 8; row++){

		// row labeling
		cout << row_offset << "  ";
		row_offset++;

		// Converts the number representation within our code into letter representation.
		for(int col=0; col < 8; col++){
			char type;

			if(board[row][col].color == 1) type = 'W';
			else if(board[row][col].color == 2) type = 'B';
			else if(board[row][col].color == 0) type = '-';

			cout << type << "  ";
		}

		cout << endl;
	}

	// column labeling
	cout << endl << "   1  2  3  4  5  6  7  8" << endl;
}

/*
 * checkerboard::load_game
 * file IO, will load board if a savegame file exists. Prompts user.
 */

void checkerboard::load_game(){
	bool user_input;

	cout << "Load save game or play new game? (1 is load save game and 0 is play new): ";
	cin >> user_input;

	if (user_input == 1){
		cout << "Loading save game..." << endl;
		// file input = someCheckerboardVariable;
		// someCheckerbaordVariable = board;
	}
	else {
		cout << "Playing new game..." << endl;
	}
}

/*
 * checkerboard::action_sequence
 * Purpose:
 * Performs all necessary actions for movement and jumping.
 */

void checkerboard::action_sequence(){

	int int_start_row, start_col, int_finish_row, finish_col;
	char start_row, finish_row;


	cout << "Please select a piece to move." << endl;
	cout << "Enter Row: ";
	cin >> start_row;
	cout << "Enter Column: ";
	cin >> start_col;

	// Converts selected piece's row in letters to a numerical input.
	int_start_row = start_row - 'A';

	// col-1 is subtracting 1 from the input of the user's column, because the user is given column from 1-8 and the array is from 0-7
	start_col = start_col - 1;

    piece& start = board[int_start_row][start_col];

    // Error checking.
    if(move_check(start)){

        // Illegal move start again.
        action_sequence();

    }

	cout << "Which space would you like to move to?" << endl << "Enter Row to move to: ";
	cin >> finish_row;
	int_finish_row = finish_row - 'A';

	cout << "Enter Column to move to: ";
	cin >> finish_col;
	finish_col = finish_col-1;

	piece& finish = board[int_finish_row][finish_col];

	// Error checking.
	if(move_check(start, int_start_row, start_col, finish, int_finish_row, finish_col)){

        // Illegal move start again.
        action_sequence();

	}

	/*
	 * if finish_row and finish_col indicate a normal "move", then:
	 * move check for a valid move
	 * move if valid
	 *
	 * else if finish_row and finish_col indicate a "jump", then:
	 * jump check for a valid jump
	 * jump if valid
	 *
	 * else:
	 * dunno wtf yet
	 */
	move(start, finish);

}


/*
 * checkerboard::move_check
 * Purpose:
 * Checks if the user's input of movement is valid.
 */

bool checkerboard::move_check(piece& start){
 	bool error = 1;

	if(start.color == 0){

        cout << "Illegal move - No checker there!!!\n";
        return error;

	}
	else return 0;
}

bool checkerboard::move_check(piece& start, int s_row, int s_col, piece& finish, int f_row, int f_col){
    bool error = 1;

	if(f_col == s_col){ // Moving straight, not diagonally.

        cout << "Illegal move - Can't move straight!!!\n";
        return error;

	}
    else if(f_row >= s_row){ // Can't move backwards or horizontally.

        cout << "Illegal move - Can't move backwards or horizontally!!!\n";
        return error;

    }
    else

        return 0;
//    else if()


	// For normal pieces.
    //  Forward left is [row-1][col-1]
    //  Forward right is [row-1][col+1]

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

void checkerboard::move(piece& start, piece& finish){

    finish = start;

	// Make the original piece blank.
	start.color = 0;
	start.king = false;

	/* debugging:
		cout << "   Color of finish is: " << finish.color << endl;
		cout << "   Is it king? " << finish.king << endl;
	*/
}

/*
 * checkerboard::end_game_check
 * Purpose:
 * Checks if game has ended.
 */

bool checkerboard::end_game_check(){

	/*
	 * white and black are automatically assumed to be extinct until the check proves otherwise.
	 * However, the end of game is not assumed to be true until proven otherwise.
	 */
	bool white_exists = false, black_exists = false, end_of_game = false;


	for(int row=0; row < 8; row++){

		for(int col=0; col < 8; col++){

			if(board[row][col].color == 1) white_exists = true;
			else if(board[row][col].color == 2) black_exists = true;
		}

	}

	if(white_exists ^ black_exists){
		end_of_game = true;

		if(white_exists){
			cout << "White wins!!!" << endl;
		}
		else {
			cout << "Black wins!!!" << endl;
		}
	}

	return end_of_game;
}

#endif /* CHECKERBOARD_H_ */
