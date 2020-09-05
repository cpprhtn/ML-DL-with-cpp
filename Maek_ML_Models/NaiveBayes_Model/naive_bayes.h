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
	// Default constructor
	NaiveBayesClassifier();

	NaiveBayesClassifier(
		int neg_max, int pos_min, const string& train_bow_file,
		const string& vocab_file, const string& sw_file);

	void test(const string& test_bow_file, bool use_bin);

	
	vector<string> mostInformative(ll num, bool use_bin);

#endif
