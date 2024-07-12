#include "bindings/greeter.h"

//#include <iostream>
#include <cstring>
#include <vector>
#include <cstdlib>

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

void greeter_greet_cc_vector(greeter_string_t *who, greeter_string_t *ret) {
  const std::string greeting = "hello ";

  std::vector<uint8_t> buf; // ((const uint8_t*) greeting, (const uint8_t*) (greeting + strlen(greeting)));
  buf.reserve(greeting.size() + who->len);

  for(size_t i=0;i<greeting.size();++i) {
    uint8_t v = greeting.data()[i]; 
    buf.push_back(v);
  } 

  for(size_t i=0;i<who->len;++i) {
    uint8_t v = who->ptr[i]; 
    buf.push_back(v);
  } 

  buf.push_back(0);

  uint8_t *out = (uint8_t*) calloc(buf.size(), 1);
  memcpy(out, buf.data(), buf.size());

  ret->ptr = out;
  ret->len = buf.size() + 1;
}
