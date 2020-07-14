#include "debug/FileDebug.hpp"
#include "src/File.hpp"
#include "src/Print.hpp"

FileDebug::FileDebug(void): Debug("File") {
	this->debugFile << "debug" << File::pathDelim << "FileTest.txt";
	this->copyFile << "debug" << File::pathDelim << "CopyFileTest.txt";
	this->equalsFile << "debug" << File::pathDelim << "EqualsFileTest.txt";
	this->dirs={"folder1","folder2","folder3"};
	this->dirsPath << this->dirs.at(0) << File::pathDelim;
	this->dirsPath << this->dirs.at(1) << File::pathDelim;
	this->dirsPath << this->dirs.at(2);
	this->success=true;
}

bool FileDebug::debugClassMethods(void){
	return (this->debugFileExists() &&
		this->debugGetCwd() &&
		this->debugGetPathFromList() &&
		this->debugGetAbsPath());
}

bool FileDebug::debugFileExists(void){
	bool rv=true;
	rv=File::fileExists(this->debugFile.str());
	Print::objectMethodDebug(std::cout,"FileExists",rv);
	return rv;
}

bool FileDebug::debugGetCwd(void){
	bool rv=true;
	std::stringstream cwdTest;
	cwdTest << File::getCwd() << File::pathDelim << this->debugFile.str();
	rv=File::fileExists(cwdTest.str());
	Print::objectMethodDebug(std::cout,"GetCwd",rv);
	return rv;
}

bool FileDebug::debugGetPathFromList(void){
	bool rv=true;
	std::string path=File::getPathFromList(this->dirs);
	rv=(path==this->dirsPath.str());
	Print::objectMethodDebug(std::cout,"GetPathFromList",rv);
	return rv;
}

bool FileDebug::debugGetAbsPath(void){
	bool rv=true;
	std::stringstream correctAbsPath;
	correctAbsPath << File::getCwd() << File::pathDelim << this->debugFile.str();
	std::string absPath=File::getAbsPath(this->debugFile.str());
	rv=(absPath==correctAbsPath.str());
	Print::objectMethodDebug(std::cout,"GetAbsPath",rv);
	return rv;
}

bool FileDebug::debugObjectMethods(void){
	return (this->debugSetPath() &&
		this->debugGetDirList() &&
		this->debugGetDrive() &&
		this->debugGetExtension() &&
		this->debugGetName() &&
		this->debugGetNumLines() &&
		this->debugEquals() &&
		this->debugCopy() &&
		this->debugChangeExtension() &&
		this->debugChangeName() &&
		this->debugClear() &&
		this->debugIterator() &&
		this->debugWrite() &&
		this->debugAppend() &&
		this->debugCopyConstructor());
}

bool FileDebug::debugSetPath(void){
	bool rv=true;
	File testFile(this->debugFile.str());
	rv=(testFile.getPath()==File::getAbsPath(this->debugFile.str()));
	Print::objectMethodDebug(std::cout,"SetPath",rv);
	return rv;
}

bool FileDebug::debugGetDirList(void){
	bool rv=true;
	File testFile(this->dirsPath.str());
	std::vector<std::string> dirsList=testFile.getDirList();
	std::string createdPath=File::getPathFromList(dirsList);
	rv=(testFile.getPath()==createdPath);
	Print::objectMethodDebug(std::cout,"GetDirList",rv);
	return rv;
}

bool FileDebug::debugGetDrive(void){
	bool rv=true;
	File testFile(File::getAbsPath(this->debugFile.str()));
	char drive=testFile.getDrive();
	rv=(drive=='C');
	Print::objectMethodDebug(std::cout,"GetDrive",rv);
	return rv;
}

bool FileDebug::debugGetExtension(void){
	bool rv=true;
	File testFile(this->debugFile.str());
	std::string ext=testFile.getExtension();
	rv=(ext=="txt");
	Print::objectMethodDebug(std::cout,"GetExtenstion",rv);
	return rv;
}

bool FileDebug::debugGetName(void){
	bool rv=true;
	File testFile(this->debugFile.str());
	std::string name=testFile.getName();
	testFile.setPath("/folder/name/");
	std::string name2=testFile.getName();
	rv=(name=="FileTest" && name2=="name");
	Print::objectMethodDebug(std::cout,"GetName",rv);
	return rv;
}

bool FileDebug::debugGetNumLines(void){
	bool rv=true;
	File testFile(this->debugFile.str());
	rv=(testFile.getNumLines()==5);
	Print::objectMethodDebug(std::cout,"GetNumLines",rv);
	return rv;
}

bool FileDebug::debugEquals(void){
	bool rv=true;
	File origFile(this->debugFile.str());
	File equalsFile(this->equalsFile.str());
	rv=(origFile==equalsFile);
	Print::objectMethodDebug(std::cout,"Equals",rv);
	return rv;
}

bool FileDebug::debugCopy(void){
	bool rv=true;
	File testFile(this->debugFile.str());
	File copyFile(this->copyFile.str());
	copyFile.copy(testFile);
	rv=(copyFile==testFile);
	Print::objectMethodDebug(std::cout,"Copy",rv);
	return rv;
}

bool FileDebug::debugChangeExtension(void){
	bool rv=true;
	std::string newExt="xml";
	std::string newNewExt="csv";
	File prevFile(this->debugFile.str());
	File testFile(this->debugFile.str());

	rv&=testFile.changeExtension(newExt);
	rv&=(testFile.getExtension()==newExt);
	rv&=(prevFile==testFile);
	rv&=testFile.changeExtension(newNewExt,false);
	rv&=(testFile.getExtension()==newNewExt);
	rv&=(prevFile==testFile);
	rv&=File::remove(testFile.getPath());
	Print::objectMethodDebug(std::cout,"ChangeExtension",rv);
	return rv;
}

bool FileDebug::debugChangeName(void){
	bool rv=true;
	std::string newName="Testing";
	std::string newNewName="ChangeNameFileTest";
	File prevFile(this->debugFile.str());
	File testFile(this->debugFile.str());

	rv&=testFile.changeName(newName);
	rv&=(testFile.getName()==newName);
	rv&=(prevFile==testFile);
	rv&=testFile.changeName(newNewName,false);
	rv&=(testFile.getName()==newNewName);
	rv&=(prevFile==testFile);
	rv&=File::remove(testFile.getPath());
	Print::objectMethodDebug(std::cout,"ChangeName",rv);
	return rv;
}

bool FileDebug::debugClear(void){
	bool rv=true;
	std::string newExt="testing";
	File testFile(this->debugFile.str());

	rv&=testFile.changeExtension(newExt);
	testFile.clear();
	rv&=(testFile.getNumLines()==0);
	rv&=File::remove(testFile.getPath());
	Print::objectMethodDebug(std::cout,"Clear",rv);
	return rv;
}

bool FileDebug::debugIterator(void){
	bool rv=true;
	File testFile(this->debugFile.str());
	int i=0;
	std::stringstream temp;
	for (File::const_iterator iter=testFile.begin(); iter!=testFile.end(); iter++, i++){
		temp << i+1;
		rv&=(*iter==temp.str());
		rv&=(iter->size()==temp.str().size());
		temp.str(std::string());
	}
	rv&=(i==5);
	File::const_iterator iter1=testFile.begin();
	File::const_iterator iter2=testFile.begin();
	iter1+=2;
	iter2+=2;
	rv&=(iter1==iter2);
	Print::objectMethodDebug(std::cout,"Iterator",rv);
	return rv;
}

bool FileDebug::debugWrite(void){
	bool rv=true;
	int i=0;
	std::string newExt="testing";
	std::string data="one\ntwo\nthree";
	File testFile(this->debugFile.str());

	rv&=testFile.changeExtension(newExt);
	testFile.write(data);
	for (File::const_iterator iter=testFile.begin(); iter!=testFile.end(); iter++, i++){
		switch (i){
			case 0: rv&=(*iter=="one"); break;
			case 1: rv&=(*iter=="two"); break;
			case 2: rv&=(*iter=="three"); break;
			default: break;
		}
	}
	rv&=(i==3);
	File::remove(testFile.getPath());
	Print::objectMethodDebug(std::cout,"Write",rv);
	return rv;
}

bool FileDebug::debugAppend(void){
	bool rv=true;
	int i=0;
	std::string newExt="testing";
	std::string data="one\ntwo\nthree";
	File testFile(this->debugFile.str());

	rv&=testFile.changeExtension(newExt);
	testFile.append(data);
	for (File::const_iterator iter=testFile.begin(); iter!=testFile.end(); iter++, i++){
		switch (i){
			case 6: rv&=(*iter=="one"); break;
			case 7: rv&=(*iter=="two"); break;
			case 8: rv&=(*iter=="three"); break;
			default: break;
		}
	}
	rv&=(i==9);
	File::remove(testFile.getPath());
	Print::objectMethodDebug(std::cout,"Append",rv);
	return rv;
}

bool FileDebug::debugCopyConstructor(void){
	bool rv=true;
	File testFile(this->debugFile.str());
	File testFile2=testFile;
	rv&=(testFile==testFile2);
	Print::objectMethodDebug(std::cout,"CopyConstructor",rv);
	return rv;
}
