
/***   include  ***/
#define _DEFAULT_SOURCE
#define _BSD_SOURCE
#define _GNU_SOURCE

#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdarg.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include "terminal.h"
#include "output.h"
#include "input.h"
#include "editor.h"

//*** defines ***/

#define KILO_VERSION "0.0.1"
#define KILO_TAB_STOP 8
#define KILO_QUIT_TIMES 3



/*** data ***/

/*   prototype  */
void editorSetStatusMessage(const char *fmt, ...);
void editorRefreshScreen();
char *editorPrompt(char *prompt);
/***  terminal 
 *  ***/

/*  row Operation */

/**  editor Operation    **/

/* Append Buffer */

void abAppend(struct abuf *ab, const char *s, int len)
{
  char *new = realloc(ab->b, ab->len + len);

  if (new == NULL)
    return;
  memcpy(&new[ab->len], s, len);
  ab->b = new;
  ab->len += len;
}

void abFree(struct abuf *ab)
{
  free(ab->b);
}

/*   output   */

/*  Input   */

/***   init  ***/

int main(int argc, char *argv[])
{
  enableRawMode();
  initEditor();

  if (argc >= 2)
  {
    editorOpen(argv[1]);
  }

  editorSetStatusMessage("Help : ctrl-s =  save  | ctrl-Q = quit");

  while (1)
  {
    editorRefreshScreen();
    editorProcessKeypress();
  }
  return 0;
}
