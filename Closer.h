//
//  Closer.cpp
//  
//
//  Created by Amanda Tu on 3/5/21.
//

#include "Facility.h"
#include <stdio.h>
#include <iostream>
using namespace std;
class Closer
{
public:
    Closer(double lat, double lon): clat(lat), clon(lon)
    {
        prevDistance = 0;
    }
    bool operator() (Facility* fac1, Facility* fac2)
    {
        return fac1->distance(clat,clon) < fac2->distance(clat,clon);
    }
    
private:
    const double clat, clon;
    double prevDistance;
};


