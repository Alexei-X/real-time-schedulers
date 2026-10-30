#ifndef TASK_H
#define TASK_H

#include "Job.h"

#define MAX_TASKS 20

typedef struct Task {
    int id;
    int offset;
    int wcet;
    int deadline;
    int period;
} Task;

typedef struct TaskSet {
    int n_tasks;
    Task **tasks;
} TaskSet;

TaskSet *create_taskset(char *task_file);
Task *create_task(int id, int offset, int wcet, int deadline, int period);
Job *release_job(Task *task, int arrival_time);
void print_task(Task *task);

#endif // TASK_H
