#include <string>

class Log {
				private:
								std::string name;
								std::string path;
								unsigned long long int size;
								unsigned long long int errorCount;
								unsigned long long int longestLine;
								int longestLineLength;
				public:
								Log(){
								};
								Log(std::string name, std::string path, unsigned long long int size): name(name), path(path), size(size) {
												this->errorCount = 0;
												this->longestLine = -1;
												this->longestLineLength = 0;
								}
								~Log();

								void setName(std::string name) {
												this->name = name;
								}

								std::string getName() {
												return this->name;
								}

								void setPath(std::string path) {
												this->path = path;
								}

								std::string getPath() {
												return this->path;
								}

								void setErrorCount(unsigned long long int errorCount) {
												this->errorCount = errorCount;
								}

								unsigned long long int getErrorCount() {
												return this->errorCount;
								}

								void setLongestLine(unsigned long long int longestLine) {
												this->longestLine = longestLine;
								}

								unsigned long long int getLongestLine() {
												return this->longestLine;
								}

								void setLongestLineLength(int length){
												this->longestLineLength = length;
								}

								int getLongestLineLength() {
												return this->longestLineLength;
								}

								unsigned long long int increaseErrorCount();

								void printLogInfo();


};
