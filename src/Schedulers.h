#ifndef SCHEDULERS_H
#define SCHEDULERS_H

#include "Task.h"
#include <stdlib.h>

#define MAX_N_JOBS 100

enum Scheduling {
    RM,
    DM,
    EDF
};

Job *rate_monotonic(Job **jobs, int n_jobs, int *job_index);
Job *deadline_monotonic(Job **jobs, int n_jobs);
Job *earliest_deadline_first(Job **jobs, int n_jobs);
bool check_for_missed_jobs(Job **jobs, int n_jobs, int time);

void schedule_tasks(enum Scheduling sch, TaskSet *taskset);

#endif // SCHEDULERS_H
