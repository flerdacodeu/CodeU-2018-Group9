#include "Dictionary.h"

void FindAllWords (Dictionary & d, std::vector<std::vector<char> > &grid, std::vector<std::string> found_words){


}
char GetRandomLetter (){
      return (char) (rand()%(1+'z'-'a') + 'a');
}


void CreateRandomGrid(std::vector<std::vector<char> > &grid){
    for (int i = 0 ; i < grid.size(); ++i){
        for (int j = 0; j < grid[i].size(); ++j){
            grid[i][j] = GetRandomLetter();
        }
    }
}
void CreateSampleGrid(std::vector<std::vector<char> > &grid){
    grid.clear();

    std::vector<char> line1{'a','a','r'};
    std::vector<char> line2{'t','c','d'};
    grid.push_back(line1);
    grid.push_back(line2);

}
void PrintGrid(std::vector<std::vector<char> > &grid){
  for (int i = 0 ; i < grid.size(); ++i){
      for (int j = 0; j < grid[i].size(); ++j){
          std::cout<<grid[i][j]<<" ";
      }
      std::cout<<std::endl;
  }
}

int main (){
  srand (time(NULL));
  int n,m;
  std::cin>>n>>m;
  std::vector<std::string> v{"cat","car","card","rat"};
  Dictionary * d = new Dictionary(v);
  std::cout<<d->IsPrefix("ra")<<d->IsWord("card")<<std::endl;
  std::vector<std::vector<char> > letter_grid(n, std::vector<char> (m,'a'));
  CreateRandomGrid (letter_grid);
  PrintGrid(letter_grid);
  CreateSampleGrid(letter_grid);
  PrintGrid(letter_grid);

}
