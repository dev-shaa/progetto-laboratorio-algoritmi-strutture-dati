
#include "zlasdtest/test.hpp"

#include "zmytest/test.hpp"

/* ************************************************************************** */

#include <iostream>

/* ************************************************************************** */

int main()
{
  std::cout << "Lasd Libraries 2022" << std::endl;
  std::string command;

  do
  {
    std::cout << std::endl
              << "Type one of the following commands:" << std::endl
              << "- 'default' to execute the standard automated test" << std::endl
              << "- 'custom' to execute the custom test" << std::endl
              << "- 'exit' to close the program" << std::endl
              << ">";

    std::cin >> command;

    if (command == "default")
      lasdtest();
    else if (command == "custom")
      myTest();

  } while (command != "exit");

  return 0;
}
