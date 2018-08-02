#include <iostream>
#include <vector>
#include "Move.h"
#include "ParkingLot.h"
using namespace std;

class RearrangingCars {

	void getAllConfigurations(ParkingLot initialState, ParkingLot finalState, vector<Move> configuration, vector<vector<Move>> *allConfigurations) {

		if (initialState == finalState) {
			(*allConfigurations).push_back(configuration);
			return;
		}
		/*INCOMPLETE: add size() method to ParkingLot Class*/
		for(int psID = 0; psID < initialState.size(); psID++) { // loop on initial parking lot state
			if(initialState.getCarAt(psID) != finalState.getCarAt(psID)) { // car not in the right position
				if(initialState.getCarAt(psID) == ParkingLot::EMPTYPS) { // empty slot
					// make move
					Move move = new Move(finalState.getCarAt(psID), initialState.getCarPs(psID), psID);
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
					Move move = new Move(finalState.getCarAt(psID), initialState.getCarPs(psID), psID);
					initialState.makeMove(move);
					(*configuration).push_back(move); // save move
				}
				else if(finalState.getCarPS(initialState.getCarAt(psID)) == initialState.getCarPS(finalState.getCarAt(psID))) { // swapable
					/*INCOMPLETE: add getRandomEmptyPs() method to ParkingLot Class*/
					int emptyPsID = initialState.getRandomEmptyPs(); // get any random empty slot
					// move the car in this position to an empty slot
					Move move = new Move(initialState.getCarAt(psID), psID, emptyPsID);
					initialState.makeMove(move);
					(*configuration).push_back(move); // save move
				}
			}
		}
		return getConfiguration( initialState, finalState, configuration);
	}
};
