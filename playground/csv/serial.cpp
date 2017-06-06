/*
  load csv file in serial using cpp

  g++ serial.cpp
  ./a.out

  https://stackoverflow.com/questions/1120140/how-can-i-read-and-parse-csv-files-in-c
  https://stackoverflow.com/questions/2808398/easily-measure-elapsed-time
*/

#include <iostream>
#include <fstream>
#include <cstdio>
#include <chrono>

void ReadFile()
{
  // std::FILE *f = std::fopen("prices-split-adjusted.csv", "r");
  // if (!f)
  // {
  //   std::perror("failed to open file");
  // }
  // std::fclose(f);
  std::ifstream f("prices-split-adjusted.csv");
  if (!f.is_open())
  {
    std::perror("failed to open file");
  }
  std::string line;
  int i = 0;
  auto begin = std::chrono::steady_clock::now();
  while (std::getline(f, line))
  {
    i++;
  }
  auto end = std::chrono::steady_clock::now();

  std::cout << i << std::endl; // 851265
  std::chrono::duration<double> elapsed_seconds = end - begin;
  std::cout << "elapsed time: " << elapsed_seconds.count() << std::endl;
  std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::seconds>(end - begin).count() << std::endl;
  std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << std::endl;
  std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << std::endl;
  f.close();
}

int main()
{
  std::cout << "Hello world" << std::endl;
  ReadFile();
  return 0;
}
