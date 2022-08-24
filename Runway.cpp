//
//  Runway.cpp
//  
//
//  Created by Amanda Tu on 3/5/21.
//

#include "Runway.h"
#include <stdio.h>

Runway::Runway(std::string s): site_number_(s.substr(0,10)), name_(s.substr(13,7)), length_(convert_length(s.substr(20,5)))
{}

std::string Runway::site_number(void) const
{
    return site_number_;
}
std::string Runway::name(void) const
{
    return name_;
}
int Runway::length(void) const
{
    return length_;
}

int Runway::convert_length(std::string s) const
{
    return stoi(s);
}
