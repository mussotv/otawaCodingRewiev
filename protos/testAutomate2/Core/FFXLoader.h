/*
 * FFXLoader.h
 *
 *  Created on: Mar 22, 2013
 *      Author: mussot
 */

#ifndef FFXLOADER_H_
#define FFXLOADER_H_

#include <elm/genstruct/Vector.h>
#include <elm/xom.h>
#include <elm/xom/XIncluder.h>
#include <elm/io/BlockInStream.h>
#include <otawa/base.h>
#include <otawa/prog/WorkSpace.h>
#include "AutomataBB.h"

class FFXLoader {
	std::vector<Automata> listeAutomates;
	otawa::WorkSpace *workspace;
public:
	FFXLoader(const elm::string&,otawa::WorkSpace *);
//	void setWorkspace(otawa::WorkSpace *);
	void scanXBody(elm::xom::Element*);
	void scanXCall(xom::Element *);
	void scanXFun(xom::Element *elem);
	void scanXContent(xom::Element *);
	otawa::Address addressOf(const string& label);
	otawa::Address addressOf(const string&, int);
	bool contains(AutomataBB autom, std::vector<Automata> liste);
	std::vector<Automata> getAutomatas();
	Option<long> scanInt(xom::Element *element, cstring name);
	void displayAllAutomatas();
	virtual ~FFXLoader();
private:
	string xline(elm::xom::Node *);
};

#endif /* FFXLOADER_H_ */
