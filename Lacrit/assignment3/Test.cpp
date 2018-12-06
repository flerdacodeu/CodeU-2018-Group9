#include "Main.hpp"

int main() {
	const std::string path = "dict.txt";
	std::string board = "aartcd";
 	Dictionary dict(path);
	dict.Fill(path);
    Main m(dict);
    m.Load(board);
    m.Print();
	std::unordered_set<std::string> res = m.Result();
	std::cout << std::endl;
	for (auto it = res.begin(); it != res.end(); ++it)
    {
		std::cout << *it  << std::endl;
    }
	return 0;
}
