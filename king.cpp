#include "piece.hpp"
#include "position.hpp"
#include "king.hpp"
#include <iostream>
#include <sstream>
using std::cout;
using std::endl;
using std::stringstream;


King::King(char color, int x , int y):Piece(color,x,y){

}
bool King::isValidMove(Piece*** board, Position destiny){

	int diferenciaV, diferenciaH;

	if(this->getColor()=='B'){
		//Verifica que no sean del mismo color
		if (board[destiny.getY()][destiny.getX()]==NULL || board[destiny.getY()][destiny.getX()]->getColor()=='N'){

			//Busca la diferencia Vertical
			if (destiny.getY()>this->position.getY()){
				diferenciaV = destiny.getY() - this->position.getY();
			}else if(destiny.getY()<this->position.getY()){
				diferenciaV = this->position.getY()-destiny.getY();
			}
			//Busca la diferencia Horizontal
			if (destiny.getX()>this->position.getX()){
				diferenciaH = destiny.getX() - this->position.getX();
			}else if(destiny.getX()<this->position.getX()){
				diferenciaH = this->position.getX()-destiny.getX();
			}

			//Si la diferencia de las posiciones es mayor a 1
			if(diferenciaH==1 || diferenciaV==1){
				return true;
			}else{
				return false;
			}
		}else if (board[destiny.getY()][destiny.getX()]->getColor()=='B'){
			return false;
		}
	}else{
		if (board[destiny.getY()][destiny.getX()]==NULL || board[destiny.getY()][destiny.getX()]->getColor()=='B'){
			//Busca la diferencia Vertical
			if (destiny.getY()>this->position.getY()){
				diferenciaV = destiny.getY() - this->position.getY();
			}else if(destiny.getY()<this->position.getY()){
				diferenciaV = this->position.getY()-destiny.getY();
			}
			//Busca la diferencia Horizontal
			if (destiny.getX()>this->position.getX()){
				diferenciaH = destiny.getX() - this->position.getX();
			}else if(destiny.getX()<this->position.getX()){
				diferenciaH = this->position.getX()-destiny.getX();
			}

			//Si la diferencia de las posiciones es mayor a 1
			if(diferenciaH==1 || diferenciaV==1){
				return true;
			}else{
				return false;
			}
		} else	{
			return false;
		}


	}




}
bool King::moveTo(Piece***board, Position destiny){
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
string King::toString()const{
	stringstream ss;
	if (color == 'N'){
		ss << "R";
	}
	else{
		ss << "r";
	}
	return ss.str();
}
