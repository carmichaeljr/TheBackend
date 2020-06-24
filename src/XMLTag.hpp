#ifndef XML_TAG_CLASS
#define XML_TAG_CLASS

#include <vector>
#include <map>
#include <string>

class XMLTag {
	public:
		XMLTag(void);
		explicit XMLTag(const std::string &nName);
		XMLTag(const std::string &nName, const std::string &nData);
		void setName(const std::string &nName);
		std::string getName(void) const;
		void setData(const std::string &nData);
		std::string getData(void) const;
		void parse(const std::string &data);
		//std::string getOpeningTag(void) const;
		//std::string getClosingTag(void) const;
		static const std::vector<std::string> inclusionTags={
			"\"\"","''"
		};
		static const std::vector<std::string> exclusionTags={
			"/>"
		};
		static const std::string splitTokens=" <>=";
	private:
		std::string name;
		std::string data;
		std::map<std::string,std::string> attributes;
		//void populateTokenList(std::vector<int> &tokenIndexes, const std::string &raw);
};

#endif
