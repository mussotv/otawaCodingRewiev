/*
 * AutomataBB.h
 *
 *  Created on: Mar 18, 2013
 *      Author: mussot
 */

#ifndef AUTOMATABB_H_
#define AUTOMATABB_H_


#include "Automata.h"
#include "Transition.h"


class AutomataBB : public Automata{
public:
	AutomataBB(elm::string, 	// nom
			std::vector<Transition>, 		// liste de transitions
			State, 				// etat initial
			std::vector<State> 	// liste d'etats terminaux
		);
	bool transitionExists(Transition);
	virtual ~AutomataBB();
};

#endif /* AUTOMATABB_H_ */
