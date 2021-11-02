#include <iostream>
#include <conio.h>
#include <ctime>
#include <Windows.h>
using namespace std;
//variables
bool gameOver = false;
bool playAgain = false;
const int width = 40, height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int ntail;
int highScore = 0;
enum direction {STOP = 0, UP, DOWN, LEFT, RIGHT};
direction dir;

void Setup(){
	srand(time(0));
	x = width/2;
	y = height/2;
	fruitX = rand() % (width);
	fruitY = rand() % (height);
	dir = STOP;
	ntail = 0;
	score = 0;
}

void Draw(){
	system("cls");
	for (int i = 0; i <= width; i++) cout << '#';
	cout << endl;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j <= width; j++){
			if (j == 0 || j == width) cout << '#';
			else if (i == y && j == x) cout << 'O';
			else if (i == fruitY && j == fruitX) cout << 'f';
			else {
				bool check = true;
				for (int k = 0; k < ntail; k++){
					if (tailX[k] == j && tailY[k] == i) {cout << "o"; check = false;}
				}
				if (check) cout << ' ';
			}
		}
		cout << endl;
	}
	for (int i = 0; i <= width; i++) cout << '#';
	cout << endl;
	cout << "score : " << score << endl;
	if (score > highScore) highScore = score;
	if (playAgain) cout << "Your high score : " << highScore << endl;
}

void Logic(){
	if (fruitX == 0 || fruitX == width || fruitY == -1 || fruitX == height){
		fruitX = rand() % (width);
		fruitY = rand() % (height);
	}

	if (x == 0) x = width-1;
	else if (x == width) x = 1;
	if (y == -1) y = height-1;
	else if (y == height) y = 0;

	for (int i = ntail; i > 0; i--){
		tailX[i] = tailX[i-1];
		tailY[i] = tailY[i-1];	
	}
	tailX[0] = x;
	tailY[0] = y;

	switch (dir) {
		case LEFT :
			x--;
			break;
		case RIGHT :
			x++;
			break;
		case UP :
			y--;
			break;
		case DOWN :
			y++;
			break;	
	}
	if (x == fruitX && y == fruitY){
		ntail++;
		score++;
		fruitX = rand() % width;
		fruitY = rand() % height;
	}
	for (int i = 0; i < ntail; i++){
		if (tailX[i] == x && tailY[i] == y) gameOver = true;
	}

}
void Input(){
	if (_kbhit()){
		switch (_getch()){
			case 'a' :
				dir = LEFT;
				break;
			case 'd' :
				dir = RIGHT;
				break;
			case 'w' :
				dir = UP;
				break;
			case 's' :
				dir = DOWN;
				break;
			case 'q' :
				gameOver = true;
				break;
		}
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	while (true){
		Setup();
		while (!gameOver){
			Input();
			Logic();
			Draw();
			Sleep(10);
		}
		if (gameOver) cout << "Game Over!\n";
		char exit;
		cout << "Do you want to play again? (y/n)\n";
		cin >> exit;
		if (exit == 'n') break;
		else if (exit == 'y') {gameOver = false; playAgain = true;}
	}
	system("pause");
	return 0;
}