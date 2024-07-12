#include "bindings/greeter.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void greeter_greet(greeter_string_t *who, greeter_string_t *ret) {
  const char *greeting = "hello ";
  const size_t N = strlen(greeting);
  const size_t M = N + who->len;

  uint8_t *out = calloc(M+1, sizeof(uint8_t));

  memcpy(out, greeting, N);
  memcpy(out + N, who->ptr, who->len);

  printf("%s\n", out);
  printf("len(out)=%zu\n", M);

  ret->ptr = out;
  ret->len = M;
}

void greeter_say_hi(greeter_string_t *ret) {
  greeter_string_set(ret, "hi :)");
  printf("hello world\n");
}
