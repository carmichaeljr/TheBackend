#ifndef FILE_CLASS
#define FILE_CLASS

#define WINDOWS 0
#define UNIX 1
#define LINUX 2
#define MAC 3
#define OS_UK -1

#if defined(_WIN32) || defined(WIN63)
	#define OS WINDOWS
#elif defined(unix) || defined(__unix) || defined(__unix__)
	#define OS UNIX
#elif defined(__APPLE__) || defined(__MACH__)
	#define OS MAC
#elif defined(__linux__) || defined(linux) || defined(__linux)
	#define OS LINUX
#else
	#define OS OS_UK
#endif

#include <memory>
#include <vector>
#include <string>
#include <sstream>
#include <utility>
#include <fstream>

class File {
	friend bool operator==(const File &rhs, const File &lhs);
	friend bool operator!=(const File &rhs, const File &lhs);
	public:
		static const char pathDelim=
#if OS==WINDOWS
		'\\';
#else
		'/';
#endif
	public:
		class iterator {
			public:
				iterator(void);
				explicit iterator(const std::string &path);
				iterator& operator++(const int num);
				iterator& operator+=(const int num);
				bool operator==(const iterator &other) const;
				bool operator!=(const iterator &other) const;
				std::string& operator*(void);
				const std::string& operator*(void) const;
				std::string* operator->(void);
				const std::string* operator->(void) const;
				~iterator(void);
			private:
				unsigned int lineNum=0;
				std::string line;
				std::string path;
				std::shared_ptr<std::ifstream> file;
		};

		explicit File(const std::string &file);
		File(const File &other);
		File(const File &&other);
		File& operator=(const File &other);
		File& operator=(const File &&other);
		void setPath(const std::string &path);
		const std::string& getPath(void) const;
		std::vector<std::string> getDirList(void) const;
		bool changeDrive(const char drive, const bool makeCopy=true);
		char getDrive(void) const;
		bool changeExtension(const std::string &newExt, const bool makeCopy=true);
		std::string getExtension(void) const;
		bool changeName(const std::string &newName, const bool makeCopy=true);
		std::string getName(void) const;
		File::iterator begin(void) const;
		File::iterator end(void) const;
		unsigned int getNumLines(void) const;
		void copy(const File &other) const;
		void write(const std::string &data);
		void append(const std::string &data);
		void clear(void);
		static bool fileExists(const std::string &file);
		static bool remove(const std::string &file);
		static std::string getCwd(void);
		static std::string getPathFromList(const std::vector<std::string> &dirs);
		static std::string getPathToApplication(void);
		//static std::vector<std::string> getFilesInDir(const std::string &str);
		static std::string getAbsPath(const std::string &relPath);
	protected:
		std::string path;
	private:
		std::pair<unsigned int, unsigned int> getDriveIndexes(void) const;
		std::pair<unsigned int, unsigned int> getExtensionIndexes(void) const;
		std::pair<unsigned int, unsigned int> getNameIndexes(void) const;
		bool modifyFilePath(const std::string &newPath, const bool makeCopy);
};

#endif
