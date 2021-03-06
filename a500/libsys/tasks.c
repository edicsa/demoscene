#include <exec/execbase.h>
#include <exec/tasks.h>
#include <proto/exec.h>

#include "common.h"
#include "tasks.h"

static void DumpTaskList(struct List *list) {
  struct Node *node = list->lh_Head;

  for (;;) {
    Log("> %lx (%ld) '%s'\n", (LONG)node, (LONG)node->ln_Pri, node->ln_Name);
    if (node == list->lh_TailPred)
      break;
    node = node->ln_Succ;
  }
}

void DumpTasks() {
  struct List *list;
  struct Node *node = (struct Node *)FindTask(NULL);

  Log("Task running:\n");
  Log("> %lx (%ld) '%s'\n", (LONG)node, (LONG)node->ln_Pri, node->ln_Name);
 
  list = &SysBase->TaskReady;
  if (!IsListEmpty(list)) {
    Log("Ready tasks:\n");
    DumpTaskList(list);
  }

  list = &SysBase->TaskWait;
  if (!IsListEmpty(list)) {
    Log("Waiting tasks:\n");
    DumpTaskList(list);
  }
}
