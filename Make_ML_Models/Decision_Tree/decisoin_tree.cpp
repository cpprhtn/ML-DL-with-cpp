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

void Instance::set_atb_Val(const std::string& atb_name, const std::string& atb_val) {
  els[atb_name] = atb_val;
}


std::ostream& operator<<(std::ostream& out, const Instance& inst) {
	for (auto it = inst.els.begin(); it != inst.els.end(); it++) {
		out << it -> first;
		out << ": ";
		out << it -> second;
		out << ", ";
	}
	return out;
}

EX::EX() {
	;
}

EX::EX(
	const std::vector<std::string>& atb_names, const std::vector<std::string>& atb_vals,
	const std::string& target_class) {
	for (int i = 0; i < atb_names.size(); i++) {
		els[atb_names[i]] = atb_vals[i];
	}
	this -> target_class = target_class;
}

std::string EX::get_T_Class() const {
	return target_class;
}

void DecisionTree::add_atb_Info(
	const std::string& atb_name, const std::vector<std::string>& atb_vals) {
	p_vals[atb_name] = atb_vals;
}

void DecisionTree::add_T_Val(const std::vector<std::string>& target_values) {
	this -> target_values = target_values;
}
