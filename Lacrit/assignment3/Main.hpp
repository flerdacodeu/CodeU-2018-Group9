#include <map>
#include <string>
#include <unordered_set>
#include <vector>
#include "Dictionary.hpp"

// prolly not the best solution to store it like that
int rows = 2;
int cols = 3;

class Main {
private:
 	struct cell {
        std::string value;
        int row;
        int col;
        std::vector<int> neighbours;
        cell(int row, int col);
    };	
	std::vector<cell> board;
    Dictionary dict;
    std::unordered_set<std::string> found_words;
    void Words(int pos, std::string str = "", std::unordered_set<int> visited = std::unordered_set<int>());

public:
    Main(Dictionary dict);
    ~Main();

    void Load(std::string letters);
    void Print();
	std::unordered_set<std::string> Result(); 
};

// Main board constructor
Main::Main(Dictionary dict) 
{
	this->dict = dict;
	int row = 0; 
	int col = 0;

	
  for (int i = 0; i < rows; i++) {
	  row = i / rows;
	  for ( int j = 0; j < cols; j++) {
        col = j % cols;
        board.push_back(cell(row, col));
	  }
  }

  //get all neighbours of a cell
  std::vector<int> shift {-1, 0, 1};
    for (cell &sq : board) {
        for (int row_shift : shift) {
            for (int col_shift : shift) {
                row = sq.row + row_shift;
                col = sq.col + col_shift;
                if (row >= 0 & row < rows & col >= 0 & col < cols & !(row_shift == 0 & col_shift == 0)) {
                    sq.neighbours.push_back(row * rows + col);
                }
            }
        }
    }
}

Main::~Main() {}

Main::cell::cell(int row, int col): 
    row(row),
    col(col)
{}

// Load a string of letters into the board
void Main::Load(std::string letters) {
 int i = 0;
    for (cell &it : board) {
        it.value = letters[i];
        i += 1;
    }
    // Clear any previously found words
    found_words.clear();
}
	
// Print the board
void Main::Print() {
for (const cell &sq : board) {
        std::cout << sq.value << " ";
        if (sq.col == cols - 1) {
         std::cout << std::endl;
        }
    }
}

std::unordered_set<std::string> Main::Result() 
{
	// a
	// Find words for all cells on the board
	for (size_t i = 0; i < board.size(); i++) 
	{
        Words(i);
    }
	return found_words;
}

// Find all words starting at a given position
void Main::Words(int position, std::string string, std::unordered_set<int> visited) {

  cell &sq = board[position];
    string += sq.value;
    visited.insert(position);

    // If the string is a word, add it to the found words
    if (dict.words.find(string) != dict.words.end()) {
        found_words.insert(string);
    }

    // If the string is a prefix, continue looking
    if (dict.prefixes.find(string) != dict.prefixes.end()) {
        for (const int &neighbour : sq.neighbours) {
            if (visited.find(neighbour) == visited.end()) {
                Words(neighbour, string, visited);
            }
        }
    }
	visited.erase(position);
}
