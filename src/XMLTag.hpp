#ifndef XML_TAG_CLASS
#define XML_TAG_CLASS

#include <vector>
#include <map>
#include <string>

class XMLTag {
	friend bool operator==(const XMLTag &rhs, const XMLTag &lhs);
	friend bool operator!=(const XMLTag &rhs, const XMLTag &lhs);
	public:
		std::string name;
		std::string data;
		XMLTag(void);
		explicit XMLTag(const std::string &nName);
		XMLTag(const std::string &nName, const std::string &nData);
		XMLTag(const XMLTag &other);
		XMLTag(const XMLTag &&other);
		XMLTag& operator=(const XMLTag &other);
		XMLTag& operator=(const XMLTag &&other);
		void setName(const std::string &nName);
		std::string& getName(void);
		void setData(const std::string &nData);
		std::string& getData(void);
		void emplace(const std::string &key, const std::string &val);
		std::string& operator[](const std::string &attrName);
		int size(void) const;
		std::map<std::string,std::string>::iterator begin(void);
		std::map<std::string,std::string>::iterator end(void);
		std::map<std::string,std::string>::iterator find(const std::string &name);
		int count(const std::string &key) const;
		void swap(XMLTag &other);
		void erase(const std::string &attr);
		void clear(void);
		int parse(const std::string &data);
		std::string getOpeningTag(bool selfClosing=false) const;
		std::string getClosingTag(void) const;
		static const int parseSuccess=0;
		static const int invalidTag=1;
		static const int unballancedAttrs=2;
		static const int unballancedTag=4;
	private:
		std::map<std::string,std::string> attributes;
		int populateSegments(std::vector<std::string> &segments, const std::string &raw) const;
		char getPairedInclusionTag(const char openTag) const;
		char getPairedExclusionTag(const char openTag) const;
		void addSegment(std::vector<std::string> &segments, const std::string &raw, const int start, const int end) const;
		int setDataFromSegments(const std::vector<std::string> &segments);
		void getParseableSegment(std::string &buf, const std::string &data) const;
		bool containsTag(const std::string &data) const;
		static const std::string splitTags;
		static const std::vector<std::string> inclusionTags;
		static const std::vector<std::string> exclusionTags;
};

#endif
