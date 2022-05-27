#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <vector>
#include "station.h"
#include <fstream>
#include "timetable.h"
#include <deque>
#include <sstream>
using namespace std;



class Scheduler{
	public:
		Scheduler(char *stationDat, char *timeTableDat);
		vector<Station> getFastestRoute(unsigned from, unsigned to, unsigned time);
		Station* getStation(unsigned id);
		void print();
	private:
		Stationlist sl;
		Timetable timeTable;
		string stamptime(unsigned time);
};

#endif
