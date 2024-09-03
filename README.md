KILO TEXT EDITOR


Kilo is a simple text editor written in C, following the tutorial "Build Your Own Text Editor" by Snaptoken. It's designed to be minimal and lightweight, featuring basic functionalities like editing, saving, and navigating through text files.

Features
Basic Text Editing: Insert, delete, and navigate text with ease.
File Operations: Open and save files.
Syntax Highlighting: (Upcoming feature) Syntax highlighting support for various programming languages.
Cross-Platform: Works on Unix-based systems.
Installation
To build Kilo, you need a C compiler like gcc. Follow the steps below to compile and run Kilo:

Clone the Repository:

bash
Copy code
git clone https://github.com/jitu7033/c_project/texteditor1/kilo.git
cd kilo
Compile the Code:

bash
Copy code
gcc -o kilo kilo.c -Wall -Wextra -pedantic -std=c99
Run the Editor:

bash
Copy code
./kilo
Usage
After launching Kilo, you can perform various text editing tasks:

Move Cursor: Use arrow keys to move the cursor.
Insert Text: Start typing to insert text at the cursor position.
Delete Text: Use Backspace to delete the character before the cursor.
Save File: Press Ctrl-S to save the current file.
Quit Editor: Press Ctrl-Q to quit Kilo. You will be prompted to save any unsaved changes.
Key Bindings
Key Combination	Action
Ctrl-Q	Quit the editor
Ctrl-S	Save the current file
Ctrl-F	Find text in the file
Arrow Keys	Move the cursor
Page Up/Down	Scroll up/down by a page
Home/End	Move to the start/end of a line
Ctrl-H	Backspace
Ctrl-L	Refresh the screen
Limitations
Kilo does not support advanced features like multi-line editing, regular expressions, or plugin support.
Syntax highlighting is currently in development.
Contributing
Contributions to Kilo are welcome. Feel free to fork the repository and submit pull requests.

Acknowledgments
This project is heavily inspired by the tutorial "Build Your Own Text Editor" by Snaptoken. The purpose of Kilo is to serve as a learning exercise in understanding how text editors work at a fundamental level.
