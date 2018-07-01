#include<iostream>
#include<vector>
#include"Testing.h"
using namespace std;

class Counter
{
	int count, rows, cols;
	vector<vector<bool>> grid;
	int deltaX[4] = { -1,0,0,1 };
	int deltaY[4] = { 0,-1,1,0 };

	bool validRow(const int &row)
	{
		return row >= 0 && row < rows;
	}

	bool validCol(const int &col)
	{
		return col >= 0 && col < cols;
	}

public:

	Counter(const vector<vector<bool>> g):grid(g), rows(g.size()), cols(g[0].size()), count(0){}

	void removeIsland(const int currentRow, const int currentCol)
	{
		grid[currentRow][currentCol] = false;

		int updatedRow, updatedCol;
		//iterating over deltaX and deltaY to move up,left,right,down
		for (int i : {0, 1, 2, 3})
		{
			updatedRow = currentRow + deltaX[i];
			updatedCol = currentCol + deltaY[i];
			if (validRow(updatedRow) && validCol(updatedCol) && grid[updatedRow][updatedCol])
			{
				removeIsland(updatedRow, updatedCol);
			}
		}
	}

	int countIslands()
	{
		for (int r = 0; r < rows; r++)
		{
			for (int c = 0; c < cols; c++)
			{
				if (grid[r][c])
				{
					count++;
					removeIsland(r, c);
				}
			}
		}

		return count;
	}
};

void givenTest()
{
	cout << "Given test...\n";
	vector<vector<bool>> grid = { { false,true,false,true }, { true,true,false,false }, { false,false,true,false }, { false,false,true,false } };
	Counter counter(grid);
	int numberOfIslands = counter.countIslands();
	EXPECT_EQ(3, numberOfIslands);
}

void zeroIslandsTest()
{
	cout << "Zero Islands Test...\n";
	vector<vector<bool>> grid = { { false,false }, { false,false }, { false,false } };
	Counter counter(grid);
	int numberOfIslands = counter.countIslands();
	EXPECT_EQ(0, numberOfIslands);
}

void diagonalIslandTest()
{
	cout << "Diagonal Island Test...\n";
	vector<vector<bool>> grid = { { true,false,false }, { false,true,false }, {false,false,true} };
	Counter counter(grid);
	int numberOfIslands = counter.countIslands();
	EXPECT_EQ(3, numberOfIslands);
}

void oneBigIslandTest()
{
	cout << "One Big Island Test...\n";
	vector<vector<bool>> grid = { { true,true,true,true }, { true,true,true,true }, { true,true,true,true } };
	Counter counter(grid);
	int numberOfIslands = counter.countIslands();
	EXPECT_EQ(1, numberOfIslands);
}

void fiveIslandsTest()
{
	cout << "Five Islands Test...\n";
	vector<vector<bool>> grid = { {true,true,false,true,false}, {true,true,false,true,false}, {false,true,false,true,true}, {false,false,true,false,false}, {false,true,true,true,false}, {true,false,false,false,true} };
	Counter counter(grid);
	int numberOfIslands = counter.countIslands();
	EXPECT_EQ(5, numberOfIslands);
}
int main()
{
	givenTest();
	zeroIslandsTest();
	diagonalIslandTest();
	oneBigIslandTest();
	fiveIslandsTest();
  
	return 0;
}
