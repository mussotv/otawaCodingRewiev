/*
 * AutomataProduct.h
 *
 *  Created on: Mar 11, 2013
 *      Author: mussot
 */

#ifndef AUTOMATAPRODUCT_H_
#define AUTOMATAPRODUCT_H_

#include "Automata.h"


class AutomataProduct : public Automata {

public:
	// Produit de deux automates
	AutomataProduct( Automata, Automata);
	// Produit de tous les automates
	void moving(otawa::Edge);
	virtual ~AutomataProduct();
};

#endif /* AUTOMATAPRODUCT_H_ */
