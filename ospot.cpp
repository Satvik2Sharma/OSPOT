#include <iostream>
#include <fstream>
#include <unistd.h>
#include <string>

using namespace std;

float getCPUUsage() {
    static long long lastUser=0, lastNice=0, lastSystem=0, lastIdle=0;
    long long user, nice, system, idle;

    ifstream file("/proc/stat");
    file >> ws; // skip whitespace
    string cpu;
    file >> cpu >> user >> nice >> system >> idle;

    long long dUser = user - lastUser;
    long long dNice = nice - lastNice;
    long long dSystem = system - lastSystem;
    long long dIdle = idle - lastIdle;

    lastUser = user;
    lastNice = nice;
    lastSystem = system;
    lastIdle = idle;

    long long active = dUser + dNice + dSystem;
    long long total = active + dIdle;

    if (total == 0) return 0;
    return (active * 100.0) / total;
}

float getMemoryUsage() {
    ifstream file("/proc/meminfo");
    string key;
    long long memTotal, memFree;

    while (file >> key) {
        if (key == "MemTotal:") file >> memTotal;
        if (key == "MemFree:") file >> memFree;
    }

    return ((memTotal - memFree) * 100.0) / memTotal;
}

long long getRunningProcesses() {
    ifstream file("/proc/stat");
    string key;
    long long processes = 0;

    while (file >> key) {
        if (key == "procs_running") {
            file >> processes;
            break;
        }
    }
    return processes;
}

void createReport(float cpu, float ram, long long proc) {
    ofstream file("ospot_report.txt");
    file << "=== OSPOT Performance Report ===\n";
    file << "CPU Usage: " << cpu << "%\n";
    file << "RAM Usage: " << ram << "%\n";
    file << "Running Processes: " << proc << "\n";
    file.close();
}

int main() {
    int choice;

    while (true) {
        cout << "\n===== OSPOT - OS Performance Observation Tool =====\n";
        cout << "1. Show CPU Usage\n";
        cout << "2. Show RAM Usage\n";
        cout << "3. Show Running Processes\n";
        cout << "4. Generate Performance Report\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            sleep(1); // needed for CPU calculation
            cout << "CPU Usage: " << getCPUUsage() << "%\n";
        }
        else if (choice == 2) {
            cout << "RAM Usage: " << getMemoryUsage() << "%\n";
        }
        else if (choice == 3) {
            cout << "Running Processes: " << getRunningProcesses() << "\n";
        }
        else if (choice == 4) {
            float cpu = getCPUUsage();
            float ram = getMemoryUsage();
            long long procs = getRunningProcesses();
            createReport(cpu, ram, procs);
            cout << "Report generated: ospot_report.txt\n";
        }
        else if (choice == 5) {
            cout << "Exiting...\n";
            break;
        }
        else {
            cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}
