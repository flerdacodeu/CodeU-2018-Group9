#include "Map.h"

int directions_x [] = {0,0,-1,1};
int directions_y [] = {1,-1,0,0};

Map::Map(const std::vector<std::vector<char> > & tiles) {
  this-> map_tiles_ = tiles;
}

Map::Map(const std::string & tiles_str) {
  this->map_tiles_.clear();
  std::vector<char> current_row;
  for (char c : tiles_str){
      if (c == '-'){
        this->map_tiles_.push_back(current_row);
        current_row.clear();
      }
      else {
        if (c == ISLAND_T || c == WATER_T)  {
          current_row.push_back(c);
        }
      }
  }
}

bool Map::InRange(int value, int min, int max) {
    return value>=min && value<=max;
}

bool Map::IsInMap(int x, int y) {
    return InRange(x, 0, this->map_tiles_.size()-1) && InRange(y, 0, this->map_tiles_[x].size()-1);
}


bool Map::ExpandNode(int x, int y, std::vector<std::vector<bool> > * visited) {
    if (!IsInMap (x,y) || (*visited)[x][y]) return false;
    (*visited)[x][y] = true;
    if (this->map_tiles_[x][y] == WATER_T){
        return false;
    }
    else { //Type is ISLAND_T
        for (int i = 0; i < 4; ++i){
                int next_x = x + directions_x[i];
                int next_y = y + directions_y[i];
                ExpandNode(next_x, next_y, visited);
        }
        return true;
    }
}

std::pair<int,int> Map::GetNextUnvisited(int x, int y, const std::vector<std::vector<bool> > & visited) {
    std::pair<int,int> next_unvisited;
    for (int i = x; i < visited.size(); ++i) {
        int j = 0;
        if (i == x) j = y; // Only set column j to y if we are in row x
        for (j; j < visited[i].size(); ++j){
            if (!visited[i][j]){
                next_unvisited.first = i;
                next_unvisited.second = j;
                return next_unvisited;
            }
        }
    }
    next_unvisited.first = this->map_tiles_.size();
    if (next_unvisited.first < 1) next_unvisited.second = 0;
    else {
      next_unvisited.second = this->map_tiles_[0].size();
    }
    return next_unvisited;
}

int Map::FindNumberIslands() {
    int num_columns = 0;
    if (this->map_tiles_.size()>0) num_columns = this->map_tiles_[0].size();
    std::vector<std::vector<bool> > visited(this->map_tiles_.size(), std::vector<bool> (num_columns,false));
    int x = 0, y = 0;
    int num_islands = 0;
    while (x<this->map_tiles_.size() && y < this->map_tiles_[x].size()){
        if (this->ExpandNode (x,y,&visited)) num_islands++;
        std::pair<int,int> next_unvisited = GetNextUnvisited (x,y,visited);
        x = next_unvisited.first;
        y = next_unvisited.second;
    }
    return num_islands;
}


int Map::GetNumRows(){
  return this->map_tiles_.size();
}
