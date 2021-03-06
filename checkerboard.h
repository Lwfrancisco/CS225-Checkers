/*
 * File: checkerboard.h
 * Course: CS225
 * Project: Checkers
 * Authors: Logan, Jacob, Steven
 */

#ifndef CHECKERBOARD_H_
#define CHECKERBOARD_H_

using namespace std;

/*
 * Parameters class contains all the necessary operating parameters
 */

class parameters {

public:
	int start_row, start_col;
	int finish_row, finish_col;

};

/*
 * Each object of the piece class represents a single square on the checkerboard, empty or otherwise.
 */

class piece {
 public:
  int color = 0;  // 0 is none, 1 is white, 2 is black

};

/*
 * Primary class. Contains all relevant info on the status of the game.
 */

class checkerboard:public parameters {
 public:
   piece board[8][8];
   checkerboard();
   ~checkerboard();
   void display();
   int action_sequence(bool *player_turn);
   bool move_check(piece&);
   void move(piece&, piece&);
   void jump(piece&, piece&);
   bool end_game_check();

   bool move_check(piece&, piece&, bool*);
   bool jump_check(piece& start, piece& finish, bool*);
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
 * ~checkerboard::checkerboard
 * Purpose:
 * Congratulate the players.
 */

checkerboard::~checkerboard(){
	cout << "Hope you enjoyed the game!!!" << endl;
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
 * checkerboard::action_sequence
 * Purpose:
 * Performs all necessary actions for movement and jumping.
 */

int checkerboard::action_sequence(bool *player){

	char char_start_row, char_finish_row;


	// Update the board.
	display();

	cout << "Please select a piece to move or type 'S' to save game." << endl;
	cout << "Enter Row: ";
	cin >> char_start_row;
	if (char_start_row == 'S'){
		return 1;	// 1 means save game is needed.
	}
	cout << "Enter Column: ";
	cin >> start_col;

	// Converts selected piece's row in letters to a numerical input.
	start_row = char_start_row - 'A';

	// col-1 is subtracting 1 from the input of the user's column, because the user is given column from 1-8 and the array is from 0-7
	start_col = start_col - 1;

    piece& start = board[start_row][start_col];

    if (start.color == 1 && *player == 1){

    	cout << "Illegal piece. Please choose a black piece." << endl;

    	return 0;
    }

    if (start.color == 2 && *player == 0){

    	cout << "Illegal piece. Please choose a white piece." << endl;

    	return 0;
    }

    // Error checking.
    if(move_check(start)){

        return 0;
    }

	cout << "Which space would you like to move to?" << endl << "Enter Row to move to: ";
	cin >> char_finish_row;
	finish_row = char_finish_row - 'A';

	cout << "Enter Column to move to: ";
	cin >> finish_col;
	finish_col = finish_col-1;

	piece& finish = board[finish_row][finish_col];


    // Rules checking.
    // Determine whether it's a move or a jump.


    if((finish_col - start_col) > 1){   // This is a jump.

        if(jump_check(start, finish, player) == 0){

        	jump(start, finish);

        	*player = !(*player);

        }

    }
    else{   // This is a move.

        if(move_check(start, finish, player) == 0){

            move(start, finish);

            *player = !(*player);
        }

    }


	return 0; // all is well
}


/*
 * checkerboard::move_check
 * Purpose:
 * Checks if the user's input of movement is valid.
 */

bool checkerboard::move_check(piece& start){
 	bool error = 1;

	if(start.color == 0){

        cout << "Illegal piece selected.\n";
        return error;

	}
	else return 0;
}

bool checkerboard::move_check(piece& start, piece& finish, bool* player){

    if(finish.color != 0){

        cout << "Can't move to occupied spaces.\n";
        return 1;

    }

	if(finish_col == start_col){ // Moving straight, not diagonally.

        cout << "Illegal move.\n";
        return 1;

	}
    else if(finish_row >= start_row && *player == 1){ // Can't move backwards or horizontally. For black checkers.

        cout << "Illegal move.\n";
        return 1;

    }
    else if(finish_row <= start_row && *player == 0){ // Can't move backwards or horizontally. For white checkers.

        cout << "Illegal move.\n";
        return 1;

    }
    else return 0;  // 0 error found.

}

/*
 * checkerboard::jump_check
 * Purpose:
 * Check for possible jump points.
 */

bool checkerboard::jump_check(piece& start, piece& finish, bool* player){

    if(finish.color != 0){

        cout << "Can't move to occupied spaces.\n";
        return 1;

    }
    else if((finish_row != start_row - 2) && *player == 1){  // For black checkers.

        cout << "Illegal move.\n";
        return 1;

    }
    else if((finish_col != start_col - 2 && finish_col != start_col + 2) && *player == 1){    // For black checkers.

        cout << "Illegal move.\n";
        return 1;

    }
    else if((finish_row != start_row + 2) && *player == 0){  // For white checkers.

        cout << "Illegal move - Can't jump there1.\n";
        return 1;

    }
    else if((finish_col != start_col - 2 && finish_col != start_col + 2) && *player == 0){ // For white checkers.

        cout << "Illegal move - Can't jump there2.\n";
        return 1;

    }
    else return 0;  // 0 error found.

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


	/* debugging:
		cout << "   Color of finish is: " << finish.color << endl;
		cout << "   Is it king? " << finish.king << endl;
	*/
}

/*
 * checkerboard::jump
 * Purpose:
 * Jumps a piece into a new position.
 */

void checkerboard::jump(piece& start, piece& finish){

	finish = start;

	// White
	if (start.color == 1){
		if (finish_col > start_col){						// White Left (from perspective up the board)
			board[finish_row-1][finish_col-1].color = 0;
		}
		else {												// White Right (from perspective up the board)
			board[finish_row-1][finish_col+1].color = 0;
		}
	}
	else if (start.color == 2){
		if (finish_col > start_col){						// Black Right (from perspective up the board)
			board[finish_row+1][finish_col-1].color = 0;
		}
		else {												// Black Left (from perspective up the board)
			board[finish_row+1][finish_col+1].color = 0;
		}

	}
	else {

	}

	// Make the original piece blank.
	start.color = 0;
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

istream& operator >> (istream& in, checkerboard& obj)
{
	for (int row = 0; row < 8; row++){
		for (int col = 0; col < 8; col++){
		    in >> obj.board[row][col].color;
		}
	}
    return in;
}

ostream& operator << (ostream& out, const checkerboard& obj)
{
	for (int row = 0; row < 8; row++){
		for (int col = 0; col < 8; col++){
		    out << obj.board[row][col].color << ' ';
		}
	}

    return out;
}

/*
 * save_game
 * Purpose:
 * Saves the checkerboard game
 */

bool save_game(checkerboard &obj, bool player_turn){

	bool user_input;

	cout << "Would you like to save your game? (1 for yes and 0 for no): ";
	cin >> user_input;

	if (user_input){
		ofstream fout("savegame");
		fout << player_turn << " ";
		fout << obj;

		fout.close();

		return 1;
	}
	else {
		cout << "Returning to the regularly scheduled massacre." << endl;

		return 0;
	}
}

/*
 * checkerboard::load_game
 * file IO, will load board if a savegame file exists. Prompts user.
 */

void load_game(checkerboard *obj, bool *player){
	bool user_input;

	cout << "Load save game or play new game? (1 is load save game and 0 is play new): ";
	cin >> user_input;

	if (user_input == 1){
		cout << "Loading save game..." << endl;

		ifstream fin("savegame");

		if(fin.is_open()){

			fin >> *player;
			fin >> *obj;
		}
		else {
			cout << "Loading previously saved game has failed. Starting new game..." << endl;
		}

		fin.close();
	}
	else {
		cout << "Playing new game..." << endl;
	}
}


#endif /* CHECKERBOARD_H_ */
