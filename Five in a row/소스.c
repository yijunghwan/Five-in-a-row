#include<stdio.h>
#include <Windows.h>//system("cls") ����� ���Ͽ� ����
#include <conio.h>//���۾��� ���ھ��� �Է¹��� ����ϱ� ���Ͽ� ����
int MAP[19][19];//�� ����                                      ����: [x��] [y��](�� 4��и� �̶�� ���� �ϸ��)    0�� ����� 2�� �� 1�� �� 3�� ������
int t = 0;//�ϼ�
void  play_graphic();//�� ���
void end_graphic(int surrender);//���� ���
int input(int* x, int* y);// ������� �Է� �Լ�                ����: ���� �Լ��鿡�� ���� ��ǥ ������ ���Ͽ� ������ �Լ� ���
int check_end(int x, int y);//������ �� �Ǵ� �� ���� �Լ�
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
	printf("���� ��: %d\n", t);
	for (y = 0; y < 19; y++)//y��
	{
		for (x = 0; x < 19; x++)//x��
		{
			switch (MAP[x][y])
			{
			case 1:
				printf("��");//�鵹
				break;
			case 2:
				printf("��");//�浹
				break;
			case 3:
				printf("��");//���� ���� �� ��ġ
				break;
			case 4:
				printf("��");//���� ���� �� ��ġ�� �鵹�� ��ĥ ���     !�̱���!
			case 5:
				printf("��");//���� ���� �� ��ġ�� �浹�� ��ĥ ���     !�̱���! 
			default:
				printf("��");//�� ���� �϶�
				break;
			}
		}
		printf("\n");
	}
	printf("���۹�\n ���� wasd \n �α� space\n ���� \\ ");

}
void end_graphic(int surrender)
{
	if (surrender = 0)
	{
		if (t % 2 + 1 == 1)
		{
			system("cls");
			printf("\n����: �浹\n����: �鵹");
		}
		else
		{
			system("cls");
			printf("\n����: �鵹\n����: �浹");
		}
	}
	else
	{

		if (t % 2 + 1 == 1)
		{
			system("cls");
			printf("\n����: �鵹\n����: �浹");
		}
		else
		{
			system("cls");
			printf("\n����: �浹\n����: �鵹");
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
			if (*x < 0)//�� Ż�� ����
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
		if (d == 32 && before != 0)//�̹� ���� �ִ��� ������ Ȯ��
		{
			d = 1;
			printf("�ذ��! �̹� ���� �ֽ��ϴ�!\n �ٽ� �Է��ϼ���.\n");
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
	int i, j, end, c;//end�� ���ӵ� �� ī��Ʈ c�� �ݴ��� Ž�� Ű���� 
	if (x == EOF)//���� �Ұ��
	{
		end_graphic(1);
		return 0;
	}
	for (i = 0, j = 0, end = 0, c = 0; i < 5; i++, j++)//���� �� Ž��
	{
		if (MAP[x + i][y] == t % 2 + 1 && c == 0)
		{
			end++;
		}
		else if (c == 0)//�ڱ� �ڽ��� �ѹ� �� ī��Ʈ ������ 1�� ����
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

	for (i = 0, j = 0, end = 0, c = 0; i < 5; i++, j++)//���� �� Ž��
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
	for (i = 0, j = 0, end = 0, c = 0; i < 5; i++, j++)//x=y �밢�� Ž��
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
	for (i = 0, j = 0, end = 0, c = 0; i < 5; i++, j++)//x=-y �밢�� Ž��
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