# Simple Line Editor — Help Guide

This document explains how to use each command available in the Simple Line Editor.

## 1. Insert Line

Adds a new line of text at a specified position.

### Example

```text
Enter your choice: 1
Enter line number to insert (1-1): 1
Enter text: Hello World
```

Output:

```text
Line inserted successfully.
```

If a line is inserted between existing lines, the following lines are shifted downward.

---

## 2. Delete Line

Deletes an existing line using its line number.

### Example

Suppose the document contains:

```text
1 | Hello World
2 | Learning C
3 | Line Editor
```

Input:

```text
Enter your choice: 2
Enter line number to delete (1-3): 2
```

The resulting document becomes:

```text
1 | Hello World
2 | Line Editor
```

---

## 3. Display Document

Displays all current lines together with their line numbers.

### Example

```text
Enter your choice: 3
```

Output:

```text
========================================
             DOCUMENT
========================================
   1 | Hello World
   2 | Learning C
   3 | Simple Line Editor
========================================
```

If no lines exist, the editor displays:

```text
Document is empty.
```

---

## 4. Save Document

Writes the current in-memory document to:

```text
document.txt
```

### Example

```text
Enter your choice: 4
```

Output:

```text
Document saved successfully to document.txt
```

The file can later be loaded using the Load command.

---

## 5. Load Document

Loads the contents of `document.txt` into the editor.

### Example

```text
Enter your choice: 5
```

Output:

```text
Document loaded successfully from document.txt
```

If the file does not exist, an error message is displayed.

---

## 6. Search

Searches the complete document for a word or phrase.

### Example

Document:

```text
1 | C programming is powerful
2 | Learning data structures
3 | Programming is fun
```

Input:

```text
Enter your choice: 6
Enter word or phrase to search: programming
```

Possible output:

```text
Search results:
Line 1: C programming is powerful
```

Search matching is case-sensitive.

---

## 7. Find & Replace

Finds text and replaces it with new text.

Two modes are available:

1. Replace on a specific line
2. Replace throughout the document

### Example

Original document:

```text
1 | I like C
2 | C is powerful
```

Input:

```text
Enter your choice: 7
Enter text to find: C
Enter replacement text: C programming
Enter choice: 2
```

Result:

```text
1 | I like C programming
2 | C programming is powerful
```

---

## 8. Undo Last Action

Restores the document state saved before the most recent modifying operation.

### Example

Before deletion:

```text
1 | Hello
2 | World
```

After deleting line 2:

```text
1 | Hello
```

Selecting:

```text
Enter your choice: 8
```

restores:

```text
1 | Hello
2 | World
```

Only the most recently stored editing state can be undone.

---

## 9. Line / Word Count

Displays basic document statistics.

### Example

```text
Enter your choice: 9
```

Output:

```text
========================================
          DOCUMENT STATISTICS
========================================
Lines      : 3
Words      : 10
Characters : 52
========================================
```

The character count represents characters stored in the document lines and does not include newline separators.

---

## 10. Exit

Closes the Simple Line Editor and releases allocated memory.

### Example

```text
Enter your choice: 10
```

Output:

```text
Thank you for using Simple Line Editor!
Goodbye!
```

Save the document before exiting if you want the latest changes written to `document.txt`.

---

# Error Messages

## Invalid Line Number

```text
Error: Invalid line number.
```

Enter a line number within the displayed valid range.

## Empty Document

```text
Error: Document is empty.
```

Add a line before attempting operations such as deletion.

## Invalid Menu Choice

```text
Error: Invalid choice. Please select 1-10.
```

Enter a number between 1 and 10.

## File Not Found

```text
Error: document.txt not found.
```

Save a document first or ensure `document.txt` exists in the project directory.

## No Undo Available

```text
No action available to undo.
```

Perform a modifying operation before using Undo.

---

# Quick Command Reference

| Option | Command | Purpose |
|---:|---|---|
| 1 | Insert Line | Add a new line |
| 2 | Delete Line | Remove a line |
| 3 | Display Document | View all lines |
| 4 | Save Document | Save to `document.txt` |
| 5 | Load Document | Load `document.txt` |
| 6 | Search | Find text |
| 7 | Find & Replace | Replace text |
| 8 | Undo | Reverse the last stored editing state |
| 9 | Statistics | Show line, word and character counts |
| 10 | Exit | Close the editor |