
#include <string>
#include <vector>
#include <unordered_map>

//노드 형태 먼저 구현
class DecisionTreeNode {
	public:
		DecisionTreeNode();

		void setAttrName(const std::string& attributeName);

		std::string getAttrName();

		void setType(const std::string& type);

		std::string getType();

		void setMaxTargetVal(const std::string& max_T_val);

		std::string getMaxTargetVal();

	protected:
		std::string attributeName; 
		std::string type; 
		std::string max_T_val;
};

class EX;

class Instance {
	public:
		Instance();

		//exam 인스턴스 생성
		Instance(const EX& exam);

		Instance(
			const std::vector<std::string>& attr_names, const std::vector<std::string>& attr_vals);

    std::string operator[](const std::string& attr_name) const;

    void setAttrVal(const std::string& attr_name, const std::string& attr_val);

		friend std::ostream& operator<<(std::ostream& out, const Instance& inst);

	protected:
		std::unordered_map<std::string, std::string> els;
};

class EX: public Instance {
	public:
		EX();

		EX(
			const std::vector<std::string>& attributeNames, const std::vector<std::string>& attr_vals,
			const std::string& target_class);

		std::string getTargetClass() const;

	private:
		std::string target_class;
};

class DecisionTree {
	public:
		void addAttrInfo(
            const std::string& attributeName,
			const std::vector<std::string>& attr_vals);

		void addTargetValues(const std::vector<std::string>& target_values);

		void build(const std::vector<EX>& train_data);

        double test(const std::vector<EX>& test_data);

		void prune(const std::vector<EX>& prune_data);

		void print();

		void printStats(const std::vector<EX>& test_data);
};
