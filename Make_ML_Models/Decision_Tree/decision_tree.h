
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <set>

//노드 형태 먼저 구현
class DecisionTreeNode {
	public:
		DecisionTreeNode();

		//setting
		void set_atb_Name(const std::string& atb_name);
		void setType(const std::string& type);
		void set_Max_T_Val(const std::string& max_T_val);


		std::string get_atb_Name();
		std::string getType();
		std::string get_Max_T_Val();

	protected:
		//leaf type일 경우 target value가 됨
		std::string atb_name; 

		//discrete, continuous, leaf 중 하나의 type
		std::string type; 

		//target value의 최대치
		std::string max_T_val;
};

class EX;

class Reader {
	public:
		static std::vector<std::vector<std::string> > readData(std::string file_loc);
		static std::set <std::string> read_T_val(std::string file_loc, int n);
};

class Instance {
	public:
		Instance();

		//exam 인스턴스 생성
		Instance(const EX& exam);

		Instance(const std::vector<std::string>& atb_names, const std::vector<std::string>& atb_vals);

    std::string operator[](const std::string& atb_name) const;

    void set_atb_Val(const std::string& atb_name, const std::string& atb_val);

	friend std::ostream& operator<<(std::ostream& out, const Instance& inst);

	protected:
		std::unordered_map<std::string, std::string> els;
};

class EX: public Instance {
	public:
		EX();

		EX(
			const std::vector<std::string>& atb_names, const std::vector<std::string>& atb_vals,
			const std::string& target_class);

		std::string get_T_Class() const;

	private:
		std::string target_class;
};

class DecisionTree {
	public:
		void add_atb_Info(
            const std::string& atb_name,
			const std::vector<std::string>& atb_vals);

		void add_T_Val(const std::vector<std::string>& target_values);

		void build(const std::vector<EX>& train_data);
        double test(const std::vector<EX>& test_data);
		void prune(const std::vector<EX>& prune_data);

		void print();
		void printStats(const std::vector<EX>& test_data);


	protected:
		int prune(DecisionTreeNode* p, std::vector<EX> prune_data);
		void build(std::vector<EX> train_data, DecisionTreeNode*& p, std::vector<std::string> check__atb_, int& nodes);


		std::string classify(const Instance& inst, DecisionTreeNode *p);

		double discInfoGain(std::vector<EX>& els_ref, const std::string& atb_name, bool in_place);

		std::pair<double, std::vector<double>> contInfoGain(const std::vector<EX>& els, const std::string& atb_name);

		double calcEntropy(const std::map<std::string, int>& els);

		void print(DecisionTreeNode *p);

		std::unordered_map<std::string, std::vector<std::string> > p_vals;

		DecisionTreeNode *root;

    	std::vector<std::string> target_values;
};
