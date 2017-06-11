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
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

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

void ReadHeader()
{
  std::ifstream f("prices-split-adjusted.csv");
  if (!f.is_open())
  {
    std::perror("failed to open file");
  }

  std::string line;
  // FIXED: has incomplete type and cannot be defined
  // #include <sstream>
  std::stringstream line_stream;
  std::string cell;
  std::vector<std::string> header;
  std::vector<std::string> values;

  std::getline(f, line);
  std::cout << line << std::endl;
  line_stream << line;
  while (std::getline(line_stream, cell, ','))
  {
    header.push_back(std::move(cell));
  }
  for (const auto &h : header)
  {
    std::cout << h << std::endl;
  }
  // FIXED: you can't reuse the line stream, need to call clear()
  // https://www.eecis.udel.edu/~breech/progteam/stringstream.html
  std::getline(f, line);
  std::cout << line << std::endl;
  line_stream.clear();
  line_stream << line;
  while (std::getline(line_stream, cell, ','))
  {
    values.push_back(std::move(cell));
  }
  for (const auto &v : values)
  {
    // std::cout << v << std::endl;
    std::printf("%s\n", v.c_str());
  }
  // now let's infer the schema? or let the user specify it? ...
  // well let the user specify it ....
  // FIXME: it's 2016-01-05 00:00:00, but it seems the stream stop on blank ?
  // FIXED: it's the problem of Kaggle
  // prices.csv and prices-split-adjusted.csv use different time format ....
  // 2016-01-05
  std::tm tm;
  std::stringstream value_stream;
  value_stream << values[0];
  // http://en.cppreference.com/w/cpp/io/manip/get_time
  value_stream >> std::get_time(&tm, "%Y-%m-%d");
  // value_stream >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
  if (value_stream.fail())
  {
    std::cout << "failed to parse time" << std::endl;
  }
  else
  {
    // FIXME: ? Jan  5 1611344960:21939:1375664304 2016
    // TODO: get epoch
    std::cout << std::put_time(&tm, "%c") << std::endl;
  }
  // TODO: parse float, double etc.
  // http://en.cppreference.com/w/cpp/string/basic_string/stof
}

int main()
{
  std::cout << "Hello world" << std::endl;
  // ReadHeader();
  ReadFile();
  return 0;
}
