#include <iostream>
#include <vector>
#include "Move.h"
#include "ParkingLot.h"
using namespace std;

class RearrangingCars {

private:
	ParkingLot initialState;    
public:
    RearrangingCars(const ParkingLot& initial state);
	void getConfiguration(ParkingLot initialState, ParkingLot finalState, vector<Move> *configuration) ;
};
