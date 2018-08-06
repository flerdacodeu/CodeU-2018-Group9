#include"ParkingLot.h"
ParkingLot::ParkingLot(int size) :
	cars(vector<int>(size-1)), Ps(vector<int>(size, EMPTYPS)), emptyPs(-1), carsNum(
		0), size(size) {}

bool ParkingLot::operator!=(const ParkingLot& PL){
	return !(cars == PL.cars && Ps == PL.Ps);
}

bool ParkingLot::addCar(int ps) {
	if (isOutOfBounds(ps)) {
		return false;
	}
	if (Ps[ps] != EMPTYPS) {
		return false;
	}
	if (isFull()) {
		return false;
	}
	Ps[ps] = carsNum;
	cars[carsNum] = ps;
	carsNum++;
	if (isFull()) {
		updateEmptyPs();
	}

	return true;
}

bool ParkingLot::isOutOfBounds(int ps) {
	return (ps < 0 || ps >= size);
}

bool ParkingLot::invalidCarNumber(int carNum) {
	return (carNum < 0 || (unsigned int)carNum >= cars.size());
}

void ParkingLot::updateEmptyPs() {
	if (!isFull()) {
		return;
	}
	for (unsigned int i = 0; i < Ps.size(); i++) {
		if (Ps[i] == -1) {
			emptyPs = i;
			return;
		}
	}
}

int ParkingLot::getSize(){
	return size;
}

bool ParkingLot::isFull() {
	return ((unsigned int)carsNum == Ps.size() - 1);
}

int ParkingLot::getCarAt(int ps) {
	if (isOutOfBounds(ps)) {
		return ERROR;
	}
	return Ps[ps];
}

int ParkingLot::getCarPs(int carNum) {
	if (invalidCarNumber(carNum)) {
		return ERROR;
	}
	return cars[carNum];
}

int ParkingLot::getEmptyPs() {
	if (!isFull()) {
		return ERROR;
	}
	return emptyPs;
}

bool ParkingLot::makeMove(Move move) {
	int from = move.getFromPs();
	int to = move.getToPs();
	int car = move.getCarNum();
	if (isOutOfBounds(from) || isOutOfBounds(to)) {
		return false;
	}
	if (Ps[from] == EMPTYPS || invalidCarNumber(Ps[from])) {
		return false;
	}
	if (invalidCarNumber(car)) {
		return false;
	}
	if (Ps[to] != EMPTYPS) {
		return false;
	}
	if (Ps[from] != car) {
		return false;
	}
	Ps[to] = car;
	cars[car] = to;
	Ps[from] = -1;
	updateEmptyPs();
	return true;
}
