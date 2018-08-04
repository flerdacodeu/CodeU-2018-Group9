/*
 * ParkingLot.h
 *
 *  Created on: Jul 31, 2018
 *      Author: Marah Ghoummaid
 */

#ifndef PARKINGLOT_H_
#define PARKINGLOT_H_
#include <iostream>
using namespace std;
#include <vector>
#include "Move.h"

/*Special Messages have negative values as follows:*/
/*relates to an empty ps */
#define EMPTYPS -1
/*relates to an error that prevents doing any action*/
#define ERROR -2

/*ParkingLot class :
 * let n be the size of the parking lot, then:
 * n-1 cars numbers are {0,1,...,n-2},
 * n parking spaces numbers are {0,1,..., n-1}.
 * Special messages have negative values as described above*/
class ParkingLot {

	/*cars[i]= the ps that car no.i is placed in*/
	vector<int> cars;
	/*Ps[i]= the car placed in Ps no.i*/
	vector<int> Ps;
	/*the number if the empty ps after the parking lot is full, otherwise -1*/
	int emptyPs;
	/*the number of cars in the parking lot*/
	int carsNum;
	/*the parking lot size- number of parking spaces*/
	int size;

	/*Helping private methods*/
	/*updates EmptyPs to the right value */
	void updateEmptyPs();
	/*returns a boolean value:
	 * true- if the given ps is out of the parkingLot range
	 * false- otherwise.*/
	bool isOutOfBounds(int ps);
	/*returns a boolean value:
	 * true- if carNum is an invalid value,
	 * false- otherwise*/
	bool invalidCarNumber(int carNum);

public:
	/*ParkingLot constructor:
	 * initializes an empty parking lot with size parking spaces.*/
	explicit ParkingLot(int size);
	/*return values:
	 * true- if the car has been added successfully
	 * false- otherwise.*/
	bool addCar(int ps);
	/*return values:
	 * true- if the parking lot is full
	 * false- otherwise*/
	bool isFull();
	/*return values:
	 * ERROR- if the given ps is out of bounds
	 * EMPTYPS- if the given ps is empty
	 * otherwise- the number of the car in ps*/
	int getCarAt(int ps);
	/*return values:
	 * ERROR- if the given carNum is invalid
	 * otherwise- the number of the ps that carNum is placed in*/
	int getCarPs(int carNum);
	/*returns a vector with indices of  the empty ps in the parking lot*/
	vector<int> getEmptyPs();
	/*moves a car from a ps to another, return values:
	 * true- if the car has been moved successfully
	 * false otherwise*/
	bool makeMove(Move move);
	/*undoes the given move, return values:
	 * true- if the car has been moved successfully
	 * false otherwise*/
	bool undoMove(Move move);

};

#endif /* PARKINGLOT_H_ */
