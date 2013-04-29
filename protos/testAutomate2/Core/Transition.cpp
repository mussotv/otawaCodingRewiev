/*
 * Transition.cpp
 *
 *  Created on: Mar 19, 2013
 *      Author: mussot
 */

//#include <string>
//#include <sstream>
#include "stdio.h"
#include "Transition.h"


Transition::Transition(){
}

Transition::Transition(uint32_t val1, uint32_t val2, transType t0, State s1, State s2) {
	addr1 = val1;
	addr2 = val2;
	t = t0;
	start = s1;
	end = s2;
}

string Transition::getDotFormat(string str){

	char chAddr1[32];
	sprintf(chAddr1, "%u", addr1);
	char chAddr2[32];
	sprintf(chAddr2, "%u", addr2);

	return start.getLabel() + " -> " + end.getLabel() + " [label = \"" + chAddr1 + " -> " + chAddr2 + "\", fontcolor=" + str + "];\n";
}

void Transition::display(){
	cout << start.getLabel() << " ---" << addr1 << "->" << addr2 << "---> " << end.getLabel() + "\n";
}

bool Transition::compareTo(Transition tran){
	return (((addr1 == 0) || (tran.addr1 == 0) || (addr1 == tran.addr1))
			&& ((addr2 == 0) || (tran.addr2 == 0) || (addr2 == tran.addr2)));
}

Transition Transition::operator+(Transition const& tr){
	uint32_t str1 = (addr1 == 0) ? tr.addr1 : addr1;
	uint32_t str2 = (addr2 == 0) ? tr.addr2 : addr2;
	return Transition(str1, str2, transType(0), start+tr.start, end+tr.end);
}

Transition::~Transition() {
}

