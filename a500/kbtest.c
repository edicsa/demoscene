#include <proto/graphics.h>

#include "startup.h"
#include "console.h"
#include "hardware.h"
#include "coplist.h"
#include "keyboard.h"

#define WIDTH 640
#define HEIGHT 256
#define DEPTH 1

static BitmapT *screen;
static CopListT *cp;
static TextFontT *topaz8;
static ConsoleT console;

static void Init() {
  screen = NewBitmap(WIDTH, HEIGHT, DEPTH);
  cp = NewCopList(100);

  CopInit(cp);
  CopSetupGfxSimple(cp, MODE_HIRES, DEPTH, X(0), Y(0), WIDTH, HEIGHT);
  CopSetupBitplanes(cp, NULL, screen, DEPTH);
  CopSetRGB(cp, 0, 0x000);
  CopSetRGB(cp, 1, 0xfff);
  CopEnd(cp);

  CopListActivate(cp);
  custom->dmacon = DMAF_SETCLR | DMAF_RASTER;

  {
    struct TextAttr textattr = { "topaz.font", 8, FS_NORMAL, FPF_ROMFONT };
    topaz8 = OpenFont(&textattr);
  }

  ConsoleInit(&console, screen, topaz8);
  ConsolePutStr(&console, "Press ESC key to exit!\n");
  ConsoleDrawCursor(&console);

  KeyboardInit();
}

static void Kill() {
  custom->dmacon = DMAF_COPPER | DMAF_RASTER;

  KeyboardKill();

  CloseFont(topaz8);
  DeleteCopList(cp);
  DeleteBitmap(screen);
}

static BOOL HandleEvent() {
  KeyEventT event;

  if (!GetKeyEvent(&event))
    return TRUE;

  if (event.modifier & MOD_PRESSED)
    return TRUE;

  if (event.code == KEY_ESCAPE)
    return FALSE;

  ConsoleDrawCursor(&console);

  if (event.code == KEY_LEFT) {
    if (console.cursor.x > 0)
      console.cursor.x--;
  }

  if (event.code == KEY_RIGHT) {
    console.cursor.x++;
    if (console.cursor.x >= console.width)
      console.cursor.x = console.width;
  }

  if (event.code == KEY_UP) {
    if (console.cursor.y > 0)
      console.cursor.y--;
  }

  if (event.code == KEY_DOWN) {
    console.cursor.y++;
    if (console.cursor.y >= console.height)
      console.cursor.y = console.height;
  }

  if (event.ascii)
    ConsolePutChar(&console, event.ascii);

  ConsoleDrawCursor(&console);

  return TRUE;
}

EffectT Effect = { NULL, NULL, Init, Kill, NULL, HandleEvent };
