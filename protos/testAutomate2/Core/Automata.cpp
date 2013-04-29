/*
 * Automata.cpp
 *
 *  Created on: Mar 11, 2013
 *      Author: mussot
 */

#include <elm/io/BufferedOutStream.h>
#include <elm/sys/System.h>
#include "Automata.h"

using namespace elm;

Automata::Automata(){
}

Automata::Automata(elm::string namep, State q0, std::vector<State> endParam){
	name = namep;
	initState = q0;
	endStates = endParam;
}

State Automata::getInitState(){
	return initState;
}

std::vector<State> Automata::getEndStates(){
	return endStates;
}

elm::string Automata::getName(){
	return name;
}

std::vector<Transition> Automata::getTransitions(){
	return transitions;
}

State Automata::getCurrentState(){
	return currentState;
}

int Automata::transitionExists(Transition tran){
	int rez = -1;
	for (unsigned int i = 0; i < transitions.size(); i++){
		if (transitions[i].compareTo(tran) == true) {
			rez = i;
			break;
		}
	}
	return rez;
}

void Automata::display(){

	cout << "Automata " << name << " [\n"
		 << "- initState = " << initState.getLabel() << "\n"
		 << "- endStates = { ";
	for (unsigned int i=0; i<endStates.size(); i++){
			 cout << endStates[i].getLabel();
			 cout << ((endStates.size()-i>1)? "," : "}\n");
		 }
	cout << "- Transitions = {\n";
	for (unsigned int i=0; i<transitions.size(); i++){
		cout << "    - ";
		transitions[i].display();
	}
	cout << "   }\n]\n\n";
}

void Automata::viewAutomata(){


	elm::cout << "Generation de l'automate " << "testAutomata_" + name << " au format dot...\n" ;

	//io::BufferedOutStream buffer = 	io::BufferedOutStream(sys::System::createRandomFile(".."),io::BufferedOutStream::default_size);

	elm::String str = "Automata_" + name + ".dot";

	io::OutStream *outs = sys::System::createFile(str);
	io::Output out(*outs);
	out << "digraph test_" << name << " {\n";
	out << "rankdir = TB;\n";
	out << "node [shape = doublecircle, color=red];";
	for (unsigned int i = 0; i< endStates.size(); i++)
		out << " " << endStates[i].getLabel();
	out << ";\n";
	out << "node [shape = circle, color=green];\n";
	for (unsigned int i=0; i<transitions.size(); i++)
		out << transitions[i].getDotFormat("blue");
	out << "}\n";
	delete outs;

}

//State Automata::nextState(Couple c, State s, string* str){
//
//	return State();
//}
