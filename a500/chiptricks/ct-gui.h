#ifndef __CT_GUI_H__
#define __CT_GUI_H__

#include "common.h"
#include "event.h"
#include "gfx.h"
#include "font.h"

typedef enum { 
  WT_GROUP, WT_LABEL, WT_BUTTON, WT_RADIOBT, WT_LAST
} WidgetTypeT;

typedef enum {
  WA_ENTERED, WA_LEFT, WA_PRESSED, WA_RELEASED, WA_LAST
} WidgetActionT;

typedef enum {
  WS_ACTIVE  = 1,
  WS_PRESSED = 2,
  WS_TOGGLED = 4,
} WidgetStateT;

typedef union Widget WidgetT;

#define WIDGET_BASE             \
  UBYTE type;                   \
  /* widget definition */       \
  Area2D area;                  \
  /* widget internal state */   \
  WidgetStateT state;           \
  /* pointer to parent */       \
  WidgetT *parent;

typedef struct {
  WIDGET_BASE
} WidgetBaseT;

typedef struct {
  WIDGET_BASE
  WidgetT **widgets;
} GroupT;

typedef struct {
  WIDGET_BASE
  char *text;
} LabelT;

typedef struct {
  WIDGET_BASE
  BitmapT **images;
} ButtonT;

#undef WIDGET_BASE

union Widget {
  UBYTE   type;
  GroupT  group;
  LabelT  label;
  ButtonT button;
  WidgetBaseT base;
};

#define BUTTON(x) (&(x)->button)
#define LABEL(x) (&(x)->label)
#define GROUP(x) (&(x)->group)

typedef struct GuiState {
  WidgetT *root;
  WidgetBaseT *lastEntered;
  WidgetBaseT *lastPressed;
  BitmapT *screen;
  FontT *font;
} GuiStateT;

typedef void (*WidgetFuncT)(GuiStateT *, WidgetT *);

#define GUI_BUTTON(name, x, y, w, h)                                    \
  WidgetT name[1] = {(WidgetT)(ButtonT)                                 \
    {WT_BUTTON, {(x), (y), (w), (h)}, 0, NULL}}

#define GUI_RADIOBT(name, x, y, w, h)                                   \
  WidgetT name[1] = {(WidgetT)(ButtonT)                                 \
    {WT_RADIOBT, {(x), (y), (w), (h)}, 0, NULL}}

#define GUI_LABEL(name, x, y, w, h)                                     \
  WidgetT name[1] = {(WidgetT)(LabelT)                                  \
    {WT_LABEL, {(x), (y), (w), (h)}, 0, NULL}}

#define GUI_GROUP(name, ...)                                            \
  WidgetT *name ## _tbl [] = {__VA_ARGS__, NULL};                       \
  WidgetT name[1] = {(WidgetT)(GroupT)                                  \
    {WT_GROUP, {0, 0, 0, 0}, 0, NULL, (WidgetT **)name ## _tbl}}

#define GUI_MAIN(root) \
  GuiStateT gui[1] = {{root}}

#define LabelFmtStr(wg, str, args...) \
  FmtStr(((LabelT *)(wg))->text, ((LabelT *)(wg))->length, (str), args)

void GuiInit(GuiStateT *gui, BitmapT *screen, FontT *font);
void GuiRedraw(GuiStateT *gui);
void GuiHandleMouseEvent(GuiStateT *gui, MouseEventT *ev);
void GuiWidgetRedraw(GuiStateT *gui, WidgetT *wg);

#endif
