#include "Map.h"


Map::Map(){

}
bool Map::ReadMap(){
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
void Map::WriteMap(){
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
    return InRange(x, 0, this->num_rows_) && InRange(y, 0, this->num_columns_);
}


int Map::FindNumberIslands(){

}
