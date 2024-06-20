#include"pms.h"
using namespace std;
Space::Space(int _Num, int _CarType){
	this->Num=_Num; this->CarType=_CarType;
	this->_Parked=0; this->TheVehicle=NULL; 
}
int Space::isParked(){
	return this->_Parked;
}


int Space::CarInTime(){
	return this->TheVehicle->getInTime();
}
int Space::CarOutTime(){
	return this->TheVehicle->getOutTime();
}
int Space::CarFee(){
	return this->TheVehicle->CalFee();
}
int Space::getType(){
	return this->CarType;
}
void Space::CarIn(Vehicle *Veh){
	this->_Parked=1;
	this->TheVehicle=Veh;
}
void Space::CarOut(){
	//delete this->TheVehicle;
	this->TheVehicle=NULL;
	this->_Parked=0;
}
Vehicle Space::getVec(){
	return *TheVehicle;
}
Floor::Floor(int _Sum){
	this->Sum=_Sum;
}
int Floor::getFloorSize(){
	return this->Sum;
}
void Floor::addSpot(Space _Spot){
	this->Sum++; 
	this->_Space.push_back(_Spot);
}
int Floor::Find(int _CarType){
	for(int i=0;i<this->Sum;i++){
		if(this->_Space[i].getType()==_CarType&&this->_Space[i].isParked()==0) return i;
	}
	return -1;
}

void Floor::CarOutSpot(int t){
	this->_Space[t].CarOut(); 
}
Space Floor::getSpace(int t){
	return this->_Space[t];
}

void Floor::CarInSpot(int t,Vehicle *Veh){
	this->_Space[t].CarIn(Veh);	
}
ParkingLot::ParkingLot(int _Sum){
	this->Sum=_Sum;
}
int ParkingLot::getLotSize(){
	return this->Sum;
}
void ParkingLot::addFloor(Floor _F){
	this->Sum++; 
	this->_Floor.push_back(_F);
}
Floor ParkingLot::getFloor(int t){
	return this->_Floor[t];
}
void ParkingLot::print()
{
	int num=0;
	cout<<"ParkingLot"<<endl<<endl;
	for(int i=0;i<this->Sum;i++)
	{
		cout<<"Floor "<<i+1<<endl;
		num=num+this->_Floor[i].getFloorSize();
		for(int j=0;j<this->_Floor[i].getFloorSize();j++){
		cout<<"Space "<<j+1<<" Type "<<this->_Floor[i].getSpace(j).getType()<<endl;
		}
		cout<<endl;
	}
	cout<<"The Parking Lot has "<<Sum<<" Floors "<<num<<" spaces."<<endl;
	cout<<endl;
}
void ParkingLot::CarInFloor(int F,int t,Vehicle *Veh)
{
	this->_Floor[F].CarInSpot(t,Veh);
}
void ParkingLot::CarOutFloor(int F,int t){
	this->_Floor[F].CarOutSpot(t);
}
ParkingLot initialize()
{
	int n=0,p=0,t=0;
	srand((unsigned)time(NULL));
	n=rand()%5+3;
	ParkingLot ParkLot(0);
	for(int i=0;i<n;i++)
	{
		Floor f(0);
		p=rand()%13+3;
		for(int j=0;j<p;j++)
		{
			t=rand()%4;
			f.addSpot(Space(j,t));
		}
		ParkLot.addFloor(f);
	}
	return ParkLot;
}
