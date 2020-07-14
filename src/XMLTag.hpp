#ifndef XML_TAG_CLASS
#define XML_TAG_CLASS

#include <vector>
#include <map>
#include <string>
#include "src/Tokenizer.hpp"

class XMLTag {
	friend bool operator==(const XMLTag &rhs, const XMLTag &lhs);
	friend bool operator!=(const XMLTag &rhs, const XMLTag &lhs);
	public:
		static const int parseSuccess=Tokenizer::parseSuccess;
		static const int unballancedTag=Tokenizer::unballancedTokens;
		static const int unballancedAttrs=2;
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
		int parse(const std::string &data);
		std::string getOpeningTag(bool selfClosing=false) const;
		std::string getClosingTag(void) const;
	public:	//map interface methods
		void emplace(const std::string &key, const std::string &val);
		std::string& operator[](const std::string &attrName);
		int size(void) const;
		std::map<std::string,std::string>::iterator begin(void);
		const std::map<std::string,std::string>::const_iterator begin(void) const;
		std::map<std::string,std::string>::iterator end(void);
		const std::map<std::string,std::string>::const_iterator end(void) const;
		std::map<std::string,std::string>::const_iterator cbegin(void);
		std::map<std::string,std::string>::const_iterator cend(void);
		std::map<std::string,std::string>::iterator find(const std::string &name);
		int count(const std::string &key) const;
		void swap(XMLTag &other);
		void erase(const std::string &attr);
		void clear(void);
	protected:
		std::map<std::string,std::string> attributes;
	private:
		static const std::string splitTokens;
		static const std::string inclusionTokens;
		static const std::string exclusionTokens;
	private:
		int setDataFromTokens(const Tokenizer &tokens);
		void getParseableSegment(std::string &buf, const std::string &data) const;
		bool containsTag(const std::string &data) const;
};

#endif
