#include "src/File.hpp"

File::iterator::iterator(void){
	this->file=nullptr;
}

File::iterator::iterator(const std::string &path){
	this->path=path;
	this->file=std::shared_ptr<std::ifstream>(new std::ifstream(this->path));
	if (!this->file->fail()){
		getline(*this->file,this->line);
	}
}

File::iterator& File::iterator::operator++(const int num){
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

File::iterator& File::iterator::operator+=(const int num){
	for (int i=0; i<num && this->file!=nullptr; i++){
		this->operator++(1);
	}
	return *this;
}

bool File::iterator::operator==(const File::iterator &other) const {
	return ((this->file==nullptr && other.file==nullptr) ||
		(this->path==other.path && this->lineNum==other.lineNum));
}
bool File::iterator::operator!=(const File::iterator &other) const {
	return !this->operator==(other);
}

std::string& File::iterator::operator*(void){
	return this->line;
}

const std::string& File::iterator::operator*(void) const {
	return this->line;
}

std::string* File::iterator::operator->(void){
	return (&this->line);
}

const std::string* File::iterator::operator->(void) const {
	return (&this->line);
}

File::iterator::~iterator(void){
	if (this->file!=nullptr && this->file->is_open()){
		this->file->close();
	}
}
