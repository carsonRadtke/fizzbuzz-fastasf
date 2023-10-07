#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define LIMIT 1'000'000'000
#define BUFFER_SIZE 64 * 1024
#define STDOUT_FD 1
#define U32_MAX_STRLEN 11

typedef unsigned int uint32;

static const char fizzbuzz_str[] = {'F', 'i', 'z', 'z','B',
                                    'u', 'z', 'z', '\n'};
static const char fizz_str[] = {'F', 'i', 'z', 'z', '\n'};
static const char buzz_str[] = {'B', 'u', 'z', 'z', '\n'};

static char buffer[BUFFER_SIZE];
static char *bufferpos = buffer;

inline void flush() {
  write(STDOUT_FD, buffer, bufferpos - buffer);
  bufferpos = buffer;
}

inline void prnt(const char *str, uint32 len) {
  if (bufferpos + len > buffer + sizeof(buffer)) {
    flush();
  }
  memcpy(bufferpos, str, len);
  bufferpos += len;
}

inline void fizzbuzz(void) { prnt(fizzbuzz_str, sizeof(fizzbuzz_str)); }
inline void fizz(void) { prnt(fizz_str, sizeof(fizz_str)); }
inline void buzz(void) { prnt(buzz_str, sizeof(buzz_str)); }
inline void number(uint32 num) {
  char numbuf[U32_MAX_STRLEN];
  char *numbuf_end = numbuf + sizeof(numbuf);
  char *numbuf_start = numbuf_end;
  
  uint32 n = num;
  *(--numbuf_start) = '\n';
  do
  {
    *(--numbuf_start) = '0' + (n % 10);
    n /= 10;
  } while (n > 0);

  prnt(numbuf_start, numbuf_end - numbuf_start);
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
