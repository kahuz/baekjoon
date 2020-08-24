//단순 시뮬레이션이라서 주석을 따로 남기지 않는다
//그저 주어진 조건을 그대로 코딩하면 되는 문제
#include <iostream>
#include <string>

using namespace std;

#define KING 1
#define STONE 2
int map[8][8] = { 0 };

string N, M;
int T = 0;
int king_row, king_col;
int stone_row, stone_col;
void move_king(string move_type)
{
	if (!move_type.compare("R"))
	{
		if (king_col + 1 >= 8)
			return;

		king_col += 1;

		if (king_col == stone_col && king_row == stone_row)
		{
			if (stone_col + 1 >= 8)
			{
				king_col -= 1;
				return;
			}
			stone_col += 1;
		}
	}
	else if (!move_type.compare("L"))
	{
		if (king_col - 1 < 0)
			return;

		king_col -= 1;

		if (king_col == stone_col && king_row == stone_row)
		{
			if (stone_col - 1 < 0)
			{
				king_col += 1;
				return;
			}
			stone_col -= 1;
		}
	}
	else if (!move_type.compare("B"))
	{
		if (king_row + 1 >= 8)
			return;

		king_row += 1;

		if (king_col == stone_col && king_row == stone_row)
		{
			if (stone_row + 1 >= 8)
			{
				king_row -= 1;
				return;
			}
			stone_row += 1;
		}
	}
	else if (!move_type.compare("T"))
	{
		if (king_row - 1 < 0)
			return;

		king_row -= 1;

		if (king_col == stone_col && king_row == stone_row)
		{
			if (stone_row - 1 < 0)
			{
				king_row += 1;
				return;
			}
			stone_row -= 1;
		}
	}
	else if (!move_type.compare("RB"))
	{
		if (king_row + 1 >= 8 || king_col + 1 >= 8)
			return;

		king_row += 1;
		king_col += 1;

		if (king_col == stone_col && king_row == stone_row)
		{
			if (stone_row + 1 >= 8 || stone_col + 1 >= 8)
			{
				king_row -= 1;
				king_col -= 1;
				return;
			}
			stone_row += 1;
			stone_col += 1;
		}
	}
	else if (!move_type.compare("LB"))
	{
		if (king_row + 1 >= 8 || king_col - 1 < 0)
			return;

		king_row += 1;
		king_col -= 1;

		if (king_col == stone_col && king_row == stone_row)
		{
			if (stone_row + 1 >= 8 || stone_col - 1 < 0)
			{
				king_row -= 1;
				king_col += 1;
				return;
			}
			stone_row += 1;
			stone_col -= 1;
		}
	}
	else if (!move_type.compare("RT"))
	{
		if (king_row - 1 < 0 || king_col + 1 >= 8)
			return;

		king_row -= 1;
		king_col += 1;

		if (king_col == stone_col && king_row == stone_row)
		{
			if (stone_row - 1 < 0 || stone_col + 1 >= 8)
			{
				king_row += 1;
				king_col -= 1;
				return;
			}
			stone_row -= 1;
			stone_col += 1;

		}
	}
	else if (!move_type.compare("LT"))
	{
		if (king_row - 1 < 0 || king_col - 1 < 0)
			return;

		king_row -= 1;
		king_col -= 1;

		if (king_col == stone_col && king_row == stone_row)
		{
			if (stone_row - 1 < 0 || stone_col - 1 < 0)
			{
				king_row += 1;
				king_col += 1;
				return;
			}
			stone_row -= 1;
			stone_col -= 1;
		}
	}
}
int main(void)
{
	cin >> N >> M >> T;

	king_row = 8 - (N.at(1) - '0');
	king_col = N.at(0) - 'A';

	stone_row = 8 - (M.at(1) - '0');
	stone_col = M.at(0) - 'A';

	map[king_row][king_col] = KING;
	map[stone_row][stone_col] = STONE;

	for (int i = 0; i < T; i++)
	{
		map[king_row][king_col] = 0;
		map[stone_row][stone_col] = 0;
		string input;
		cin >> input;
		move_king(input);

		map[king_row][king_col] = KING;
		map[stone_row][stone_col] = STONE;

	}
	map[king_row][king_col] = KING;
	map[stone_row][stone_col] = STONE;

	king_col += 'A';
	king_row = (8 - king_row) + '0';
	stone_col += 'A';
	stone_row = (8 - stone_row) + '0';
	string res_king_col, res_king_row;
	res_king_col = (char)king_col;
	res_king_row = (char)king_row;
	string res_stone_col, res_stone_row;
	res_stone_col = (char)stone_col;
	res_stone_row = (char)stone_row;
	cout << res_king_col << res_king_row << endl;
	cout << res_stone_col << res_stone_row << endl;
	return 0;
}