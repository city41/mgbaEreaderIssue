#include "clib/erapi.h"

extern int __end[];

int main() {
  // not convinced this is actually needed, but the c examples and e-snake do it
  ERAPI_InitMemory((ERAPI_RAM_END - (u32)__end) >> 10);
  ERAPI_SetBackgroundMode(0);
  ERAPI_LoadBackgroundSystem(3, 12);
  ERAPI_FadeIn(1);

  for (;;) {
    ERAPI_RenderFrame(1);
  }
}
