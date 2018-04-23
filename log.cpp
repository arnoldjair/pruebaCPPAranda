#include <iostream>
#include <fstream>
#include <string>
#include "log.h"

Log::~Log(){
}

unsigned long long int Log::increaseErrorCount() {
				this->errorCount = this->errorCount + 1; // this->errorCount++;
				return this->errorCount;
}

void Log::printLogInfo() {
				std::cout<<"\tName: "<<this->name<<std::endl;
				std::cout<<"\tPath: "<<this->path<<std::endl;
				std::cout<<"\tsize: "<<this->size<<" bytes"<<std::endl;
				std::cout<<"\tError count: "<<this->errorCount<<std::endl;
				std::cout<<"\tLongest line: "<<this->longestLine<<std::endl;
				std::cout<<"\tCommon error: "<<this->commonError<<std::endl;
				std::cout<<"\tCommon error count: "<<this->commonErrorCount<<std::endl;
				std::cout<<"\tInfo count: "<<this->infoCount<<std::endl;
				std::cout<<"\tDebug count: "<<this->debugCount<<std::endl;
				std::cout<<"\tUnique lines:"<<std::endl;
				for (std::map<std::string, unsigned long long int>::iterator it = this->lineMap.begin(); it != this->lineMap.end(); ++it) {
								std::cout<<"\t\t"<<it->first << " => " << it->second <<std::endl;
				}
				std::cout<<std::endl<<std::endl<<std::endl;
}

void Log::printLogInfo(std::string filename) {
				std::ofstream logFile(filename, std::ios::app);
				if(logFile.is_open()) {
								logFile<<"\tName: "<<this->name<<std::endl;
								logFile<<"\tPath: "<<this->path<<std::endl;
								logFile<<"\tsize: "<<this->size<<" bytes"<<std::endl;
								logFile<<"\tError count: "<<this->errorCount<<std::endl;
								logFile<<"\tLongest line: "<<this->longestLine<<std::endl;
								logFile<<"\tCommon error: "<<this->commonError<<std::endl;
								logFile<<"\tCommon error count: "<<this->commonErrorCount<<std::endl;
								logFile<<"\tInfo count: "<<this->infoCount<<std::endl;
								logFile<<"\tDebug count: "<<this->debugCount<<std::endl;
								logFile<<"\tUnique lines:"<<std::endl;
								for (std::map<std::string, unsigned long long int>::iterator it = this->lineMap.begin(); it != this->lineMap.end(); ++it) {
												logFile <<"\t\t"<< it->first << " => " << it->second <<std::endl;
								}
								logFile<<std::endl<<std::endl<<std::endl;
								logFile.close();
				}


}

unsigned long long int Log::increaseInfoCount() {
				this->infoCount = this->infoCount + 1;
				return this->infoCount;
}

unsigned long long int Log::increaseDebugCount() {
				this->debugCount = this->debugCount + 1;
				return this->debugCount;
}
