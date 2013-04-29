/*
 * AutomataProduct.cpp
 *
 *  Created on: Mar 11, 2013
 *      Author: mussot
 */

#include "AutomataProduct.h"

AutomataProduct::AutomataProduct( Automata a, Automata b) {

	name = a.getName() + "_" + b.getName();
	initState = a.getInitState() + b.getInitState();
	for (int i=0; i< a.getEndStates().size(); i++)
		for (int j=0; j<b.getEndStates().size(); j++){
			endStates.push_back(a.getEndStates()[i]+b.getEndStates()[j]);
		}


	for (int i=0; i<a.getTransitions().size(); i++){
		int k;
		if ((k = b.transitionExists(a.getTransitions()[i])) != -1){
			transitions.push_back(a.getTransitions()[i] + b.getTransitions()[k]);
		}
	}


	currentState = initState;
}

// méthode permettant de modifier l'état courant de l'automate
//void AutomataProduct::moving(otawa::Edge edge){
//	otawa::BasicBlock bb1 = *edge.source();
//	otawa::BasicBlock bb2 = *edge.target();
//	otawa::address_t adrBb1 = bb1.address();
//	otawa::address_t adrBb2 = bb2.address();
//	cout << adrBb1.page();
//	cout << adrBb2.page();


//}


AutomataProduct::~AutomataProduct() {

}

