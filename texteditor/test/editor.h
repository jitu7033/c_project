#include<termios.h>

struct abuf
{
  char *b;
  int len;
};

void editorInsertChar(int c);
void editorInsertNewline();
void editorDelChar();
char *editorRowsToString(int *buflen);
void editorOpen(char *filename);
void editorSave();
void editorScroll();
void editorDrawRows(struct abuf *ab);
void editorDrawStatusBar(struct abuf *ab);
void editorDrawMessageBar(struct abuf *ab);
void editorRefreshScreen();
void editorSetStatusMessage(const char *fmt, ...);










