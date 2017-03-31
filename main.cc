/*
 * main.cc
 *
 *  Created on: Mar 30, 2017
 *      Author: logan
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

};

int main(){
 checkerboard a;
 a.display();

}

/*
 * Initializes board to correct configuration.
 */

checkerboard::checkerboard(){

/*
 * j is row, i is column on checkerboard
 */

/*
	for(int j=0; j < 3; j++){
		for (int i=0; i < 8; i+=2){
			board[i+(j%2)][j].color = 1;
		}
	}
*/
	for(int row=0; row < 8; row++){
		for (int col=0; col < 8; col++){
			board[col][row].position = (col+1) + (row * 8);
		}
	}

	/*
	for(int position = 1; position < 24; position+=2){
		for(int row=0; row < 8; row++){
			for (int col=0; col < 8; col++){
				if(board[col][row].position == position){
					board[col][row].color = 1;
				}
			}
		}
	}
*/
}

void checkerboard::display(){

	for(int j=0; j < 8; j++){

		for (int i=0; i < 8; i++){
			cout << board[i][j].color << "  ";
		}

		cout << endl;
	}
}
