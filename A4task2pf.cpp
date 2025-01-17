// A4task2pf.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
struct Patient {
    int patientID;
    string name;
    int age;
    string disease;
    int roomNumber;
};
void addPatient(vector<Patient>& patients) {
    Patient newPatient;
    cout << "Enter Patient ID: ";
    cin >> newPatient.patientID;
    cin.ignore();
    cout << "Enter Name: ";
    getline(cin, newPatient.name);
    cout << "Enter Age: ";
    cin >> newPatient.age;
    cin.ignore();
    cout << "Enter Disease: ";
    getline(cin, newPatient.disease);
    cout << "Enter Room Number: ";
    cin >> newPatient.roomNumber;

    patients.push_back(newPatient);

    ofstream outFile("patients.dat", ios::app | ios::binary);
    outFile.write(reinterpret_cast<char*>(&newPatient), sizeof(Patient));
    outFile.close();

    cout << "Patient added successfully." << endl;
}

void searchPatientByID(const vector<Patient>& patients, int searchID) {
    bool found = false;
    for (const auto& patient : patients) {
        if (patient.patientID == searchID) {
            cout << "Patient Found!" << endl;
            cout << "Patient ID: " << patient.patientID << endl;
            cout << "Name: " << patient.name << endl;
            cout << "Age: " << patient.age << endl;
            cout << "Disease: " << patient.disease << endl;
            cout << "Room Number: " << patient.roomNumber << endl;
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Patient with ID " << searchID << " not found." << endl;
    }
}

void displayAllPatients(const vector<Patient>& patients) {
    if (patients.empty()) {
        cout << "No patients in the system." << endl;
        return;
    }

    cout << "Patient Details:" << endl;
    for (const auto& patient : patients) {
        cout << "Patient ID: " << patient.patientID << endl;
        cout << "Name: " << patient.name << endl;
        cout << "Age: " << patient.age << endl;
        cout << "Disease: " << patient.disease << endl;
        cout << "Room Number: " << patient.roomNumber << endl;
        cout << "-----------------------------" << endl;
    }
}

void loadPatientsFromFile(vector<Patient>& patients) {
    ifstream inFile("patients.dat", ios::binary);
    if (inFile) {
        Patient tempPatient;
        while (inFile.read(reinterpret_cast<char*>(&tempPatient), sizeof(Patient))) {
            patients.push_back(tempPatient);
        }
    }
}

void displayMenu() {
    cout << "\nHospital Patient Management System" << endl;
    cout << "1. Add a New Patient" << endl;
    cout << "2. Search for a Patient by Patient ID" << endl;
    cout << "3. Display All Patients" << endl;
    cout << "4. Exit" << endl;
    cout << "Enter your choice: ";
}

int main() {
    vector<Patient> patients;

    loadPatientsFromFile(patients);

    int choice;
    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            addPatient(patients);
            break;
        case 2: {
            int searchID;
            cout << "Enter Patient ID to search: ";
            cin >> searchID;
            searchPatientByID(patients, searchID);
            break;
        }
        case 3:
            displayAllPatients(patients);
            break;
        case 4:
            cout << "Exiting the program..." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 4);

    return 0;
}
