#include <stdio.h>

typedef unsigned int i32;

inline void fizzbuzz(void) { printf("%s\n", "FizzBuzz"); }
inline void fizz(void) { printf("%s\n", "Fizz"); }
inline void buzz(void) { printf("%s\n", "Buzz"); }
inline void number(i32 num) { printf("%d\n", num); }

void fizzbuzz_impl(i32 N) {
  i32 i = 0;
  for (; i < N; i++)
  {
    if (i % 15 == 0) fizzbuzz();
    else if (i % 3 == 0) fizz();
    else if (i % 5 == 0) buzz();
    else number(i);
  }
}

int main() {
  fizzbuzz_impl(1'000'000'000);
  return 0;
}
