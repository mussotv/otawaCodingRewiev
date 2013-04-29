/*
 * FFXLoader.cpp
 *
 *  Created on: Mar 22, 2013
 *      Author: mussot
 */

#include <cstdio>
#include "FFXLoader.h"

FFXLoader::FFXLoader(const elm::string& path, otawa::WorkSpace *wsp)  {


	workspace = wsp;

	xom::Builder builder;
	xom::Document *doc = builder.build(&path);
	if(!doc)
		cerr << "cannot open " << path;

	// perform inclusion
	xom::XIncluder::resolveInPlace(doc);

	// scan the root element
	xom::Element *root = doc->getRootElement();
	ASSERT(root);
	if(root->getLocalName() != "flowfacts")
		cerr << "bad flow fact format in " << path;
	scanXBody(root);

}

//
//void FFXLoader::setWorkspace(otawa::WorkSpace *wsp){
//	workspace = wsp;
//}

void FFXLoader::scanXBody(xom::Element *body){
	for(int i = 0; i < body->getChildCount(); i++) {
		xom::Node *child = body->getChild(i);
		if(child->kind() == xom::Node::ELEMENT) {
			xom::Element *element = (xom::Element *)child;
			xom::String name = element->getLocalName();

			if (name == "call"){
				scanXCall(element);
			}
			if(name == "loop"){
//				scanXLoop(element);TODO
			}
			else if(name == "function"){
				scanXFun(element);//TODO
			}
			else if(name == "noreturn") {
//				Address addr = scanAddress(element, cpath);TODO
//				if(!addr.isNull())
//					onNoReturn(addr);
//				else
//					onWarning(_ << "ignoring this because its address cannot be determined: " << xline(element));
			}
			else if(name == "return") {
//				Address addr = scanAddress(element, cpath);TODO
//				if(!addr.isNull())
//					onReturn(addr);
//				else
//					onWarning(_ << "ignoring this because its address cannot be determined: " << xline(element));
			}
			else if(name == "nocall") {
//				Address addr = scanAddress(element, cpath);TODO
//				if(!addr.isNull())
//					onNoCall(addr);
//				else
//					onWarning(_ << "ignoring this because its address cannot be determined: " << xline(element));
			}
			else if(name == "flowfacts")
				scanXBody(element);
			else if(name == "ignore-entry"){
//				scanIgnoreEntry(element);TODO
			}
			else if(name == "multibranch"){
//				scanMultiBranch(element);TODO
			}
			else if(name == "multicall"){
//				scanMultiCall(element);TODO
			}
			else
				cout << "garbage at \"" << xline(child) << "\"";
		}
	}
}



/**
 * Scan a call element that may have possibly two forms:
 * @li contains a list of called functions,
 * @li contains a function content (compatibility with old syntax).
 */
void FFXLoader::scanXCall(xom::Element *element)  {

	State init("C_n"+element->getAttributeValue("name").value());
	State end("C_"+element->getAttributeValue("name").value());
	std::vector<State> endStates;
	endStates.push_back(init);

	std::vector<Transition> trans;
	Option<long> line = scanInt(element, "line");
	otawa::Address addressElement  = addressOf(*element->getAttributeValue("source"), *line);

	trans.push_back(Transition(addressElement.address(),
			0,
			Transition::transType(0),
			init,
			end
	));
	/*elm to str : std::string(&cstring(elm::string))*/
	Option<long> numCall = scanInt(element, "numcall");
	char chNum[32];
	std::sprintf(chNum, "%ld", numCall.value());

	AutomataBB scanCallAutom("C_" + element->getAttributeValue("name").value() + chNum, trans,init, endStates);

	listeAutomates.push_back(scanCallAutom);
//	cout << "automata pushed : ";
//	scanCallAutom.display();

	// look for functions
	xom::Elements *elems = element->getChildElements("function");

	// list of function form
	if(elems->size() != 0) {

		// scan the content
		for(int i = 0; i < elems->size(); i++){
 			scanXFun(elems->get(i));
		}
	}

	// old form
	else {
		// scan the content
		scanXContent(element);
	}

	// cleanup
	delete elems;
}

void FFXLoader::scanXFun(xom::Element *element){
	otawa::Address addr;

	// look for the name attribute
	Option<xom::String> val = element->getAttributeValue("name");
	if(val) {
		addr = addressOf(*val);
		if(!addr)
			cerr << " no function named \"" << *val << "\" from " << xline(element);
	}




	State init("F_n"+element->getAttributeValue("name").value());
	State end("F_"+element->getAttributeValue("name").value());
	std::vector<State> endStates;
	endStates.push_back(init);

	std::vector<Transition> trans;

	trans.push_back(Transition(0,
			addr.address(),
			Transition::transType(0),
			init,
			end
	));

	AutomataBB scanFunAutom("F_" + element->getAttributeValue("name").value(), trans,init, endStates);

	if (!contains(scanFunAutom, listeAutomates)){
			listeAutomates.push_back(scanFunAutom);
		}

	// or an address
//	else { TODO : clarify
//		addr = scanAddress(element);
//		if(addr.isNull()) {
//			onWarning(_ << "ignoring this function whose address cannot be found: "<< xline(element));
//			return;
//		}
//	}
	// get the address
//	Inst *inst = _fw->process()->findInstAt(addr);
//	if(!inst)
//		throw ProcessorException(*this,
//			_ << " no instruction at  " << addr << " from " << xline(element));

	// scan the content
	scanXContent(element);
}


/**
 * Scan the content of 'function' or of a 'loop'.
 * @param element	Container element.
 * @param path		Current context path.
 */
void FFXLoader::scanXContent(xom::Element *elem) {

	for(int i = 0; i < elem->getChildCount(); i++) {
		xom::Node *child = elem->getChild(i);
		if(child->kind() == xom::Node::ELEMENT) {
			xom::Element *element = (xom::Element *)child;
			xom::String name = element->getLocalName();
			if(name == "loop"){
//				scanXLoop(element);
			}
			else if(name == "call"){
				scanXCall(element);
			}
			else if(name == "conditional"){
//				scanXConditional(element);
			}
		}
	}
}


bool FFXLoader::contains(AutomataBB autom, std::vector<Automata> liste ){
	bool rez = false;
	for (int i=0; i<liste.size(); i++)
		if (liste[i].getName() == autom.getName())
			rez = true;
	return rez;
}



/**
 * Build an XML element position for user.
 * @param element	Current XML element.
 */
string FFXLoader::xline(xom::Node *element) {
	return _ << element->getBaseURI() << ":" << element->line();
}

otawa::Address FFXLoader::addressOf(const string& label) {
	otawa::Address res = workspace->process()->findLabel(label);
	if(res.isNull())
		cerr << "label \"" << label << "\" does not exist.";
	return res;
}
/**
 * Get the address matching the given source file name and line.
 * @param file	Source file path.
 * @param line	Line in the source file.
 * @return		Matching first address.
 * @throw ProcessorException	If the file/line cannot be resolved to an address.
 */
otawa::Address FFXLoader::addressOf(const string& file, int line) {
	genstruct::Vector<Pair<otawa::Address, otawa::Address> > addresses;
 	workspace->process()->getAddresses(file.toCString(), line, addresses);
 	if(!addresses) {
		cout << "Cannot find the source line " << file << ":" << line << "\n";
		return otawa::Address::null;
	}
 	return addresses[0].fst;
}


std::vector<Automata> FFXLoader::getAutomatas(){
	return listeAutomates;
}

Option<long> FFXLoader::scanInt(xom::Element *element, cstring name){
	Option<xom::String> val = element->getAttributeValue(name);
	if(!val)
		return none;
	io::BlockInStream buf(val);
	io::Input in(buf);
	long res=0;
	try {
		in >> res;
	}
	catch(io::IOException& e) {
		cerr << "bad formatted address(" << e.message() << ") at " << xline(element);
	}
	return res;
}


void FFXLoader::displayAllAutomatas(){
	for (unsigned int i = 0; i < listeAutomates.size(); i++) {
		listeAutomates[i].display();
	}
}


FFXLoader::~FFXLoader() {
}

