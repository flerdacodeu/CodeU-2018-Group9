#include <vector>
#include <iostream>

#ifndef MAP_H
#define MAP_H
class Map {
    private:
        // Define the char used to indicate water and island
        const char ISLAND_T = 'T';
        const char WATER_T = 'F';

        int num_rows_;
        int num_columns_;
        std::vector<std::vector<char> > map_tiles_;

        //If position x,y is an island, it sets all of the island tiles to True
        bool ExpandNode(int x, int y, std::vector<std::vector<bool> > & visited);

        //Get the next position marked as not visited
        std::pair<int,int> GetNextUnvisited (int x, int y, const std::vector<std::vector<bool> > & visited);

        bool InRange(int value, int min, int max);
        bool IsInMap(int x, int y);
    public:
        Map(const std::vector<std::vector<char> > & tiles);
        Map(const std::string & tiles);

        //returns the number of islands in the map
        int FindNumberIslands();

        int GetNumRows();
        int GetNumCols();
};

#endif
