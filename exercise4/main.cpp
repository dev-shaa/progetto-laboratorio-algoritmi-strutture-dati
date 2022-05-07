
#include "zlasdtest/test.hpp"

#include "zmytest/test.hpp"

/* ************************************************************************** */

#include <iostream>

/* ************************************************************************** */

int main()
{
  std::cout << "Lasd Libraries 2022" << std::endl;

  char command;
  bool exitRequest = false;

  do
  {
    std::cout << "\navailable commands:\n- q to quit\n- d to execute default test\n- m to execute manual test\n>";

    if (std::cin >> command)
    {
      switch (command)
      {
      case 'q':
        exitRequest = true;
        break;
      case 'd':
        lasdtest();
        break;
      case 'm':
        std::cout << "\n";
        manualTest();
      default:
        std::cerr << "invalid input\n";
        break;
      }
    }
    else
    {
      // handleInvalidInput();
    }
  } while (!exitRequest);

  return 0;
}
