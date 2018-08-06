#include<iostream>
#include"ParkingLot.h"
#include"RearrangingCars.h"
#include"Move.h"
#include"TestingMacros.h"

void pdfTest()
{
	ParkingLot initialState(4), finalState(4);

	initialState.addCar(0);
	initialState.addCar(1);
	initialState.addCar(3);

	finalState.addCar(1);
	finalState.addCar(2);
	finalState.addCar(0);

	RearrangingCars RC;
	vector<Move> *moves = new vector<Move>();
	RC.getConfiguration(initialState, finalState, moves);

	vector<Move> *expected = new vector<Move>();
	(*expected).push_back(Move(1, 1, 2));
	(*expected).push_back(Move(0, 0, 1));
	(*expected).push_back(Move(2, 3, 0));

	if((*expected).size() == (*moves).size())
		for (int i = 0; i < (*expected).size(); i++){
		EXPECT_EQ((*expected)[i].getCarNum(), (*moves)[i].getCarNum());
		EXPECT_EQ((*expected)[i].getFromPs(), (*moves)[i].getFromPs());
		EXPECT_EQ((*expected)[i].getToPs(), (*moves)[i].getToPs());
	}
}

int main()
{
	pdfTest();
	system("pause");
	return 0;
}
