#ifndef EDITOR_H
#define EDITOR_H

/* =========================================
   Simple Line Editor
   Header File
   ========================================= */

#define MAX_LINES 1000
#define MAX_LINE_LENGTH 500
#define FILE_NAME "document.txt"

/* Document storage */
extern char *lines[MAX_LINES];
extern int line_count;

/* Undo storage */
extern char *undo_lines[MAX_LINES];
extern int undo_count;
extern int undo_available;

/* Helper functions */
char *duplicate_string(const char *source);
void clear_input_buffer(void);
void read_text(char *buffer, int size);
int read_integer(void);
void free_document(void);
void free_undo(void);

/* Undo operations */
int save_undo_state(void);
void undo_action(void);

/* Core editor operations */
void insert_line(void);
void delete_line(void);
void display_document(void);

/* File operations */
void save_file(void);
void load_file(void);

/* Search operations */
void search_text(void);
char *replace_text(
    const char *source,
    const char *find,
    const char *replace
);
void find_replace(void);

/* Statistics */
void document_statistics(void);

/* User interface */
void display_menu(void);

#endif