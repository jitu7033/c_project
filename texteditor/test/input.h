#define CTRL_KEY(k) ((k) & 0x1f)
char *editorPrompt(char *prompt);
void editorMoveCursor(int key);
void editorProcessKeypress();
void initEditor();


