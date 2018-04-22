#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "lib/boost/filesystem.hpp"
#include "lib/boost/filesystem/fstream.hpp"
#include "zlib.h"
#include "log.h"
using namespace std;


int main(int argc, char **argv){			
				ZLib* zlib = new ZLib();
				string path(argv[1]);
				zipper::Unzipper unzipper = zlib->getUnzipper(path);

				vector<zipper::ZipEntry> entries = unzipper.entries();

				cout<<"Número de entradas: "<<entries.size()<<endl;
				std::string logsPath;
				std::vector<Log> logs;

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
												}

								}
				}

				cout<<"Total logs found: "<<logs.size()<<endl;

				if(logsPath.size() != 0) {
								cout<<"Logs folder found: "<<logsPath<<endl;
								unzipper.extractEntry(logsPath);
				}
				boost::filesystem::path dstFolder = "tmp";
				boost::filesystem::create_directory(dstFolder);

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
								//Hash
								std::hash<std::string> hash_fn;

								//Map
								std::map<std::size_t, unsigned long long int> hashMap;
								std::map<std::size_t, std::string> lineMap;

								while(std::getline(ss, line)){
												lineLength = line.length();
												if(lineLength > it.getLongestLine()) {
																it.setLongestLineLength(lineLength);
																it.setLongestLine(count);
												}

												size_t str_hash = hash_fn(line);
												if(hashMap.count(str_hash) == 0) {
																hashMap.insert(std::pair<std::size_t, unsigned long long int>(str_hash, 1));
																lineMap.insert(std::pair<std::size_t, std::string>(str_hash, line));
																cout<<"First line inserted"<<endl;
												} else {
																unsigned long long int currCount = hashMap.at(str_hash);
																cout<<"Found: "<<currCount<<endl;
												}
												//toca meter en el objeto los dos hash map. 
												//crear un map para las líneas que tienen error.
												//crear un contador en el objeto para los tres tipos de logs.
												//
												count++;
								}

								//unzipper.extractEntry(it.getName());
				}


				unzipper.close();
}