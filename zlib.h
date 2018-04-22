#include <string>
#include "zipper.h"
#include "unzipper.h"

using namespace std;

class ZLib {
				public:
								ZLib() {
								};
								~ZLib();
								zipper::Unzipper getUnzipper(string path);
};
