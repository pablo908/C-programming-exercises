#include <cstdio>

  int main() {
    // 42 = green bg
    printf("%c[%dmHELLO!\n", 0x1B, 42);
  }

