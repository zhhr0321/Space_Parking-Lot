#include"pms.h"
using namespace std;
int main()
{
	int CarSum=rand()%30+30,type=0,intime=0,outtime=0,NowTime=0,CarCheck=0,Sp=0;bool b=0;
	ParkingLot ParkLot(0); 
	ParkLot=initialize();
	ParkLot.print();
	vector<Vehicle> Cars; NowTime=time(NULL);
	for(int i=0;i<CarSum;i++)
	{
		type=rand()%4; intime=NowTime+rand()%10+2;
		outtime=intime+rand()%10+2;
		Cars.push_back(Vehicle(intime,outtime,type,0,0,0));
	}
	while(CarCheck<CarSum){
		NowTime=time(NULL);
		for(int j=0;j<(int)Cars.size();j++){
			if(NowTime==Cars[j].getInTime()&&(Cars[j].getParked()==0)){
				b=0;
				for(int k=0;k<ParkLot.getLotSize();k++){
					Sp=ParkLot.getFloor(k).Find(Cars[j].getCarType());
					if((b==0)&&Sp!=-1){
						Cars[j].SetParked();
						//cout<<k<<" "<<Sp<<" "<<ParkLot.getFloor(k).getSpace(Sp).isParked()<<" ! "<<endl;
						//ParkLot.getFloor(k).getSpace(Sp).CarIn(&Cars[j]);
						ParkLot.CarInFloor(k,Sp,&Cars[j]);
						//cout<<k<<" "<<Sp<<" "<<ParkLot.getFloor(k).getSpace(Sp).isParked()<<" ! "<<endl;
						//cout<<ParkLot.getFloor(k).getSpace(Sp).getVec().getParked()<<endl;
						b=1;
						cout<<"Car "<<j<<" goes to floor "<<k+1<<" Spot "<<Sp+1<<endl;
						break;
					}	
				}
				if(b==0&&Cars[j].getchecked()==0) {cout<<"Sorry, there are no spots for the car "<<j<<endl;Cars[j].Setchecked();CarCheck++;}
			}
		}
		for(int k=0;k<ParkLot.getLotSize();k++){
			for(int j=0;j<ParkLot.getFloor(k).getFloorSize();j++){
				if(ParkLot.getFloor(k).getSpace(j).isParked()==1&&NowTime==ParkLot.getFloor(k).getSpace(j).getVec().getOutTime()&&ParkLot.getFloor(k).getSpace(j).getVec().getprint()==0) {
					ParkLot.getFloor(k).getSpace(j).getVec().print_ticket();
					ParkLot.CarOutFloor(k,j);
					CarCheck++;
				}
			}
		}
	}
}
