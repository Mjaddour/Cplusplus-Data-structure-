#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Define a structure to represent a course
struct Course {
    string courseNumber;
    string name;
    vector<string> prerequisites;
};

// Function to split a string into tokens based on a delimiter
vector<string> tokensize(const string& inputString, const string& del = "") {
    vector<string> stringArray;
    size_t start = 0;
    size_t end = inputString.find(del);
    while (end != string::npos) {
        stringArray.push_back(inputString.substr(start, end - start));
        start = end + del.size();
        end = inputString.find(del, start);
    }
    stringArray.push_back(inputString.substr(start, end - start));
    return stringArray;
}

// Function to load course data from a text file
vector<Course> LoadDataStructure() {
    ifstream find("ABCU_Advising_Program_Input.csv", ios::in);
    vector<Course> courses;
    string line;
    while (getline(find, line)) { // Read lines until end of file
        if (line.empty())
            continue;

        Course course;
        vector<string> tokenInformation = tokensize(line, ",");
        course.courseNumber = tokenInformation[0];
        course.name = tokenInformation[1];
        for (unsigned i = 2; i < tokenInformation.size(); ++i) {
            course.prerequisites.push_back(tokenInformation[i]);
        }
        courses.push_back(course);
    }
    find.close();
    return courses;
}

// Function to print details of a single course
void printCourse(Course course) {
    string courseNumber = course.courseNumber;
    string name = course.name;
    vector<string> prerequisites = course.prerequisites;
    cout << courseNumber << ", " << name;

    cout << endl << endl;
}

// Function to print the list of courses
void printCourseList(const vector<Course>& courses) {
    vector<Course> sortedCourses = courses; // Make a copy for sorting
    sort(sortedCourses.begin(), sortedCourses.end(), [](const Course& a, const Course& b) {
        return a.name < b.name;
        });

    cout << "Sorted list of courses in alphabetical order by name:" << endl;
    for (const Course& course : sortedCourses) {
        cout << course.courseNumber << ", " << course.name << endl;
    }
}


// Function to search for a specific course and display its details
void searchCourse(const vector<Course>& courses) { // Pass vector by const reference
    int n = courses.size();
    string courseNumber;
    int flag = 0;
    cout << "What course do you want to know about? ";
    cin >> courseNumber;

    for (unsigned i = 0; i < n; i++) {
        if (courses[i].courseNumber == courseNumber) {
            flag = 1;
            string name = courses[i].name;
            vector<string> prerequisites = courses[i].prerequisites;
            cout << courseNumber << ", " << name << endl;
            cout << "Prerequisites: ";
            if (prerequisites.empty()) {
                cout << "None";
            }
            else {
                for (unsigned j = 0; j < prerequisites.size(); j++) {
                    cout << prerequisites[j];
                    if (j < prerequisites.size() - 1)
                        cout << ", ";
                }
            }
            cout << endl << endl;

            break; // No need to continue searching
        }
    }

    if (flag == 0) {
        cout << "Course with given course number not found" << endl;
    }
}

int main(int argc, char** argv) {
    vector<Course> courses;
    cout << "Welcome to the course planner." << endl;
    cout << endl;

    int choice;
    while (choice != 9); {
        cout << endl;
        cout << "   1. Load Data Structure." << endl;
        cout << "   2. Print Course List." << endl;
        cout << "   3. Print Course." << endl;
        cout << "   9. Exit" << endl;
        cout << endl;
        cout << "What would you like to do? ";
        cin >> choice;

        switch (choice) {
        case 1:
            courses = LoadDataStructure(); // Load course data
            break;
        case 2:
            if (courses.empty()) {
                cout << "No data loaded. Please load data first." << endl;
            }
            else {
                cout << "Here is a sample schedule:" << endl << endl;
                printCourseList(courses); // Print the list of courses
            }
            break;
        case 3:
            if (courses.empty()) {
                cout << "No data loaded. Please load data first." << endl;
            }
            else {
                searchCourse(courses); // Search for a specific course
            }
            break;
        case 9:
            cout << "Thank you for using the course planner!" << endl; // Exit message
            break;
        default:
            cout << choice << " is not a valid option." << endl; // Invalid choice
        }
    } 

    return 0;
}
