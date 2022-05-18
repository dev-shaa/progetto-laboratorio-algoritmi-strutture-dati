
#include "zlasdtest/test.hpp"

#include "zmytest/test.hpp"

/* ************************************************************************** */

#include <iostream>

/* ************************************************************************** */

#define CMD_MENU_QUIT 0
#define CMD_DEFAULT_TEST 1
#define CMD_MANUAL_TEST 2

int main()
{
  std::cout << "Lasd Libraries 2022" << std::endl;

  int command;
  bool exitRequest = false;

  do
  {
    std::cout << "\navailable commands:\n- " << CMD_MENU_QUIT << " to quit\n- " << CMD_DEFAULT_TEST << " to execute default test\n- " << CMD_MANUAL_TEST << " to execute manual test\n>";

    if (std::cin >> command)
    {
      switch (command)
      {
      case CMD_MENU_QUIT:
        exitRequest = true;
        break;
      case CMD_DEFAULT_TEST:
        lasdtest();
        break;
      case CMD_MANUAL_TEST:
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
