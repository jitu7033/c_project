
#include "editor.h"
#include "terminal.h"
#include "output.h"
#include "stdarg.h"
#include <fcntl.h>

#define ABUF_INIT {NULL, 0}
struct abuf ab = ABUF_INIT;

void editorInsertChar(int c)
{
  if (E.cy == E.numrows)
  {
    editorInsertRow(E.numrows, "", 0);
  }
  editorRowInsertChar(&E.row[E.cy], E.cx, c);
  E.cx++;
}

void editorInsertNewline()
{
  if (E.cx == 0)
  {
    editorInsertRow(E.cy, "", 0);
  }
  else
  {
    erow *row = &E.row[E.cy];
    editorInsertRow(E.cy + 1, &row->chars[E.cx], row->size - E.cx);
    row = &E.row[E.cy];
    row->size = E.cx;
    row->chars[row->size] = '\0';
    editorUpdateRow(row);
  }
  E.cy++;
  E.cx = 0;
}

void editorDelChar()
{
  if (E.cy == E.numrows)
    return;
  if (E.cx == 0 && E.cy == 0)
    return;

  erow *row = &E.row[E.cy];
  if (E.cx > 0)
  {
    editorRowDelChar(row, E.cx - 1);
    E.cx--;
  }
  else
  {
    E.cx = E.row[E.cy - 1].size;
    editorRowAppendString(&E.row[E.cy - 1], row->chars, row->size);
    editorDelRow(E.cy);
    E.cy--;
  }
}

/*****  file i/o  ****/

char *editorRowsToString(int *buflen)
{
  int totlen = 0;
  int j;
  for (j = 0; j < E.numrows; j++)
    totlen += E.row[j].size + 1;
  *buflen = totlen;

  char *buf = malloc(totlen);
  char *p = buf;
  for (j = 0; j < E.numrows; j++)
  {
    memcpy(p, E.row[j].chars, E.row[j].size);
    p += E.row[j].size;
    *p = '\n';
    p++;
  }

  return buf;
}

void editorOpen(char *filename)
{
  // char *line = "Hello World";
  // ssize_t linelen = 13;
  free(E.filename);

  // it make the copy of the gien string allocating the required memory and assuming you will free
  E.filename = strdup(filename);

  // lets allow to the user open actual file
  FILE *fp = fopen(filename, "r");
  if (!fp)
    die("fopen");

  char *line = NULL;  // recently empty
  size_t linecap = 0; // we dont no line capacity
  ssize_t linelen;
  while ((linelen = getline(&line, &linecap, fp)) != -1)
  { // when read whole file then give me -1 then return the file
    while (linelen > 0 && (line[linelen - 1] == '\n' || line[linelen - 1] == '\r'))
      linelen--;
    editorInsertRow(E.numrows, line, linelen);
  }
  free(line); // free the all memory we take in every row
  fclose(fp); // close the file
  E.dirty = 0;
}

void editorSave()
{
  if (E.filename == NULL){
    E.filename = editorPrompt("Save as : %s (ESC to cancel)");
    if(E.filename ==  NULL){
      editorSetStatusMessage("save aborted");
      return ;
    }
  }
  int len;
  char *buf = editorRowsToString(&len);

  int fd = open(E.filename, O_RDWR | O_CREAT, 0644);

  if (fd != -1)
  {
    if (ftruncate(fd, len) != -1)
    {
      if (write(fd, buf, len) == len)
      {
        close(fd);
        free(buf);
        E.dirty = 0;
        editorSetStatusMessage("%d byte written to desk ", len);
        return;
      }
    }
    close(fd);
  }
  editorSetStatusMessage("can't save ! I/O error %s", strerror(errno));
  free(buf);
}


void editorScroll()
{
  E.rx = 0;
  if (E.cy < E.numrows)
  {
    E.rx = editorRowCxToRx(&E.row[E.cy], E.cx);
  }
  if (E.cy < E.rowoff)
  {
    E.rowoff = E.cy;
  }
  if (E.cy >= E.rowoff + E.screenrows)
  {
    E.rowoff = E.cy - E.screenrows + 1;
  }
  if (E.rx < E.coloff)
  {
    E.coloff = E.rx;
  }
  if (E.rx >= E.coloff + E.screencols)
  {
    E.coloff = E.rx - E.screencols + 1;
  }
}

void editorDrawRows(struct abuf *ab)
{
  int y;
  for (y = 0; y < E.screenrows; y++)
  {
    int filerow = y + E.rowoff;
    if (filerow >= E.numrows)
    {
      if (E.numrows == 0 && y == E.screenrows / 3)
      {
        char welcome[80];
        int welcomelen = snprintf(welcome, sizeof(welcome),
                                  "Kilo editor -- version %s", KILO_VERSION);
        if (welcomelen > E.screencols)
          welcomelen = E.screencols;
        int padding = (E.screencols - welcomelen) / 2;
        if (padding)
        {
          abAppend(ab, "~", 1);
          padding--;
        }
        while (padding--)
          abAppend(ab, " ", 1);
        abAppend(ab, welcome, welcomelen);
      }
      else
      {
        abAppend(ab, "~", 1);
      }
    }
    else
    {
      int len = E.row[filerow].rsize - E.coloff;
      if (len < 0)
        len = 0;
      if (len > E.screencols)
        len = E.screencols;
      abAppend(ab, &E.row[filerow].render[E.coloff], len);
    }
    abAppend(ab, "\x1b[K", 3);
    // if (y < E.screenrows - 1) {
    abAppend(ab, "\r\n", 2);
    // }
  }
}

// to make the status bar

void editorDrawStatusBar(struct abuf *ab)
{
  abAppend(ab, "\x1b[7m", 4);
  char status[80], rstatus[80];
  int len = snprintf(status, sizeof(status), "%.20s - %d lines %s",
                     E.filename ? E.filename : "[No Name]", E.numrows,
                     E.dirty ? "(modified)" : "");
  int rlen = snprintf(rstatus, sizeof(rstatus), "%d/%d",
                      E.cy + 1, E.numrows);
  if (len > E.screencols)
    len = E.screencols;
  abAppend(ab, status, len);
  while (len < E.screencols)
  {
    if (E.screencols - len == rlen)
    {
      abAppend(ab, rstatus, rlen);
      break;
    }
    else
    {
      abAppend(ab, " ", 1);
      len++;
    }
  }
  abAppend(ab, "\x1b[m", 3);
  abAppend(ab, "\r\n", 2);
}

void editorDrawMessageBar(struct abuf *ab)
{

  abAppend(ab, "\x1b[K", 3);
  int msglen = strlen(E.statusmsg);
  if (msglen > E.screencols)
    msglen = E.screencols;
  if (msglen && time(NULL) - E.statusmsg_time < 5)
  {
    abAppend(ab, E.statusmsg, msglen);
  }
}

void editorRefreshScreen()
{
  editorScroll();

  struct abuf ab = ABUF_INIT;

  abAppend(&ab, "\x1b[?25l", 6);
  abAppend(&ab, "\x1b[H", 3);

  editorDrawRows(&ab);
  editorDrawStatusBar(&ab);
  editorDrawMessageBar(&ab);

  char buf[32];
  snprintf(buf, sizeof(buf), "\x1b[%d;%dH", (E.cy - E.rowoff) + 1,
           (E.rx - E.coloff) + 1);
  abAppend(&ab, buf, strlen(buf));

  abAppend(&ab, "\x1b[?25h", 6);

  write(STDOUT_FILENO, ab.b, ab.len);
  abFree(&ab);
}

void editorSetStatusMessage(const char *fmt, ...)
{
  va_list ap;
  va_start(ap, fmt);
  vsnprintf(E.statusmsg, sizeof(E.statusmsg), fmt, ap);
  va_end(ap);
  E.statusmsg_time = time(NULL);
}

