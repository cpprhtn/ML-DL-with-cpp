#include <sstream>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <utility>

#include "naive_bayes.h"

using namespace std;

NaiveBayesClassifier::NaiveBayesClassifier() {
	;
}

NaiveBayesClassifier::NaiveBayesClassifier(
	int Max_n, int Min_p, const string& train_data,
	const string& voca_data, const string& sw_data = "") {

	//setting
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

	vector<pair<pair<ll, ll>, pair<ll, ll>>> words_freq;

	//setup
	words_freq.resize(voca_size);
	prob_word.resize(voca_size);
	for (auto& word_info: words_freq) {
		word_info.first.first = 0;
		word_info.first.second = 0;
		word_info.second.first = 0;
		word_info.second.second = 0;
	}

	//populate
	ifstream in(train_data);
	if (!in.is_open()) {
		cerr << "File opening failed\n";
		exit(0);
	}
	string line;
	ll pos_wobin_freq = 0, neg_wobin_freq = 0, pos_wbin_freq = 0, neg_wbin_freq = 0;
	//iteration 하나당 review도 한번검토
	while (getline(in, line)) {

		//review값 확인
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

		//encoded된 단어 처리
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
				words_freq[a].first.first += b;
				pos_wobin_freq += b;
				words_freq[a].second.first += 1;
				++pos_wbin_freq;
			} else {
				words_freq[a].first.second += b;
				neg_wobin_freq += b;
				words_freq[a].second.second += 1;
				++neg_wbin_freq;
			}
		}
	}

	in.close();

	//populate
	for (ll i = 0; i < voca_size; i++) {
		prob_word[i].first.first = (1.0 + words_freq[i].first.first) / (pos_wobin_freq + voca_size);
		prob_word[i].first.second = (1.0 + words_freq[i].first.second) / (neg_wobin_freq + voca_size);
		prob_word[i].second.first = (1.0 + words_freq[i].second.first) / (pos_wbin_freq + voca_size);
		prob_word[i].second.second = (1.0 + words_freq[i].second.second) / (neg_wbin_freq + voca_size);
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
	//iteration 하나당 review도 한번검토
	while (getline(in, line)) {
		//review 값 확인
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

		//인스턴스 분류
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

	//실제 출력 구간
	cout << fixed << setprecision(6)
	<< "Accuracy: " << (static_cast<double>(tp + tn) / (tp + tn + fp + fn)) * 100 << "%\n"
	<< "Precision: " << (static_cast<double>(tp)) / (tp + fp) << "\n"
	<< "Recall: " << (static_cast<double>(tp)) / (tp + fn) << "\n"
	<< "F1 Measure: " << (2 * static_cast<double>(tp)) / (2 * tp + fp + fn) << "\n";
}

vector<string> NaiveBayesClassifier::most_important(ll num, bool use_bin) {
	//find P(w/+ve sentiment) / P(w/-ve sentiment) for each word
	vector<pair<ld,ll>> temp;
	for(int i =0 ;i<prob_word.size(); i++) {
		if(!use_bin)
			temp.push_back(make_pair(prob_word[i].first.first/prob_word[i].first.second,i));
		else temp.push_back(make_pair(prob_word[i].second.first/prob_word[i].second.second,i));
	}
	sort(temp.begin(),temp.end());
	reverse(temp.begin(),temp.end());

	//num 변수의 특성 반환
	vector<string> return_vec;
	for(int i=0; i<num; i++)	return_vec.push_back(voca_word[temp[i].second]);
	return return_vec;
}

vector<string> NaiveBayesClassifier::readWords(const string& sw_data) {
	ifstream fin(sw_data,ios::in);
	vector<string> data;

	while(!fin.eof()){
		string s;
		fin>>s;
		stringstream str(s);
		data.push_back(s);
	}
	return data;
}

bool NaiveBayesClassifier::classify(stringstream& bow_review_instance, bool use_bin) {
	stringstream& ss = bow_review_instance;
	ld pos_prob = log(static_cast<ld>(reviews_p) / (reviews_p + reviews_n));
	ld neg_prob = log(static_cast<ld>(reviews_n) / (reviews_p + reviews_n));

	ll a, b;
	char discard;
	while (!ss.eof()) {
		ss >> a;
		ss.get(discard);
		ss >> b;
		ss.get(discard);

		//stopword이면 skip
		if (sw_drop && binary_search(stop_words.begin(), stop_words.end(), voca_word[a])) {
			continue;
		}
		if (use_bin) {
			pos_prob += log(prob_word[a].second.first);
			neg_prob += log(prob_word[a].second.second);
		} else {
			pos_prob += (b * log(prob_word[a].first.first));
			neg_prob += (b * log(prob_word[a].first.second));
		}
	}
	return (pos_prob >= neg_prob ? true : false);
}
