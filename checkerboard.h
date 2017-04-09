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
   int action_sequence(bool *player_turn);
   bool move_check(piece&);
   void move(piece&, piece&, bool*);
   void jump(piece&, piece&, bool*);
   bool end_game_check();

   bool black_move_check(piece&, int, int, piece&, int, int);
   bool black_jump_check(piece& start, int s_row, int s_col, piece& finish, int f_row, int f_col);

   bool white_move_check(piece&, int, int, piece&, int, int);
   bool white_jump_check(piece& start, int s_row, int s_col, piece& finish, int f_row, int f_col);
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

	int int_start_row, start_col, int_finish_row, finish_col;
	char start_row, finish_row;


	// Update the board.
	display();

	cout << "Please select a piece to move or type 'S' to save game." << endl;
	cout << "Enter Row: ";
	cin >> start_row;
	if (start_row == 'S'){
		return 1;	// 1 means save game is needed.
	}
	cout << "Enter Column: ";
	cin >> start_col;

	// Converts selected piece's row in letters to a numerical input.
	int_start_row = start_row - 'A';

	// col-1 is subtracting 1 from the input of the user's column, because the user is given column from 1-8 and the array is from 0-7
	start_col = start_col - 1;

    piece& start = board[int_start_row][start_col];

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
	cin >> finish_row;
	int_finish_row = finish_row - 'A';

	cout << "Enter Column to move to: ";
	cin >> finish_col;
	finish_col = finish_col-1;

	piece& finish = board[int_finish_row][finish_col];


    // Rules checking.
    // Determine whether it's a move or a jump.


    if((finish_col - start_col) > 1){   // This is a jump.

        if(black_jump_check(start, int_start_row, start_col, finish, int_finish_row, finish_col) == 0){

            if(finish_col < start_col) // Left jump.
                board[int_finish_row - 1][finish_col - 1].color = 0;    // Eat enemy checker.

            else if(finish_col > start_col) // Right jump.
                board[int_finish_row - 1][finish_col + 1].color = 0;    // Eat enemy checker.

            move(start, finish, player);

        }

    }
    else{		    	// This is a move.

        if(black_move_check(start, int_start_row, start_col, finish, int_finish_row, finish_col) == 0){

            move(start, finish, player);
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

bool checkerboard::black_move_check(piece& start, int s_row, int s_col, piece& finish, int f_row, int f_col){

    if(finish.color != 0){

        cout << "Can't move to occupied spaces.\n";
        return 1;

    }

	if(f_col == s_col){ // Moving straight, not diagonally.

        cout << "Illegal move.\n";
        return 1;

	}
    else if(f_row >= s_row){ // Can't move backwards or horizontally.

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

bool checkerboard::black_jump_check(piece& start, int s_row, int s_col, piece& finish, int f_row, int f_col){

    if(finish.color != 0){

        cout << "Can't move to occupied spaces.\n";
        return 1;

    }
    else if((f_row != s_row - 2)){

        cout << "Illegal move.\n";
        return 1;

    }
    else if(f_col != s_col - 2 && f_col != s_col + 2){

        cout << "Illegal move.\n";
        return 1;

    }
    else return 0;  // 0 error found.

}

bool white_move_check(piece& start, int s_row, int s_col, piece& finish, int f_row, int f_col)
{

    if(finish.color != 0){

        cout << "Can't move to occupied spaces.\n";
        return 1;

    }

	if(f_col == s_col){ // Moving straight, not diagonally.

        cout << "Illegal move - Can't move straight!!!\n";
        return 1;

	}
    else if(f_row <= s_row){ // Can't move backwards or horizontally.

        cout << "Illegal move - Can't move backwards!!!\n";
        return 1;

    }

    else return 0;  // 0 error found.

}

bool white_jump_check(piece& start, int s_row, int s_col, piece& finish, int f_row, int f_col)
{

    if(finish.color != 0){

        cout << "Can't move to occupied spaces.\n";
        return 1;

    }
    else if((f_row != s_row + 2)){

        cout << "Illegal move - Can't jump there1.\n";
        return 1;

    }
    else if(f_col != s_col - 2 && f_col != s_col + 2){

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

void checkerboard::move(piece& start, piece& finish, bool *player){

    finish = start;

	// Make the original piece blank.
	start.color = 0;
	start.king = false;

	*player = !(*player);


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

istream& operator >> (istream& in, checkerboard& obj)
{
	for (int row = 0; row < 8; row++){
		for (int col = 0; col < 8; col++){
		    in >> obj.board[row][col].color;
		    in >> obj.board[row][col].king;
		}
	}
    return in;
}

ostream& operator << (ostream& out, const checkerboard& obj)
{
	for (int row = 0; row < 8; row++){
		for (int col = 0; col < 8; col++){
		    out << obj.board[row][col].color << ' ';
		    out << obj.board[row][col].king << endl;
		}
	}

    return out;
}

/*
 * save_game
 * Purpose:
 * Saves the checkerboard game
 */

void save_game(checkerboard obj, bool player_turn){

	bool user_input;

	cout << "Would you like to save your game? (1 for yes and 0 for no): ";
	cin >> user_input;

	if (user_input){
		ofstream fout("savegame");
		fout << player_turn << " ";
		fout << obj;

		fout.close();

		exit(0);
	}
	else {
		cout << "Returning to the regularly scheduled massacre." << endl;
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
			cout << "File is open" << endl;
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
