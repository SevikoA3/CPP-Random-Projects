#include <iostream>
#include <conio.h>
#include <ctime>
#include <Windows.h>
#include <vector>
#include <stdlib.h>
using namespace std;
//setup var
bool gameOver = false, notPlayAgain = false, check = false;
const int width = 60;
const int height = 21;
int level, mod, score, highscore = 0;
char ch;
//player var
int X1, X2, X3, X4, Y1, Y2, Y3, Y4;
//bullet var
vector<int> bulletX;
vector<int> bulletY;
//meteor var
vector<int> meteorX;
vector<int> meteorY;
int meteorT = 0;

void Setup(){
	bulletX.clear();
	bulletY.clear();
	meteorX.clear();
	meteorY.clear();
	level = 0;
	mod = 20;
	score = 0;
	srand(time(0));
	X1 = height/2;
	X2 = height/2+1;
	X3 = height/2+2;
	X4 = height/2+1;
	Y1 = 1;
	Y2 = 1;
	Y3 = 1;
	Y4 = 2;		
}

void Logic(){
	meteorT++;
	level++;
	if (level % 100 == 0 && mod > 0) mod--;
	if (meteorT % mod == 0){
		meteorX.push_back((rand() % (height-4) + 2));
		meteorY.push_back(width-2);
	}
	if (!bulletX.empty()){
		for (int i = 0; i < bulletX.size(); i++) bulletY[i]++;
	}
	for(int i = 0; i < meteorX.size(); i++){
		meteorY[i]--;
		if (meteorY[i] == 0){
			meteorX.erase(meteorX.begin()+i);
			meteorY.erase(meteorY.begin()+i);
			gameOver = true;
		}
		for (int j = 0; j < bulletX.size(); j++){
			if (bulletY[j] == width-1){
				bulletX.erase(bulletX.begin()+j);
				bulletY.erase(bulletY.begin()+j);
		}
			if ((meteorX[i] == bulletX[j] && meteorY[i] == bulletY[j]) || (meteorX[i] == bulletX[j] && meteorY[i] == bulletY[j]+1)){
				bulletX.erase(bulletX.begin()+j);
			 	bulletY.erase(bulletY.begin()+j);
			 	meteorX.erase(meteorX.begin()+i);
			 	meteorY.erase(meteorY.begin()+i);
			 	score++;
			}
		}
	}
	if (score > highscore) highscore = score;
}

void Input(){
	if (_kbhit()){
		switch (_getch()){
			case 'f' :{
				bulletX.push_back(X2);
				bulletY.push_back(Y2+1);
				break;
			}
			case 'w' :{
				if (X1 == 1) break;
				X1--;
				X2--;
				X3--;
				X4--;
				break;
			}
			case 's' :{
				if (X3 == height-2) break;
				X1++;
				X2++;
				X3++;
				X4++;
				break;
			}
			case 'q' :{
				gameOver = true;
				break;
			}
		}
	}

}

void Draw(){
	system("cls");
	for (int i = 0; i < height; i++){
		for (int j = 0; j < width; j++){
			if (i == 0 || i == height-1) cout << '#';
			else if (j == 0 || j == width-1) cout << "#";
			else if ((i == X1 && j == Y1) || (i == X2 && j == Y2) || (i == X3 && j == Y3) || (i == X4 && j == Y4)) cout << 'O';
			else {
				bool check = true;
				for (int k = 0; k < bulletX.size(); k++){
					if (i == bulletX[k] && j == bulletY[k]) {
						cout << '-';
						check = false;
					}
				}
				for (int k = 0; k < meteorX.size(); k++){
					if (i == meteorX[k] && j == meteorY[k]) {
						cout << '0';
						check = false;
					}
				}
				if (check) cout << ' ';
			}
		}
		cout << endl;
	}
	cout << "score : " << score << endl;
	if (check) cout << "highscore : " << highscore << endl;
	cout << "press 'q' to quit" << endl;
}

int main(){
	ios_base::sync_with_stdio(false); cin.tie(); cout.tie();
	while (!notPlayAgain){
		Setup();
		while (!gameOver){
			Input();
			Logic();
			Draw();
			Sleep(10);
		}
		cout << "Game Over!" << endl;
		if (gameOver) cout << "do you want to play again? (y/n)" << endl;
		cin >> ch;
		if (ch == 'y'){
			gameOver = false;
			check = true;
		}
		else if (ch == 'n') notPlayAgain = true;
	}
	return 0;
}