#ifndef NAIVE_BAYES_H_
#define NAIVE_BAYES_H_

#include <string>
#include <vector>
#include <utility>
#include <iostream>
#include <fstream>
#include <map>

#define ll long long
#define ld long double

using namespace std;

class NaiveBayesClassifier {
public:
	NaiveBayesClassifier();

	NaiveBayesClassifier(
		int Max_n, int Min_p, const string& train_data,
		const string& voca_data, const string& sw_data);
	void test(const string& test_data, bool using_2);
	vector<string> mostInformative(ll num, bool using_2);

private:

	vector<string> readWords(const string& sw_data);
	bool classify(stringstream& review_instance, bool using_2);
	vector<pair<pair<ld, ld>, pair<ld, ld>>> prob_word;
	vector<string> stop_words;
	vector<string> voca_word;

	ll reviews_p;
	ll reviews_n;
	int Max_n;
	int Min_p;
	bool sw_drop;
};

#endif
