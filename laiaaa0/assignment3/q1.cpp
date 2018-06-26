#include "TestingFunctions.cpp"


bool InRange (int value, int min_value, int max_value){
  return (value>=min_value && value<=max_value);
}

bool IsInGrid (int i, int j,const std::vector<std::vector<char> > &grid){
    return (InRange(i,0,grid.size()-1) && InRange(j,0,grid[i].size()-1));
}

void FindAllWordsRecursive (int x, int y, const Dictionary & d,
                            std::vector<std::vector<char> > &grid,
                            std::vector<std::vector<bool> > &visited,
                            std::string current_word,
                            std::vector<std::string> &found_words) {
  current_word += grid[x][y];
  visited[x][y] = true;
  if (d.IsWord(current_word)){
    found_words.push_back(current_word);
  }
  if (!d.IsPrefix(current_word)) return;

  for (int i = 0; i<8; ++i){
    for (delta_x : {0,1,-1}){
      for (delta_y : {0,1,-1}){
        int next_x = x+delta_x;
        int next_y = y+delta_y;
        if (IsInGrid(next_x,next_y,grid) && !visited[next_x][next_y]) {
          FindAllWordsRecursive(next_x,next_y,d,grid,visited,current_word,found_words);
        }
      }
    }
  }
}



std::vector<std::string> FindAllWords (const Dictionary &d, std::vector<std::vector<char> > &grid){
  int n = grid.size();
  std::vector<std::string>all_words;
  for (int i = 0 ; i < n; ++i){
      int m = grid[i].size();
      for (int j = 0; j < m; ++j){
        std::vector<std::vector<bool> > visited_positions(n, std::vector<bool> (m,false));
        FindAllWordsRecursive (i,j,d,grid,visited_positions,"",all_words);
      }
    }
    return all_words;
}


int main (){


  all_tests();

}
