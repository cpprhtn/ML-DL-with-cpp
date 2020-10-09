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

void DecisionTreeNode::set_Max_T_Val(const std::string& max_T_val) {
	this -> max_T_val = max_T_val;
}

std::string DecisionTreeNode::get_Max_T_Val() {
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

void DecisionTree::build(const std::vector<EX>& train_data) {
	std::vector<std::string> atb_all;
	for (auto it = p_vals.begin(); it != p_vals.end(); it++) {
		atb_all.push_back(it -> first);
	}
	int nodes = 0;
	build(train_data, root, atb_all, nodes);
}

void DecisionTree::build(std::vector<EX> train_data,
	DecisionTreeNode*& p, std::vector<std::string> check_atb, int& nodes) {

	std::string Max_O_T_Val;

	if (!train_data.empty()) {
		std::map<std::string, int> occ;
		for (auto const& x: train_data) {
			occ[x.get_T_Class()]++;
		}
		int max = -1;
		for (auto const& x: occ) {
			if (x.second > max) {
				max = x.second;
				Max_O_T_Val = x.first;
			}
		}
	}

	//교육 데이터가 있는지 확인하고, 없는 경우 무작위로 대상 클래스를 할당
	if (check_atb.empty()) {
		p = new DecisionTreeNode;++nodes;
		if (train_data.empty()) {
			p -> set_atb_Name(target_values[0]);
		} else {
			p -> set_atb_Name(Max_O_T_Val);
		}
		p -> setType("leaf");
		p -> set_Max_T_Val(p -> get_atb_Name());
		return;
	}

	if (train_data.empty()) {
		p = new DecisionTreeNode;++nodes;
		p -> set_atb_Name(target_values[0]);
		p -> setType("leaf");
		p -> set_Max_T_Val(p -> get_atb_Name());
		return;
	}