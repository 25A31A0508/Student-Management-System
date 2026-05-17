#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

// Structure to hold student details
struct Student {
    string id;
    string name;
    int age;
    string course;
};

// Function declarations
void addStudent();
void displayStudents();
void searchStudent();
void updateStudent();
void deleteStudent();
void showMenu();

const string FILE_NAME = "students.txt";

int main() {
    int choice;
    do {
        showMenu();
        cout << "Enter your choice (1-6): ";
        while (!(cin >> choice)) {
            cout << "Invalid input! Please enter a number between 1 and 6: ";
            cin.clear();
            cin.ignore(123, '\n');
        }
        cin.ignore(); // Clear newline character from buffer

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: cout << "\nExiting system. Goodbye!\n"; break;
            default: cout << "\nInvalid choice! Please try again.\n";
        }
    } while (choice != 6);

    return 0;
}

// Display UI Menu
void showMenu() {
    cout << "\n============================================\n";
    cout << "        STUDENT MANAGEMENT SYSTEM           \n";
    cout << "============================================\n";
    cout << "1. Add New Student\n";
    cout << "2. Display All Students\n";
    cout << "3. Search Student by ID\n";
    cout << "4. Update Student Record\n";
    cout << "5. Delete Student Record\n";
    cout << "6. Exit Application\n";
    cout << "--------------------------------------------\n";
}

// 1. Add a New Student Record (Append to file)
void addStudent() {
    Student s;
    ofstream outFile(FILE_NAME, ios::app);

    if (!outFile) {
        cout << "\n[Error] Could not open file for writing.\n";
        return;
    }

    cout << "\n--- Add New Student ---\n";
    cout << "Enter Student ID: ";
    getline(cin, s.id);
    cout << "Enter Full Name: ";
    getline(cin, s.name);
    cout << "Enter Age: ";
    cin >> s.age;
    cin.ignore(); // Clear buffer
    cout << "Enter Course/Major: ";
    getline(cin, s.course);

    // Write data to file separated by newlines to easily handle spaces in names
    outFile << s.id << "\n" << s.name << "\n" << s.age << "\n" << s.course << "\n";
    outFile.close();

    cout << "\n[Success] Student record added successfully!\n";
}

// 2. Display All Student Records
void displayStudents() {
    ifstream inFile(FILE_NAME);
    if (!inFile) {
        cout << "\n[Notice] No records found. Try adding a student first.\n";
        return;
    }

    Student s;
    cout << "\n----------------------------------------------------------------------\n";
    cout << left << setw(10) << "ID" << setw(25) << "Name" << setw(10) << "Age" << setw(25) << "Course" << endl;
    cout << "----------------------------------------------------------------------\n";

    // Read file line-by-line matching the structure format
    while (getline(inFile, s.id)) {
        getline(inFile, s.name);
        inFile >> s.age;
        inFile.ignore(); // skip newline after age
        getline(inFile, s.course);

        cout << left << setw(10) << s.id 
             << setw(25) << s.name 
             << setw(10) << s.age 
             << setw(25) << s.course << endl;
    }
    cout << "----------------------------------------------------------------------\n";
    inFile.close();
}

// 3. Search Student by ID
void searchStudent() {
    ifstream inFile(FILE_NAME);
    if (!inFile) {
        cout << "\n[Notice] No records found.\n";
        return;
    }

    string searchId;
    cout << "\nEnter Student ID to search: ";
    getline(cin, searchId);

    Student s;
    bool found = false;

    while (getline(inFile, s.id)) {
        getline(inFile, s.name);
        inFile >> s.age;
        inFile.ignore();
        getline(inFile, s.course);

        if (s.id == searchId) {
            cout << "\n--- Student Found ---\n";
            cout << "ID:      " << s.id << "\n";
            cout << "Name:    " << s.name << "\n";
            cout << "Age:     " << s.age << "\n";
            cout << "Course:  " << s.course << "\n";
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "\n[Info] Student with ID " << searchId << " not found.\n";
    }
    inFile.close();
}

// 4. Update Student Record
void updateStudent() {
    ifstream inFile(FILE_NAME);
    if (!inFile) {
        cout << "\n[Notice] No records found to update.\n";
        return;
    }

    string targetId;
    cout << "\nEnter Student ID to update: ";
    getline(cin, targetId);

    vector<Student> students;
    Student s;
    bool found = false;

    // Load all records into a vector memory block
    while (getline(inFile, s.id)) {
        getline(inFile, s.name);
        inFile >> s.age;
        inFile.ignore();
        getline(inFile, s.course);

        if (s.id == targetId) {
            found = true;
            cout << "\nRecord Found! Enter New Details:\n";
            cout << "Enter New Name (Current: " << s.name << "): ";
            getline(cin, s.name);
            cout << "Enter New Age (Current: " << s.age << "): ";
            cin >> s.age;
            cin.ignore();
            cout << "Enter New Course (Current: " << s.course << "): ";
            getline(cin, s.course);
        }
        students.push_back(s);
    }
    inFile.close();

    if (!found) {
        cout << "\n[Info] Student with ID " << targetId << " not found.\n";
        return;
    }

    // Rewrite the file with the updated data
    ofstream outFile(FILE_NAME, ios::trunc);
    for (const auto& student : students) {
        outFile << student.id << "\n" << student.name << "\n" << student.age << "\n" << student.course << "\n";
    }
    outFile.close();
    cout << "\n[Success] Student record updated successfully!\n";
}

// 5. Delete Student Record
void deleteStudent() {
    ifstream inFile(FILE_NAME);
    if (!inFile) {
        cout << "\n[Notice] No records found to delete.\n";
        return;
    }

    string targetId;
    cout << "\nEnter Student ID to delete: ";
    getline(cin, targetId);

    vector<Student> students;
    Student s;
    bool found = false;

    // Filter data: read all records except the target one
    while (getline(inFile, s.id)) {
        getline(inFile, s.name);
        inFile >> s.age;
        inFile.ignore();
        getline(inFile, s.course);

        if (s.id == targetId) {
            found = true; // Skip adding this student to the vector
            continue;
        }
        students.push_back(s);
    }
    inFile.close();

    if (!found) {
        cout << "\n[Info] Student with ID " << targetId << " not found.\n";
        return;
    }

    // Rewrite the file without the deleted record
    ofstream outFile(FILE_NAME, ios::trunc);
    for (const auto& student : students) {
        outFile << student.id << "\n" << student.name << "\n" << student.age << "\n" << student.course << "\n";
    }
    outFile.close();
    cout << "\n[Success] Student record deleted successfully!\n";
}
