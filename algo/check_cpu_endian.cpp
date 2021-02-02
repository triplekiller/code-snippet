#include <iostream>

int checkCPUEndian() {
  union {
    unsigned int a;
    unsigned char b;
  } un;

  un.a = 1;

  return (un.b == 1);
}

int main(int argc, char **argv) {
  if (checkCPUEndian) {
    std::cout << "little endian\n";
  } else {
    std::cout << "big endian\n";
  }

  return 0;
}
