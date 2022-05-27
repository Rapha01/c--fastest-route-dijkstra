#ifndef STATION_H
#define STATION_H

#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

class EOFException {};

class Station{
	public:
		Station(){};
		Station (unsigned sid, string sname);
		string getName(void);
		unsigned getId(void);
		int getFromStation(void);
		unsigned getArriveTime(void);
		void setArriveTime(unsigned time);
		void setFromStation(int sid);
		void setId(unsigned sid);
		unsigned getFromTrain(void);
		void setFromTrain(unsigned tid);
		
		bool operator< (const Station &a) const  { return id < a.id; }
	private:
		string name;
		unsigned id, arriveTime, fromTrain;
		int fromStation;
};

class Stationlist{
	public:
		Stationlist(){};
		Stationlist(char *stationDat);
		Station* getStation(unsigned id);
		vector<Station>* getStations();
	private:
		vector<Station> stations;
};
#endif
