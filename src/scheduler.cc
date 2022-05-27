#include "scheduler.h"

Scheduler::Scheduler(char *stationDat,char *timeTableDat) {
	int id;
	string name;

	Timetable tt(timeTableDat);
	timeTable = tt;
	
	Stationlist stl(stationDat);
	sl = stl;
}


vector<Station> Scheduler::getFastestRoute(unsigned from, unsigned to, unsigned time) {
	Station* station = sl.getStation(from);
	station->setArriveTime(time);
	station->setFromStation(-1);
	Station* nextDest;
	Station* lastStation;
	vector<Station*> bestRouteReversed;
	deque<Station*> bestRoute;
	int i;
	
	/*
	*	Get next rechable station until destination is reached and save fromStations and fromTrains, so the Path can be recreated
	*/
	nextDest = timeTable.getNextReachableStation(&sl,3601);
	while(nextDest != NULL && nextDest->getId() != to){
		nextDest = timeTable.getNextReachableStation(&sl,3601);
	}
	
	station = nextDest;
	lastStation = nextDest;
	i=0;
	do{
		bestRoute.push_front(station);

		lastStation = station;
		station = sl.getStation(station->getFromStation());	
		i++;
	}while(station->getId() != from && i < sl.getStations()->size());
	bestRoute.push_front(station);
	
	Station* station1;
	Station* station2;
	for (i = 0; i < bestRoute.size()-1; i++){
		station1 = bestRoute[i];
		station2 = bestRoute[i+1];
		cout << "From Station: " << sl.getStation(station1->getId())->getName()
				<< " with Train:" << station2->getFromTrain() 
				<< " at " << stamptime(timeTable.getDepartTime(station2->getFromTrain(),station1->getId()))
				<< " To Station: " << sl.getStation(station2->getId())->getName() 
				<< " Time of Arrival: " << stamptime(station2->getArriveTime()) << "\n";
	}
	
	
	vector<Station> streturn;
	return streturn;
}

string Scheduler::stamptime(unsigned time){
	unsigned hours, min;
	hours = time/60/60;
	min = time/60%60;
	
	stringstream ss;
	ss << hours << "h " << min << "m";
	string str = ss.str();
	
	return str;
	
}

/*
void Scheduler::print(){
	for (int i = 0; i < stationList.size(); i++){
		cout << stationList[i].getId();
	}
	
}*/