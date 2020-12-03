#include <iostream>
#include "Header.h"


using namespace std;
struct Point
{
	int x, y;
};
#define MAX 100
int length = 4; // chieu dai ban dau cua ran
bool endGame; // trang thai cua game(ket thuc hay chua)
int point = 0; // diem so cua nguoi choi
Point ran[MAX];

void ve_tren();
void ve_duoi();
void ve_phai();
void ve_trai();
void draw();
void snake(int toadox[], int toadoy[]); // ve ran
void delete_snake(int toadox[], int toadoy[]); // xoa duoi cua con ran
void init_snake(int toadox[], int todoy[]); // khoi tao ran
void them(int a[], int x);
void xoa(int a[], int vt);
void xu_ly_ran(int toadox[], int toadoy[], int x, int y, int &xfood, int &yfood);
bool check_cham_tuong(int x, int y);
bool check_cham_duoi(int toadox[], int toadoy[]);
bool check_endGame(int toadox[], int toadoy[]);
void draw_food(int& xfood, int& yfood, int toadox[], int toadoy[]);
bool check_ran_de_qua(int xfood, int yfood, int toadox[], int toadoy[]);
bool checkEatFood(int xfood, int yfood, int toadox[], int toadoy[]);
int main()
{
	srand(time(NULL));
	int toadox[MAX], toadoy[MAX];
	draw();
	init_snake(toadox, toadoy);
	snake(toadox, toadoy);
	int xfood = 0, yfood = 0;
	draw_food(xfood, yfood, toadox, toadoy);	
	int x = 50, y = 13;
	int check = 2;
	while (endGame == false)
	{
		gotoXY(45, 1);
		SetColor(10);
		cout << "GAME RAN SAN MOI" << endl;
		gotoXY(50, 2);
		cout << "SCORE:" << point << endl;
		SetColor(7);
		// 0 : di xuong
		// 1 : di len
		// 2 : qua phai 
		// 3 : qua trai
		//dieu khien
		if (_kbhit()) // tra ve true neu nguoi dung nhap tu ban phim
		{
			char kitu = _getch();
			if (kitu == -32)
			{
				kitu = _getch();
				if (kitu == 72 && check != 0) // di len
				{
					check = 1;
				}
				else if (kitu == 80 && check != 1) // di xuong
				{
					check = 0;
				}
				else if (kitu == 77 && check != 3) // qua phai
				{
					check = 2;
				}
				else if (kitu == 75 && check != 2) // qua trai
				{
					check = 3;
				}
			}
		}
		// di chuyen
		if (check == 0) // di xuong
		{
			y++;
		}
		else if (check == 1) // di len
		{
			y--;
		}
		else if (check == 2) // qua phai
		{
			x++;
		}
		else if (check == 3) // qua trai
		{
			x--;
		}	
		delete_snake(toadox, toadoy);
		xu_ly_ran(toadox, toadoy, x, y, xfood, yfood);
		endGame = check_endGame(toadox, toadoy);
		Sleep(100);
	}
	SetColor(10);
	system("cls");
	cout << "GAME OVER" << endl;
	cout << "SCORE: " << point << endl;
	SetColor(7);
	_getch();
	return 0;
}

void ve_tren() // ve tuong phia tren
{
	int x = 10;
	int y = 3;
	while (x <= 100)
	{
		gotoXY(x, y);
		cout << "=";
		x++;
	}
}
void ve_duoi()
{

	int x = 10;
	int y = 30;
	while (x <= 100)
	{
		gotoXY(x, y);
		cout << "=";
		x++;
	}
}
void ve_phai()
{
	int x = 100;
	int y = 3;
	while (y <= 30)
	{
		gotoXY(x, y);
		cout << "=";
		y++;
	}
}
void ve_trai()
{
	int x = 10;
	int y = 3;
	while (y <= 30)
	{
		gotoXY(x, y);
		cout << "=";
		y++;
	}
}
void draw()
{
	SetColor(11);
	ve_tren();
	ve_duoi();
	ve_phai();
	ve_trai();
	SetColor(7);
}
void init_snake(int toadox[], int toadoy[])
{
	//toa do ran xuat hien
	int x = 50;
	int y = 13;
	for (int i = 0; i < length; i++)
	{
		toadox[i] = x;
		toadoy[i] = y;
		x--;
	}
}
void snake(int toadox[], int toadoy[])
{
	for (int i = 0; i < length; i++)
	{
		gotoXY(toadox[i], toadoy[i]);
		if (i == 0)
		{
			cout << "0";
		}
		else
		{
			cout << "o";
		}
	}
}
void delete_snake(int toadox[], int toadoy[]) // xoa duoi cua con ran
{
	for (int i = 0; i < length; i++)
	{
		gotoXY(toadox[i], toadoy[i]);
		cout << " ";
	}
}
void xu_ly_ran(int toadox[], int toadoy[], int x, int y, int &xfood, int &yfood)
{
	them(toadox, x);
	them(toadoy, y);
	if (checkEatFood(xfood, yfood, toadox, toadoy) == false)
	{
		xoa(toadox, length - 1);
		xoa(toadoy, length - 1);
	}
	else
	{
		draw_food(xfood, yfood, toadox, toadoy);
		point++;	
	}
	snake(toadox, toadoy);
}
void them(int a[], int x)
{
	for (int i = length; i > 0; i--)
	{
		a[i] = a[i - 1];
	}
	a[0] = x;
	length++;
}
void xoa(int a[], int vt)
{
	for (int i = vt; i < length; i++)
	{
		a[i] = a[i + 1];
	}
	length--;
}
bool check_cham_tuong(int x, int y)
{
	if (y == 3 && (x >= 10 && x <= 100)) // cham vao tuong tren
	{
		return true;
	}
	else if (y == 30 && (x >= 10 && x <= 100)) // cham vao tuong duoi
	{
		return true;
	}
	else if (x == 100 && (y >= 5 && y <= 30)) // cham vao tuong phai
	{
		return true;
	}
	else if (x == 10 && (y >= 5 && y <= 30)) // cham vao tuong trai
	{
		return true;
	}
	return false;
}
bool check_cham_duoi(int toadox[], int toadoy[])
{
	for (int i = 1; i < length; i++)
	{
		if (toadox[0] == toadox[i] && toadoy[0] == toadoy[i])
		{
			return true;
		}
	}
	return false;
}
bool check_endGame(int toadox[], int toadoy[])
{
	bool kt1 = check_cham_duoi(toadox, toadoy);
	bool kt2 = check_cham_tuong(toadox[0], toadoy[0]);
	if (kt1 == true || kt2 == true)
	{
		return true;
	}
	return false;
}
void draw_food(int &xfood, int &yfood, int toadox[], int toadoy[])
{
	do
	{
		xfood = rand() % (99 - 11 + 1) + 11;
		yfood = rand() % (25 - 2 + 1) + 2;
	} while (check_ran_de_qua(xfood, yfood, toadox, toadoy) == true);
	int i = rand() % 15 + 1;
	SetColor(i);
	gotoXY(xfood, yfood);
	cout << "$";
	SetColor(7);
}
bool check_ran_de_qua(int xfood, int yfood, int toadox[], int toadoy[])
{
	for (int i = 0; i < length; i++)
	{
		if (xfood == toadox[i] && yfood == toadoy[i])
		{
			return true;
		}
	}
	return false;
}
bool checkEatFood(int xfood, int yfood, int toadox[], int toadoy[])
{
	if (toadox[0] == xfood && toadoy[0] == yfood)
	{
		return true;
	}
	return false;
}