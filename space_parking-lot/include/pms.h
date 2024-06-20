#ifndef PMS_H
#define PMS_H
#include<iostream>
#include<vector>
#include<ctime>
#include<cstdlib>


class Vehicle{
	protected:
		int InTime,OutTime,CarType;
		int Parked;
		int whether_checked;
		int whether_print;
	public:
		Vehicle(int _In,int _Out,int _Type,int _Parked,int _whether_checked,int _whether_print);
		int getInTime();
		int getOutTime();
		int getCarType();
		int CalFee();
		int getParked();
		void SetParked();
		void Setchecked();
		int getchecked();
		void Setprint();
		int getprint();
		void print_ticket();
		void type_change();
};

class Space{
	protected:
		int _Parked;
		int Num,CarType;
		Vehicle *TheVehicle;
	public:
		Space(int _Num,int _CarType);
		int isParked();
		void CarIn(Vehicle *Veh);
		void CarOut();
		int CarInTime();
		int CarOutTime();
		int CarFee();
		int getType();
		Vehicle getVec();
};

class Floor{
	protected:
		std::vector<Space> _Space;
		int Sum;
	public:
		Floor(int _Sum);
		int getFloorSize(); 
		void addSpot(Space _Spot);
		int Find(int _CarType);
		void CarInSpot(int t,Vehicle *Veh);
		void CarOutSpot(int t);
		Space getSpace(int t);
};

class ParkingLot{
	protected:
		std::vector<Floor> _Floor;
		int Sum;
	public:
		ParkingLot(int _Sum);
		int getLotSize();
		void addFloor(Floor _F);
		Floor getFloor(int t);
		void print();
		void CarInFloor(int F,int t,Vehicle *Veh);
		void CarOutFloor(int F,int t);
};

ParkingLot initialize();
#endif