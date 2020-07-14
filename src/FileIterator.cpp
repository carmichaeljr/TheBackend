#include "src/File.hpp"

File::const_iterator::const_iterator(void){
	this->file=nullptr;
}

File::const_iterator::const_iterator(const std::string &path){
	this->path=path;
	this->file=std::shared_ptr<std::ifstream>(new std::ifstream(this->path));
	if (!this->file->fail()){
		getline(*this->file,this->line);
	}
}

File::const_iterator& File::const_iterator::operator++(const int num){
	this->line="";
	if (!this->file->fail() && !this->file->eof()){
		getline(*this->file,this->line);
	}
	if (this->file->eof() && this->line==""){
		this->file->close();
		this->file=nullptr;
	}
	this->lineNum++;
	return *this;
}

File::const_iterator& File::const_iterator::operator+=(const int num){
	for (int i=0; i<num && this->file!=nullptr; i++){
		this->operator++(1);
	}
	return *this;
}

bool File::const_iterator::operator==(const File::const_iterator &other) const {
	return ((this->file==nullptr && other.file==nullptr) ||
		(this->path==other.path && this->lineNum==other.lineNum));
}
bool File::const_iterator::operator!=(const File::const_iterator &other) const {
	return !this->operator==(other);
}

const std::string& File::const_iterator::operator*(void) const {
	return this->line;
}

const std::string* File::const_iterator::operator->(void) const {
	return (&this->line);
}

File::const_iterator::~const_iterator(void){
	if (this->file!=nullptr && this->file->is_open()){
		this->file->close();
	}
}
