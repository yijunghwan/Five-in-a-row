#include<stdio.h>
#include <Windows.h>//system("cls") 사용을 위하여 포함
#include <conio.h>//버퍼없고 에코없는 입력문을 사용하기 위하여 포함
int MAP[19][19];//맵 변수                                      설명: [x축] [y축](제 4사분면 이라고 생각 하면됨)    0은 빈공간 2는 흑 1은 흰돌 3은 선택중
int t = 0;//턴수
void  play_graphic();//맵 출력
void end_graphic(int surrender);//승패 출력
int input(int* x, int* y);// 사용자의 입력 함수                설명: 이후 함수들에도 사용될 좌표 정보를 위하여 포인터 함수 사용
int check_end(int x, int y);//게임의 끝 판단 및 끝냄 함수
int main()
{
	int x = 0, y = 0;
	do
	{
		t++;
		input(&x, &y);
	} while (check_end(x, y));
	return 0;
}
void play_graphic()
{
	system("cls");
	int x, y;
	printf("현재 턴: %d\n", t);
	for (y = 0; y < 19; y++)//y축
	{
		for (x = 0; x < 19; x++)//x축
		{
			switch (MAP[x][y])
			{
			case 1:
				printf("●");//백돌
				break;
			case 2:
				printf("○");//흑돌
				break;
			case 3:
				printf("ж");//현재 선택 한 위치
				break;
			case 4:
				printf("◆");//현재 선택 한 위치가 백돌과 겹칠 경우     !미구현!
			case 5:
				printf("◇");//현재 선택 한 위치가 흑돌과 겹칠 경우     !미구현! 
			default:
				printf("·");//빈 공간 일때
				break;
			}
		}
		printf("\n");
	}
	printf("조작법\n 방향 wasd \n 두기 space\n 서랜 \\ ");

}
void end_graphic(int surrender)
{
	if (surrender = 0)
	{
		if (t % 2 + 1 == 1)
		{
			system("cls");
			printf("\n승자: 흑돌\n패자: 백돌");
		}
		else
		{
			system("cls");
			printf("\n승자: 백돌\n패자: 흑돌");
		}
	}
	else
	{

		if (t % 2 + 1 == 1)
		{
			system("cls");
			printf("\n승자: 백돌\n패자: 흑돌");
		}
		else
		{
			system("cls");
			printf("\n승자: 흑돌\n패자: 백돌");
		}
	}
}
int input(int* x, int* y)
{
	char d = 0;
	*x = 9;
	*y = 9;
	int before = MAP[*x][*y];
	MAP[*x][*y] = 3;
	play_graphic();
	while (d != 32)
	{
		d = _getch();
		MAP[*x][*y] = before;
		switch (d)
		{
		case 'A':
		case 'a':
			(*x)--;
			if (*x < 0)//맵 탈출 방지
				*x = 0;
			break;
		case'D':
		case'd':
			(*x)++;
			if (*x > 18)
				*x = 18;
			break;
		case 'S':
		case 's':
			(*y)++;
			if (*y > 18)
				*y = 18;
			break;
		case 'W':
		case 'w':
			(*y)--;
			if (*y < 0)
				*y = 0;
			break;
		case '\\':
			(*x) = EOF;
			return 0;
		default:
			break;
		}
		if (d == 32 && before != 0)//이미 돌이 있는지 없는지 확인
		{
			d = 1;
			printf("※경고! 이미 돌이 있습니다!\n 다시 입력하세요.\n");
			continue;
		}
		before = MAP[*x][*y];
		MAP[*x][*y] = 3;
		play_graphic();
	}
	MAP[*x][*y] = t % 2 + 1;
	return 0;
}
int check_end(int x, int y)
{
	int i, j, end, c;//end가 연속된 돌 카운트 c는 반대쪽 탐색 키워드 
	if (x == EOF)//서랜 할경우
	{
		end_graphic(1);
		return 0;
	}
	for (i = 0, j = 0, end = 0, c = 0; i < 5; i++, j++)//가로 줄 탐색
	{
		if (MAP[x + i][y] == t % 2 + 1 && c == 0)
		{
			end++;
		}
		else if (c == 0)//자기 자신을 한번 더 카운트 함으로 1로 설정
		{
			c++;
			i = 1;
			j = 1;
		}
		if (MAP[x - i][y] == t % 2 + 1 && c == 1)
		{
			end++;
		}
	}
	if (end > 4)
	{
		end_graphic(0);
		return 0;
	}

	for (i = 0, j = 0, end = 0, c = 0; i < 5; i++, j++)//세로 줄 탐색
	{
		if (MAP[x][y + j] == t % 2 + 1 && c == 0)
		{
			end++;
		}
		else if (c == 0)
		{
			c++;
			i = 1;
			j = 1;
		}
		if (MAP[x][y - j] == t % 2 + 1 && c == 1)
		{
			end++;
		}
	}
	if (end > 4)
	{
		end_graphic(0);
		return 0;
	}
	for (i = 0, j = 0, end = 0, c = 0; i < 5; i++, j++)//x=y 대각선 탐색
	{
		if (MAP[x + i][y - j] == t % 2 + 1 && c == 0)
		{
			end++;
		}
		else if (c == 0)
		{
			c++;
			i = 1;
			j = 1;
		}
		if (MAP[x - i][y + j] == t % 2 + 1 && c == 1)
		{
			end++;
		}

	}
	if (end > 4)
	{
		end_graphic(0);
		return 0;
	}
	for (i = 0, j = 0, end = 0, c = 0; i < 5; i++, j++)//x=-y 대각선 탐색
	{
		if (MAP[x + i][y + j] == t % 2 + 1 && c == 0)
		{
			end++;
		}
		else if (c == 0)
		{
			c++;
			i = 1;
			j = 1;
		}
		if (MAP[x - i][y - j] == t % 2 + 1 && c == 1)
		{
			end++;
		}
	}
	if (end > 4)
	{
		end_graphic(0);
		return 0;
	}
	return 1;
}