#include <memory>
#include <iostream>

class Test
{
private:
    /* data */
public:
    ~Test()
    {
        std::cout << "Znicen!" << std::endl;
    }
};

int main()
{
    {
        std::unique_ptr<Test> u_test_1 = std::make_unique<Test>(Test());
        std::cout << "TEST\n";
    }
    
    std::shared_ptr<int> s_cislo_1 = std::make_shared<int>(100);
    {
        std::shared_ptr<int> s_cislo_2 = s_cislo_1;
        std::cout << s_cislo_1.use_count() << std::endl;
    }
    std::cout << s_cislo_1.use_count() << std::endl;
    std::cout << "TEST\n";
    return 0;
}
