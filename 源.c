#include<stdio.h>
#include<stdlib.h>
#include<windows.h>

void to_xy(int x, int y);
void panel_score();
void background();
void show_pos();
void MoveBox(int x, int y, int xt, int yt);
int isfree(int x, int y, char ch);
void start();
int victory();
void show_goals();
void load(FILE* fp);
void show_map();

char maze[10][10];
int locat1[2] = { 10,10 };		//迷宫坐标
int locat2[2] = { 11,11 };		//当前坐标
int box1[2] = { 18,18 };					//箱子坐标
int box2[2] = { 18,19 };
int box3[2] = { 20,20 };
int goal[3][2] = { { 14,15 },{ 11,13 },{ 17,16 } };
int win = 0;



void main()
{
	char input;
	FILE* fp;
	if (fopen_s(&fp, "map1.txt", "r") != 0)
		puts("cannot open file");
	load(fp);

	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);

	system("color 0f");

	
	//start();

	while (1)
	{
		//background();
		show_map();
		//show_goals();
		show_pos();
		
		if (win)
		{
			win = 0;

			system("color 0f");
			system("cls");
			locat2[0] = 11;
			locat2[1] = 11;
			to_xy(locat1[0], locat1[1]);
			background();
			to_xy(locat2[0], locat2[1]);
			show_pos();
		}

		input = _getch();
		switch (input)
		{
		case'w':
			if(isfree(locat2[1]  - 1, locat2[0],'*'))		//人不靠墙
			{
				if (isfree(locat2[0], locat2[1] - 1, '#'))			//不靠箱子且不靠墙
				{
					
					to_xy(locat2[0], locat2[1]);
					printf(" ");
					locat2[1]--;
				}
				else if (isfree(locat2[0], locat2[1] - 2, '*') && isfree(locat2[0], locat2[1] - 2, '#'))	//靠箱子且可移动
				{
					MoveBox(locat2[0], locat2[1] - 1, locat2[0], locat2[1] - 2);
					to_xy(locat2[0], locat2[1]);
					printf(" ");
					locat2[1]--;
				}
			}

			break;
		case's':
			if (isfree(locat2[1] + 1, locat2[0], '*'))		//人不靠墙
			{
				if (isfree(locat2[0], locat2[1] + 1, '#'))			//不靠箱子且不靠墙
				{

					to_xy(locat2[0], locat2[1]);
					printf(" ");
					locat2[1]++;
				}
				else if (isfree(locat2[0], locat2[1] + 2, '*') && isfree(locat2[0], locat2[1] + 2, '#'))	//靠箱子且可移动
				{
					MoveBox(locat2[0], locat2[1] + 1, locat2[0], locat2[1] + 2);
					to_xy(locat2[0], locat2[1]);
					printf(" ");
					locat2[1]++;
				}
			}

			break;
		case'a':
			if (isfree(locat2[1] , locat2[0]-1, '*'))		//人不靠墙
			{
				if (isfree(locat2[0]-1, locat2[1] , '#'))			//不靠箱子且不靠墙
				{

					to_xy(locat2[0], locat2[1]);
					printf(" ");
					locat2[0]--;
				}
				else if (isfree(locat2[0]-2, locat2[1] , '*') && isfree(locat2[0]-2, locat2[1], '#'))	//靠箱子且可移动
				{
					MoveBox(locat2[0]-1, locat2[1], locat2[0]-2, locat2[1]);
					to_xy(locat2[0], locat2[1]);
					printf(" ");
					locat2[0]--;
				}
			}

			break;
		case'd':
			if (isfree(locat2[1], locat2[0] + 1, '*'))		//人不靠墙
			{
				if (isfree(locat2[0] + 1, locat2[1], '#'))			//不靠箱子且不靠墙
				{

					to_xy(locat2[0], locat2[1]);
					printf(" ");
					locat2[0]++;
				}
				else if (isfree(locat2[0] + 2, locat2[1], '*') && isfree(locat2[0] + 2, locat2[1], '#'))	//靠箱子且可移动
				{
					MoveBox(locat2[0] + 1, locat2[1], locat2[0] + 2, locat2[1]);
					to_xy(locat2[0], locat2[1]);
					printf(" ");
					locat2[0]++;
				}
			}
			break;
	
		}
		if (victory())
		{
			panel_score();
		}
	}
	
}


void to_xy(int x, int y)												//到指定坐标
{
	HANDLE hout;
	COORD coord;
	coord.X = x;
	coord.Y = y;
	hout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hout, coord);
}
void background()
{
	for (int i = 0; i < 10; i++)
	{
		maze[i][0] = maze[i][9] = '*';
		for (int j = 0; j < 10; j++)
		{
			maze[0][j] = maze[9][j] = '*';

		}
	}
	to_xy(locat1[0], locat1[1]);
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			printf("%c", maze[i][j]);
			if (j == 9)
			{
				to_xy(locat1[0], locat1[1] + i + 1);
			}
		}
	}

}


void panel_score()
{
	system("color 0a");

	to_xy(locat1[0] + 8, locat1[1] + 4);
	printf("############################");
	to_xy(locat1[0] + 8, locat1[1] + 5);
	printf("#                          #");
	to_xy(locat1[0] + 8, locat1[1] + 6);
	printf("#                          #");
	to_xy(locat1[0] + 8, locat1[1] + 7);
	printf("#       - VICTORY -        #");
	to_xy(locat1[0] + 8, locat1[1] + 8);
	printf("#                          #");
	to_xy(locat1[0] + 8, locat1[1] + 9);
	printf("#                          #");
	to_xy(locat1[0] + 8, locat1[1] + 10);
	printf("#                          #");
	to_xy(locat1[0] + 8, locat1[1] + 11);
	printf("############################");

	system("pause");
}


void show_pos()
{
	to_xy(locat2[0], locat2[1]);
	printf("O");
}
void show_goals()
{
	if (maze[goal[0][1]-10][goal[0][0]-10]!= '#')
	{
		to_xy(goal[0][0], goal[0][1]);
		printf("%c", '@');
	}
	if (maze[goal[1][1]-10][goal[1][0]-10] != '#')
	{
		to_xy(goal[1][0], goal[1][1]);
		printf("%c", '@');
	}
	if (maze[goal[2][1]-10][goal[2][0]-10] != '#')
	{
		to_xy(goal[2][0], goal[2][1]);
		printf("%c", '@');
	}
}


int isfree(int y, int x,char ch)
{
	if (maze[x-10][y-10] == ch)
		return 0;
	else
		return 1;
}
void MoveBox(int y, int x,int yt,int xt)
{
	maze[x-10][y-10] = ' ';
	maze[xt-10][yt-10] = '#';

}
void start()
{
	maze[6][6] = maze[3][5]=maze[2][4]= '#';
	maze[5][4] = maze[3][1] = maze[6][7] = '@';
}
int victory()
{
	int count =0;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (maze[i][j] == '@')
			{
				count++;

			}
		}
	}
	if (count == 0)
	{
		win = 1;
		return 1;
	}
	else
		return 0;
}
void load(FILE* fp)
{
	char ch;

		
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				fscanf_s(fp, "%c", &ch);
				while (ch == '\n')
					fscanf_s(fp, "%c", &ch);
				maze[i][j] = ch;
			}
		}

}
void show_map()
{
	to_xy(locat1[0], locat1[1]);
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			printf("%c", maze[i][j]);
			if (j == 9)
			{
				to_xy(locat1[0], locat1[1] + i + 1);
			}
		}
	}
}