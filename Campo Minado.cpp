#include <iostream>
#include<cstdlib>
#include <ctime>
using namespace std;

int genBomb(int grade) {
	int num = 0;
	while (num == 0) {
		num = rand() % (grade - 1);
	}
	return num;
}

struct Bomba {
	int line;
	int colum;
};

int main() {
	
	// configurando geração de números
	srand((unsigned) time(NULL));
	
	//inputs
	int grade, nBombas;
	
	cout << "\n Digite o tamanho do campo: ";
	cin >> grade;
	cout << "\n Digite a quantidade de bombas: ";
	cin >> nBombas;
	
	//configurando jogo
	char campo[grade][grade];
	
	for(int l = 0; l < grade; l++){
		for(int c = 0; c < grade; c++) {
			campo[l][c] = '0';
		}
	}
	
	struct Bomba posBombas[nBombas];
	
	int control = 0;
	
	for (int i = 0; i < nBombas; ) {
		struct Bomba newBomb;
		newBomb.line = genBomb(grade);
		newBomb.colum = genBomb(grade);
		if (posBombas[i-1].line != newBomb.line || posBombas[i-1].colum != newBomb.colum ) {	
			posBombas[i] = newBomb;
			campo[posBombas[i].line][posBombas[i].colum] = 'B';
			for(int l = newBomb.line - 1; l <= newBomb.line + 1; l++) {
				for (int c = newBomb.colum - 1; c <= newBomb.colum + 1; c++) {
					if (campo[l][c] != 'B') {
						campo[l][c]++;
					}
				}
			}
			i++;
		}
	}
	
	char hideCamp [grade][grade];
		
	for(int l = 0; l < grade; l++){
		for(int c = 0; c < grade; c++) {
			hideCamp[l][c] = '*';
		}
	}
	
	//jogando
	
	bool finishGame = false;
	
	int winCondition = 0;
	
	while(!finishGame) {
		
		if(winCondition == (grade * grade) - nBombas) {
			cout << "\n VOCE EH UM CAMPEAO";
			finishGame = true;
			break;
		}
		
		char coordX;
		char coordY;

		char coordC = 'A';
		char coordL = 'A';
		
		cout << "(X)";
		for (int i = 0; i < grade; i++) {
			cout << "(" << coordC << ")";
			coordC++;
		}
		
		for(int l = 0; l < grade; l++){
			cout << "\n";
			cout << "(" << coordL << ")";
			coordL++;
			
			for(int c = 0; c < grade; c++) {
				if (hideCamp[l][c] == '*') {
					cout << "[" << hideCamp[l][c] << "]";
				}
				else {
					cout << "{" << hideCamp[l][c] << "}";
				}
			}
		}
		
		cout << "\nDigite a coordenada da Linha: ";
		cin >> coordX;
		cout << "Digite coordenada da Coluna: ";
		cin >> coordY;
		coordX -= 65;
		coordY -= 65;
		
		if(campo[coordX][coordY] == 'B') {
			cout << "\n BOOOOOOOM - VC PERDEU!";
			finishGame = true;
		} 
		else {
			hideCamp[coordX][coordY] = campo[coordX][coordY];
		}
		winCondition++;
	}
}


