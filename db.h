#include <string>
#include <map>

class DB {
				private:
								std::string name;
								std::string path;
								unsigned long long int size;
				public:
								DB(){
								};
								DB(std::string name, std::string path, unsigned long long int size): name(name), path(path), size(size) {

								}
								~DB();

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

								void setSize(unsigned long long int size) {
												this->size = size;
								}

								unsigned long long int getSize() {
												return this->size;
								}

								void printDBInfo();

								void printDBInfo(std::string filename);

								void processDBs(std::string path, std::string logName);


};
