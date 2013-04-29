/*
 * Transition.h
 *
 *  Created on: Mar 19, 2013
 *      Author: mussot
 */

#ifndef TRANSITION_H_
#define TRANSITION_H_

#include <otawa/base.h>
#include "State.h"


class Transition {
public:
	enum transType {UNDEFINED, CALL, RETURN, ENTRY, EXIT};
private:
	uint32_t addr1;
	uint32_t addr2;
	transType t;
	State start;
	State end;
public:
	Transition();
	Transition(uint32_t, uint32_t, transType, State, State);
	// parametre : couleur de la police
	bool compareTo(Transition);
	elm::string getDotFormat(elm::string);
	void display();
	Transition operator+(Transition const&);
	virtual ~Transition();
};

#endif /* TRANSITION_H_ */
