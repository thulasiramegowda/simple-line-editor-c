#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 1000
#define MAX_LINE_LENGTH 500
#define FILE_NAME "document.txt"

/* =========================
   Document Storage
   ========================= */

char *lines[MAX_LINES];
int line_count = 0;

/* =========================
   Undo Storage
   ========================= */

char *undo_lines[MAX_LINES];
int undo_count = 0;
int undo_available = 0;

/* =========================
   Helper Functions
   ========================= */

/* Create a duplicate of a string */
char *duplicate_string(const char *source)
{
    char *copy = malloc(strlen(source) + 1);

    if (copy == NULL)
    {
        return NULL;
    }

    strcpy(copy, source);
    return copy;
}

/* Clear remaining characters from input buffer */
void clear_input_buffer()
{
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF)
    {
        /* discard */
    }
}

/* Read a complete line of text */
void read_text(char *buffer, int size)
{
    if (fgets(buffer, size, stdin) == NULL)
    {
        buffer[0] = '\0';
        return;
    }

    if (strchr(buffer, '\n') == NULL)
    {
        clear_input_buffer();
    }

    buffer[strcspn(buffer, "\n")] = '\0';
}

/* Read an integer safely */
int read_integer()
{
    char input[50];
    char *end;
    long value;

    while (1)
    {
        read_text(input, sizeof(input));

        value = strtol(input, &end, 10);

        if (end != input && *end == '\0')
        {
            return (int)value;
        }

        printf("Invalid input. Please enter a number: ");
    }
}

/* Free the current document */
void free_document()
{
    int i;

    for (i = 0; i < line_count; i++)
    {
        free(lines[i]);
        lines[i] = NULL;
    }

    line_count = 0;
}

/* Free undo history */
void free_undo()
{
    int i;

    for (i = 0; i < undo_count; i++)
    {
        free(undo_lines[i]);
        undo_lines[i] = NULL;
    }

    undo_count = 0;
    undo_available = 0;
}

/* =========================
   Undo Functions
   ========================= */

/* Save current document before modification */
int save_undo_state()
{
    int i;

    free_undo();

    for (i = 0; i < line_count; i++)
    {
        undo_lines[i] = duplicate_string(lines[i]);

        if (undo_lines[i] == NULL)
        {
            int j;

            for (j = 0; j < i; j++)
            {
                free(undo_lines[j]);
                undo_lines[j] = NULL;
            }

            undo_count = 0;
            undo_available = 0;

            return 0;
        }
    }

    undo_count = line_count;
    undo_available = 1;

    return 1;
}

/* Restore previous document */
void undo_action()
{
    int i;

    if (!undo_available)
    {
        printf("\nNo action available to undo.\n");
        return;
    }

    free_document();

    for (i = 0; i < undo_count; i++)
    {
        lines[i] = duplicate_string(undo_lines[i]);

        if (lines[i] == NULL)
        {
            printf("\nError: Unable to restore previous document.\n");
            free_document();
            free_undo();
            return;
        }
    }

    line_count = undo_count;

    free_undo();

    printf("\nLast action undone successfully.\n");
}

/* =========================
   Insert Line
   ========================= */

void insert_line()
{
    int position;
    int i;
    char text[MAX_LINE_LENGTH];

    if (line_count >= MAX_LINES)
    {
        printf("\nError: Maximum number of lines reached.\n");
        return;
    }

    printf("\nEnter line number to insert (1-%d): ", line_count + 1);
    position = read_integer();

    if (position < 1 || position > line_count + 1)
    {
        printf("Error: Invalid line number.\n");
        return;
    }

    printf("Enter text: ");
    read_text(text, sizeof(text));

    if (strlen(text) == 0)
    {
        printf("Error: Empty lines are not allowed.\n");
        return;
    }

    /*
       Allocate the new line before changing
       the existing document.
    */
    char *new_line = duplicate_string(text);

    if (new_line == NULL)
    {
        printf("Error: Memory allocation failed.\n");
        return;
    }

    if (!save_undo_state())
    {
        free(new_line);
        printf("Error: Unable to create undo state.\n");
        return;
    }

    /*
       Move existing lines downward.
       Example:

       1: Hello
       2: World

       Insert at 2

       World moves to 3.
    */
    for (i = line_count; i >= position; i--)
    {
        lines[i] = lines[i - 1];
    }

    lines[position - 1] = new_line;
    line_count++;

    printf("\nLine inserted successfully.\n");
}

/* =========================
   Delete Line
   ========================= */

void delete_line()
{
    int position;
    int i;

    if (line_count == 0)
    {
        printf("\nError: Document is empty.\n");
        return;
    }

    printf("\nEnter line number to delete (1-%d): ", line_count);
    position = read_integer();

    if (position < 1 || position > line_count)
    {
        printf("Error: Invalid line number.\n");
        return;
    }

    if (!save_undo_state())
    {
        printf("Error: Unable to create undo state.\n");
        return;
    }

    free(lines[position - 1]);

    /*
       Move lines upward.
    */
    for (i = position - 1; i < line_count - 1; i++)
    {
        lines[i] = lines[i + 1];
    }

    lines[line_count - 1] = NULL;
    line_count--;

    printf("\nLine deleted successfully.\n");
}

/* =========================
   Display Document
   ========================= */

void display_document()
{
    int i;

    printf("\n========================================\n");
    printf("             DOCUMENT\n");
    printf("========================================\n");

    if (line_count == 0)
    {
        printf("Document is empty.\n");
    }
    else
    {
        for (i = 0; i < line_count; i++)
        {
            printf("%4d | %s\n", i + 1, lines[i]);
        }
    }

    printf("========================================\n");
}

/* =========================
   Save File
   ========================= */

void save_file()
{
    FILE *file;
    int i;

    file = fopen(FILE_NAME, "w");

    if (file == NULL)
    {
        printf("\nError: Unable to open %s for writing.\n", FILE_NAME);
        return;
    }

    for (i = 0; i < line_count; i++)
    {
        fprintf(file, "%s\n", lines[i]);
    }

    fclose(file);

    printf("\nDocument saved successfully to %s\n", FILE_NAME);
}

/* =========================
   Load File
   ========================= */

void load_file()
{
    FILE *file;
    char buffer[MAX_LINE_LENGTH];
    char *new_line;

    file = fopen(FILE_NAME, "r");

    if (file == NULL)
    {
        printf("\nError: %s not found.\n", FILE_NAME);
        return;
    }

    if (!save_undo_state())
    {
        fclose(file);
        printf("Error: Unable to create undo state.\n");
        return;
    }

    free_document();

    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        if (line_count >= MAX_LINES)
        {
            printf("Warning: Maximum line limit reached.\n");
            break;
        }

        buffer[strcspn(buffer, "\n")] = '\0';

        new_line = duplicate_string(buffer);

        if (new_line == NULL)
        {
            printf("Error: Memory allocation failed while loading.\n");
            fclose(file);
            return;
        }

        lines[line_count] = new_line;
        line_count++;
    }

    fclose(file);

    printf("\nDocument loaded successfully from %s\n", FILE_NAME);
}

/* =========================
   Search
   ========================= */

void search_text()
{
    char search_term[MAX_LINE_LENGTH];
    int found = 0;
    int i;

    if (line_count == 0)
    {
        printf("\nDocument is empty.\n");
        return;
    }

    printf("\nEnter word or phrase to search: ");
    read_text(search_term, sizeof(search_term));

    if (strlen(search_term) == 0)
    {
        printf("Error: Search text cannot be empty.\n");
        return;
    }

    printf("\nSearch results:\n");

    for (i = 0; i < line_count; i++)
    {
        if (strstr(lines[i], search_term) != NULL)
        {
            printf("Line %d: %s\n", i + 1, lines[i]);
            found = 1;
        }
    }

    if (!found)
    {
        printf("No matches found.\n");
    }
}

/* =========================
   Replace All Occurrences
   ========================= */

char *replace_text(
    const char *source,
    const char *find,
    const char *replace)
{
    const char *current;
    char *result;
    char *write_position;

    size_t source_length = strlen(source);
    size_t find_length = strlen(find);
    size_t replace_length = strlen(replace);

    size_t occurrences = 0;
    size_t result_length;

    if (find_length == 0)
    {
        return duplicate_string(source);
    }

    /*
       Count occurrences.
    */
    current = source;

    while ((current = strstr(current, find)) != NULL)
    {
        occurrences++;
        current += find_length;
    }

    if (occurrences == 0)
    {
        return duplicate_string(source);
    }

    /*
       Calculate required memory.
    */
    result_length =
        source_length +
        occurrences * (replace_length - find_length);

    result = malloc(result_length + 1);

    if (result == NULL)
    {
        return NULL;
    }

    /*
       Build replaced string.
    */
    current = source;
    write_position = result;

    while (1)
    {
        const char *match = strstr(current, find);

        if (match == NULL)
        {
            strcpy(write_position, current);
            break;
        }

        size_t characters_before_match =
            (size_t)(match - current);

        memcpy(
            write_position,
            current,
            characters_before_match);

        write_position += characters_before_match;

        memcpy(
            write_position,
            replace,
            replace_length);

        write_position += replace_length;

        current = match + find_length;
    }

    return result;
}

/* =========================
   Find & Replace
   ========================= */

void find_replace()
{
    char find[MAX_LINE_LENGTH];
    char replace[MAX_LINE_LENGTH];
    char *new_line;

    int choice;
    int line_number;
    int start;
    int end;
    int i;
    int changed = 0;

    if (line_count == 0)
    {
        printf("\nDocument is empty.\n");
        return;
    }

    printf("\n========================================\n");
    printf("           FIND & REPLACE\n");
    printf("========================================\n");

    printf("Enter text to find: ");
    read_text(find, sizeof(find));

    if (strlen(find) == 0)
    {
        printf("Error: Search text cannot be empty.\n");
        return;
    }

    printf("Enter replacement text: ");
    read_text(replace, sizeof(replace));

    printf("\n1. Replace on a specific line\n");
    printf("2. Replace throughout the document\n");
    printf("Enter choice: ");

    choice = read_integer();

    if (choice == 1)
    {
        printf("Enter line number (1-%d): ", line_count);
        line_number = read_integer();

        if (line_number < 1 || line_number > line_count)
        {
            printf("Error: Invalid line number.\n");
            return;
        }

        start = line_number - 1;
        end = line_number;
    }
    else if (choice == 2)
    {
        start = 0;
        end = line_count;
    }
    else
    {
        printf("Error: Invalid choice.\n");
        return;
    }

    /*
       First check whether a replacement
       is actually needed.
    */
    for (i = start; i < end; i++)
    {
        if (strstr(lines[i], find) != NULL)
        {
            changed = 1;
            break;
        }
    }

    if (!changed)
    {
        printf("\nNo matching text found.\n");
        return;
    }

    if (!save_undo_state())
    {
        printf("Error: Unable to create undo state.\n");
        return;
    }

    for (i = start; i < end; i++)
    {
        if (strstr(lines[i], find) != NULL)
        {
            new_line = replace_text(
                lines[i],
                find,
                replace);

            if (new_line == NULL)
            {
                printf("Error: Memory allocation failed.\n");
                return;
            }

            free(lines[i]);
            lines[i] = new_line;
        }
    }

    printf("\nFind & Replace completed successfully.\n");
}

/* =========================
   Document Statistics
   ========================= */

void document_statistics()
{
    long character_count = 0;
    long word_count = 0;

    int i;
    int inside_word;

    for (i = 0; i < line_count; i++)
    {
        int j;

        character_count += strlen(lines[i]);

        inside_word = 0;

        for (j = 0; lines[i][j] != '\0'; j++)
        {
            if (lines[i][j] != ' ' &&
                lines[i][j] != '\t')
            {
                if (!inside_word)
                {
                    word_count++;
                    inside_word = 1;
                }
            }
            else
            {
                inside_word = 0;
            }
        }
    }

    printf("\n========================================\n");
    printf("          DOCUMENT STATISTICS\n");
    printf("========================================\n");
    printf("Lines      : %d\n", line_count);
    printf("Words      : %ld\n", word_count);
    printf("Characters : %ld\n", character_count);
    printf("========================================\n");
}

/* =========================
   Main Menu
   ========================= */

void display_menu()
{
    printf("\n\n");
    printf("========================================\n");
    printf("          SIMPLE LINE EDITOR\n");
    printf("========================================\n");
    printf("  1. Insert Line\n");
    printf("  2. Delete Line\n");
    printf("  3. Display Document\n");
    printf("  4. Save Document\n");
    printf("  5. Load Document\n");
    printf("  6. Search\n");
    printf("  7. Find & Replace\n");
    printf("  8. Undo Last Action\n");
    printf("  9. Line / Word Count\n");
    printf(" 10. Exit\n");
    printf("========================================\n");
    printf("Enter your choice: ");
}

/* =========================
   Main Function
   ========================= */

int main()
{
    int choice;

    printf("\n========================================\n");
    printf("       WELCOME TO SIMPLE LINE EDITOR\n");
    printf("========================================\n");

    /*
       Automatically load document.txt
       if it already exists.
    */
    FILE *startup_file = fopen(FILE_NAME, "r");

    if (startup_file != NULL)
    {
        fclose(startup_file);

        printf("\nExisting document found.\n");
        load_file();

        /*
           Loading at startup should not count
           as an undoable editing action.
        */
        free_undo();
    }
    else
    {
        printf("\nStarting with a new empty document.\n");
    }

    while (1)
    {
        display_menu();

        choice = read_integer();

        switch (choice)
        {
            case 1:
                insert_line();
                break;

            case 2:
                delete_line();
                break;

            case 3:
                display_document();
                break;

            case 4:
                save_file();
                break;

            case 5:
                load_file();
                break;

            case 6:
                search_text();
                break;

            case 7:
                find_replace();
                break;

            case 8:
                undo_action();
                break;

            case 9:
                document_statistics();
                break;

            case 10:
                free_document();
                free_undo();

                printf("\nThank you for using Simple Line Editor!\n");
                printf("Goodbye!\n\n");

                return 0;

            default:
                printf("\nError: Invalid choice. Please select 1-10.\n");
        }
    }
}