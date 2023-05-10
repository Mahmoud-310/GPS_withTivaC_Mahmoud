#ifndef CALCULATIONS_H_
#define CALCULATIONS_H_

#include <iostream>
#include <cmath>

// #define degToDec(degrees, minutes, seconds) (degrees + (minutes)/60.0 + (seconds)/3600.0)

 double distance(double latitude1, double longitude1,double latitude2, double longitude2)
    {
		latitude1 = (latitude1) * (M_PI / 180);
		latitude2 = (latitude2) * (M_PI / 180);
		double latDeltaRad = (latitude2 - latitude1) *	(M_PI / 180);
		double longDeltaRad = (longitude2 - longitude1) * (M_PI / 180);		
		
		double hs_of_distance_over_radius = pow(sin(latDeltaRad / 2), 2) +pow(sin(longDeltaRad / 2), 2) *cos(latitude1) * cos(latitude2);
		double distance_over_radius = 2 * asin(sqrt(hs_of_distance_over_radius));
		return 6371 * distance_over_radius * 1000; // radius of earth is 6371 KM nearly
	}

	char reachedTarget(double latitude1, double longitude1,double latitude2, double longitude2){
		if(distance(latitude1,  longitude1, latitude2, longitude2)<3)
			return 1;
		return 0;
	}

#endif