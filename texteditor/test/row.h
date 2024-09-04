#define KILO_VERSION "0.0.1"
#define KILO_TAB_STOP 8
#define KILO_QUIT_TIMES 3
#include <stdio.h>
#include <time.h>
#include <termios.h>

typedef struct erow
{ // erow stand for editor row
  int idx;
  int size;
  int rsize;
  char *chars;
  char *render;
  unsigned char *hl;
  int hl_open_comment;
} erow;


struct editorConfig
{
  // cursor movment
  int cx;     // the column
  int cy;     // the row
  int rx;     // index into the render field
  int rowoff; // this is used for scrolling but it is vertically
  int coloff; // this is used for scrolling but it is horizontally
  int screenrows;
  int screencols;
  int numrows;
  erow *row;
  int dirty; // if file are changed btw opening and closing
  char *filename;
  char statusmsg[80];
  time_t statusmsg_time;

  struct termios orig_termios;
};

extern struct editorConfig E;


int editorRowCxToRx(erow *row, int cx);
int editorRowRxToCx(erow *row, int rx);
void editorUpdateRow(erow *row);
void editorInsertRow(int at, char *s, size_t len);
void editorFreeRow(erow *row);
void editorDelRow(int at);
void editorRowInsertChar(erow *row, int at, int c);
void editorRowAppendString(erow *row, char *s, size_t len);
void editorRowDelChar(erow *row, int at);