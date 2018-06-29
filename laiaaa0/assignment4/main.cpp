#include "Map.h"

int main (){
    Map m;
    m.ReadMap();
    m.WriteMap();
    std::cout<<m.FindNumberIslands()<<std::endl;
}
