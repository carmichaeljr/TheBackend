#include "File.hpp"

File::iterator::iterator(void){
	this->file=nullptr;
}

File::iterator::iterator(const std::string &path){
	this->file=std::shared_ptr<std::ifstream>(new std::ifstream(path));
	if (!this->file->fail()){
		getline(*this->file,this->line);
	}
}

bool File::iterator::isFileNull(void) const {
	return (this->file==nullptr);
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
	return *this;
}

File::iterator& File::iterator::operator+=(const int num){
	for (int i=0; i<num && this->file!=nullptr; i++){
		this->operator++(1);
	}
	return *this;
}

bool File::iterator::operator==(const File::iterator &other) const {
	return (this->file==nullptr && other.isFileNull());
}
bool File::iterator::operator!=(const File::iterator &other) const {
	return !this->operator==(other);
}

File::iterator::~iterator(void){
	if (this->file!=nullptr && this->file->is_open()){
		this->file->close();
	}
}
