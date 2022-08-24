//
// mayday.cpp
//
// use: mayday latitude longitude min_length
//
// Provide a list of facilities and runways closest to the location specified
// by the coordinates (latitude,longitude).
// Only facilities having runways longer than min_length are printed.
// Only runways longer than min_length are printed.
//
// Input:
//   latitude, longitude in degrees decimal
//   min_length in ft
// Output:
//   list of nearest facilities and runways including distance in nautical miles

#include "Facility.h"
#include "Runway.h"
#include "Closer.h"
#include "SiteNumber.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <cassert>
#include <cmath>
using namespace std;

int main(int argc, char**argv)
{
  // use: mayday current_latitude current_longitude min_runway_length
  // latitude and longitudes in degrees decimal
  // min runway length of runway in ft

  assert(argc==4);
    const double current_latitude = atof(argv[1]);
    const double current_longitude = atof(argv[2]);
    const int min_runway_length = atoi(argv[3]);

  vector<Facility*> facilities;
  // load facilities data
  // Insert your code here
    
    ifstream ftxt;
    ftxt.open("Facilities.txt");
    string line;
    while(getline(ftxt,line))
    {
        Facility* f = new Facility(line);
        facilities.push_back(f);
    }
    ftxt.close();

  // sort facilities in order of proximity to the current position
  sort(facilities.begin(), facilities.end(),
       Closer(current_latitude,current_longitude));

    //for(int i = 0; i < 20; i++)
        //cout << facilities[i]->name() << " " << facilities[i]->distance(current_latitude,current_longitude) <<endl;

  vector<Runway*> runways;
  // load runways data
  // Insert your code here

    ifstream rtxt;
    rtxt.open("Runways.txt");
    while(getline(rtxt,line))
    {
        Runway* r = new Runway(line);
        runways.push_back(r);
    }
    rtxt.close();



  // list up to 10 nearest facilities that have a long enough runway
  // list each runway that is long enough
  int count = 0;
  for ( unsigned int i = 0; i < facilities.size() && count < 10; i++ )
  {
    Facility *a = facilities[i];

    // Find all runways of this facility that are long enough
    vector<Runway*> good_runways;
    // Insert your code here
      vector<Runway*>::iterator iter = find_if(runways.begin(),runways.end(),SiteNumber(a->site_number()));
      while(iter != runways.end())
      {
          Runway* test = *iter;
          if(test->length() >= min_runway_length)
              good_runways.push_back(*iter);
          iter = find_if(next(iter),runways.end(),SiteNumber(a->site_number()));
      }
      
    // print this facility if it has long enough runways
    if ( !good_runways.empty() )
    {
      //increment count of good facilities
      count++;

      cout << a->type() << " " << a->code() << " "
           << a->name() << " ";
      cout.setf(ios_base::fixed,ios_base::floatfield);
      cout.setf(ios_base::right, ios_base::adjustfield);
      cout.width(5);
      cout.precision(1);
      cout << a->distance(current_latitude,current_longitude)
           << " NM" << endl;

      // print all runways that are long enough
      for ( unsigned int i = 0; i < good_runways.size(); i++ )
      {
        Runway *r = good_runways[i];
        cout << "  Runway: " << r->name() << "  length: " << r->length()
             << " ft" << endl;
      }
    }
  }
    for(unsigned int i = 0; i < facilities.size(); i++)
        delete facilities[i];
    for(unsigned int i = 0; i < runways.size(); i++)
        delete runways[i];
}
