#include <iostream>
#include <cmath>
#include <cstdlib>
#include <string>
#include <ctime>
#include <fstream>

#include "decision_tree.h"

std::vector<EX> get_Data(const std::string& file_loc, const std::vector<std::string>& atb_names, bool have_Data) {

	std::vector<EX> els;
	std::vector<std::vector<std::string>> data = Reader::read_Data(file_loc);
	for (int i = 0; i < data.size(); i++) {
		std::string T_value = data[i][data[i].size() - 2];
		data[i].pop_back();
		data[i].pop_back();
		els.push_back(EX(atb_names, data[i], T_value));
	}

 	if (have_Data) {
	  for (auto const& atb_name: atb_names) {
			std::map<std::string, std::map<std::string, int>> bins;

			for (int i = 0; i < els.size(); i++) {
				if (els[i][atb_name] != missing_atb) {
					bins[els[i].get_T_Class()][els[i][atb_name]]++;
				}
			}

			//값 채워줌
			for (int i = 0; i < els.size(); i++) {
				if (els[i][atb_name] == missing_atb) {
					int max = -1;
					std::string atb_val;
                    
					for (auto const &x: bins[els[i].get_T_Class()]) {
						if (x.second > max) {
							max = x.second;
							atb_val = x.first;
						}
					}
					els[i].set_atb_Val(atb_name, atb_val);
				}
			}
		}
 	}
	return els;
}

std::vector<std::string> get_atb_Names(const std::vector<std::vector<std::string>>& dat) {
	std::vector<std::string> atb_names;
	for (int i = 0; i < dat.size(); i++) {
		atb_names.push_back(dat[i][0]);
	}
	return atb_names;
}

void fill_atb_Info(const std::vector<std::vector<std::string>>& dat, DecisionTree& dt){
	for (int i = 0; i < dat.size(); i++) {
		std::vector<std::string> temp;
		for (int j = 1; j < dat[i].size(); j++) {
			if (dat[i][j] == "continuous") {
				break;
			} else {
				temp.push_back(dat[i][j]);
			}
		}
		dt.add_atb_Info(dat[i][0], temp);
	}
}

int main(){
	std::vector<std::string> T_values;
	std::vector<std::string> atb_names;
	T_values.push_back(">50K");
	T_values.push_back("<=50K");

	std::vector<std::vector<std::string>> dat = Reader::read_Data("../data/adult_attr");
	std::vector<EX> prune_data = get_Data("../data/adult_data_prune", atb_names, true);
	std::vector<EX> test_data = get_Data("../data/adult_test", atb_names, true);
	std::vector<EX> examples=get_Data("../data/adult_data_train", atb_names, false);
	std::vector<EX> rfexamples=get_Data("../data/adult_data", atb_names, false);
}