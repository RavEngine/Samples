#include <RavEngine/SharedObject.hpp>
#include <unordered_map>

using namespace RavEngine;
using namespace std;

/**
* Test shared object
*/
int Test_SharedObject() {
    //weak ref test
    {
        WeakRef<SharedObject> weak;
        {
            Ref<SharedObject> obj(new SharedObject());
            weak = obj;
        }
        assert(weak.isNull());
    }
    return 0;
}

int main(int argc, const char** argv) {
    const unordered_map <string, std::function<int(void)>> tests = {
        {"SharedObject",&Test_SharedObject}
    };

    const std::string test = argv[1];
    if (tests.find(test) != tests.end()) {
       return tests.at(test)();
    }
    else {
        cerr << "No test with name: " << test << endl;
        return -1;
    }
}