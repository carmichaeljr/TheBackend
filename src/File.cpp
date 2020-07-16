//C headers
#include <errno.h>
#include <climits>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
//C++ headers
#include "src/File.hpp"
#include "src/HelperFunctions.hpp"

#if OS==WINDOWS
	#include <windows.h>
#endif

File::File(const std::string &path){
	this->setPath(path);
}

File::File(const File &other):
	path(other.path) {
	//
}

File::File(const File &&other){
	*this=std::move(other);
}

File& File::operator=(const File &other){
	this->clear();
	this->path=other.path;
	return *this;
}

File& File::operator=(const File &&other){
	if (this!=&other){
		this->clear();
		this->path=other.path;
	}
	return *this;
}

void File::setPath(const std::string &path){
	this->path=File::getAbsPath(path);
}
const std::string& File::getPath(void) const {
	return this->path;
}

std::vector<std::string> File::getDirList(void) const {
	unsigned int prevIndex=0;
	std::vector<std::string> rv;
	for (unsigned int index=this->path.find(File::pathDelim); 
		index!=std::string::npos;
		prevIndex=index+1, index=this->path.find(File::pathDelim,prevIndex)){
		rv.push_back(this->path.substr(prevIndex,index-prevIndex));
	}
	rv.push_back(this->path.substr(prevIndex,this->path.size()-prevIndex));
	return rv;
}

bool File::changeDrive(const char newDrive, const bool makeCopy){
	std::stringstream newPath;
	const std::pair<unsigned int, unsigned int> indexes=this->getDriveIndexes();
	newPath << newDrive << this->path.substr(indexes.second);
	return this->modifyFilePath(newPath.str(),makeCopy);
}
char File::getDrive(void) const {
	char rv;
	const std::pair<unsigned int, unsigned int> indexes=this->getDriveIndexes();
	if (indexes.second!=std::string::npos && indexes.second>0){
		rv=this->path[indexes.second-1];
	}
	return rv;
}

bool File::changeExtension(const std::string &newExt, const bool makeCopy){
	std::stringstream newPath;
	const std::pair<unsigned int, unsigned int> indexes=this->getExtensionIndexes();
	const std::pair<unsigned int, unsigned int> rest={ 0,indexes.first };
	newPath << this->path.substr(rest.first,rest.second-rest.first) << newExt;
	return this->modifyFilePath(newPath.str(),makeCopy);
}
std::string File::getExtension(void) const {
	std::string rv;
	const std::pair<unsigned int, unsigned int> index=this->getExtensionIndexes();
	if (index.first!=std::string::npos && index.first<this->path.size()){
		rv=this->path.substr(index.first);
	}
	return rv;
}

bool File::changeName(const std::string &newName, const bool makeCopy){
	std::stringstream newPath;
	const std::pair<unsigned int, unsigned int> indexes=this->getNameIndexes();
	const std::pair<unsigned int, unsigned int> firstHalf={ 0,indexes.first };
	const std::pair<unsigned int, unsigned int> secondHalf={ indexes.second,this->path.size() };
	newPath << this->path.substr(firstHalf.first,firstHalf.second-firstHalf.first);
	newPath << newName;
	newPath << this->path.substr(secondHalf.first,secondHalf.second-secondHalf.first);
	return this->modifyFilePath(newPath.str(),makeCopy);
}
std::string File::getName(void) const {
	std::string rv;
	if (this->path.size()>0){
		const std::pair<unsigned int, unsigned int> indexes=this->getNameIndexes();
		rv=this->path.substr(indexes.first,indexes.second-indexes.first);
	}
	return rv;
}

File::const_iterator File::cbegin(void) const {
	return File::const_iterator(this->path);
}

File::const_iterator File::cend(void) const {
	return File::const_iterator();
}

unsigned int File::getNumLines(void) const {
	unsigned int rv=0;
	if (this->path.size()>0 && File::fileExists(this->path)){
		char iterC=' ';
		FILE *file=fopen(&this->path.at(0),"r");
		for (; file!=nullptr && iterC!=EOF; iterC=fgetc(file)){
			rv+=(iterC=='\n')? 1: 0;
		}
		(file!=nullptr)? fclose(file): 0;
	}
	return rv;
}

void File::copy(const File &other) const {
	if (File::fileExists(other.getPath())){
		std::ofstream thisFile(this->path);
		std::ifstream otherFile(other.getPath());
		for (std::string str; !otherFile.fail() && !thisFile.fail() && !otherFile.eof();
			getline(otherFile,str), thisFile << str << std::endl);
		otherFile.close();
		thisFile.close();
	}			
}

void File::write(const std::string &data){
	if (File::fileExists(this->path)){
		std::ofstream file(this->path);
		if (!file.fail()){
			file << data;
		}
		file.close();
	}
}

void File::append(const std::string &data){
	if (File::fileExists(this->path)){
		std::ofstream file(this->path,std::ios_base::app);
		if (!file.fail()){
			file << data;
		}
		file.close();
	}
}

void File::clear(void){
	if (File::fileExists(this->path)){
		std::ofstream file(this->path);
		file.close();
	}
}

//Private Methods===============================================================
//First: inclusive, second: exclusive
std::pair<unsigned int,unsigned int> File::getDriveIndexes(void) const {
	return { 0, this->path.find(':') };
}

//First: inclusive, second: exclusive
std::pair<unsigned int,unsigned int> File::getExtensionIndexes(void) const {
	return { this->path.find_last_of('.')+1, this->path.size() };
}

//First: inclusive, second: exclusive
std::pair<unsigned int,unsigned int> File::getNameIndexes(void) const {
	unsigned int end=this->path.find_last_of('.');
	unsigned int start=this->path.find_last_of(File::pathDelim);
	unsigned int secondDelim=this->path.find_last_of(File::pathDelim,start-1);
	if (start==this->path.size()-1 && end==std::string::npos){
		end=start;
		start=secondDelim;
	}
	(end==std::string::npos)? end=this->path.size(): 0;
	(start==std::string::npos)? start=-1: 0;
	return { start+1,end };
}

bool File::modifyFilePath(const std::string &newPath, const bool makeCopy){
	bool rv=!File::fileExists(newPath);
	if (rv){
		if (makeCopy){
			File newFile(newPath);
			newFile.copy((const File)*this);
		} else {
			rename(&this->path[0],&newPath[0]);
		}
		this->path=newPath;
	}
	return rv;
}

//Friend methods================================================================
bool operator==(const File &rhs, const File &lhs){
	bool rv=(rhs.path==lhs.path);
	if (!rv){
		rv=true;
		std::ifstream rhsFile(rhs.path), lhsFile(lhs.getPath());
		for (char rhsChar=' ', lhsChar=' ';
			!lhsFile.fail() && !rhsFile.fail() && !lhsFile.eof() && !rhsFile.eof() && rv;
			lhsFile >> lhsChar, rhsFile >> rhsChar){
			rv=((lhsChar==rhsChar) && (lhsFile.eof()==rhsFile.eof()));
		}
		rhsFile.close();
		lhsFile.close();
	}
	return rv;
}

bool operator!=(const File &rhs, const File &lhs){
	return !(rhs==lhs);
}

//Class Methods=================================================================
#if OS==UNIX
bool File::fileExists(const std::string &file){
	struct stat buffer;   
  	return (stat(file.c_str(),&buffer)==0);
}
#elif OS==WINDOWS
bool File::fileExists(const std::string &file){
	struct _stat buffer;
	return (_stat(file.c_str(),&buffer)==0);
}
#endif

bool File::remove(const std::string &file){
	bool rv=false;
	if (File::fileExists(file)){
		//Need to access the remove in the global scope of the c-header
		rv=(::remove(file.c_str())==0);
	}
	return rv;
}

std::string File::getCwd(void){
	std::string rv(PATH_MAX,' ');
	for (char* result=getcwd(&rv[0],rv.size()-1); result==NULL && errno==ERANGE;
		rv.resize(rv.size()+PATH_MAX), result=getcwd(&rv[0],rv.size()-1));
	HelperFunc::trimWhitespaceAtEnd(rv);
	return rv;
}

std::string File::getPathFromList(const std::vector<std::string> &dirs){
	std::stringstream str;
	for (unsigned int i=0; i<dirs.size(); i++){
		str << dirs.at(i);
		if (i<dirs.size()-1){
			str << File::pathDelim;
		}
	}
	return str.str();
}

#if OS==WINDOWS
std::string File::getPathToApplication(void){
	std::string rv(PATH_MAX,' ');
	for (int result=GetModuleFileName(NULL,&rv[0],rv.size()-1); 
		result==0 && GetLastError()==ERROR_INSUFFICIENT_BUFFER;
		rv.resize(rv.size()+PATH_MAX), 
		result=GetModuleFileName(NULL,&rv[0],rv.size()-1));
	HelperFunc::trimWhitespaceAtEnd(rv);
	return rv;
}
#elif OS==UNIX || OS==LINUX
std::string File::getPathToApplication(void){
	std::string rv(PATH_MAX,' ');
	for (int result=readlink("/proc/self/exe",&rv[0],rv.size()-1);
		result==-1;
		rv.resize(rv.size()+PATH_MAX),
		result=readlink("proc/self/exe",&rv[0],rv.size()-1));
	HelperFunc::trimWhitespaceAtEnd(rv);
	return rv;
}
#endif

#if OS==WINDOWS
std::string File::getAbsPath(const std::string &relPath){
	std::string rv(PATH_MAX,' ');
	_fullpath(&rv[0],&relPath[0],rv.size()-1);
	HelperFunc::trimWhitespaceAtEnd(rv);
	return rv;
}
#elif OS==LUNIX || OS==UNIX
std::string File::getAbsPath(const std:;string &relPath){
	std::string rv(PATH_MAX,' ');
	realpath(&rv[0],&relPath[0]);
	trimSubString(rv);
	return rv;
}
#endif
