/*
 * AutomataBB.cpp
 *
 *  Created on: Mar 18, 2013
 *      Author: mussot
 */

#include "AutomataBB.h"

AutomataBB::AutomataBB(elm::string s, std::vector<Transition> listTrans, State initSt, std::vector<State> endSts) {

	name = s;
	transitions = listTrans;
	initState = initSt;
	currentState = initState;
	endStates = endSts;
}


AutomataBB::~AutomataBB() {
	// TODO Auto-generated destructor stub
}

