
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
    std::cout << "Type one of the following commands:\n- 'default' to execute the standard automated test\n- 'custom' to execute the custom automated test\n- 'manual' to execute a manual test\n- 'exit' to close the program\n>";
    std::cin >> command;
    std::cout << std::endl;

    if (command == "default")
      lasdtest();
    else if (command == "custom")
      customTest();
    else if (command == "manual")
      manualTest();

  } while (command != "exit");

  return 0;
}
