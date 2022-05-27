#ifndef TIMETABLE_H
#define TIMETABLE_H

#include <iostream>
#include <vector>
#include <fstream>
#include "station.h"
#include <cstdlib>
using namespace std;

class Trainstop{
	public:
		unsigned trainId, stationId, arriveTime, departTime;
	private:		
};

class Timetable{
	public:
		Timetable(){};
		Timetable (char *timeTableDat);
		unsigned timestamp(unsigned hour, unsigned min);
		Station* getNextReachableStation(Stationlist* sl, unsigned time);
		vector<Trainstop> getMarkedDepartures(Stationlist* sl);
		vector<Station> getNewDestinations(vector<Trainstop> departures, Stationlist* sl);
		void print();
		unsigned getDepartTime(unsigned trainId, unsigned stationId);
	private:
		vector<Trainstop> trainstops;
};

#endif
