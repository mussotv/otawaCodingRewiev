/*
 * State.cpp
 *
 *  Created on: Feb 27, 2013
 *      Author: mussot
 */

#include "State.h"

State::State() {
}

State::State(elm::string s){
	label = s;
}

elm::string State::getLabel(){
	return label;
}

State State::operator+(State const& s){
	return State(label + "_" +  s.label);
}

int State::operator==(State const& s){
	return label == s.label;
}

State::~State() {
}

