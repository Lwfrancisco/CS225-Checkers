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

checkerboard::checkerboard(){

	for(int j=0; j < 8; j++){

	  for (int i=0; i < 8; i+=2){
	   board[i][j].color = 1;
	  }

	  cout << endl;
	 }
}

void checkerboard::display(){

	for(int j=0; j < 8; j++){

		for (int i=0; i < 8; i++){
			cout << board[i][j].color << "  ";
		}

		cout << endl;
	}
}
