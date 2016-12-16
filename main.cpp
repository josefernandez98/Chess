#include <iostream>
#include <string>
#include "position.hpp"
#include "piece.hpp"
#include "king.hpp"
#include "queen.hpp"
#include "knight.hpp"
#include "bishop.hpp"
#include "rook.hpp"
#include "pawn.hpp"

using namespace std;

Piece*** crearTablero(int rows, int cols);
void destruirTablero(Piece*** tablero, int rows, int cols);
void imprimir(Piece*** tablero);
void chessInit(Piece*** tablero);
int charToInt(char coordenada);
bool ganar(Piece*** tablero);

int main(int argc, char const *argv[]){
	const int ROWS = 8;
	const int COLS = 8;
	Piece*** tablero = crearTablero(ROWS,COLS);

	string nombre1,nombre2;
	cout<<"Jugador1 ingrese su nombre: "<<endl;
	cin>>nombre1;
	cout<<"Jugador2 ingrese su nombre: "<<endl;
	cin>>nombre2;
	int turno=0;
	bool gano=false;
	char coordenada1, coordenada2;
	while(!gano){
		bool valid = false;//variable de validacion
		imprimir(tablero);
		turno++;
		int x=0,y=0,x1=0,y1=0;
		if (turno % 2 == 1) {
			while(!valid){//ciclo de validacion
				cout<<"Turno de: "<<nombre1<<endl;
				cout<<"Ingrese columna de la pieza que desea mover: ";
				cin>>x;

				//Este for se usa para validar que el usuario Ingrese
				//una columna valida
				for (;(x > 8) || (x <= 0);) {
					cout << "No ha ingresado una columna valida." << endl;
					cout<<"Turno de: "<<nombre1<<endl;
					cout<<"Ingrese columna de la pieza que desea mover: ";
					cin>>x;
				}//Fin del for
				x--;

				cout<<"Ingrese fila de la pieza que desea mover: ";
				cin >> coordenada1;
				y = charToInt(coordenada1);
				//Este for se usa para validar que ingrese filas validas
				for (;y == -1;) {
					cout << "No ha ingresado una fila valida." << endl;
					cout<<"Ingrese fila de la pieza que desea mover: ";
					cin >> coordenada1;
					y = charToInt(coordenada1);
				}//Fin del for

				cout<<"Ingrese columna a la desea mover la pieza: ";
				cin>>x1;
				//Este for se usa para validar que el usuario Ingrese
				//una columna valida
				for (;(x1 > 8) || (x1 <= 0);) {
					cout << "No ha ingresado una columna valida." << endl;
					cout<<"Ingrese columna de la pieza que desea mover: ";
					cin>>x;
				}//Fin del for
				x1--;

				cout<<"Ingrese fila a la desea mover la pieza: : ";
				cin >> coordenada2;
				y1 = charToInt(coordenada2);
				//Este for se usa para validar que ingrese filas validas
				for (;y1 == -1;) {
					cout << "No ha ingresado una fila valida." << endl;
					cout<<"Ingrese fila de la pieza que desea mover: ";
					cin >> coordenada2;
					y1 = charToInt(coordenada2);
				}//Fin del for

				Position pos(x1,y1);
				if (tablero[y][x]->getColor()=='B' && tablero[y][x] != NULL){//validacion de mover
					if(tablero[y][x]->moveTo(tablero,pos))
						valid = true;//variable de validacion
					else
						valid = false;
				}else{
					cerr << "No se puede mover las piezas del juagdor opuesto" << endl;
				}
			}

		}else{
			while(!valid){//ciclo de validacion
				cout<<"Turno de: "<<nombre2<<endl;
				cout<<"Ingrese columna de la pieza que desea mover: ";
				cin>>x;
				x--;
				cout<<"Ingrese fila de la pieza que desea mover: ";
				cin >> coordenada1;
				y = charToInt(coordenada1);
				cout<<"Ingrese columna a la desea mover la pieza: ";
				cin>>x1;
				x1--;
				cout<<"Ingrese fila a la desea mover la pieza: : ";
				cin >> coordenada2;
				y1 = charToInt(coordenada2);

				Position pos(x1,y1);
				if (tablero[y][x]->getColor()=='N' && tablero[y][x] != NULL){//validacion de mover
					if(tablero[y][x]->moveTo(tablero,pos))
						valid = true;//variable de validacion
					else
						valid = false;
				}else{
					cerr << "No se puede mover las piezas del jugador opuesto" << endl;
				}
			}
		}
		gano = ganar(tablero);
	}

	destruirTablero(tablero,ROWS,COLS);
	return 0;
}
Piece*** crearTablero(int rows, int cols){
	Piece*** retval = new Piece**[rows];
	for (int i = 0; i < rows; ++i)	{
		retval[i] = new Piece*[cols];
	}
	for (int i = 0; i < rows; ++i){
		for (int j = 0; j < cols; ++j){
			retval[i][j] = NULL;
		}
	}
	chessInit(retval);
	return retval;
}
void destruirTablero(Piece*** tablero, int rows, int cols){
	for (int i = 0; i < cols; ++i)	{
		delete[] tablero[i];
	}
	delete[] tablero;
}
void imprimir(Piece*** tablero){//imprimir tablero
	char letras[] = "ABCDEFGH";
	int numeros[] = {1,2,3,4,5,6,7,8};
	for (int i = 0; i < 8; ++i){
		for (int j = 0; j < 8; ++j)	{
			if(tablero[i][j] != NULL)
				cout << "[" << tablero[i][j]->toString() << "]";
			else
				cout << "[ ]";
		}
		cout << letras[i] << endl;
	}
	for (int i = 0; i < 8; ++i)	{
		cout << " " << numeros[i] << " ";
	}
	cout << endl;
}
void chessInit(Piece*** tablero){//Inicializar tablero
	//piezas blancas
	//torres
	tablero[0][0] = new Rook('B',0,0);
	tablero[0][7] = new Rook('B',7,0);
	//caballos
	tablero[0][1] = new Knight('B',1,0);
	tablero[0][6] = new Knight('B',6,0);
	//alfiles
	tablero[0][2] = new Bishop('B',2,0);
	tablero[0][5] = new Bishop('B',5,0);
	//rey
	tablero[0][3] = new King('B',3,0);
	//reina
	tablero[0][4] = new Queen('B',4,0);
	//peones
	for (int i = 0; i < 8; ++i){
		tablero[1][i] = new Pawn('B',i,1);
	}
	//piezas negras
	//torres
	tablero[7][0] = new Rook('N',0,7);
	tablero[7][7] = new Rook('N',7,7);
	//caballos
	tablero[7][1] = new Knight('N',1,7);
	tablero[7][6] = new Knight('N',6,7);
	//alfiles
	tablero[7][2] = new Bishop('N',2,7);
	tablero[7][5] = new Bishop('N',5,7);
	//rey
	tablero[7][3] = new King('N',3,7);
	//reina
	tablero[7][4] = new Queen('N',4,7);
	//peones
	for (int i = 0; i < 8; ++i){
		tablero[6][i] = new Pawn('N',i,6);
	}
}
int charToInt(char coordenada){
	/*
	Cambie el switch case a una serie de if's
	porque así funcionaba.
	Retorna negativo 1 en caso de que no ingrese
	una fila valida.
	*/
	if (coordenada == 'a') {
		return 0;
	} else if (coordenada == 'b') {
		return 1;
	} else if (coordenada == 'c') {
		return 2;
	} else if (coordenada == 'd') {
		return 3;
	} else if (coordenada == 'e') {
		return 4;
	} else if (coordenada == 'f') {
		return 5;
	} else if (coordenada == 'g') {
		return 6;
	} else if (coordenada == 'h') {
		return 7;
	} else 	if (coordenada == 'A') {
		return 0;
	} else if (coordenada == 'B') {
		return 1;
	} else if (coordenada == 'C') {
		return 2;
	} else if (coordenada == 'D') {
		return 3;
	} else if (coordenada == 'E') {
		return 4;
	} else if (coordenada == 'F') {
		return 5;
	} else if (coordenada == 'G') {
		return 6;
	} else if (coordenada == 'H') {
		return 7;
	} else {
		return -1;
	}//Fin de los if
}//Fin del metodo

bool ganar(Piece*** tablero){
	int cont=0;
	for (int i = 0; i < 8; ++i){
		for (int j = 0; j < 8; ++j){
			if(dynamic_cast<King*>(tablero[i][j]) != NULL){
				King* king = dynamic_cast<King*>(tablero[i][j]);
				cont++;
			}
		}
	}
	if (cont==1)
	{
		return true;
	}
	return false;
}
