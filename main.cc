#include <iostream>
#include <fstream>
#include <cstdlib>
#include "checkerboard.h"

using namespace std;

int main(){

	checkerboard a;


/*
 * player: 2 player game, bool indicates which player's turn it is.
 * TERMINATED: indicates the game is over when true.
 */
	bool player = 0, TERMINATED = 0;

	// prompts the user if they want to load an old savegame file.
	load_game(&a, &player);


	while(!TERMINATED){

		cout << "Player " << player << "'s turn." << endl;

		if (a.action_sequence(&player)){
			save_game(a, player);
		}


		TERMINATED = a.end_game_check();
	}

}
