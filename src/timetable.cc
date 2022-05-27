#include "timetable.h"

Timetable::Timetable(char *timeTableDat) {
	ifstream t (timeTableDat);
	
	unsigned trainId, stationId, arriveHour, arriveMin, departHour, departMin, passEnt, passLeav;
	int h=0;
	try {
		while(t >> trainId >> stationId >> arriveHour >> arriveMin >> departHour >> departMin >> passEnt >> passLeav){
			Trainstop ttemp;
			ttemp.trainId = trainId;
			ttemp.stationId = stationId;
			ttemp.arriveTime = timestamp(arriveHour,arriveMin);
			ttemp.departTime = timestamp(departHour,departMin);
			
			trainstops.push_back (ttemp);
			h++;
			
		}
	}
	catch (EOFException) {}
}


Station* Timetable::getNextReachableStation(Stationlist* sl, unsigned time){
	
	int i;
	vector<Trainstop> departures;
	departures = getMarkedDepartures(sl);
	vector<Station> newDestinations;
	newDestinations = getNewDestinations(departures,sl);
	
	/*
	*	Using newDestinations, find the Destination, that is the shortest afar (from a not marked 
	*	station)
	*/
	unsigned lowest = 0;
	for (i = 0; i < newDestinations.size(); i++){
		if(newDestinations[i].getArriveTime() < newDestinations[lowest].getArriveTime()){
			lowest = i;
		}
	}
	
	Station* nextDest = sl->getStation(newDestinations[lowest].getId());	
	nextDest->setArriveTime(newDestinations[lowest].getArriveTime());
	nextDest->setFromStation(newDestinations[lowest].getFromStation());
	nextDest->setFromTrain(newDestinations[lowest].getFromTrain());
	
	return nextDest;
}


/*
*	With all possible departures from marked stations, 
*	find all reachable, unmarked destinations.
*/
vector<Station> Timetable::getNewDestinations(vector<Trainstop> departures, Stationlist* sl){
	Trainstop departStop;
	Trainstop nextStop;
	Trainstop arriveStop;
	int i,j;
	vector<Station> newDestinations;
	
	for (i = 0; i < departures.size(); i ++){
		departStop = departures[i];
		nextStop.arriveTime = 1000000;
		
		for (j = 0; j < trainstops.size(); j ++){
			arriveStop = trainstops[j];
			if(departStop.trainId == arriveStop.trainId){			
				if(arriveStop.arriveTime < nextStop.arriveTime && 
					arriveStop.arriveTime > departStop.departTime){		
					nextStop = arriveStop;
				}
			}
		}
		
		if(sl->getStation(nextStop.stationId)->getFromStation() == 0){
			Station a(nextStop.stationId, " ");
			
			if(sl->getStation(departStop.stationId)->getFromTrain() == nextStop.trainId){
				a.setFromStation(sl->getStation(departStop.stationId)->getFromStation());
			}
			else{
				a.setFromStation(departStop.stationId);
			}
			a.setFromTrain(departStop.trainId);		
			a.setArriveTime(nextStop.arriveTime);
			newDestinations.push_back(a);
		}
		
	}
	
	if(newDestinations.size()== 0){
		cerr << "No Path found";
		exit(1);
	}

	return newDestinations;
	
}

/*
*	Get the Departures from all marked stations
*/
vector<Trainstop> Timetable::getMarkedDepartures(Stationlist* sl){
	vector<Trainstop> departures;
	int i,j;
	vector<Station>* stations = sl->getStations();
	
	for (i = 0; i < stations->size(); i++){
		Station station = (*stations)[i];
		if(station.getFromStation() != 0){
			for ( j = 0; j < trainstops.size(); j ++){
				if (trainstops[j].stationId == station.getId() &&
					trainstops[j].departTime >= station.getArriveTime()){					
					departures.push_back(trainstops[j]);								
				}
			}	
		}
	}
	
	return departures;
}



unsigned Timetable::timestamp(unsigned hour, unsigned min){
	return hour*60*60+min*60;
}

void Timetable::print(){
	for (int j = 0; j < trainstops.size(); j++){
		cout << trainstops[j].stationId << " " << trainstops[j].trainId << "\n";
	}
}

unsigned Timetable::getDepartTime(unsigned trainId, unsigned stationId){
	for (int i = 0; i < trainstops.size(); i ++){
		if(trainstops[i].trainId == trainId && trainstops[i].stationId == stationId){
			return trainstops[i].departTime;
		}
	}
	return 0;
}