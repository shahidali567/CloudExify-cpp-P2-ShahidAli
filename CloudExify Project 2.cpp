#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

const int MAX = 50;

struct Student{
    int id;
    string name;
    int Rollnumber;
    float computer;
    float math;
    float chemistry;
    float physics;
    float Average;
};

Student students[MAX];
int number = 0;

float calcAverage(Student s){
    return (s.computer + s.math + s.chemistry + s.physics) / 4.0;
}

void addStudent(){
    if (number >= MAX){
        cout << "Maximum students reached!" << endl;
        return;
    }

    Student s;
    s.id = number + 1;

    cout << "\n--- ADD STUDENT ---" << endl;
    cout << "Name: ";
    cin.ignore();
    getline(cin, s.name);
    cout << "Roll Number: ";
    cin >> s.Rollnumber;
    
    cout << "Computer Marks (0-100) ";
    cin >> s.computer;
    while (s.computer < 0 || s.computer > 100){
        cout << "Must be between 0 and 100 ";
        cin >> s.computer;
    }

    cout << "Math Marks (0-100) ";
    cin >> s.math;
    while (s.math < 0 || s.math > 100){
        cout << "Must be between 0 and 100 ";
        cin >> s.math;
    }

    cout << "Chemistry Marks (0-100) ";
    cin >> s.chemistry;
    while (s.chemistry < 0 || s.chemistry > 100){
        cout << "Must be between 0 and 100 ";
        cin >> s.chemistry;
    }

    cout << "Physics Marks (0-100) ";
    cin >> s.physics;
    while (s.physics < 0 || s.physics > 100){
        cout << "Must be between 0 and 100 ";
        cin >> s.physics;
    }

    s.Average = calcAverage(s);
    students[number] = s;
    number++;

    cout << "Student added successfully!" << endl;
    cout << "Average: " << fixed << setprecision(1) << s.Average << endl;
}

void displayAll(){
    if (number == 0){
        cout << "No students found!" << endl;
        return;
    }

    cout << "\n" << string(90, '=') << endl;
    cout << left
         << setw(6) << "ID"
         << setw(18) << "Name"
         << setw(12) << "Roll No"
         << setw(9) << "Comp"
         << setw(9) << "Math"
         << setw(11) << "Chem"
         << setw(10) << "Physics"
         << setw(9) << "Average"
         << endl;

    cout << string(90, '-') << endl;

    for (int i = 0; i < number; i++){
        cout << left
             << setw(6) << students[i].id
             << setw(18) << students[i].name
             << setw(12) << students[i].Rollnumber
             << setw(9) << fixed << setprecision(1) << students[i].computer
             << setw(9) << students[i].math
             << setw(11) << students[i].chemistry
             << setw(10) << students[i].physics
             << setw(9) << students[i].Average
             << endl;
    }

    cout << string(70, '=') << endl;
    cout << "Total Students: " << number << endl;
}

void showStats(){
    if (number == 0) {
        cout << "No student record found!" << endl;
        return;
    }

    int topper = 0;
    int lowest = 0;
    float totalAverage = 0;
    int pass = 0;
 
for (int i = 0; i < number; i++){
        totalAverage += students[i].Average;

        if (students[i].Average > students[topper].Average)
            topper = i;

        if (students[i].Average < students[lowest].Average)
            lowest = i;

        if (students[i].Average >= 50)
            pass++;
    }

    cout << "\n========== CLASS REPORT ==========" << endl;
    cout << "Students       : " << number << endl;
    cout << "Class Average  : " << fixed << setprecision(2)
         << totalAverage / number << endl;
    cout << "Passed         : " << pass << endl;
    cout << "Failed         : " << number - pass << endl;
    cout << "Top Student    : " << students[topper].name
         << " (" << students[topper].Average << ")" << endl;
    cout << "Lowest Student : " << students[lowest].name
         << " (" << students[lowest].Average << ")" << endl;
}


void saveToFile(){
    ofstream file("students.txt");

    if (!file){
        cout << "Unable to save data!" << endl;
        return;
    }
    file << number << endl;

    for (int i = 0; i < number; i++){
        file << students[i].id << endl;
        file << students[i].name << endl;
        file << students[i].Rollnumber << endl;
        file << students[i].computer << endl;
        file << students[i].math << endl;
        file << students[i].chemistry << endl;
        file << students[i].physics << endl;
    }
    file.close();
    cout << "Data saved successfully!" << endl;
}

void loadFromFile(){
    ifstream file("students.txt");

    if (!file){
        cout << "No saved record found!" << endl;
        return;
    }

    file >> number;
    file.ignore();

for (int i = 0; i < number; i++){
        file >> students[i].id;
        file.ignore();

        getline(file, students[i].name);

       file >> students[i].Rollnumber;
       file >> students[i].computer;
       file >> students[i].math;
       file >> students[i].chemistry;
       file >> students[i].physics;
       file.ignore();

        students[i].Average = calcAverage(students[i]);
    }
    file.close();
    cout << "Data loaded successfully!" << endl;
}

void sortByAverage(){
    if (number == 0){
        cout << "No students found!" << endl;
        return;
    }

    for (int i = 0; i < number - 1; i++){
        for (int j = 0; j < number - i - 1; j++){
            if (students[j].Average < students[j + 1].Average){
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }

cout << "Students sorted by average successfully!" << endl;
}

void menu(){
    
    cout << "\n      STUDENT MANAGEMENT SYSTEM" << endl;
    cout << "==========================================" << endl;
    cout << "1. Add Student" << endl;
    cout << "2. View All Students" << endl;
    cout << "3. Show Statistics" << endl;
    cout << "4. Sort by Average" << endl;
    cout << "5. Save to File" << endl;
    cout << "6. Load from File" << endl;
    cout << "7. Exit" << endl;
    cout << "==========================================" << endl;
    cout << "Enter Choice: ";
}

int main(){
    int choice;
    do{
        menu();
        cin >> choice;

        switch (choice){
        case 1:
            addStudent();
            break;
        case 2:
            displayAll();
            break;
        case 3:
            showStats();
            break;
        case 4:
            sortByAverage();
            break;
        case 5:
            saveToFile();
            break;
        case 6:
            loadFromFile();
            break;
        case 7:
            cout << "Thank you for using Student Management System!" << endl;
            break;
        default:
            cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 7);
    return 0;
}