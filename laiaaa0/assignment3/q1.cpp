
#include "TestingFunctions.cpp"

int directions_x []= {1,-1,0,0,1,-1,-1,1};
int directions_y []= {0,0,1,-1,1,1,-1,-1};

bool IsInGrid (int i, int j,const std::vector<std::vector<char> > &grid){
    if (i>=0 && i<grid.size()){
      if (j>=0 && j<grid[i].size()) return true;
    }
    return false;
}

void FindAllWordsRecursive (int x, int y, Dictionary * d, std::vector<std::vector<char> > &grid, std::vector<std::vector<bool> > &visited,  std::string current_word,std::vector<std::string> &found_words){
  current_word = current_word+grid[x][y];
  visited[x][y] = true;
  if (d->IsWord(current_word)){
    found_words.push_back(current_word);
  }
  if (d->IsPrefix(current_word)){
      for (int i = 0; i<8; ++i){
        if (IsInGrid(x+directions_x[i],y+directions_y[i],grid) && !visited[x+directions_x[i]][y+directions_y[i]]){
          FindAllWordsRecursive(x+directions_x[i],y+directions_y[i],d,grid,visited,current_word,found_words);
        }

      }
  }


}
std::vector<std::string> FindAllWords (Dictionary *d, std::vector<std::vector<char> > &grid){
  int n = grid.size();
  int m;
  std::vector<std::string>all_words;
  for (int i = 0 ; i < n; ++i){
      m = grid[i].size();
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
