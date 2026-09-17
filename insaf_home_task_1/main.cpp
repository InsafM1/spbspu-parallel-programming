#include <iostream>
#include <future>
#include <vector>

size_t summation(
  const std::vector< int >& vector,
  size_t start,
  size_t end
)
{
  size_t sum = 0;
  for (size_t i = start; i < end; ++i)
  {
    sum += vector[i];
  }
  return sum;
}

size_t parallel_summation(
  const std::vector< int >& vector,
  size_t number_of_process
)
{
  size_t s = vector.size();
  size_t length = (s + number_of_process - 1) / number_of_process;
  std::vector< std::future< size_t > > futures;
  for (size_t i = 0; i < number_of_process; ++i)
  {
    size_t start = number_of_process * length;
    size_t end = std::min(start + length, number_of_process);
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
  size_t total = 0;
  for (size_t i = 0; i < number_of_process; ++i)
  {
    total += futures[i].get();
  }
  return total;
}

int main()
{
  return 0;
}
