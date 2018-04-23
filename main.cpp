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

				ZLib* zlib = new ZLib();
				std::ofstream ofs;
				ofs.open(logName, std::ofstream::out | std::ofstream::trunc);
				//ofs.close();

				zipper::Unzipper unzipper = zlib->getUnzipper(path);

				vector<zipper::ZipEntry> entries = unzipper.entries();

				cout<<"Número de entradas: "<<entries.size()<<endl;
				std::string logsPath;
				std::vector<Log> logs;

				ofs<<"Logs greater than 10MB: "<<endl;

				for(std::vector<zipper::ZipEntry>::iterator it = entries.begin(); it != entries.end(); ++it) {
								//cout<<"Entry: "<<it->name<<endl;
								std::size_t pos = it->name.find("/logs/");
								if(pos != std::string::npos) {
												//test if the last character is /
												if(it->name.at(it->name.size() - 1) == '/'){
																cout<<"Folder found: "<<it->name<<endl;
																logsPath = it->name;
												} else {
																pos = it->name.find("/logs/") + 6;
																std::string name = it->name.substr(pos);
																Log log = Log(name, it->name, it->uncompressedSize);
																logs.push_back(log);
																if(it->uncompressedSize >= 10000000) {
																				ofs<<"\tname => "<<it->uncompressedSize*1.0 / 10000000<<" MB"<<endl; 
																}
												}

								}
				}

				ofs<<"Logs:"<<endl;

				ofs.close();

				cout<<"Total logs found: "<<logs.size()<<endl;

				if(logsPath.size() != 0) {
								cout<<"Logs folder found: "<<logsPath<<endl;
				}

				for(auto& it : logs) {
								//In memory
								std::vector<unsigned char> content;
								unzipper.extractEntryToMemory(it.getPath(), content);
								std::string contentA(content.begin(), content.end());
								//boost::filesystem::path p{"tmp/"+it.getName()};
								//boost::filesystem::ofstream ofs{p};
								//ofs << contentA;
								std::stringstream ss(contentA);
								std::string line;
								int lineLength = 0;
								unsigned long long int count = 0;
								unsigned long long int commonErrorCount = 0;
								std::string commonError;
								//Hash
								std::hash<std::string> hash_fn;

								//Map
								std::map<std::size_t, unsigned long long int> hashMap;
								std::map<std::size_t, std::string> lineHashMap;
								//std::map<std::string, unsigned long long int> lineHashMap;
								std::map<std::size_t, unsigned long long int> errorMap;

								while(std::getline(ss, line)){
												//Error count
												std::size_t pos = line.find("ERROR");
												if(pos != std::string::npos) {
																it.increaseErrorCount();
																std::string currError = line.substr(pos + 11);
																std::map<std::size_t, unsigned long long int>::iterator currIt = errorMap.find(hash_fn(currError));
																if(currIt != errorMap.end()) {
																				currIt->second = currIt->second + 1;
																				if(currIt->second + 1 > commonErrorCount) {
																								commonErrorCount = currIt->second;
																								commonError = currError;
																				}
																} else {
																				errorMap.insert(std::pair<std::size_t, unsigned long long int>(hash_fn(currError), 1));
																				if(commonErrorCount == 0){
																								commonErrorCount = 1;
																								commonError = currError;
																				}
																}
																//std::cout<<"Curr err: "<<commonError<<std::endl;
												}

												//Info count
												pos = line.find("INFO");
												if(pos != std::string::npos) {
																it.increaseInfoCount();
												}

												//Debug count
												pos = line.find("DEBUG");
												if(pos != std::string::npos) {
																it.increaseDebugCount();
												}

												//Longest line
												lineLength = line.length();
												if(lineLength > it.getLongestLine()) {
																it.setLongestLineLength((unsigned long long int)lineLength);
																it.setLongestLine(count + 1);
												}

												line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());

												//std::regex pattern("\\b\\d{4}[-]\\d{2}[-]\\d{2}\\b");
												//std::regex pattern("\\b\\d{4}[-]\\d{2}[-]\\d{2}[ ]\\d{2}[:]\\d{2}[:]\\d{2}\\b");
												//Muy costoso
												/*if(line.length() > 22 && regex_search(line,  pattern)) { //Osea, si hay una fecha
													line = line.substr(22);
													}*/
												if(line.find("[") == 0 && line.find("]") == 20) {
																line = line.substr(22);
												}

												size_t str_hash = hash_fn(line);
												std::map<std::size_t, unsigned long long int>::iterator lineIt = hashMap.find(str_hash);
												if(lineIt != hashMap.end()) {
																lineIt->second = lineIt->second + 1;
												} else {
																hashMap.insert(std::pair<std::size_t, unsigned long long int>(str_hash, 1));
																lineHashMap.insert(std::pair<std::size_t, std::string>(str_hash, line));
												}
												count++;
								}

								std::map<std::string, unsigned long long int> lineMap;
								for(auto &hashMapIt: hashMap) {
												//cout<<"First: "<<hashMapIt.first<<". Second: "<<hashMapIt.second<<std::endl;
												auto val = lineHashMap[hashMapIt.first];
												lineMap[val] = hashMapIt.second;
								}

								it.setCommonErrorCount(commonErrorCount);
								it.setCommonError(commonError);
								it.setLineMap(lineMap);
								it.printLogInfo(logName);

				}


				unzipper.close();
}
