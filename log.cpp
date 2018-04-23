#include <iostream>
#include "log.h"

Log::~Log(){
}

unsigned long long int Log::increaseErrorCount() {
				this->errorCount = this->errorCount + 1; // this->errorCount++;
				return this->errorCount;
}

void Log::printLogInfo() {
				std::cout<<"Name: "<<this->name<<std::endl;
				std::cout<<"Path: "<<this->path<<std::endl;
				std::cout<<"size: "<<this->size<<std::endl;
				std::cout<<"Error count: "<<this->errorCount<<std::endl;
				std::cout<<"Longest line: "<<this->longestLine<<std::endl;
				std::cout<<"Common error: "<<this->commonError<<std::endl;
				std::cout<<"Common error count: "<<this->commonErrorCount<<std::endl;
				std::cout<<"Info count: "<<this->infoCount<<std::endl;
				std::cout<<"Debug count: "<<this->debugCount<<std::endl;
				std::cout<<"Unique lines:"<<std::endl;
				for (std::map<std::string, unsigned long long int>::iterator it = this->lineMap.begin(); it != this->lineMap.end(); ++it) {
								std::cout << it->first << " => " << it->second <<std::endl;
				}
				std::cout<<std::endl<<std::endl<<std::endl;
}

unsigned long long int Log::increaseInfoCount() {
				this->infoCount = this->infoCount + 1;
				return this->infoCount;
}

unsigned long long int Log::increaseDebugCount() {
				this->debugCount = this->debugCount + 1;
				return this->debugCount;
}
