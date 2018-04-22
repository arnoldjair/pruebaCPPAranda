#include <string>
#include <iostream>
#include "zlib.h"
#include "zipper.h"
#include "unzipper.h"
//using namespace std;
using namespace zipper;

zipper::Unzipper ZLib::getUnzipper(string path){
				Unzipper unzipper(path);
				return unzipper;
}
