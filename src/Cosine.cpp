// Standard headers
#include <thread>
#include <iostream>

int main(int argc, char **argv)
{
    unsigned int n = std::thread::hardware_concurrency();
    std::cout << n << " concurrent threads are supported.\n";
    return 0;
}
