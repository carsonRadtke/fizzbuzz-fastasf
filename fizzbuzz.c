#include <unistd.h>

// #define LIMIT 16
#define LIMIT 1'000'000'000

typedef unsigned int uint32;

static const char fizzbuzz_str[] = {'F', 'i', 'z', 'z', 'B',
                                    'u', 'z', 'z', '\n'};
static const char fizz_str[] = {'F', 'i', 'z', 'z', '\n'};
static const char buzz_str[] = {'B', 'u', 'z', 'z', '\n'};

static char buffer[64 * 1024] = {0};
static char *bufferpos = buffer;

inline void flush() {
  write(1, buffer, bufferpos - buffer);
  bufferpos = buffer;
}

inline void cp(const char *str, uint32 len) {
  if (bufferpos + len > buffer + sizeof(buffer)) {
    flush();
  }
  for (uint32 i = 0; i < len; i++)
    *(bufferpos++) = *(str++);
}

inline void fizzbuzz(void) { cp(fizzbuzz_str, sizeof(fizzbuzz_str)); }
inline void fizz(void) { cp(fizz_str, sizeof(fizz_str)); }
inline void buzz(void) { cp(buzz_str, sizeof(buzz_str)); }
inline void number(uint32 num) {
  char numbuf[21];
  char *digptr = &numbuf[sizeof(numbuf) - 1];
  *digptr = '\n';

  uint32 n = num;
  while (n > 0) {
    *(--digptr) = '0' + (n % 10);
    n /= 10;
  }

  cp(digptr, numbuf + sizeof(numbuf) - digptr);
}

void fizzbuzz_impl(uint32 N) {
  uint32 i = 0;
  for (; i + 15 < N; i += 15)
  {
    fizzbuzz();
    number(i + 1);
    number(i + 2);
    fizz();
    number(i + 4);
    buzz();
    fizz();
    number(i + 7);
    number(i + 8);
    fizz();
    buzz();
    number(i + 11);
    fizz();
    number(i + 13);
    number(i + 14);
  }
  for (; i < N; i++) {
    if (i % 15 == 0)
      fizzbuzz();
    else if (i % 3 == 0)
      fizz();
    else if (i % 5 == 0)
      buzz();
    else
      number(i);
  }
  flush();
}

int main() {
  fizzbuzz_impl(LIMIT);
  return 0;
}
