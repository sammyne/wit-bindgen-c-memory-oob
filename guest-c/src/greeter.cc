#include "bindings/greeter.h"

#include <iostream>
#include <cstring>

void greeter_greet_cc(greeter_string_t *who, greeter_string_t *ret) {
  std::string buf("hello ");
  std::string w((const char*) who->ptr, who->len);
  buf += w;

  // FIXME(sammyne): 尚未清楚这里为啥不能使用。
  //std::cout << buf << std::endl;

  uint8_t *out = (uint8_t*) calloc(buf.size(), 1);
  memcpy(out, buf.data(), buf.size());

  ret->ptr = out;
  ret->len = buf.size() + 1;
}
