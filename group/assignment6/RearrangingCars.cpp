#include <iostream>
#include <vector>
#include "Move.h"
#include "ParkingLot.h"
#include "rearragingCars.h"
using namespace std;

RearrangingCars(const ParkingLot& initialState_){
	initialState = initialState_;
}
void getAllConfigurations( ParkingLot& initialState, ParkingLot& finalState, vector<Move> configuration, vector<vector<Move>> *allConfigurations) {

	if (initialState == finalState) {
		(*allConfigurations).push_back(configuration);
		return;
	}
	/*INCOMPLETE: add size() method to ParkingLot Class*/
	for(int psID = 0; psID < initialState.size(); psID++) { // loop on initial parking lot state
		if(initialState.getCarAt(psID) != finalState.getCarAt(psID)) { // car not in the right position
			if(initialState.getCarAt(psID) == ParkingLot::EMPTYPS) { // empty slot
				// make move
				Move move = new Move(finalState.getCarAt(psID), initialState.getCarPs(finalState.getCarAt(psID)), psID); 
				initialState.makeMove(move); 
				configuration.push_back(move);
				// recurse to find all possible configurations
				getAllConfigurations(initialState, finalState, configuration, allConfigurations);
				// undo the move for backtracking
				configuration.pop_back();
				initialState.undoMove(move); /*INCOMPLETE: add undoMove method to ParkingLot Class*/
			}
			else if(finalState.getCarPS(initialState.getCarAt(psID)) == initialState.getCarPS(finalState.getCarAt(psID))) { // swapable
				/*INCOMPLETE: add getAllEmptyPs method to ParkingLot Class*/
				vector<int> emptyPs = initialState.getAllEmptyPs(); // get all empty slots in intitial state
				for(int emptyPsID : emptyPS) { // loop on them
					// move the required car in the empty slot
					Move move = new Move(initialState.getCarAt(psID), psID, emptyPsID);
					/*INCOMPLETE: update emptyPS vector*/
					initialState.makeMove(move);
					configuration.push_back(move);
					// recurse to find all possible configurations
					getAllConfigurations(initialState, finalState, configuration, allConfigurations);
					// undo the move for backtracking
					configuration.pop_back();
					initialState.undoMove(move); /*INCOMPLETE: add undoMove method to ParkingLot Class*/
				}
			}
		}
	}
}
void getConfiguration(ParkingLot initialState, ParkingLot finalState, vector<Move> *configuration) {

	if (initialState == finalState) {
		return;
	}

	for (int psID = 0; psID < initialState.size(); psID++) { // loop on initial parking lot state
		if (initialState.getCarAt(psID) != finalState.getCarAt(psID)) { // car not in the right position
			if (initialState.getCarAt(psID) == ParkingLot::EMPTYPS) { // empty slot
				// move the required car in the empty slot
				Move move = new Move(finalState.getCarAt(psID), initialState.getCarPs(finalState.getCarAt(psID)), psID); 
				initialState.makeMove(move);
				(*configuration).push_back(move); // save move
			}
			else { // swapable
				/*INCOMPLETE: add getRandomEmptyPs() method to ParkingLot Class*/
				int emptyPsID = initialState.getRandomEmptyPs(); // get any random empty slot
				// move the car in this position to an empty slot
				Move move = new Move(initialState.getCarAt(psID), psID, emptyPsID);
				/*INCOMPLETE: update emptyPS vector*/
				initialState.makeMove(move);
				(*configuration).push_back(move); // save move
				psID--; //now it became empty still need to move the right car
			}
		}
	}
	return;
}
