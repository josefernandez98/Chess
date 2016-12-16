#include "piece.hpp"
#include "queen.hpp"
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

Queen::Queen(char color, int x, int y):Piece(color, x, y){

}
bool Queen::isValidMove(Piece*** board, Position destiny){
	Bishop b(this->color,this->position.getX(),this->position.getY());
	Rook r(this->color,this->position.getX(),this->position.getY());
	if (r.isValidMove(board, destiny)||b.isValidMove(board, destiny)) {
		return true;
	} else {
		return false;
	}
}
bool Queen::moveTo(Piece*** board, Position destiny){
	if(isValidMove(board,destiny)){
		board[position.getY()][position.getX()] = NULL;
		position = destiny;
		board[position.getY()][position.getX()] = this;
		return true;
	}
	else{
		cout << "Invalid move" << endl;
		return false;
	}
}

string Queen::toString()const{
	stringstream ss;
	if (color == 'N'){
		ss << "Q";
	}
	else{
		ss << "q";
	}
	return ss.str();
}
