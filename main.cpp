#include <iostream>
#include <queue>
#include <stack>
#define Mx 999999999

using namespace std;

struct info 
{
	int x1, x2, x3, N, Sit;
};

info S,ANSWER;
double X[10];
info memo[400][400][400];
queue <info> cal;
stack <info> Ans;
int num = 1;

void Pic_PrintBed();
void Calibration();
bool fns_check(info X);
void init();
void nodetracking();
void Print_Sit(int Z, int ZCnt);
void Pic_PrintBed2();
void line();

int main()
{
	system("mode con cols=80 lines=30");
	init();
	ANSWER.N = Mx;
	cout << "daVinci 1.1 Plus Print Bed Calibration Program" << endl << "(제작자 :Hanmin 김신건)" << endl;
	Pic_PrintBed();
	
	cout << "위의 그림에 따라 측정된 PrintBed의 높이를 입력하세요." << endl;
	cout << "X1: ";
	cin >> X[1];
	cout << "X2: ";
	cin >> X[2];
	cout << "X3: ";
	cin >> X[3];

	S.x1 = (int)((double)100 * X[1]);
	S.x2 = (int)((double)100 * X[2]);
	S.x3 = (int)((double)100 * X[3]);
	S.N = 0;
	S.Sit = 0;
	memo[S.x1][S.x2][S.x3].N = 0;
	cal.push(S);
	Calibration();
	line();
	cout << "Calibration 후 예상 높이"<<endl;
	cout <<"X1: "<<(double)ANSWER.x1/100 <<" X2: "<< (double)ANSWER.x2/100 << " X3: " << (double)ANSWER.x3/100 << " " << endl;
	line();
	cout << "Calibration 방법" << endl;
	line();
	Pic_PrintBed2();
	line();
	Ans.push(ANSWER);
	nodetracking();
	//system("pause");
}

void init()
{
	for (int x = 0; x < 400; x++)
		for (int y = 0; y < 400; y++)
			for (int z = 0; z < 400; z++)
				memo[x][y][z].N = Mx,memo[x][y][z].Sit=-1;
}

void Pic_PrintBed()
{
	int Size =10;
	cout << "       벽면" << endl;
	for (int y = 1; y <= Size; y++)
	{
		for (int x = 1; x <= Size; x++)
		{
			if (x == 1 && y == 1)cout << (char)1;
			else if (x == Size && y == 1)cout << (char)2;
			else if (x == 1 && y == Size)cout << (char)3;
			else if (x == Size&&y == Size)cout << (char)4;
			else if (x == 1 || x == Size)cout << (char)5;
			else if (y == 1 || y == Size)cout << (char)6 << (char)6;
			else if (x == Size - 1 && y == 2)cout << "X1";
			else if (x == Size - 1 && y == Size - 1)cout << "X2";
			else if (x == 2 && y == Size - 1)cout << "X3";
			else cout << "  ";
		}
		cout << endl;
	}
	cout << "       앞면" << endl << endl;
}

void Pic_PrintBed2()
{
	int Size = 10;
	cout << endl << "       벽면" << endl;
	for (int y = 1; y <= Size; y++)
	{
		for (int x = 1; x <= Size; x++)
		{
			if (x == 1 && y == 1)cout << (char)1;
			else if (x == Size && y == 1)cout << (char)2;
			else if (x == 1 && y == Size)cout << (char)3;
			else if (x == Size&&y == Size)cout << (char)4;
			else if (x == 1 || x == Size)cout << (char)5;
			else if (y == 1 || y == Size)cout << (char)6 << (char)6;
			else if (x == Size - 1 && y == 2)cout << "Y1";
			else if (x == Size / 2 && y == Size - 1)cout << "Y2";
			else if (x == 2 && y == 2)cout << "Y3";
			else cout << "  ";
		}
		cout << endl;
	}
	cout << "       앞면" << endl << endl;
}

void line()
{
	for (int x = 0; x < 60; x++)cout << (char)6;
	cout << endl;
}

bool fns_check(info X)
{
	int Gap,falseCheck=0;
	if (X.x1 > 230 && X.x2 > 230 && X.x3 > 230)
	{
		if(X.x1 < 260 && X.x2 < 260 && X.x3 < 260)
		{
			if (X.x1 > X.x2) Gap = X.x1 - X.x2;
			else Gap = X.x2 - X.x1;
			if (Gap > 20) return false,falseCheck++;

			if (X.x2 > X.x3) Gap = X.x2 - X.x3;
			else Gap = X.x3 - X.x2;
			if (Gap > 20) return false, falseCheck++;

			if (X.x1 > X.x3) Gap = X.x1 - X.x3;
			else Gap = X.x3 - X.x1;
			if (Gap > 20) return false, falseCheck++;

			if (falseCheck == 0) return true;
		}
	}return false;
}

void Calibration()
{
	
	while (!cal.empty()/*&&!fns_check(cal.front())*/)
	{
		info Z;
		int Xnum;
		Z.x1 = cal.front().x1;
		Z.x2 = cal.front().x2;
		Z.x3 = cal.front().x3;
		Z.N = cal.front().N;
		Z.Sit = cal.front().Sit;

		if (fns_check(Z)&&ANSWER.N>Z.N)
		{
			//cout << Z.x1 << " " << Z.x2 << " " << Z.x3 << " " << Z.N << endl;
			ANSWER = Z;
		}
		// 1번 상황
		if (Z.x1 + 24 < 400 && Z.x2 + 12 < 400 && Z.x3 - 12 > 50)
		{
			if (Z.Sit == 1) Xnum = Z.N;
			else Xnum = Z.N + 1;

			if (memo[Z.x1 + 24][Z.x2+ 12][Z.x3 - 12].N > Xnum)
			{
				memo[Z.x1 + 24][Z.x2 + 12][Z.x3 - 12].x1 = Z.x1;
				memo[Z.x1 + 24][Z.x2 + 12][Z.x3 - 12].x2 = Z.x2;
				memo[Z.x1 + 24][Z.x2 + 12][Z.x3 - 12].x3 = Z.x3;
				memo[Z.x1 + 24][Z.x2 + 12][Z.x3 - 12].N = Xnum;
				memo[Z.x1 + 24][Z.x2 + 12][Z.x3 - 12].Sit = 1;

				info SS;
				SS.x1 = Z.x1 + 24;
				SS.x2 = Z.x2 + 12;
				SS.x3 = Z.x3 - 12;
				SS.N = Xnum;
				SS.Sit = 1;
				cal.push(SS);
			}
		}


		//2번 상황
		if (Z.x1 - 24 >50 && Z.x2 - 12 > 50 && Z.x3 + 12 < 400)
		{
			if (Z.Sit == 2) Xnum = Z.N;
			else Xnum = Z.N + 1;

			if (memo[Z.x1 - 24][Z.x2 - 12][Z.x3 + 12].N > Xnum)
			{
				memo[Z.x1 - 24][Z.x2 - 12][Z.x3 + 12].x1 = Z.x1;
				memo[Z.x1 - 24][Z.x2 - 12][Z.x3 + 12].x2 = Z.x2;
				memo[Z.x1 - 24][Z.x2 - 12][Z.x3 + 12].x3 = Z.x3;
				memo[Z.x1 - 24][Z.x2 - 12][Z.x3 + 12].N = Xnum;
				memo[Z.x1 - 24][Z.x2 - 12][Z.x3 + 12].Sit = 2;

				info SS;
				SS.x1 = Z.x1 - 24;
				SS.x2 = Z.x2 - 12;
				SS.x3 = Z.x3 + 12;
				SS.N = Xnum;
				SS.Sit = 2;
				cal.push(SS);
			}
		}

		//3번 상황
		if (Z.x1 > 50 && Z.x2 + 24 < 400 && Z.x3 + 24 < 400)
		{
			if (Z.Sit == 3) Xnum = Z.N;
			else Xnum = Z.N + 1;

if (memo[Z.x1][Z.x2 + 24][Z.x3 + 24].N > Xnum)
{
	memo[Z.x1][Z.x2 + 24][Z.x3 + 24].x1 = Z.x1;
	memo[Z.x1][Z.x2 + 24][Z.x3 + 24].x2 = Z.x2;
	memo[Z.x1][Z.x2 + 24][Z.x3 + 24].x3 = Z.x3;
	memo[Z.x1][Z.x2 + 24][Z.x3 + 24].N = Xnum;
	memo[Z.x1][Z.x2 + 24][Z.x3 + 24].Sit = 3;

	info SS;
	SS.x1 = Z.x1;
	SS.x2 = Z.x2 + 24;
	SS.x3 = Z.x3 + 24;
	SS.N = Xnum;
	SS.Sit = 3;
	cal.push(SS);
}
		}

		//4번 상황

		if (Z.x1 > 50 && Z.x2 - 24 > 50 && Z.x3 - 24 > 50)
		{
			if (Z.Sit == 4) Xnum = Z.N;
			else Xnum = Z.N + 1;

			if (memo[Z.x1][Z.x2 - 24][Z.x3 - 24].N > Xnum)
			{
				memo[Z.x1][Z.x2 - 24][Z.x3 - 24].x1 = Z.x1;
				memo[Z.x1][Z.x2 - 24][Z.x3 - 24].x2 = Z.x2;
				memo[Z.x1][Z.x2 - 24][Z.x3 - 24].x3 = Z.x3;
				memo[Z.x1][Z.x2 - 24][Z.x3 - 24].N = Xnum;
				memo[Z.x1][Z.x2 - 24][Z.x3 - 24].Sit = 4;

				info SS;
				SS.x1 = Z.x1;
				SS.x2 = Z.x2 - 24;
				SS.x3 = Z.x3 - 24;
				SS.N = Xnum;
				SS.Sit = 4;
				cal.push(SS);
			}
		}

		//5번 상황

		if (Z.x1 > 50 && Z.x2 - 24 > 50 && Z.x3 + 24 < 400)
		{
			if (Z.Sit == 5) Xnum = Z.N;
			else Xnum = Z.N + 1;

			if (memo[Z.x1][Z.x2 - 24][Z.x3 + 24].N > Xnum)
			{
				memo[Z.x1][Z.x2 - 24][Z.x3 + 24].x1 = Z.x1;
				memo[Z.x1][Z.x2 - 24][Z.x3 + 24].x2 = Z.x2;
				memo[Z.x1][Z.x2 - 24][Z.x3 + 24].x3 = Z.x3;
				memo[Z.x1][Z.x2 - 24][Z.x3 + 24].N = Xnum;
				memo[Z.x1][Z.x2 - 24][Z.x3 + 24].Sit = 5;

				info SS;
				SS.x1 = Z.x1;
				SS.x2 = Z.x2 - 24;
				SS.x3 = Z.x3 + 24;
				SS.N = Xnum;
				SS.Sit = 5;
				cal.push(SS);
			}
		}

		//6번 상황

		if (Z.x1 > 50 && Z.x2 + 24 < 400 && Z.x3 - 24 > 50)
		{
			if (Z.Sit == 6) Xnum = Z.N;
			else Xnum = Z.N + 1;

			if (memo[Z.x1][Z.x2 + 24][Z.x3 - 24].N > Xnum)
			{
				memo[Z.x1][Z.x2 + 24][Z.x3 - 24].x1 = Z.x1;
				memo[Z.x1][Z.x2 + 24][Z.x3 - 24].x2 = Z.x2;
				memo[Z.x1][Z.x2 + 24][Z.x3 - 24].x3 = Z.x3;
				memo[Z.x1][Z.x2 + 24][Z.x3 - 24].N = Xnum;
				memo[Z.x1][Z.x2 + 24][Z.x3 - 24].Sit = 6;

				info SS;
				SS.x1 = Z.x1;
				SS.x2 = Z.x2 + 24;
				SS.x3 = Z.x3 - 24;
				SS.N = Xnum;
				SS.Sit = 6;
				cal.push(SS);
			}
		}

		cal.pop();
	}
}

void nodetracking()
{
	//cout << endl;
	while (Ans.top().N != 0)
	{
		info ZZ;
		ZZ.x1 = memo[Ans.top().x1][Ans.top().x2][Ans.top().x3].x1;
		ZZ.x2 = memo[Ans.top().x1][Ans.top().x2][Ans.top().x3].x2;
		ZZ.x3 = memo[Ans.top().x1][Ans.top().x2][Ans.top().x3].x3;
		ZZ.N = memo[Ans.top().x1][Ans.top().x2][Ans.top().x3].N;
		ZZ.Sit = memo[Ans.top().x1][Ans.top().x2][Ans.top().x3].Sit;
		Ans.push(ZZ);
		//cout << ZZ.x1 << " " << ZZ.x2 << " " << ZZ.x3 << endl;
	}

	//cout << endl;
	int Z = -1, ZCnt = 0;
	while (!Ans.empty())
	{
		//cout << Ans.top().Sit << endl;
		if (Ans.size() == 1)
		{
			Print_Sit(Ans.top().Sit, ZCnt);
		}
		else if (Z == Ans.top().Sit)
		{
			ZCnt++;
		} 
		else
		{
			Print_Sit(Z, ZCnt);
			Z = Ans.top().Sit;
			ZCnt = 1;
		}
		Ans.pop();
	}
}

void Print_Sit(int Z, int ZCnt)
{
	
	switch (Z)
	{
	case 1:
		cout << num++ << "번째 작업: ";
		cout << "Y1 조정나사를 사용자의 방향으로 ";
		break;
	case 2:
		cout << num++ << "번째 작업: ";
		cout << "Y1 조정나사를 사용자의 반대 방향으로 ";
		break;
	case 3:
		cout << num++ << "번째 작업: ";
		cout << "Y2 조정나사를 왼쪽으로 ";
		break;
	case 4:
		cout << num++ << "번째 작업: ";
		cout << "Y2 조정나사를 오른쪽으로 ";
		break;
	case 5:
		cout << num++ << "번째 작업: ";
		cout << "Y3 조정나사를 사용자의 반대 방향으로 ";
		break;
	case 6:
		cout << num++ << "번째 작업: ";
		cout << "Y3 조정나사를 사용자의 방향으로 ";
		break;
	}

	if (Z!=0&&Z!=-1&&ZCnt % 4 == 0)
	{
		cout << ZCnt / 4 << "바퀴 돌려주세요." << endl;
	}
	else if(Z != 0 && Z != -1&&ZCnt/4!=0)
	{
		cout << ZCnt / 4 << "바퀴 돌린 후 " << "4분의 " << ZCnt % 4 << "바퀴 돌려주세요." << endl;
	}
	else if(Z != 0 && Z != -1)
	{
		cout<< "4분의 " << ZCnt % 4 << "바퀴 돌려주세요." << endl;
	}
}
