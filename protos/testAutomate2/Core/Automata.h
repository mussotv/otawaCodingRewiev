/*
 * Automata.h
 *
 *  Created on: Mar 11, 2013
 *      Author: mussot
 */

#ifndef AUTOMATA_H_
#define AUTOMATA_H_

#include <otawa/cfg/Edge.h>

#include <vector>

#include "Transition.h"

class Automata {
protected:
	elm::string name;
	State initState;
	std::vector<State> endStates;
	std::vector<Transition> transitions;
	State currentState;
public:
	Automata();
	Automata(elm::string);
	Automata(elm::string, State, std::vector<State>);
	elm::string getName();
	State getInitState();
	std::vector<State> getEndStates();
	std::vector<Transition> getTransitions();
	State getCurrentState();
	// retourne l'indice de la transition dans le tableau transitions
	int transitionExists(Transition);
	void display();
	void viewAutomata();
//	virtual State nextState(Couple, State, string*);
};

#endif /* AUTOMATA_H_ */
