#ifndef SCHEDULERS_H
#define SCHEDULERS_H

#include "Task.h"
#include <stdlib.h>

enum Scheduling {
    RM,
    DM,
    EDF
};

Job *rate_monotonic(Job **jobs, int n_jobs);
Job *deadline_monotonic();
Job *earliest_deadline_first(Job **jobs, int n_jobs);

void schedule_tasks(enum Scheduling sch, Task **taskset, int n_tasks, int t_max);

#endif // SCHEDULERS_H
