#include <vector>

class Islands 
{
	private: 
		std::vector<std::vector<bool>> grid; 
	public: 
		int rows;
		int cols;
		Islands(std::vector<std::vector<bool>> grid);
		bool isValid(const std::vector<std::vector<bool>> &mat, int row, int col, int rows, int cols, const std::vector<std::vector<bool>> &visited);
		void DFS(const std::vector<std::vector<bool>> &mat, int row, int col, int rows, int cols, std::vector<std::vector<bool>> &visited);
		int countIslands(const std::vector<std::vector<bool>> &mat, int rows, int cols);

};
