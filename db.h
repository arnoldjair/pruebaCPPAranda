#include <string>
#include <map>

class DBEntry {
				private:
								std::string tblName;
								std::string sql;
								unsigned long long int numRecords;
				public:
								DBEntry() {
												this->numRecords = 0;
								}

								DBEntry(std::string tblName, std::string sql, unsigned long long int numRecords): tblName(tblName), sql(sql), numRecords(numRecords) {

								}

								~DBEntry();

								void setTblName(std::string tblName) {
												this->tblName = tblName;
								}

								std::string getTblName() {
												return this->tblName;
								}

								void setSql(std::string sql){
												this->sql = sql;
								}

								std::string getSql() {
												return this->sql;
								}

								void setNumRecords(unsigned long long int numRecords) {
												this->numRecords = numRecords;
								}

								unsigned long long int getNumRecords() {
												return this->numRecords;
								}
};

class DB {
				private:
								std::string name;
								std::string path;
								std::vector<DBEntry> entries;
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

								void setEntries(std::vector<DBEntry> &entries) {
												this->entries = entries;
								}


								void printDBInfo();

								void printDBInfo(std::string filename);

								void processDBs(std::string path, std::string logName);


};


