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

void schedule_tasks(enum Scheduling sch, TaskSet *taskset, int t_max) {
    int final_schedule[taskset->n_tasks];
    int n_jobs = 0;
    Job **current_jobs = (Job**) malloc(MAX_N_JOBS * sizeof(Job*));
    Job *executing_job = (Job*) malloc(sizeof(Job));
    if (current_jobs == NULL || executing_job == NULL) {
        fprintf(stderr, "Error allocating memory for jobs.");
        exit(1);
    }
    for (int ts = 0; ts < t_max; ts++) {
        for (int task_idx = 0; task_idx < taskset->n_tasks; task_idx++) {
            Job *potential_job = release_job(taskset->tasks[task_idx], ts);
            if (potential_job != NULL) {
                current_jobs[n_jobs++] = potential_job;
            }
        }
        switch (sch) {
            case RM:
                printf("Rate Monotonic Scheduling\n");
                executing_job = rate_monotonic(current_jobs, n_jobs);
            case DM:
                printf("Deadline Monotonic Scheduling\n");
                executing_job = deadline_monotonic(current_jobs, n_jobs);
            case EDF:
                printf("Earliest Deadline First Scheduling\n");
                executing_job = earliest_deadline_first(current_jobs, n_jobs);
        }
    }
}
