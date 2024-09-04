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

struct abuf
{
  char *b;
  int len;
};
#define ABUF_INIT {NULL, 0}
struct abuf ab = ABUF_INIT;

struct editorConfig E;
void editorScroll();
void editorDrawRows(struct abuf *ab);
void editorDrawStatusBar(struct abuf *ab);
void editorDrawMessageBar(struct abuf *ab);
void editorRefreshScreen();
void editorSetStatusMessage(const char *fmt, ...);






