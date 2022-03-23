#include "app/app.hpp"

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

    app::start_app();

    return 0;
}

#endif
