#include <vector>
#include <iostream>

class Map {
    private:
        const char ISLAND_T = 'T'; 
        const char WATER_T = 'F'; 

        int num_rows_;
        int num_columns_;
        std::vector<std::vector<char> > map_tiles_;
    public:
        Map();
        bool ReadMap();
        void WriteMap();
        int FindNumberIslands();

        bool InRange(int value, int min, int max);
        bool IsInMap(int x, int y);
};
