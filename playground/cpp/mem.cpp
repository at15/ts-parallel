/*
  Try out basic C++ operations that involve memory
*/

#include <iostream>
#include <vector>

void move()
{
  std::vector<std::string> vec;

  std::string sc("copy me!");
  std::string sm("move me!");

  vec.push_back(std::move(sm));

  std::cout << sc << std::endl; // nothing
  std::cout << sm << std::endl; // empty line, note we still have the endl
}

std::string giveMeString()
{
  return std::string("ha?");
}

int main()
{
  std::cout << "C++ Mem operation demos" << std::endl;
  move();
  std::cout << giveMeString() << std::endl;
}
