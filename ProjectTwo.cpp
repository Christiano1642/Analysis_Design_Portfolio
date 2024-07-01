#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

class Course {
public:
    string courseId;
    string title;
    vector<string> prerequisites;

    // Default constructor
    Course() = default;

    // Parameterized constructor
    Course(string id, string name, vector<string> prereqs) {
        courseId = id;
        title = name;
        prerequisites = prereqs;
    }
};

void loadCourses(const string& filename, map<string, Course>& courses) {
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Could not open file " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string id, name, prereq;
        vector<string> prereqs;

        getline(ss, id, ',');
        getline(ss, name, ',');

        while (getline(ss, prereq, ',')) {
            prereqs.push_back(prereq);
        }

        courses[id] = Course(id, name, prereqs);
    }

    file.close();
    cout << "Courses loaded successfully!" << endl;
}

void printCourseList(const map<string, Course>& courses) {
    vector<string> courseIds;
    for (const auto& entry : courses) {
        courseIds.push_back(entry.first);
    }

    sort(courseIds.begin(), courseIds.end());

    cout << "Here is a sample schedule:" << endl;
    for (const string& id : courseIds) {
        cout << id << ", " << courses.at(id).title << endl;
    }
}

void printCourseDetails(const map<string, Course>& courses, const string& courseId) {
    auto it = courses.find(courseId);
    if (it != courses.end()) {
        cout << it->second.courseId << ", " << it->second.title << endl;
        cout << "Prerequisites: ";
        for (size_t i = 0; i < it->second.prerequisites.size(); ++i) {
            cout << it->second.prerequisites[i];
            if (i < it->second.prerequisites.size() - 1) {
                cout << ", ";
            }
        }
        cout << endl;
    }
    else {
        cout << "Course not found." << endl;
    }
}

void displayMenu() {
    cout << "1. Load Data Structure." << endl;
    cout << "2. Print Course List." << endl;
    cout << "3. Print Course." << endl;
    cout << "9. Exit" << endl;
    cout << "What would you like to do? ";
}

int main() {
    map<string, Course> courses;
    string filename;
    int choice;

    cout << "Welcome to the course planner." << endl;

    while (true) {
        displayMenu();
        cin >> choice;

        // Handle invalid input
        if (cin.fail()) {
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the rest of the input
            cout << "Invalid input. Please enter a valid option." << endl;
            continue;
        }

        switch (choice) {
        case 1:
            cout << "Enter the filename to load: ";
            cin >> filename;
            loadCourses(filename, courses);
            break;
        case 2:
            if (courses.empty()) {
                cout << "No courses loaded. Please load the data first." << endl;
            }
            else {
                printCourseList(courses);
            }
            break;
        case 3: {
            if (courses.empty()) {
                cout << "No courses loaded. Please load the data first." << endl;
            }
            else {
                cout << "What course do you want to know about? ";
                string courseId;
                cin >> courseId;
                transform(courseId.begin(), courseId.end(), courseId.begin(), ::toupper);
                printCourseDetails(courses, courseId);
            }
            break;
        }
        case 9:
            cout << "Thank you for using the course planner!" << endl;
            return 0;
        default:
            cout << choice << " is not a valid option." << endl;
            break;
        }
    }
}
