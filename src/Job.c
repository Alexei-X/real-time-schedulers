#include "Job.h"
#include <stdio.h>

bool is_deadline_missed(Job *job, int time) {
    return (time > job->abs_deadline);
}

bool schedule(Job *job, int time) {
    job->exec_time += time;
    return (job->exec_time >= job->duration);
}

void print_job(Job *job) {
    printf("Job : \n");
    printf(" duration : %d | ", job->duration);
    printf(" release time : %d | ", job->release_time);
    printf(" absolute deadline : %d | ", job->abs_deadline);
    printf(" execution time : %d | ", job->exec_time);
    printf(" period : %d\n", job->period);
}

