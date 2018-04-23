#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>
#include "lib/boost/filesystem.hpp"
#include "lib/boost/filesystem/fstream.hpp"
#include "zlib.h"
#include "log.h"
#include "sqlite3.h"
#include "db.h"
using namespace std;


int main(int argc, char **argv){			

				if(argc == 1) {
								cout<<"Usage: "<<endl<<"./programa <zipfilepath> <logname> <dblogname>"<<endl;
				}
				string path(argv[1]);
				string logName("log.txt");
				string dbLogname("dbLog.txt");
				if(argc >= 3) {
								logName = argv[2];
				} 
				if(argc >= 4) {
								dbLogname = argv[3]; //Como que mejor verifico si hay algo en la pos.
				}

				Log log;
				log.processLogs(path, logName);

				DB db;
				db.processDBs(path, dbLogname);
				//sqlite3 *db;
				//int rc = sqlite3_open("Hola.db", &db);
				


}
