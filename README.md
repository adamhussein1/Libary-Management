# Library Management System

A small command-line library management tool written in C. It lets you add, delete, and display books in memory, and save/load the book list to a flat file database.

## Build

```bash
gcc -o library Libary.c
```

## Run

```bash
./library
```

You'll see a menu:

```
Library Management System
1. Add book
2. Delete last book
3. Display book list
4. Save the book list to the database
5. Read the book list from the database
6. Exit the program
```

Enter a number and press Enter to choose an option.

## Menu options

1. **Add book** — Prompts for title, author, ISBN (1–11 characters), publication month (1–12), publication year (1950–2024), and genre. Re-prompts on invalid ISBN, month, or year.
2. **Delete last book** — Removes the most recently added book from the list.
3. **Display book list** — Prints all books currently in memory in a table.
4. **Save the book list to the database** — Writes the current book list to a file named `database`.
5. **Read the book list from the database** — Intended to load a previously saved book list back into memory.
6. **Exit the program** — Quits the application.

## Data model

Each book has:

| Field             | Max size        |
|-------------------|------------------|
| Title             | 15 chars         |
| Author            | 15 chars         |
| ISBN              | 1–11 chars       |
| Genre             | 19 chars         |
| Publication month | 1–12             |
| Publication year  | 1950–2024        |

The library holds up to 20 books at a time (`MAX_LIBRARY_SIZE`).

## Known issues

- **Save fails silently:** `saveDatabase` opens the file with an invalid mode string, so saving currently always fails.
- **Read is not implemented:** `readDatabase` doesn't open or parse the database file, so loading a saved list doesn't work yet.
- **Off-by-one on capacity:** the "list full" check in `Addbook` allows one book to be written past the end of the array before rejecting further additions.
- **Unbounded input for title/author/ISBN:** these fields are read without a width limit, so a long entry can overflow the field's buffer.

## Requirements

- A C compiler (e.g. `gcc` or `clang`)
- No external dependencies — only `stdio.h`, `stdlib.h`, and `string.h`
