#include <stdio.h>

class Test {
public:
  Test()  { printf("%s,%d: Hello, Project-N!\n", __func__, __LINE__); }
  ~Test() { printf("%s,%d: Goodbye, Project-N!\n", __func__, __LINE__); }
};

Test test;

int main() {
  printf("%s,%d: Hello world!\n", __func__, __LINE__);
  while (1);
  return 0;
}
