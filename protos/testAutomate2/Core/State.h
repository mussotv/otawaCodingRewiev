/*
 * State.h
 *
 *  Created on: Feb 27, 2013
 *      Author: mussot
 */

#ifndef STATE_H_
#define STATE_H_

#include <iostream>
#include <sstream>
#include <otawa/base.h>

using namespace elm;

class State {
	elm::string label;
public:
	State();
//	State(int);
	State(elm::string);
	elm::string getLabel();
	State operator+(State const&);
	int operator==(State const&);
	virtual ~State();

};

#endif /* STATE_H_ */
