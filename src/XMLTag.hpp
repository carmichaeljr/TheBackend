#ifndef XML_TAG_CLASS
#define XML_TAG_CLASS

#include <vector>
#include <map>
#include <string>

//TODO -
//iterator???
//set/add/remove/clear/has attributes
//clear
//equals
//get opening/closing tag
//the big 5

class XMLTag {
	//friend operator==
	public:
		XMLTag(void);
		explicit XMLTag(const std::string &nName);
		XMLTag(const std::string &nName, const std::string &nData);
		void setName(const std::string &nName);
		std::string& getName(void);
		void setData(const std::string &nData);
		std::string& getData(void);
		void emplace(const std::string &key, const std::string &val);
		std::string& operator[](const std::string &attrName);
		//size
		std::map<std::string,std::string>::iterator begin(void);
		std::map<std::string,std::string>::iterator end(void);
		std::map<std::string,std::string>::iterator find(const std::string &name);
		int count(const std::string &key) const;
		void swap(XMLTag &other);
		//void erase(const std::string &attr);
		//clear
		int parse(const std::string &data);
		//std::string getOpeningTag(void) const;
		//std::string getClosingTag(void) const;
		static const int parseSuccess=0;
		static const int invalidTag=1;
		static const int unballancedAttrs=2;
		static const int unballancedTag=4;
	private:
		std::string name;
		std::string data;
		std::map<std::string,std::string> attributes;
		int populateSegments(std::vector<std::string> &segments, const std::string &raw) const;
		char getPairedInclusionTag(const char openTag) const;
		char getPairedExclusionTag(const char openTag) const;
		void addSegment(std::vector<std::string> &segments, const std::string &raw, const int start, const int end) const;
		int setDataFromSegments(const std::vector<std::string> &segments);
		static const std::string splitTags;
		static const std::vector<std::string> inclusionTags;
		static const std::vector<std::string> exclusionTags;
};

#endif
