

#include "Runway.h"

#include <string>

class SiteNumber
{
public:
    SiteNumber(string site) : snum(site){}
    bool operator () (Runway* cRunway)
    {
        return snum == cRunway->site_number();
    }
private:
    const string snum;
};
