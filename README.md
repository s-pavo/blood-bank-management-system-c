# blood-bank-management-system-c

## Project Overview
The **Blood Bank Management System** is a **menu-driven console application** developed in **C language**.  
It helps manage blood donor records efficiently using a **doubly linked list** and **file handling**.

This project demonstrates core concepts of **Data Structures**, **Dynamic Memory Allocation**, and **File Operations** in C.

---

## Features
- Add new blood donor details  
- Display all registered donors  
- Search donors by blood group  
- Delete donor records  
- Save donor data to a file  
- Load donor data from a file  
- Menu-driven and user-friendly interface  

---

## Concepts Used
- C Programming  
- Structures  
- Pointers  
- Doubly Linked List  
- Dynamic Memory Allocation (`malloc`, `free`)  
- File Handling (`fopen`, `fprintf`, `fscanf`)  
- Safe input handling (`fgets`, `sscanf`)  

---

## Data Structure
Each donor is stored as a node in a **doubly linked list**, containing:
- Name  
- Age  
- Blood Group  
- Pointer to previous node  
- Pointer to next node  

This allows **efficient insertion and deletion** of donor records.

---

## How to Compile and Run

### Using GCC (Linux / WSL / VS Code Terminal)

```bash
gcc bloodbank.c -o bloodbank
./bloodbank
