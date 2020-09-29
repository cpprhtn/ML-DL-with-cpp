
#include <string>
#include <vector>
#include <unordered_map>

//노드 형태 먼저 구현
class DecisionTreeNode {
	public:
		DecisionTreeNode();

		//setting
		void setAttrName(const std::string& attributeName);
		void setType(const std::string& type);
		void setMaxTargetVal(const std::string& max_T_val);


		std::string getAttrName();
		std::string getType();
		std::string getMaxTargetVal();

	protected:
		//leaf type일 경우 target value가 됨
		std::string attributeName; 

		//discrete, continuous, leaf 중 하나의 type
		std::string type; 

		//target value의 최대치
		std::string max_T_val;
};

class EX;

class Instance {
	public:
		Instance();

		//exam 인스턴스 생성
		Instance(const EX& exam);

		Instance(
			const std::vector<std::string>& atb_names, const std::vector<std::string>& atb_vals);

    std::string operator[](const std::string& atb_name) const;

    void setAttrVal(const std::string& atb_name, const std::string& atb_val);

		friend std::ostream& operator<<(std::ostream& out, const Instance& inst);

	protected:
		std::unordered_map<std::string, std::string> els;
};

class EX: public Instance {
	public:
		EX();

		EX(
			const std::vector<std::string>& attributeNames, const std::vector<std::string>& atb_vals,
			const std::string& target_class);

		std::string getTargetClass() const;

	private:
		std::string target_class;
};

class DecisionTree {
	public:
		void addAttrInfo(
            const std::string& attributeName,
			const std::vector<std::string>& atb_vals);

		void addTargetValues(const std::vector<std::string>& target_values);

		void build(const std::vector<EX>& train_data);

        double test(const std::vector<EX>& test_data);

		void prune(const std::vector<EX>& prune_data);

		void print();

		void printStats(const std::vector<EX>& test_data);
};
