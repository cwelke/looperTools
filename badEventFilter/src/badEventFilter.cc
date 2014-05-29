#include <map>
#include <set>
#include <iostream>
#include <fstream>

#include "../include/badEventFilter.h"

void eventFilter::loadBadEventList( std::string listname )
{

  ifstream filterFile;
  filterFile.open(listname.c_str());
  unsigned long int run = 0;
  unsigned long int lumi = 0;
  unsigned long int event = 0;

  while( filterFile.good() )
	{
	  filterFile>>run>>lumi>>event;
	  eventList[run][lumi].insert(event);
	}

  filterFile.close();
}

bool eventFilter::eventFails( unsigned long int run, unsigned long int lumi, unsigned long int event )
{

  if( eventList.count(run) > 0 ){
	if( eventList[run].count(lumi) > 0 ){
	  if( eventList[run][lumi].count(event) > 0){
		return true;
	  }
	}
  }
  return false;

}

//Test Implemetation
void badEventFilter()
{

  eventFilter toomany;
  toomany.loadBadEventList("badEventLists/toomanyStrip_badEvents_trimmed.txt");
  if( toomany.eventFails( 208686, 97, 94333976 ) )
  	std::cout<<"fail1"<<std::endl; //should print
  if( toomany.eventFails( 201191, 99, 92334813 ) )
  	std::cout<<"fail2"<<std::endl; //should not print

  eventFilter many;
  many.loadBadEventList("badEventLists/manyStrip_badEvents_trimmed.txt");
  if( many.eventFails( 208686, 97, 94333976 ) )
	std::cout<<"fail3"<<std::endl; //should print
  if( many.eventFails( 201191, 99, 92334813 ) )
	std::cout<<"fail4"<<std::endl; //should not print

  eventFilter ecal;
  ecal.loadBadEventList("badEventLists/ecalLaser_badEvents_trimmed.txt");
  if( ecal.eventFails( 208686, 97, 94333976 ) )
	std::cout<<"fail5"<<std::endl; //should not print
  if( ecal.eventFails( 201191, 99, 92334813 ) )
	std::cout<<"fail6"<<std::endl; //should print


}
