
#include <string>
#include <vector>

class EX;

class Instance {
	public:
		Instance();
};

class Example: public Instance {
	public:
		Example();

		Example(
			const std::vector<std::string>& attr_names, const std::vector<std::string>& attr_vals,
			const std::string& target_class);

		std::string getTargetClass() const;

	private:
		std::string target_class;
};

class DecisionTree {
	public:
		void addAttrInfo(
            const std::string& attr_name,
			const std::vector<std::string>& attr_vals);

		void addTargetValues(const std::vector<std::string>& target_values);

		void build(const std::vector<EX>& train_data);

        double test(const std::vector<EX>& test_data);

		void prune(const std::vector<EX>& prune_data);

		void print();

		void printStats(const std::vector<EX>& test_data);
};
