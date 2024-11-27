#include <iostream>
#include <vector>

using namespace std;

class TestClass
{
    /*int id;
    /*char name;
    char surname;#1#
    int age;*/
    vector<int> relations;
};

int main(int argc, char* argv[])
{
    std::cout << "TestCLass Bytes size:" << sizeof(TestClass) << std::endl;
    std::cout << "Vector Bytes size:" << sizeof(std::vector<int>) << std::endl;
    return 0;
}
