#include "station.h"

Station::Station(unsigned sid, string sname) {
	id = sid;
	name = sname;
	fromStation = 0;
	fromTrain = 0;
	/*s >> id >> name;
	if (!s) throw EOFException ();  // abort constructor!*/
}

string Station::getName(void) {
   return name;
}

unsigned Station::getId(void) {
   return id;
}

int Station::getFromStation(void) {
   return fromStation;
}

unsigned Station::getArriveTime(void) {
   return arriveTime;
}

void Station::setFromStation(int sid) {
   fromStation = sid;
}

void Station::setArriveTime(unsigned time) {
   arriveTime = time;
}

void Station::setId(unsigned sid) {
   id = sid;
}

unsigned Station::getFromTrain(void){
	return fromTrain;
}

void Station::setFromTrain(unsigned tid){
	fromTrain = tid;
}

Stationlist::Stationlist(char *stationDat) {
	int id;
	string name;
	
	ifstream s (stationDat);
	try {
		while(s >> id >> name){
			//cout << a << b << "||";
			Station stemp(id,name);
			stations.push_back (stemp);
		}
	}
	catch (EOFException) {}
}

vector<Station>* Stationlist::getStations() {
	return &stations;
}

Station* Stationlist::getStation(unsigned id) {
	//cout << "GGG" << stationList.size() << "GGG";
	for (int k = 0; k < stations.size(); k++){
		if(stations[k].getId() == id){
			return &stations[k];
		}
	}
	return NULL;
}