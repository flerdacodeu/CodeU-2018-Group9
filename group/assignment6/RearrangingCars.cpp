#include <iostream>
#include <vector>
#include "Move.h"
#include "ParkingLot.h"
#include "rearragingCars.h"
using namespace std;

RearrangingCars(const ParkingLot& initialState_){
	initialState = initialState_;
}
void getConfiguration(ParkingLot initialState, ParkingLot finalState, vector<Move> *configuration) {
	while(initialState != finalState){
		while (finalState.getCarAt(emptyPsID)!=initialState.getCarAt(emptyPsID)) { 
			// move the required car in the empty slot
			Move move = new Move(finalState.getCarAt(emptyPsID), initialState.getCarPs(finalState.getCarAt(emptyPsID)), emptyPsID); 
			initialState.makeMove(move);
			(*configuration).push_back(move); // save move
		}
		if(initialState.getCarAt(emptyPsID) == ParkingLot::EMPTYPS && finalState.getCarAt(emptyPsID)==initialState.getCarAt(emptyPsID)) { 
			int firstIncorrectCar;
			for(int i = 0; i < initialState.size(); i++)
				if(initialState.getCarAt(i) != finalState.getCarAt(i)){
					firstIncorrectCar=i;
					break;
				}
			// move the car in this position to an empty slot
			Move move = new Move(initialState.getCarAt(firstIncorrectCar), firstIncorrectCar, emptyPsID);
			initialState.makeMove(move);
			(*configuration).push_back(move); // save move
		}
	}
	return;
}
