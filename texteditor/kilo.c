/***   include  ***/
#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <errno.h>

/***   Define   ***/

#define CTRL_KEY(k) ((k) & 0x1f)

/*** data ***/

struct editorConfig{

	int screenRows;
	int screenCols;

	struct termios orig_termios;
};
struct editorConfig E;



/***  terminal  ***/

void die(const char *s)
{
	write(STDOUT_FILENO,"\x1b[2J",4);
	write(STDOUT_FILENO,"\x1b[H",3);
	perror(s);
	exit(1);
}

void disableRawMode()
{
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &E.orig_termios) == -1)
		die("tcsetattr");
}

void enableRawMode()
{

	if (tcgetattr(STDIN_FILENO, &E.orig_termios) == -1)
		die("tcgetattr"); 
	atexit(disableRawMode);
	struct termios raw = E.orig_termios;
	raw.c_iflag &= ~(IXON | ICRNL | BRKINT | INPCK | ISTRIP);
	raw.c_cflag |= (CS8);
	raw.c_cc[VMIN] = 0;
	raw.c_cc[VTIME] = 1;
	raw.c_lflag &= ~(ICANON | IEXTEN | ISIG);
	raw.c_oflag = ~(OPOST);
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
		die("tcsetattr");
}


char editorReadKey(){
	int nread;
	char c;
	while((nread = read(STDIN_FILENO, &c ,1)) != 1){
		if(nread == -1 && errno != EAGAIN)die("read");
	}
	return c;
}


int getWindowSize(int *rows,int *cols){
	struct winsize ws;

	if(1 || ioctl(STDOUT_FILENO , TIOCGWINSZ , &ws) == -1 || ws.ws_col == 0){
		if(write(STDOUT_FILENO,"\x1b[999C\x1b[999B",12)!=12)return -1;
		editorReadKey();
	}
	else{
		*cols = ws.ws_col;
		*rows = ws.ws_row;
		return 0;
	}
	
}

/*   output   */

void editorDrawRows(){
	int y;
	for(y = 0; y<E.screenRows; y++){
		write(STDOUT_FILENO,"~\r\n",3);
	}
}

void editorRefreshScreen(){
	write(STDOUT_FILENO,"\x1b[2J",4);
	write(STDOUT_FILENO,"\xb1[H",3);
	
	editorDrawRows();

	write(STDOUT_FILENO,"\x1b[H",3);
}


/*  Input   */
void editorProcessKeyPress(){
	char c = editorReadKey();

	switch(c){
		case CTRL_KEY('q'):
			write(STDOUT_FILENO,"\x1b[2J",4);
			write(STDOUT_FILENO,"\x1b[H",3);
			exit(0);
			break;
	}
}

void initEditor(){
	if(getWindowSize(&E.screenRows,&E.screenCols)==-1)die("getWindowSize");
}


/***   init  ***/

int main()
{
	enableRawMode();
	initEditor();

	while(1){
		editorProcessKeyPress();
		editorRefreshScreen();
	}
	return 0;
}
