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
	if (sw_data != "") {
		stop_words = readWords(sw_data);
		sw_drop = true;
	}
	voca_word = readWords(voca_data);
	ll voca_size = voca_word.size();
	
	vector<pair<pair<ll, ll>, pair<ll, ll>>> freq_word;

	//setup freq_word, prob_word
	freq_word.resize(voca_size);
	prob_word.resize(voca_size);
	for (auto& word_info: freq_word) {
		word_info.first.first = 0;
		word_info.first.second = 0;
		word_info.second.first = 0;
		word_info.second.second = 0;
	}
	// populate freq_word
	ifstream in(train_data);
	if (!in.is_open()) {
		cerr << "File opening failed\n";
		exit(0);
	}
	
	string line;
	ll pos_wobin_freq = 0, neg_wobin_freq = 0, pos_wbin_freq = 0, neg_wbin_freq = 0; // total word frequencies
}
