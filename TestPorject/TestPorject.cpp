#include <iostream>
#include <fstream>
#include <sstream>
#include <typeindex>
#include <vector>
#include <unordered_map>

#define Debug_Output(x) std::cout<<(x)<<std::endl

using namespace std;

class Base;
class Child;

inline std::string LoadStringFromFile(const std::string& path)
{
    std::string shaderCode;
    std::ifstream shaderFile;
    try
    {
        shaderFile.open(path);
        std::stringstream shaderStream;
        shaderStream << shaderFile.rdbuf();
        shaderFile.close();
        shaderCode = shaderStream.str();
    }
    catch (std::ifstream::failure& e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
    }
    return shaderCode;
}

class Base
{
public:
    template <typename Type>
    static Type* Get()
    {
        static Type* type = new Type;
        return type;
    }

protected:
    Base()
    {
        Debug_Output("Base Construct");
    }

    virtual ~Base()
    {
    }
};

class Child : public Base
{
    friend Base;

protected:
    Child()
    {
        Debug_Output("Child Construct");
    }

    ~Child()
    {
    }
};

#define UI_CODES(x) x

int main(int argc, char* argv[])
{
    std::string codes_str = LoadStringFromFile("Resource/test_codes.txt");
    UI_CODES(codes_str);
    std::cout << "end test" << std::endl;
}
