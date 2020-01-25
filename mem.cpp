#include <iostream>
#include <string>
using namespace std;
int main()
{
    string text("aaaabccabcabcaaacababaa");
    int len = text.size();
    int * next = new int[len];
    std::cout << "before delete" << std::endl;
    delete[] next;
    std::cout << "after delete" << std::endl;
    return 0;
}

