# Linked List Implementation in C

This repository contains a C program that implements a **doubly linked list** to manage a collection of student records. Each student has a unique **ID**, a **name**, and a **grade**. The program provides functionality to **add**, **insert**, **search**, **delete**, and **print** student records within the linked list.

## Features
- **Add student**: Add a new student to the end of the list.
- **Insert student**: Insert a student at a specified position in the list.
- **Search by ID**: Find a student based on their ID.
- **Search by Name**: Find a student based on their name.
- **Delete student**: Remove a student from the list at a given position.
- **Print list**: Display all students in the list.
- **Free list**: Free all memory by deleting all nodes in the list.

## Program Structure
- **Student Structure**: Holds the student’s `id`, `name`, and `grade`.
- **Node Structure**: Represents each element in the doubly linked list. Each node stores a student record and points to the previous and next nodes.
- **Operations**: The program allows for basic linked list operations such as adding, inserting, deleting, searching, and printing student records.

## How to Use:
1. Run the program and select an operation from the menu.
2. For adding or inserting a student, input the student’s ID, name, and grade when prompted.
3. For search operations, enter either the student’s ID or name.
4. Deleting or freeing the list will remove the specified student(s) or clear the entire list.

## Compilation:
```bash
gcc main.c -o main ./main
