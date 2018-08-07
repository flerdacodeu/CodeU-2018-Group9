#include <vector>
#include "Unit_tests.h"


void test_emptyGrid()
{
	std::vector<std::vector<bool>> grid
	{};
	Islands i(grid);
    EXPECT_EQ(0, i.countIslands(grid, i.rows, i.cols));	

}

void tets_noWater()
{
	std::vector<std::vector<bool>> grid
	{ 	{0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
	};
	Islands i(grid);
    EXPECT_EQ(0, i.countIslands(grid, i.rows, i.cols));	

}

void test_allWater()
{
	std::vector<std::vector<bool>> grid
	{ 	{1, 1, 1, 1},
        {1, 1, 1, 1},
        {1, 1, 1, 1},
        {1, 1, 1, 1}
	};
	Islands i(grid);
    EXPECT_EQ(1, i.countIslands(grid, i.rows, i.cols));	
}

void test_wholeRowIslands()
{
	std::vector<std::vector<bool>> grid
	{ 	{1, 1, 1, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
	};
	Islands i(grid);
    EXPECT_EQ(1, i.countIslands(grid, i.rows, i.cols));	

}

void test_wholeColIslands()
{
	std::vector<std::vector<bool>> grid
	{ 	{0, 0, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 1, 0}
	};
	Islands i(grid);
    EXPECT_EQ(1, i.countIslands(grid, i.rows, i.cols));	

}

void test_assignmentExample()
{
	std::vector<std::vector<bool>> grid
	{ 	{0, 1, 0, 1},
        {1, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 1, 0}
	};
	Islands i(grid);
    EXPECT_EQ(3, i.countIslands(grid, i.rows, i.cols));	

}
 
int main()
{
	void test_emptyGrid();
	void tets_noWater();
	void test_allWater();
	void test_allIslands();
	void test_wholeRowIslands();
	void test_wholeColIslands();
	void test_assignmentExample();
	return 0;
}
