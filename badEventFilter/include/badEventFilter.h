#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>

#ifndef BADEVENTFILTER_H
#define BADEVENTFILTER_H

class badEvents
{

public:

  bool eventFails( int run, int lumi, ULong64_t event );
  void loadBadEventList( std::string listname );
  void printBadEventList();

private:

  std::vector <int> l_run, l_lumi;
  std::vector <ULong64_t> l_event;

};

#endif
