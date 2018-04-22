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
}
