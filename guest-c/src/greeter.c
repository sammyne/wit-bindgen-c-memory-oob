#include "bindings/greeter.h"

#include <stdio.h>

void greeter_greet(greeter_string_t *who, greeter_string_t *ret) {
  greeter_string_set(ret, "hello world :)");
}
