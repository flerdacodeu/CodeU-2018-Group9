#include "Move.h"

Move::Move(int car, int from, int to) :
	carNum(car), fromPs(from), toPs(to){}

int Move::getCarNum(){
	return carNum;
}

int Move::getFromPs(){
	return fromPs;
}

int Move::getToPs(){
	return toPs;
}
