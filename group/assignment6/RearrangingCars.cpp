#include<iostream>
#include<vector>
#include"Move.h"
#include"RearrangingCars.h"
using namespace std;

void RearrangingCars::getConfiguration(ParkingLot initialState, ParkingLot finalState, vector<Move> *configuration) 
{
	while (initialState != finalState) 
	{
		int emptyPsID = initialState.getEmptyPs();
		while (finalState.getCarAt(emptyPsID) != initialState.getCarAt(emptyPsID)) 
		{
			// move the required car in the empty slot
			Move move(finalState.getCarAt(emptyPsID), initialState.getCarPs(finalState.getCarAt(emptyPsID)), emptyPsID);
			initialState.makeMove(move);
			(*configuration).push_back(move); // save move
		}
		if (initialState.getCarAt(emptyPsID) == EMPTYPS && finalState.getCarAt(emptyPsID) == initialState.getCarAt(emptyPsID)) 
		{
			int firstIncorrectCar;
			for (int i = 0; i < initialState.getSize(); i++)
				if (initialState.getCarAt(i) != finalState.getCarAt(i)) 
				{
					firstIncorrectCar = i;
					break;
				}
			// move the car in this position to an empty slot
			Move move(initialState.getCarAt(firstIncorrectCar), firstIncorrectCar, emptyPsID);
			initialState.makeMove(move);
			(*configuration).push_back(move); // save move
		}
	}
	return;
}
