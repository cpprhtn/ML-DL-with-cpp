#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>

using namespace std;

#include "naive_bayes.h"

int main() {
	// setting
	int Max_n = 4, Max_p = 7;
	string train_data = "../data/train.feat";
	string test_data = "../data/test.feat";
	string voca_data = "../data/imdb.vocab";
	string sw_data = "../data/sw";
	ll num_words = 10;
	vector<string> words;

	cout << "\nstop words 제거 전\n";
	cout << "``````````````````````````\n";
	NaiveBayesClassifier nb1(Max_n, Max_p, train_data, voca_data, "");

	cout << "이진화 X\n";
	clock_t t = clock();
	nb1.test(test_data, false);
	cout << "Time : " << setprecision(4) << ((clock() - t) / static_cast<double>(CLOCKS_PER_SEC)) << " seconds\n";
	cout << num_words << " 가장 중요한 단어:\n";
	words = nb1.most_important(num_words, false);
	for (ll i = 0; i < num_words; i++) {
		cout << words[i] << " ";
	}
	cout << "\n";

	cout << "\n이진화 O\n";
	t = clock();
	nb1.test(test_data, true);
	cout << "Time : " << setprecision(4) << ((clock() - t) / static_cast<double>(CLOCKS_PER_SEC)) << " seconds\n";
	cout << num_words << " 가장 중요한 단어:\n";
	words = nb1.most_important(num_words, true);
	for (ll i = 0; i < num_words; i++) {
		cout << words[i] << " ";
	}
	cout << "\n";

	cout << "\nstop words 제거 후\n";
	cout << "````````````````````````\n";
	NaiveBayesClassifier nb2(Max_n, Max_p, train_data, voca_data, sw_data);

	cout << "이진화 X\n";
	t = clock();
	nb2.test(test_data, false);
	cout << "Time : " << setprecision(4) << ((clock() - t) / static_cast<double>(CLOCKS_PER_SEC)) << " seconds\n";
	cout << num_words << " 가장 중요한 단어:\n";
	words = nb2.most_important(num_words, false);
	for (ll i = 0; i < num_words; i++) {
		cout << words[i] << " ";
	}
	cout << "\n";

	cout << "\n이진화 O\n";
	t = clock();
	nb2.test(test_data, true);
	cout << "Time : " << setprecision(4) << ((clock() - t) / static_cast<double>(CLOCKS_PER_SEC)) << " seconds\n";
	cout << num_words << " 가장 중요한 단어:\n";
	words = nb2.most_important(num_words, true);
	for (ll i = 0; i < num_words; i++) {
		cout << words[i] << " ";
	}
	cout << "\n\n";
	return 0;
}
