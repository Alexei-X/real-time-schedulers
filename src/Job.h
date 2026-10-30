#ifndef JOB_H
#define JOB_H

#include <stdbool.h>

typedef struct Job {
    int release_time;
    int abs_deadline;
    int duration;
    int exec_time;
    int period;
} Job;

bool is_deadline_missed(Job *job, int time);
bool schedule(Job *job, int time);
void print_job(Job *job);

#endif // JOB_H
