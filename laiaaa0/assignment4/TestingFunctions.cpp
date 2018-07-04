#include "TestingFunctions.h"

void test_Example(){
    std::vector<std::vector<char > > tiles(4,std::vector<char> (4,'F'));
    tiles[0][1] = 'T';
    tiles[1][1] = 'T';
    tiles[1][0] = 'T';
    tiles[0][3] = 'T';
    tiles[2][2] = 'T';
    tiles[3][2] = 'T';
    Map map(tiles);
    EXPECT_EQ(3,map.FindNumberIslands());
}


void test_EmptyMap(){
    std::vector<std::vector<char > > tiles(0,std::vector<char> (0));
    Map map(tiles);
    EXPECT_EQ(0,map.FindNumberIslands());
}

void test_AllWater(){
    std::vector<std::vector<char > > tiles(5,std::vector<char> (5));
    for (int i = 0; i < 5; ++i){
      for (int j = 0; j < 5; ++j){
        tiles[i][j] = 'F';
      }
    }
    Map map(tiles);
    EXPECT_EQ(0,map.FindNumberIslands());
}

void test_AllIsland(){
    std::vector<std::vector<char > > tiles(5,std::vector<char> (5));
    for (int i = 0; i < 5; ++i){
      for (int j = 0; j < 5; ++j){
        tiles[i][j] = 'T';
      }
    }
    Map map(tiles);
    EXPECT_EQ(map.FindNumberIslands(),1);
}
void test_CreateMapFromStr(){
  std::string map_str = "FTFT-"
                        "TTFF-"
                        "FFTF-"
                        "FFTF-";
  Map map(map_str);
  EXPECT_EQ(4,map.GetNumRows());
  EXPECT_EQ(3,map.FindNumberIslands());
}
void test_IslandSurroundingIsland(){
  std::string map_str = "TTTTT-"
                        "TFFFT-"
                        "TFTFT-"
                        "TFFFT-"
                        "TTTTT-";
  Map map(map_str);
  EXPECT_EQ(2,map.FindNumberIslands());
}
void all_tests(){
  test_Example();
  test_EmptyMap();
  test_AllWater();
  test_AllIsland();
  test_CreateMapFromStr();
  test_IslandSurroundingIsland();
}
