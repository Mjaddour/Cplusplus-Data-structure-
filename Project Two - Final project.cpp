#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <limits>

using namespace std;

// Define a tructure to represent a course
struct Course {
    string courseNumber;
    string name;
    vector<string> prerequisites;
};

// Function to split a string into tokens based on a delimiter
vector<string> tokensize(const string& inputString, const string& del = ",") {
    vector<string> stringArray;
    size_t start = 0;
    size_t end = inputString.find(del);
    while (end != string::npos) {
        stringArray.emplace_back(inputString.substr(start, end - start));
        start = end + del.size();
        end = inputString.find(del, start);
    }
    stringArray.emplace_back(inputString.substr(start, end - start));
    return stringArray;
}


// Function to load course data from a text file
unordered_map<string, Course> LoadDataStructure() {
    ifstream find("ABCU_Advising_Program_Input.csv", ios::in);
    unordered_map<string, Course> courseMap;
    string line;

    if (!find.is_open()) {
        cerr << "Error: Could not open the file!" << endl;
        return courseMap;
    }

    while (getline(find, line)) {
        if (line.empty())
            continue;

        Course course;
        vector<string> tokenInformation = tokensize(line);

        if (tokenInformation.size() < 2) {
            cerr << "Error: Malformed line in input file: " << line << endl;
            continue; // Skip this line and move to the next
        }

        course.courseNumber = tokenInformation[0];
        course.name = tokenInformation[1];

        // If there are any prerequisites, store them
        for (unsigned i = 2; i < tokenInformation.size(); ++i) {
            course.prerequisites.push_back(tokenInformation[i]);
        }

        courseMap[course.courseNumber] = course;
    }

    find.close();
    return courseMap;
  
}

// Function to print details of a single course
void printCourse(const Course& course) {
    cout << course.courseNumber << ", " << course.name << endl;
    cout << "Prerequisites: ";
    if (course.prerequisites.empty()) {
        cout << "None";
    } else {
        for (unsigned j = 0; j < course.prerequisites.size(); ++j) {
            cout << course.prerequisites[j];
            if (j < course.prerequisites.size() - 1)
                cout << ", ";
        }
    }
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
void searchCourse(const unordered_map<string, Course>& courseMap) {
    string courseNumber;
    cout << "What course do you want to know about? ";
    cin >> courseNumber;
    
    // Use map lookup
    auto it = courseMap.find(courseNumber); 
    if (it != courseMap.end()) {
        // Print course details if found
        printCourse(it->second); 
    } else {
        cout << "Course with given course number not found" << endl;
    }
}

int main() {
    unordered_map<string, Course> courseMap;
    vector<Course> courses;
    
    cout << "Welcome to the course planner." << endl;

    int choice = 0;
    while (choice != 9) {
        cout << endl;
        cout << "   1. Load Data Structure." << endl;
        cout << "   2. Print Course List." << endl;
        cout << "   3. Print Course." << endl;
        cout << "   9. Exit" << endl;
        cout << endl;
        cout << "What would you like to do? ";
        
        // Input validation for menu selection
        while (!(cin >> choice)) {
            // Clear the error flag
            cin.clear(); 
            // Ignore invalid input
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "Please enter a valid number: ";
        }

        switch (choice) {
        case 1:
            courseMap = LoadDataStructure();
            if (courseMap.empty()) {
                cout << "Error: No data loaded. Ensure the file is correct." << endl;
            } else {
                courses.clear();
                for (const auto& pair : courseMap) {
                    courses.push_back(pair.second);
                }
                cout << "Data loaded successfully!" << endl;
            }
            break;
        case 2:
            if (courses.empty()) {
                cout << "No data loaded. Please load data first." << endl;
            } else {
                printCourseList(courses);
            }
            break;
        case 3:
            if (courseMap.empty()) {
                cout << "No data loaded. Please load data first." << endl;
            } else {
                searchCourse(courseMap);
            }
            break;
        case 9:
            cout << "Thank you for using the course planner!" << endl;
            break;
        default:
            cout << choice << " is not a valid option." << endl;
        }
    }

    return 0;
}
