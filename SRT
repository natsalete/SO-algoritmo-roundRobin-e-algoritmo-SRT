#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int remaining_time;

    Process(int id, int arrival_time, int burst_time)
        : id(id), arrival_time(arrival_time), burst_time(burst_time), remaining_time(burst_time) {}

    bool operator<(const Process& other) const {
        return arrival_time < other.arrival_time;
    }
};

void srt(vector<Process>& processes) {
    int n = processes.size();
    int current_time = 0;
    int completed = 0;
    vector<int> completion_time(n);
    vector<int> waiting_time(n);

    while (completed < n) {
        int shortest = -1;
        int shortest_time = INT_MAX;

        for (int i = 0; i < n; ++i) {
            if (processes[i].arrival_time <= current_time && processes[i].remaining_time < shortest_time && processes[i].remaining_time > 0) {
                shortest = i;
                shortest_time = processes[i].remaining_time;
            }
        }

        if (shortest == -1) {
            current_time++;
            continue;
        }

        processes[shortest].remaining_time--;
        current_time++;

        if (processes[shortest].remaining_time == 0) {
            completed++;
            int finish_time = current_time;
            completion_time[shortest] = finish_time;
            waiting_time[shortest] = finish_time - processes[shortest].burst_time - processes[shortest].arrival_time;
        }
    }

    cout << "Process ID\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\n";
    for (int i = 0; i < n; ++i) {
        cout << processes[i].id << "\t\t" << processes[i].arrival_time << "\t\t" << processes[i].burst_time << "\t\t" << completion_time[i] << "\t\t\t" << waiting_time[i] << endl;
    }
}

int main() {
    vector<Process> processes = {
        {1, 0, 6},
        {2, 2, 4},
        {3, 4, 2},
        {4, 6, 5}
    };

    sort(processes.begin(), processes.end());

    srt(processes);

    return 0;
}
