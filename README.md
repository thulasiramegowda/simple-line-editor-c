# Simple Line Editor in C

A command-line based line editor developed in C as part of the Portfolio Building Studio Course coding competition.

The editor allows users to create, view, modify, search, save, and load a text document directly from the terminal.

## Team Members

1. Thulasi Rame Gowda
2. Safa Sayed
3. Sudeeksha

## Features

### Core Features

- Insert a line at any valid position
- Delete a line using its line number
- Display the complete document with line numbers
- Save the document to a text file
- Load a previously saved document

### Bonus Features

- Search for a word or phrase
- Find and replace text
- Replace text on a specific line or throughout the document
- Undo the most recent editing action
- Display line, word, and character statistics

## Data Structure

The editor uses an **array of strings** to store the document in memory.

Each element of the array represents one line of the document.

Example:

```text
lines[0] -> "Hello World"
lines[1] -> "Learning C"
lines[2] -> "Simple Line Editor"
```

An array-based structure was chosen because the editor operates mainly using line numbers. It provides simple indexed access and makes displaying and accessing individual lines straightforward.

## Project Structure

```text
simple-line-editor-c/
|
|-- src/
|   |-- editor.c
|   `-- editor.h
|
|-- README.md
|-- HELP.md
|-- .gitignore
`-- document.txt
```

`document.txt` is generated when the user saves a document.

## Requirements

To compile the project, a C compiler such as GCC is required.

Check GCC installation with:

```bash
gcc --version
```

## Compilation

From the root directory of the project, run:

```bash
gcc src/editor.c -o editor
```

On Windows, this creates:

```text
editor.exe
```

## Running the Program

### Windows PowerShell

```powershell
.\editor.exe
```

### Linux/macOS

```bash
./editor
```

## Editor Menu

```text
========================================
          SIMPLE LINE EDITOR
========================================
  1. Insert Line
  2. Delete Line
  3. Display Document
  4. Save Document
  5. Load Document
  6. Search
  7. Find & Replace
  8. Undo Last Action
  9. Line / Word Count
 10. Exit
========================================
```

## Error Handling

The editor handles common invalid operations such as:

- Invalid menu choices
- Invalid line numbers
- Deleting from an empty document
- Searching an empty document
- Missing files during loading
- Exceeding the maximum number of lines
- Invalid numeric input
- Memory allocation failures

## File Handling

The editor stores saved documents in:

```text
document.txt
```

The saved document can later be loaded back into memory.

## Undo

Before a modifying operation, the editor stores a copy of the current document state.

The Undo command restores the most recently saved state.

## Documentation

Detailed instructions for every command are available in:

```text
HELP.md
```

## Technologies Used

- C
- GCC
- Git
- GitHub
- Visual Studio Code