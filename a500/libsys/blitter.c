#include "blitter.h"

UWORD FirstWordMask[16] = {
  0xFFFF, 0x7FFF, 0x3FFF, 0x1FFF, 0x0FFF, 0x07FF, 0x03FF, 0x01FF,
  0x00FF, 0x007F, 0x003F, 0x001F, 0x000F, 0x0007, 0x0003, 0x0001
};

UWORD LastWordMask[16] = {
  0xFFFF, 0x8000, 0xC000, 0xE000, 0xF000, 0xF800, 0xFC00, 0xFE00,
  0xFF00, 0xFF80, 0xFFC0, 0xFFE0, 0xFFF0, 0xFFF8, 0xFFFC, 0xFFFE
};

#define L_OR     ((ABC | ABNC | NABC | NANBC) | (SRCA | SRCC | DEST))
#define L_EOR    ((ABNC | NABC | NANBC) | (SRCA | SRCC | DEST))
#define L_SOLID  (LINEMODE)
#define L_ONEDOT (LINEMODE | ONEDOT)

UWORD LineMode[4][2] = {
  {  L_OR, L_SOLID },
  { L_EOR, L_SOLID }, 
  {  L_OR, L_ONEDOT },
  { L_EOR, L_ONEDOT }
};
