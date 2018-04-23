#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>
#include "zlib.h"
#include "db.h"
#include "sqlite3.h"

DB::~DB(){
}

void DB::printDBInfo() {
				std::cout<<"\tName: "<<this->name<<std::endl;
				std::cout<<"\tPath: "<<this->path<<std::endl;
				std::cout<<"\tsize: "<<this->size<<" bytes"<<std::endl;
				std::cout<<std::endl<<std::endl<<std::endl;
}

void DB::printDBInfo(std::string filename) {
				std::ofstream logFile(filename, std::ios::app);
				if(logFile.is_open()) {
								logFile<<"\tName: "<<this->name<<std::endl;
								logFile<<"\tPath: "<<this->path<<std::endl;
								logFile<<"\tsize: "<<this->size<<" bytes"<<std::endl;
								logFile<<std::endl<<std::endl<<std::endl;
								logFile.close();
				}


}

void DB::processDBs(std::string path, std::string logName) {
				ZLib* zlib = new ZLib();
				std::ofstream ofs;
				ofs.open(logName, std::ofstream::out | std::ofstream::trunc);

				zipper::Unzipper unzipper = zlib->getUnzipper(path);

				vector<zipper::ZipEntry> entries = unzipper.entries();

				cout<<"Número de entradas: "<<entries.size()<<endl;
				std::string dbsPath;
				std::vector<DB> dbs;

				for(std::vector<zipper::ZipEntry>::iterator it = entries.begin(); it != entries.end(); ++it) {
								std::size_t pos = it->name.find("/data/");
								if(pos != std::string::npos) {
												if(it->name.at(it->name.size() - 1) == '/'){
																cout<<"Folder found: "<<it->name<<endl;
																dbsPath = it->name;
												} else {
																unzipper.extractEntry(it->name);
																sqlite3 *sqliteDB;
																const char *sqliteName = it->name.c_str();
																cout<<"Opening "<<it->name<<endl;
																int rc = sqlite3_open(sqliteName, &sqliteDB);
																if(rc == SQLITE_OK) {
																				std::string sql("SELECT * FROM sqlite_master where type='table'");
																				rc = sqlite3_exec(sqliteDB, sql.c_str(), NULL, 0, NULL);
																				if(rc != SQLITE_OK) {
																								cout<<"Not a valid db"<<endl;
																				} else {
																								std::cout<<"Valid db"<<endl;
																								pos = it->name.find("/data/") + 6;
																								std::string name = it->name.substr(pos);
																								DB db = DB(name, it->name, it->uncompressedSize);
																								dbs.push_back(db);
																				}
																} else {
																				cout<<"Database error"<<endl;
																}
												}

								}
				}

				ofs<<"DBs:"<<endl;

				ofs.close();

				cout<<"Total dbs found: "<<dbs.size()<<endl;

				if(dbsPath.size() != 0) {
								cout<<"DBs folder found: "<<dbsPath<<endl;
				}

				for(auto& it : dbs) {
								unzipper.extractEntry(it.getPath());
								it.printDBInfo(logName);

				}


				unzipper.close();

}


