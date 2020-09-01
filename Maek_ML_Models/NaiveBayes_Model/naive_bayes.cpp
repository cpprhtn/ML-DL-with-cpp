#include <algorithm>
#include <cmath>


NaiveBayesClassifier::NaiveBayesClassifier() {

}

NaiveBayesClassifier::NaiveBayesClassifier(
	int neg_max, int pos_min, const string& train_bow_file,
	const string& vocab_file, const string& sw_file = "") {

	// setting
	pos_reviews = 0;
	neg_reviews = 0;
	this -> neg_max = neg_max;
	this -> pos_min = pos_min;
	omit_sw = false;

	// populate words_freq
	ifstream in(train_bow_file);
	if (!in.is_open()) {
		cerr << "File opening failed\n";
		exit(0);
	}

	string line;
	ll pos_wobin_freq = 0, neg_wobin_freq = 0, pos_wbin_freq = 0, neg_wbin_freq = 0; // total word frequencies
}
