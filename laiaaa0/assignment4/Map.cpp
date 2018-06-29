#include "Map.h"

int directions_x [] = {0,0,-1,1};
int directions_y [] = {1,-1,0,0};

Map::Map() {

}
bool Map::ReadMap() {
    bool return_value = true;
    this->map_tiles_.clear();
    std::cin>>this->num_rows_>>this->num_columns_;
    for (int i = 0; i < this->num_rows_; i++){
        std::vector<char>map_row(this->num_columns_);
        for (int j = 0; j < this->num_columns_; j++){
            std::cin>>map_row[j];
            if (map_row[j]!=ISLAND_T && map_row[j]!=WATER_T) return_value = false;
        }
        this->map_tiles_.push_back(map_row);
    }

    return return_value;
}
void Map::WriteMap() {
    for (int i = 0; i < this->num_rows_; i++){
        for (int j = 0; j < this->num_columns_; j++){
            std::cout<<this->map_tiles_[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
}

bool Map::InRange(int value, int min, int max) {
    return value>=min && value<=max;
}

bool Map::IsInMap(int x, int y) {
    return InRange(x, 0, this->num_rows_-1) && InRange(y, 0, this->num_columns_-1);
}


bool Map::ExpandNode(int x, int y, std::vector<std::vector<bool> > & visited) {
    if (!IsInMap (x,y)) return false;
    if (visited[x][y]) return false;
    visited[x][y] = true;
    if (this->map_tiles_[x][y] == WATER_T){
        return false;
    }
    else if (this->map_tiles_[x][y] == ISLAND_T){
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
    for (int i = 0; i < visited.size(); ++i) {
        for (int j = 0; j < visited[i].size(); ++j){
            if (!visited[i][j]){
                next_unvisited.first = i;
                next_unvisited.second = j;
                return next_unvisited;
            }
        }
    }
    next_unvisited.first = this->num_rows_;
    next_unvisited.second = this->num_columns_;
    return next_unvisited;
} 

int Map::FindNumberIslands() { 
    std::vector<std::vector<bool> > visited(this->num_rows_, std::vector<bool> (this->num_columns_,false));
    int x = 0, y = 0;
    int num_islands = 0;
    while (x<this->num_rows_ && y < this->num_columns_){
        if (this->ExpandNode (x,y,visited)) num_islands++;
        std::pair<int,int> next_unvisited = GetNextUnvisited (x,y,visited);       
        x = next_unvisited.first;
        y = next_unvisited.second;
    }
    return num_islands;
}
