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

	//populate freq_word
	ifstream in(train_data);
	if (!in.is_open()) {
		cerr << "File opening failed\n";
		exit(0);
	}
	
	string line;
	ll p_wobin_freq = 0, n_wobin_freq = 0, p_wbin_freq = 0, n_wbin_freq = 0; //total word frequencies


	//process each bow review in one iteration
	while (getline(in, line)) {

		//obtain sentiment of the review
		stringstream ss;
		ss.str(line);
		ll rating;
		bool is_pos;
		ss >> rating;
		if (rating <= Max_n) {
			is_pos = false;
			++reviews_n;
		} else if (rating >= Min_p) {
			is_pos = true;
			++reviews_p;
		} else {
			cerr << "Unexpected Neutral: " << rating << "\n";
			exit(0);
		}

		//process the words encoded as bow and populate freq_word
		ll a, b;
		char discard;
		while (!ss.eof()) {
			ss >> a;
			ss.get(discard);
			ss >> b;
			ss.get(discard);
			if (sw_drop && binary_search(stop_words.begin(), stop_words.end(), voca_word[a])) {
				continue;
			}
			if (is_pos) {
				freq_word[a].first.first += b;
				p_wobin_freq += b;
				freq_word[a].second.first += 1;
				++p_wbin_freq;
			} else {
				freq_word[a].first.second += b;
				n_wobin_freq += b;
				freq_word[a].second.second += 1;
				++n_wbin_freq;
			}
		}
	}

	in.close();

	//populate prob_word
	for (ll i = 0; i < voca_size; i++) {
		prob_word[i].first.first = (1.0 + freq_word[i].first.first) / (p_wobin_freq + voca_size);
		prob_word[i].first.second = (1.0 + freq_word[i].first.second) / (n_wobin_freq + voca_size);
		prob_word[i].second.first = (1.0 + freq_word[i].second.first) / (p_wbin_freq + voca_size);
		prob_word[i].second.second = (1.0 + freq_word[i].second.second) / (n_wbin_freq + voca_size);
	}
}

void NaiveBayesClassifier::test(const string& test_bow_file, bool use_bin) {
	ifstream in(test_bow_file);
	if (!in.is_open()) {
		cerr << "File opening failed\n";
		exit(0);
	}

	ll tp = 0, fp = 0, fn = 0, tn = 0;
	string line;
	//consider one review in each iteration
	while (getline(in, line)) {
		//obtain the sentiment of the review
		ll rating;
		stringstream ss;
		ss.str(line);
		ss >> rating;
		bool is_pos;
		if (rating <= Max_n) {
			is_pos = false;
		} else if (rating >= Min_p) {
			is_pos = true;
		} else {
			cerr << "Unexpected Neutral: " << rating << "\n";
			exit(0);
		}

		//classify the instance
		if (classify(ss, use_bin)) {
			if (is_pos) {
				++tp;
			} else {
				++fp;
			}
		} else {
			if (is_pos) {
				++fn;
			} else {
				++tn;
			}
		}
	}
	in.close();

	//print
	cout << fixed << setprecision(6)
	<< "Accuracy: " << (static_cast<double>(tp + tn) / (tp + tn + fp + fn)) * 100 << "%\n"
	<< "Precision: " << (static_cast<double>(tp)) / (tp + fp) << "\n"
	<< "Recall: " << (static_cast<double>(tp)) / (tp + fn) << "\n"
	<< "F1 Measure: " << (2 * static_cast<double>(tp)) / (2 * tp + fp + fn) << "\n";
}