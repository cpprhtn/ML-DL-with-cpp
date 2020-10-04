#include <cmath>
#include <cstdlib>
#include <iostream>

#include "decision_tree.h"


DecisionTreeNode::DecisionTreeNode() {
	;
}

void DecisionTreeNode::set_atb_Name(const std::string& atb_name) {
	this -> atb_name = atb_name;
}

std::string DecisionTreeNode::get_atb_Name() {
	return atb_name;
}

void DecisionTreeNode::setType(const std::string& type) {
	this -> type = type;
}

std::string DecisionTreeNode::getType() {
	return type;
}

void DecisionTreeNode::setMaxTargetVal(const std::string& max_T_val) {
	this -> max_T_val = max_T_val;
}

std::string DecisionTreeNode::getMaxTargetVal() {
	return max_T_val;
}

Instance::Instance() {
	;
}

Instance::Instance(const EX& exmp) {
	els = exmp.els;
}

Instance::Instance(
	const std::vector<std::string>& atb_names, const std::vector<std::string>& atb_vals) {
	for (int i = 0; i < atb_names.size(); i++) {
		els[atb_names[i]] = atb_vals[i];
	}
}

std::string Instance::operator[](const std::string& atb_name) const {
	return els.at(atb_name);
}