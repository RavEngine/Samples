#include <RavEngine/CTTI.hpp>
#include <unordered_map>
#include <iostream>
#include <cassert>
#include <functional>

using namespace RavEngine;
using namespace std;

int Test_CTTI(){
	
	auto t1 = CTTI<int>;
	auto t2 = CTTI<float>;
	auto t3 = CTTI<int>;
	
	assert(t1 == t3);
	assert(t1 != t2);
	assert(t2 != t3);
	
	return 0;
}

int main(int argc, const char** argv) {
    const unordered_map <string, std::function<int(void)>> tests{
		{"CTTI",&Test_CTTI}
    };
	
	if (argc < 2){
		cerr << "No test provided - use ctest" << endl;
		return -1;
	}
	
    const std::string test = argv[1];
    if (tests.find(test) != tests.end()) {
       return tests.at(test)();
    }
    else {
        cerr << "No test with name: " << test << endl;
        return -1;
    }
    return 0;
}
