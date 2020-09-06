#include <sstream>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <utility>

#include "naive_bayes.h"

NaiveBayesClassifier::NaiveBayesClassifier() {

}

NaiveBayesClassifier::NaiveBayesClassifier(
	int Max_n, int Min_p, const string& train_data,
	const string& voca_data, const string& sw_data = "") {

	// setting
	reviews_p = 0;
	reviews_n = 0;
	this -> Max_n = Max_n;
	this -> Min_p = Min_p;
	sw_drop = false;

	// populate words_freq
	ifstream in(train_data);
	if (!in.is_open()) {
		cerr << "File opening failed\n";
		exit(0);
	}

	vector<pair<pair<ll, ll>, pair<ll, ll>>> words_freq;

	
	string line;
	ll pos_wobin_freq = 0, neg_wobin_freq = 0, pos_wbin_freq = 0, neg_wbin_freq = 0; // total word frequencies
}
