
# TODO List Manager (C++ Project)

This project builds a simple command‑line TODO list generator using a custom
**ordered singly linked list**.
Users enter tasks in the format:

The program validates input, stores tasks in sorted order, and outputs a
formatted `output.txt` file.

---

## Features

- Input parsing and validation (task text, yes/no completion, priority 1–5)
- Duplicate detection by task text with interactive replace/skip
- Ordered insertion:
  - Incomplete tasks come **before** completed tasks
  - Within the same completion status, **lower priority number** comes first
- Pretty output file with GitHub‑style checkboxes

## How to Run

From the project root:

```bash
g++ -std=c++20 main.cpp validation/validation.cpp linkedlist/linkedlist_util.cpp -o main
./main
```

## Project Structure
.
├── main.cpp
├── validation/
│   ├── validation.hpp
│   └── validation.cpp
└── linkedlist/
    ├── linkedlist_util.hpp
    ├── linkedlist_util.cpp
    ├── node.hpp
    └── node.cpp


# 🧠 High‑Level Flow

1. Read user input until `"exit"`.
2. Parse each line into: (tasks, completed, priority)
3. Validate each field:
- task must be **non‑empty**
- completed must be **"yes" or "no"**
- priority must be **integer in [1, 5]**

4. If a duplicate task text is found:
- Ask user whether to **replace** or **skip**

5. Insert into an ordered linked list:
- Incomplete tasks **first**
- Then ascending **priority**

6. Write `output.txt` with:
- `- [ ]` for **incomplete** tasks
- `- [X]` for **completed** tasks


## What Each Part Contains

### **main.cpp**
- Handles user input
- Calls validation functions
- Checks for duplicates and prompts user (replace/skip)
- Inserts items into the ordered linked list
- Writes the final `output.txt`

### **validation/**
- Cleans and trims user input
- Splits lines of the form `"task, yes/no, priority"`
- Validates:
  - task text : non empty string
  - completion flag ("yes"/"no")
  - priority (1–5) valid integer

### **linkedlist/**
- Defines the `Node` class
- Implements the `ordered_linkedlist` class using elements from the `Node` class:
  - insert node
  - delete node
  - search for node
  - print into output file

## Example
### **Input**
dishes, no, 3
study, yes, 2
shower, no, 1
exit
### **Output (output.txt)**
[]shower, Priority: 1
[] dishes, Priority: 3
[X] study, Priority: 2