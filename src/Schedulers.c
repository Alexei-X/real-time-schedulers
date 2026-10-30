#include "Schedulers.h"
#include <stdio.h>

Job *rate_monotonic(Job **jobs, int n_jobs) {
    Job *current_min = jobs[0];
    for (int i = 1; i < n_jobs; i++) {
        if (jobs[i]->period < current_min->period) {
            current_min = jobs[i];
        }
    }
    return current_min;
}

Job *deadline_monotonic() {
    return NULL;
}

Job *earliest_deadline_first(Job **jobs, int n_jobs) {
    Job *current_min = jobs[0];
    for (int i = 1; i < n_jobs; i++) {
        if (jobs[i]->abs_deadline < current_min->abs_deadline) {
            current_min = jobs[i];
        }
    }
    return current_min;
}

void schedule_tasks(enum Scheduling sch, Task **taskset, int n_tasks, int t_max) {
    int final_schedule[n_tasks];
    
    for (int ts = 0; ts < t_max; ts++) {

        switch (sch) {
            case RM:
                printf("Rate Monotonic Scheduling\n");
            case DM:
                printf("Deadline Monotonic Scheduling\n");
            case EDF:
                printf("Earliest Deadline First Scheduling\n");
        }
    }
}
