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

	/*Parameters:
	Max_n - 부정 정서로 간주되는 최대 등급
	Min_p - 긍정적 감정으로 간주되는 최소 등급
	train_data - 훈련 데이터 파일 경로
	voca_data - vocabulary 파일 경로
	sw_data - stopwords 파일 경로
	*/
	NaiveBayesClassifier(
		int Max_n, int Min_p, const string& train_data,
		const string& voca_data, const string& sw_data);

	//훈련된 나이브 베이즈 분류기 출력
	/*Parameters:
	test_data - 테스트 데이터 파일 경로
	using_2 - binarization 사용 시 true
	*/
	void test(const string& test_data, bool using_2);

	//가장 중요한 특성 반환
	/*Parameters:
	num - 반환할 특성 수
	using_2 - binarization 사용 시 true
	*/
	vector<string> most_important(ll num, bool using_2);

private:

	//파일에서 읽은 단어의 벡터 반환
	vector<string> readWords(const string& sw_data);

	//인스턴스에 대한 분류 반환
	/*Parameters:
	review_instance - 문자열에 대한 검토
	using_2 - binarization 사용 시 true
	*/
	bool classify(stringstream& review_instance, bool using_2);

	/*
	words_prob[i].first - 이항 미포함
	words_prob[i].second - 이항 포함
						.first - prob given positive
						.second -  prob given negative
	*/
	vector<pair<pair<ld, ld>, pair<ld, ld>>> prob_word;

	//stop words 저장
	vector<string> stop_words;

	//vocabulary word 저장
	//constructor
	vector<string> voca_word;

	//positive reviews
	ll reviews_p;

	//negative reviews
	ll reviews_n;

	//부정적 요소중 최고값
	int Max_n;

	//긍정적 요소중 최소값
	int Min_p;

	//stopwards 생략시 bool 값은 True
	bool sw_drop;
};

#endif
