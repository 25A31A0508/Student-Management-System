📋 Project Overview
The Student Management System is a console-based software application developed in C++ to automate and streamline the management of student records. Serving as a lightweight alternative to a full database, it allows users to perform core CRUD (Create, Read, Update, Delete) operations through an interactive, menu-driven command-line interface.

The primary objective of the system is to ensure data persistence, meaning student records are securely stored in a physical file (students.txt) and remain intact even after the application is closed.

✨ Key Features
Add Student Records: Captures unique Student ID, Full Name, Age, and Course/Major, and appends them to the storage file.

Display All Records: Reads the data file and displays all records in a cleanly aligned, tabular formatting directly in the console window.

Search Functionality: Allows users to look up a specific student quickly by inputting their unique Student ID.

Update Records: Modifies existing information (Name, Age, Course) for a specific student while keeping their ID intact.

Delete Records: Permanently removes a student's entry from the system and updates the storage file dynamically.

Input Validation: Features basic safety checks (like clearing the input buffer) to prevent the program from crashing if a user enters letters instead of numbers in the menu.

🛠️ Technical Specifications
Programming Language: C++

Paradigm: Procedural & Structural Programming

Core Libraries Used:

<iostream>: For standard console input and output operations.

<fstream>: For file handling capabilities (ifstream to read, ofstream to write).

<string>: To manipulate textual data safely (handling spaces in student names via getline()).

<vector>: To temporarily hold and manipulate datasets in RAM during updating and deleting processes.

<iomanip>: To format the console table structure using standard widths (setw).

💾 File Architecture & Data Flow
Instead of holding data only in the computer's volatile RAM, this system utilizes a local text-based flat file (students.txt) as its permanent database.

Storage Format
To prevent errors when a student's name includes spaces (e.g., "John Doe"), the program writes each attribute on a completely new line:

Plaintext
101
John Doe
20
Computer Science
The Update/Delete Pipeline
Because text files cannot be easily edited line-by-line in real-time, the application utilizes a Memory Filtering Pattern:

It reads all records from students.txt into a std::vector in RAM.

It modifies or skips (deletes) the target record inside the vector.

It completely clears the text file and writes the newly updated vector data back to the disk.
