# Kilo Editor

Kilo is a simple, terminal-based text editor written in C. It is designed to be lightweight and straightforward, providing essential text editing functionalities.

## Features

- **Basic text editing**: Insert, delete, and navigate through text.
- **Line-based editing**: Works with lines of text, handling tabs and newline characters.
- **Status bar**: Displays filename, line count, and modification status.
- **Scrolling**: Handles vertical and horizontal scrolling.
- **File I/O**: Open and save files.
- **Raw mode**: Efficient handling of user input with minimal overhead.

## Getting Started

### Prerequisites

- A Unix-like operating system (Linux, macOS)
- GCC or Clang compiler

### Building

1. Clone the repository:
    ```bash
    git clone https://github.com/jitu7033/c_project/tree/main/texteditor1
    ```
2. Navigate to the project directory:
    ```bash
    cd texteditor1
    ```
3. Compile the code:
    ```bash
    make
    ./kilo
    ```

### Usage

Run the editor with:
```bash
./kilo [filename]
```
**[filename]:** Optionally specify a file to open.  
**Controls**  
**Ctrl-Q:** Quit the editor. If there are unsaved changes, you'll need to press Ctrl-Q multiple times.  
**Ctrl-S:** Save the current file.  
**Arrow Keys:** Move the cursor around.  
**Ctrl-F:** Placeholder for future find functionality.  
**Home:** Move cursor to the beginning of the line.  
**End:** Move cursor to the end of the line.  
**Page Up:** Scroll up by one page.  
**Page Down:** Scroll down by one page.  
**Backspace / Ctrl-H / Delete:** Delete the character before or after the cursor.  
