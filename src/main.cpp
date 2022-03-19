#include <iostream>


#ifdef PYTHON_ONLY

int main()
{
    std::cout << "Hello World!\n";

    std::system("python python/main.py foo bar");

    return 0;
}

#endif


#ifndef PYTHON_ONLY

int main()
{
    std::cout << "Hello World!\n";

    std::system("python python/main.py foo bar");

    std::cout << "Application launches now!\n";

    return 0;
}

#endif
