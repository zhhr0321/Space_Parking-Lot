#include"pms.h"
using namespace std;
Vehicle::Vehicle(int _In,int _Out,int _Type,int _Parked,int _whether_checked,int _whether_print){
	this->InTime=_In; this->OutTime=_Out; this->CarType=_Type; this->Parked=_Parked;this->whether_checked=_whether_checked;this->whether_print=_whether_print;
}
int Vehicle::getInTime(){
	return this->InTime;
}
int Vehicle::getOutTime(){
	return this->OutTime;
}
int Vehicle::getCarType(){
	return this->CarType;
}
int Vehicle::CalFee(){
	switch(this->CarType){
		case 0: return 10*(this->OutTime-this->InTime); break;
		case 1: return 5*(this->OutTime-this->InTime); break;
		case 2: return 20*(this->OutTime-this->InTime); break;
		case 3: return 2*(this->OutTime-this->InTime); 
	}
	return 0;
}
int Vehicle::getParked(){
	return this->Parked;
}
void Vehicle::SetParked(){
	this->Parked=1;
}
void Vehicle::Setchecked(){
	this->whether_checked=1;
}
int Vehicle::getchecked(){
	return this->whether_checked;
}
void Vehicle::type_change(){
	cout<<"Your car type is: ";
	switch(this->CarType){
		case 0: cout<<"Car"<<endl;break;
		case 1: cout<<"Motobike"<<endl;break;
		case 2: cout<<"Van"<<endl;break;
		case 3: cout<<"Bike"<<endl;
	}
}
void Vehicle::print_ticket(){
	cout<<"Your start time is: "<<this->InTime<<endl;
	cout<<"Your end time is:"<<this->OutTime<<endl;
	this->type_change();
	cout<<"Your fee is: "<<this->CalFee()<<endl;
	//this->whether_print=1;
}
void Vehicle::Setprint(){
	this->whether_print=1;
}
int Vehicle::getprint(){
	return whether_print;
}
