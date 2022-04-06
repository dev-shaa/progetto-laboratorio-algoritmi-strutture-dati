
#include "zlasdtest/test.hpp"

#include "zmytest/test.hpp"

/* ************************************************************************** */

#include <iostream>

/* ************************************************************************** */

#define EXIT_INPUT "exit"

int main()
{
  std::cout << "Lasd Libraries 2022" << std::endl;

  // TODO: chiedi all'utente cosa eseguire

  std::string command;

  do
  {
    // std::cout << "Type 'custom', 'lasd' or 'exit'" << std::endl;
    // std::cin >> command;

    myTest();

    // if (command == "custom")
    //   myTest();
    // else if (command == "lasd")
    //   lasdtest(); // To call in the menu of your library test!

  } while (command != EXIT_INPUT);

  return 0;
}
