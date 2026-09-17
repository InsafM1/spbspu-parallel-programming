#include <iostream>
#include <future>
#include <vector>
#include <cstring>
#include <string>
#include <algorithm>
#include "clicker.hpp"

using data_t = std::vector< unsigned long long >;
using value_t = data_t::value_type;

value_t summation(
  const std::vector< unsigned long long >& vector,
  size_t start,
  size_t end
)
{
  value_t sum = 0;
  for (size_t i = start; i < end; ++i)
  {
    sum += vector[i];
  }
  return sum;
}

value_t parallel_summation(
  const std::vector< unsigned long long >& vector,
  size_t number_of_process
)
{
  size_t s = vector.size();
  size_t length = (s + number_of_process - 1) / number_of_process;
  std::vector< std::future< value_t > > futures;
  for (size_t i = 0; i < number_of_process; ++i)
  {
    size_t start = i * length;
    size_t end = std::min(start + length, s);
    futures.push_back(
      std::async(
        std::launch::async,
        summation,
        std::ref(vector),
        start,
        end
      )
    );
  }

  value_t total = 0;
  for (size_t i = 0; i < number_of_process; ++i)
  {
    total += futures[i].get();
  }
  return total;
}

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cerr << "Exactly one argument is expected\n";
    return 1;
  }

  size_t number_of_process = 0;
  try
  {
    size_t pos = 0;
    number_of_process = std::stoi(argv[1], &pos);
    if (pos != std::strlen(argv[1]))
    {
      std::cerr << "Invalid argument: incorrectly recorded numbers\n";
      return 1;
    }
  }
  catch(const std::exception& e)
  {
    std::cerr << "Invalid argument: " << e.what() << '\n';
    return 1;
  }

  if (number_of_process == 0)
  {
    std::cerr << "Argument must be > 0\n";
    return 0;
  }

  constexpr size_t size{200'000'000};
  double init{0}, total{0};
  value_t sum{0};
  data_t values(size, 1);
  double result{0};
  for (size_t i = 0; i < 5; ++i)
  {
    Clicker clicker;
    sum += parallel_summation(values, number_of_process);
    result += clicker.millisec();
    sum = 0;
  }

  std::cout << number_of_process << ": " << result / 5.0 << '\n';
  return 0;
}
