#include <iostream>
#include <vector>

using namespace std;

class Move{
    
    int movedCar;
    int fromPs;
    int toPs;
    
    public:
    Move(int movedCar,int fromPs,int toPs);
};


class ParkingLot{
	
	vector<int> cars;
    vector<int> Ps;
	int emptyPs;
	
	public:
	ParkingLot(const vector<int>& parkingSpaces);
	bool makeMove(Move move);

	
};

class RearrangingCars{
    
	ParkingLot initialState;
    
    public:
    RearrangingCars(const vector<int>& initial state);
    vector<Move> generateMoves(const vector<int>& finalState);
    
};
