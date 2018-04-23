#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>
#include "lib/boost/filesystem.hpp"
#include "lib/boost/filesystem/fstream.hpp"
#include "zlib.h"
#include "log.h"
using namespace std;


int main(int argc, char **argv){			

				if(argc == 1) {
								cout<<"Usage: "<<endl<<"./programa <zipfilepath> <logname>"<<endl;
				}
				string path(argv[1]);
				string logName("log.txt");
				if(argc >= 3) {
								logName = argv[2];
				} 

				Log log;
				log.processLogs(path, logName);

}
