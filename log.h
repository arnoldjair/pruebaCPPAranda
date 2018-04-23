#include <string>
#include <map>

class Log {
				private:
								std::string name;
								std::string path;
								unsigned long long int size;
								unsigned long long int errorCount;
								unsigned long long int longestLine;
								int longestLineLength;
								unsigned long long int commonErrorCount;
								unsigned long long int infoCount;
								unsigned long long int debugCount;
								std::string commonError;
								std::map<std::string, unsigned long long int> lineMap;
				public:
								Log(){
								};
								Log(std::string name, std::string path, unsigned long long int size): name(name), path(path), size(size) {
												this->errorCount = 0;
												this->longestLine = 0;
												this->longestLineLength = 0;
												this->commonErrorCount = 0;
												this->infoCount = 0;
												this->debugCount = 0;
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

								void setCommonErrorCount(unsigned long long int commonErrorCount) {
												this->commonErrorCount = commonErrorCount;
								}

								unsigned long long int getCommonErrorCount() {
												return this->commonErrorCount;
								}

								void setCommonError(std::string commonError) {
												this->commonError = commonError;
								}

								std::string getCommonError() {
												return this->commonError;
								}

								void setInfoCount(unsigned long long int infoCount){
												this->infoCount = infoCount;
								}

								unsigned long long int getInfoCount(){
												return this->infoCount;
								}

								void setDebugCount(unsigned long long int debugCount) {
												this->debugCount = debugCount;
								}

								unsigned long long int getDebugCount() {
												return this->debugCount;
								}

								void setLineMap(std::map<std::string, unsigned long long int>  &lineMap) {
												this->lineMap = lineMap;
								}

								std::map<std::string, unsigned long long int>  *getLineMap() {
												return &this->lineMap;
								}
								unsigned long long int increaseErrorCount();
								unsigned long long int increaseInfoCount();
								unsigned long long int increaseDebugCount();

								void printLogInfo();

								void printLogInfo(std::string filename);


};
