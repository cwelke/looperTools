#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>

#include "../include/badEventFilter.h"

bool badEvents::eventFails( int run, int lumi, ULong64_t event )
{
  bool foundRun = false;
  bool foundLumi = false;
  bool foundEvent = false;

  if( std::find(l_run.begin(), l_run.end(), run) != l_run.end() ){ 
	foundRun = true; 
	if( std::find(l_lumi.begin(), l_lumi.end(), lumi) != l_lumi.end() ){ 
	  foundLumi = true; 
	  if( std::find(l_event.begin(), l_event.end(), event) != l_event.end() ){ 
		foundEvent = true; 
	  }
	}
  }

  if( foundRun && foundLumi && foundEvent ) return false;
  else return true;
}

void badEvents::loadBadEventList( std::string listname )
{

  std::cout<<"Loading filter: "<<listname<<std::endl;

  ifstream filterFile;
  filterFile.open(listname.c_str());
  int val1 = 0;
  int val2 = 0;
  ULong64_t val3 = 0;

  while( filterFile.good() )
	{
	  filterFile>>val1>>val2>>val3;
	  l_run.push_back(val1);
	  l_lumi.push_back(val2);
	  l_event.push_back(val3);
	}

  filterFile.close();
}

void badEvents::printBadEventList()
{
  std::cout<<"Run\tLumi\tEvent "<<std::endl;
  for( size_t ind = 0; ind < l_run.size(); ind++ ){
	std::cout<<l_run.at(ind)<<"\t"<<l_lumi.at(ind)<<"\t"<<l_event.at(ind)<<std::endl;
  }
}

//Test Implemetation
void badEventFilter()
{

  //implementation for ecallaser filter
  badEvents ecalLaser;
  std::string ecalLaser_list = "badEventLists/ecalLaser_badEvents_trimmed.txt";
  ecalLaser.loadBadEventList( ecalLaser_list );
  // ecalLaser.printBadEventList();

  if( ecalLaser.eventFails(201191,	99,	92334813) )
	std::cout<<"Passes 1!"<<std::endl;// should not print
  if( ecalLaser.eventFails(112321, 3411, 567812345) )
	std::cout<<"Passes 2!"<<std::endl;

  //implementation for manystrip filter
  badEvents manystrip;
  std::string manyStrip_list = "badEventLists/manyStrip_badEvents_trimmed.txt";
  manystrip.loadBadEventList( manyStrip_list );
  // manystrip.printBadEventList();

  if( manystrip.eventFails(208686,	97,	94333976) )
	std::cout<<"Passes 1!"<<std::endl;// should not print
  if( manystrip.eventFails(112321, 3411, 567812345) )
	std::cout<<"Passes 2!"<<std::endl;

  //implementation for tootoomanystrip filter
  badEvents toomanystrip;
  std::string toomanystrip_list = "badEventLists/toomanyStrip_badEvents_trimmed.txt";
  toomanystrip.loadBadEventList( toomanystrip_list );
  // toomanystrip.printBadEventList();

  if( toomanystrip.eventFails(208686,	97,	94333976) )
	std::cout<<"Passes 1!"<<std::endl;// should not print
  if( toomanystrip.eventFails(112321, 3411, 567812345) )
	std::cout<<"Passes 2!"<<std::endl;

}
