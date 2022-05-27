#include "station.h"
#include "timetable.h"
#include "scheduler.h"

int main (int argc, char *argv[]){
	
	if (argc < 7) {
		cerr << "usage: programm bahnhof.dat zug.dat fahrplan.dat vonbahnhof vonstunde vonminute nachbahnhof \n";
		exit (1);
	}
	
	Scheduler sched(argv[1],argv[3]);
	
	sched.getFastestRoute(atoi(argv[4]), atoi(argv[7]), atoi(argv[5])*60*60+atoi(argv[6])*60);
	
	return 0;
}
