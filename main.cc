#include <iostream>
#include <fstream>
#include "checkerboard.h"
#include "savegame.h"

using namespace std;

int main(){

	checkerboard a;


/*
 * player: 2 player game, bool indicates which player's turn it is.
 * TERMINATED: indicates the game is over when true.
 */
	bool player = 0, TERMINATED = 0;

	// prompts the user if they want to load an old savegame file.
	//a.load_game();


	while(!TERMINATED){

		// Update the board.
		a.display();

		cout << "Player " << player << "'s turn." << endl;

		a.action_sequence(player);

		player = !player;

		TERMINATED = a.end_game_check();
	}

}
