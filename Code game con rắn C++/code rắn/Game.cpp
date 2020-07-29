#include<iostream>
#include<ctime>
#include"Console.h"
using namespace std;
#define SNAKE_BODY_CHAR 15
#define SNAKE_HEAD_CHAR 111
#define MAX 150
#define FOOD_CHAR 42

//phím di chuyển
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

//tọa độ các tường
#define ON_WALL 2
#define BELOW_WALL 18
#define LEFT_WALL 3
#define RIGHT_WALL 24

//tạo tường trên bằng kí hiệu
#define ON_WALL_CHAR 220
#define BELOW_WALL_CHAR 223
#define LEFT_WALL_CHAR 221
#define RIGHT_WALL_CHAR 222
struct Coordinate {
	int x, y;
};
Coordinate snake[MAX];
int score = 0;//điểm ban đầu
int length = 3;//số lượng đốt rắn ban đầu
int direction = RIGHT;//hướng đi mặc định
int speed = 300;//tốc độ ban đầu của rắn

void Create_snake();//tạo tọa độ rắn ban đầu
void Display_snake(Coordinate tail_old);

void Draw_wall();//vẽ tường để rắn chạy và kiểm tra thua khi đụng tường

void Change_direction(int& direction);//thay đổi hướng đi
Coordinate Move(int direction);

Coordinate Display_food();//tạo mồi mới

bool Check_lose();//kiểm tra thua
void Lose();//hàm xuất ra màn hình khi thua
void Win();//hàm xuất khi đốt rắn đã đầy, game thắng

bool Check_food(Coordinate food_coordinate);//kiểm tra ăn mồi để thêm đốt
int Add_tail();//hàm thêm đốt khi đã ăn mồi
int main() {
	resizeConsole(1000, 500);//sửa đổi khung hình console
	noCursorType();//xóa con trỏ nháy
	Draw_wall();
	Create_snake();
	Coordinate food_coordinate = Display_food();
	gotoXY(LEFT_WALL, ON_WALL - 1);
	cout << "Diem: " << score;
	while (1) {
		Coordinate tail_old = Move(direction);
		Change_direction(direction);
		Display_snake(tail_old);
		if (Check_food(food_coordinate) == true) {
			food_coordinate = Display_food();
			if (Add_tail() == MAX + 1) {
				break;
			}
			score++;
			speed--;
			gotoXY(LEFT_WALL + 6, ON_WALL - 1);
			cout << score;
		}
		if (Check_lose() == true)
			break;
		Sleep(speed);
	}
	if (length == MAX + 1) Win();
	else Lose();
	system("pause");
}
void Create_snake() {
    snake[0].x = LEFT_WALL + 3;
	snake[1].x = LEFT_WALL + 2;
	snake[2].x = LEFT_WALL + 1;
	snake[0].y = snake[1].y = snake[2].y = ON_WALL + 1;
}
void Display_snake(Coordinate tail_old) {
	gotoXY(snake[0].x, snake[0].y);
	cout << (char)SNAKE_HEAD_CHAR;
	for (int i = 1; i < length; i++) {
		gotoXY(snake[i].x, snake[i].y);
		cout << (char)SNAKE_BODY_CHAR;
	}
	gotoXY(tail_old.x, tail_old.y);
	cout << " ";
}
void Draw_wall() {
	for (int i = LEFT_WALL; i <= RIGHT_WALL; i++) {
		gotoXY(i, ON_WALL);
		cout << (char)ON_WALL_CHAR;
		gotoXY(i, BELOW_WALL + 1);
		cout << (char)BELOW_WALL_CHAR;
	}
	for (int i = ON_WALL + 1; i <= BELOW_WALL; i++) {
		gotoXY(LEFT_WALL, i);
		cout << (char)LEFT_WALL_CHAR;
		gotoXY(RIGHT_WALL, i);
		cout << (char)RIGHT_WALL_CHAR;
	}
}
void Change_direction(int& direction) {
	int Key = inputKey();
	if (Key == 'w' || Key == 'W' || Key == KEY_UP) direction = UP;
	else if (Key == 's' || Key == 'S' || Key == KEY_DOWN) direction = DOWN;
	else if (Key == 'd' || Key == 'D' || Key == KEY_RIGHT) direction = RIGHT;
	else if (Key == 'a' || Key == 'A' || Key == KEY_LEFT) direction = LEFT;
}
Coordinate Move(int direction) {
	Coordinate dotCuoiCu = snake[length - 1];
	for (int i = length - 1; i >= 1; i--) {
		snake[i] = snake[i - 1];
	}
	switch (direction) {
	case UP:
		snake[0].y--;
		break;
	case DOWN:
		snake[0].y++;
		break;
	case LEFT:
		snake[0].x--;
		break;
	case RIGHT:
		snake[0].x++;
		break;
	}
	return dotCuoiCu;
}
Coordinate Display_food() {
	srand(time(NULL));
	int x = LEFT_WALL + 1 + rand() % (RIGHT_WALL - 1 - (LEFT_WALL + 1) + 1);
	int y = ON_WALL + 1 + rand() % (BELOW_WALL - 1 - (ON_WALL + 1) + 1);
	//rand[a, b] = b rand() % (a - b + 1)
	gotoXY(x, y);
	cout << (char)FOOD_CHAR;
	return Coordinate{ x, y };
}
bool Check_lose() {
	if (snake[0].y == ON_WALL || snake[0].y == BELOW_WALL || 
		snake[0].x == LEFT_WALL || snake[0].x == RIGHT_WALL) return true;
}
void Lose() {
	system("cls");
	cout << "Game lost.\nDiem: " << score << endl;
}
void Win() {
	system("cls");
	cout << "Game won." << endl;
}
bool Check_food(Coordinate food_coordinate) {
	if (snake[0].x == food_coordinate.x && snake[0].y == food_coordinate.y) return true;
	else return false;
}
int Add_tail() {
	snake[length] = snake[length - 1];
	length++;
	return length;
}